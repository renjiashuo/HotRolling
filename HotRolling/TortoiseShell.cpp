/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 乌龟壳类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 乌龟壳类
/// <para>存储乌龟壳信息</para>
/// </summary>
===========================================================</remark>*/

#include "TortoiseShell.h"
#include "global.h"


#pragma region TortoiseShell成员函数
//////////////////////////////////////////////////////////////////////////

#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////

TortoiseShell::TortoiseShell(Group *groups)
{
	// 初始化基础参数
	this->m_tortoiseShellName = s_mapSetOfTortoiseShell.size() + 1;
	this->m_TortoiseShell_len = 0;
	this->m_startTime = 0;
	this->m_finishTime = 0;
	this->m_timeSpan = 0;
	this->nom_roll_width = 0;
	// 初始化乌龟壳内的板坯组
	m_groups.insert(make_pair(make_pair(100000.0, 100000.0 + groups->roll_len), groups));
}

TortoiseShell::~TortoiseShell()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region 乌龟壳计划相关
//////////////////////////////////////////////////////////////////////////

void TortoiseShell::InitShell()
{
	const double samewidth_limit = 500000.0;//同宽公里数限制
	try
	{
		Environment::Initialize();//环境初始化
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");//连接数据库（IP地址/服务名，“用户名”，“密码“）
		Statement st(con);//创建数据集
		ostring rowid;
		st.Execute("select * from TIP00SI04");//选择表
		Resultset rs = st.GetResultset();
		// 读取计划类型组合方式
		while (rs.Next())
		{
			pair<int, int> temp;
			temp = make_pair(rs.Get<int>(14), rs.Get<int>(15));
			plantype.insert(make_pair(temp, rs.Get<int>(16)));
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();
	#pragma region 创建初始乌龟壳
	//////////////////////////////////////////////////////////////////////////
	// 遍历有DHCR标记和无烫辊材标记的钢卷组的map集合
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// 一个钢卷组及其计划类型
		Group* group = iter->second;
		int	plan_type = group->plan_type;
		// 遍历已有乌龟壳
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// 这个乌龟壳
			TortoiseShell* tortoiseShell = iter2->second;
			// 这个乌龟壳里的第一个钢卷组及其计划类型
			Group* group2 = tortoiseShell->m_groups.begin()->second;
			int	plan_type2 = group2->plan_type;
			// 如果是相同的组合方式，则不用查找了
			if (plan_type == plan_type2)
				break;
			// 查找这两个计划类型的组合方式
			map<pair<int, int>, int>::iterator iter3 = plantype.find(make_pair(plan_type, plan_type2));
			int type = iter3->second;
			// 如果组合方式不是"计划内不能种组合"，则此钢卷组可以和当前乌龟壳组合。
			if (type != 2)
				break;
		}
		// 如果遍历了所有乌龟壳，发现都不能组合，那么添加一个新的乌龟壳，并且放入该钢卷组
		if (iter2 == s_mapSetOfTortoiseShell.end())
		{
			// 如果钢卷组内的公里数大于最大同宽公里数限制，则分割成小钢卷组
			if (group->roll_len >= samewidth_limit)
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, samewidth_limit);
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
			// 否则，直接将整个钢卷组加入到乌龟壳中
			else
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
		}
		// 如果大钢卷组为空，即全部放入小钢卷组，则删除之
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
		}
		// 如果大钢卷组不为空，则指向下一个
		else
			iter++;
	}
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion
}

void TortoiseShell::FinishShell()
{
	const double samewidth_limit = 500000.0;//同宽公里数限制
	// 遍历有DHCR标记和无烫辊材标记的钢卷组的map集合
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// 准备放入的钢卷组及其计划类型
		Group* group = iter->second;
		int	plan_type = group->plan_type;
		// 遍历已有乌龟壳
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// 这个乌龟壳
			TortoiseShell* tortoiseShell = iter2->second;
			// 遍历这个乌龟壳里的钢卷组
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups.begin();
			for (; iter3 != tortoiseShell->m_groups.end(); iter3++)
			{
				// 乌龟壳里的钢卷组的起止位置及钢卷组
				int begin_location = iter3->first.first;
				int end_location = iter3->first.second;
				Group *group2 = iter3->second;
				// 这个钢卷组的计划类型
				int	plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == 2)
					break;
				// 如果准备放入的钢卷组与目前乌龟壳中最后一个钢卷组不能相邻组合，同上
				if (iter3 == --(tortoiseShell->m_groups.end()) && type == 1)
					break;;
			}
			// 如果1）顺利的查找到了这个乌龟壳里的最后一个钢卷组也没触发break。2）同宽公里数满足。则说明准备放入的钢卷组可以放入本乌龟壳中，那么放入吧
			if (iter3 == tortoiseShell->m_groups.end() && 
				((group->nom_roll_width == tortoiseShell->nom_roll_width && tortoiseShell->same_width_lonth < samewidth_limit) ||
				(group->nom_roll_width != tortoiseShell->nom_roll_width)))
			{
				// 如果钢卷组内的公里数大于最大同宽公里数限制，则分割成小钢卷组
				if (group->roll_len >= samewidth_limit - tortoiseShell->nom_roll_width)
				{
					// 创建小钢卷组
					Group *group_new = new Group(group, samewidth_limit - tortoiseShell->nom_roll_width);
					Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
					// 将小钢卷组插入到当前乌龟壳的末尾
					int end_location = tortoiseShell->m_groups.rbegin()->first.second;
					tortoiseShell->m_groups.insert(make_pair(make_pair(end_location, end_location + group->roll_len), group_new));
					// 如果该钢卷组与乌龟壳中最后一个钢卷组不同宽
					if (group->nom_roll_width != tortoiseShell->nom_roll_width)
					{
						tortoiseShell->nom_roll_width = group_new->nom_roll_width;
						tortoiseShell->same_width_lonth = group_new->roll_len;
					}
					// 否则
					else
					{
						tortoiseShell->same_width_lonth += group_new->roll_len;
					}
				}
				// 否则，直接将整个钢卷组加入到乌龟壳中
				else
				{
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
					// 将小钢卷组插入到当前乌龟壳的末尾
					int end_location = tortoiseShell->m_groups.rbegin()->first.second;
					tortoiseShell->m_groups.insert(make_pair(make_pair(end_location, end_location + group->roll_len), group_new));
					// 如果该钢卷组与乌龟壳中最后一个钢卷组不同宽
					if (group->nom_roll_width != tortoiseShell->nom_roll_width)
					{
						tortoiseShell->nom_roll_width = group_new->nom_roll_width;
						tortoiseShell->same_width_lonth = group_new->roll_len;
					}
					// 否则
					else
					{
						tortoiseShell->same_width_lonth += group_new->roll_len;
					}
				}
				// 跳出乌龟壳遍历，回到准备放入的钢卷组的遍历
				break;
			}
		}
		// 如果遍历了所有乌龟壳，发现都不能组合，那么添加一个新的乌龟壳，并且放入该钢卷组
		if (iter2 == s_mapSetOfTortoiseShell.end())
		{
			// 如果钢卷组内的公里数大于最大同宽公里数限制，则分割成小钢卷组
			if (group->roll_len >= samewidth_limit)
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, samewidth_limit);
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
			// 否则，直接将整个钢卷组加入到乌龟壳中
			else
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
		}
		// 如果大钢卷组为空，即全部放入小钢卷组，则删除之
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
		}
	}
}

void TortoiseShell::showResult()
{
	// 输出此时乌龟壳的编号、在乌龟壳里的钢卷组编号和钢卷组里钢卷的钢卷号
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_groups.begin(); iter3 != (*iter2).second->m_groups.end(); iter3++)
		{
			for (vector<SteelCoil*>::iterator iter4 = (*iter3).second->m_SteelCoil.begin(); iter4 != (*iter3).second->m_SteelCoil.end(); iter4++)
			{
				cout << iter2->first << "	" << iter3->second->group_no << "	" << (*iter4)->mat_no << endl;
			}
		}
	}
	cout << endl << endl;
	// 每个钢卷组剩下的刚卷数
	cout << "每个钢卷组剩下的刚卷数： " << endl;
	for (map<int, Group*> ::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end(); iter++)
	{
		cout << iter->first << "       ";
		cout << iter->second->m_SteelCoil.size() << endl;
	}
	cout << endl;
	for (map<int, Group*> ::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	{
		cout << iter->first << "      ";
		cout << iter->second->m_SteelCoil.size() << endl;
	}
	cout << endl;
	cout << "s_mapSetOfGroup集合里还剩 " << Group::s_mapSetOfGroup.size() << " 个钢卷组" << endl;
	cout << endl;
	cout << "s_mapSetOfGroup1集合里还剩 " << Group::s_mapSetOfGroup1.size() << " 个钢卷组" << endl;
	cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group静态变量
//////////////////////////////////////////////////////////////////////////
map<int, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<int, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
map<pair<int, int>, int>		TortoiseShell::plantype = map<pair<int, int>, int>();
////////////////////////////////////////////////////////////////////////
#pragma endregion