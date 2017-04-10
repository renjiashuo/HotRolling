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

TortoiseShell::TortoiseShell(Group *group)
{
	// 初始化基础参数
	this->m_tortoiseShellName = s_mapSetOfTortoiseShell.size() + 1;
	this->m_TortoiseShell_len = 0;
	this->m_startTime = 0;
	this->m_finishTime = 0;
	this->m_timeSpan = 0;
	//this->nom_roll_width = 0;
	// 初始化乌龟壳内的板坯组
	//m_groups.insert(make_pair(make_pair(100000.0, 100000.0 + group->roll_len), group));
	m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, 1), group));
	// 待放钢卷的计划类型
	int	plan_type = group->plan_type;
	// 预留烫辊材
	vector<Group*> tang_temp;
	// 上一个烫辊材的宽度
	double width = 0;
	// 总共预留烫辊材的个数
	int num = 0;
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	{
		// 准备放入的钢卷组及其计划类型
		Group* group2 = iter->second;
		int	plan_type2 = group2->plan_type;
		// 如果烫辊材计划类型与初始化乌龟壳的钢卷计划类型一样，则放入烫辊材
		if (plan_type == plan_type2 && group2->nom_roll_width != width)
		{
			width = group2->nom_roll_width;
			// 如果该钢卷组内钢卷个数大于3，则只拿出3块做烫辊材，否则全部做烫辊材
			if (group2->m_SteelCoil.size() > 3)
			{
				int needCount = 3;
				// 最多总共需要6块烫辊材
				if (6 - num < needCount)
					needCount = 6 - num;
				// 已预留烫辊材数量更新
				num += needCount;
				// 建立新的小钢卷组
				Group *group_temp = new Group(group2, needCount);
				tang_temp.push_back(group_temp);
			}
			else
			{
				int needCount = group2->m_SteelCoil.size();
				// 最多总共需要6块烫辊材
				if (6 - num < needCount)
					needCount = 6 - num;
				// 已预留烫辊材数量更新
				num += needCount;
				// 建立新的小钢卷组
				Group *group_temp = new Group(group2, needCount);
				tang_temp.push_back(group_temp);
			}
		}
		if (num >= 6)
			break;
	}
	// 将预留烫辊材分配到这个乌龟壳的前端
	for (int i = 0; i < tang_temp.size(); i++)
	{
		if (m_groups.empty())
			m_groups.insert(make_pair(make_pair(0, tang_temp[i]->roll_len), tang_temp[i]));
		else
			m_groups.insert(make_pair(make_pair(m_groups.rbegin()->first.second, m_groups.rbegin()->first.second + tang_temp[i]->roll_len), tang_temp[i]));
	}
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
	const double tangwidth_limit = 100000.0;//同宽公里数限制
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
			Group* group2 = tortoiseShell->m_groups_temp.begin()->second;
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
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				//tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				//tortoiseShell->same_width_lonth = group_new->roll_len;
			}
			// 否则，直接将整个钢卷组加入到乌龟壳中
			else
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				//tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				//tortoiseShell->same_width_lonth = group_new->roll_len;
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

	#pragma region 遍历有DHCR标记和无烫辊材标记的钢卷组的map集合
	//////////////////////////////////////////////////////////////////////////
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// 准备放入的钢卷组及其计划类型
		Group* group = iter->second;
		int	plan_type = group->plan_type;
		// 如果大钢卷组为空，即全部放入小钢卷组，则删除之
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
			continue;
		}
		// 遍历已有乌龟壳
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// 这个乌龟壳
			TortoiseShell* tortoiseShell = iter2->second;
			// 检查同宽公里数是否满足，若不满足，则这个乌龟壳不能放这个钢卷组
			if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end() && tortoiseShell->width_lonth.find(group->nom_roll_width)->second >= samewidth_limit)
				continue;
			// 遍历这个乌龟壳里的钢卷组
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups_temp.begin();
			for (; iter3 != tortoiseShell->m_groups_temp.end(); iter3++)
			{
				// 乌龟壳里的钢卷组的宽度
				int width = iter3->first.first;
				Group *group2 = iter3->second;
				// 这个钢卷组的计划类型
				int	plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == 2)
					break;
			}
			// 如果1）顺利的查找到了这个乌龟壳里的最后一个钢卷组也没触发break，则说明准备放入的钢卷组可以放入本乌龟壳中，那么放入吧
			if (iter3 == tortoiseShell->m_groups_temp.end())
			{
				// 计算这个宽度的钢卷组在这个乌龟壳中的已有总长度（不算即将加入的这个钢卷组）
				double lonth = 0;
				if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end())
					lonth = tortoiseShell->width_lonth.find(group->nom_roll_width)->second;
				// 如果钢卷组内的公里数大于最大同宽公里数限制，则分割成小钢卷组
				if (group->roll_len >= samewidth_limit - lonth)
				{
					// 创建小钢卷组
					Group *group_new = new Group(group, samewidth_limit - lonth);
					// 将小钢卷组插入到当前乌龟壳的临时钢卷组变量中
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// 更新乌龟壳中钢卷组的同宽公里数
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				}
				// 否则，直接将整个钢卷组加入到乌龟壳中
				else
				{
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					// 将小钢卷组插入到当前乌龟壳的末尾
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// 更新乌龟壳中钢卷组的同宽公里数
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
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
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
			// 否则，直接将整个钢卷组加入到乌龟壳中
			else
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
		}
		// 如果大钢卷组为空，即全部放入小钢卷组，则删除之
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region 遍历有烫辊材标记的钢卷组的map集合
	//////////////////////////////////////////////////////////////////////////
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end();)
	{
		// 准备放入的钢卷组及其计划类型
		Group* group = iter->second;
		int	plan_type = group->plan_type;
		// 如果大钢卷组为空，即全部放入小钢卷组，则删除之
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup1.erase(iter);
			continue;
		}
		// 遍历已有乌龟壳
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// 这个乌龟壳
			TortoiseShell* tortoiseShell = iter2->second;
			// 检查同宽公里数是否满足，若不满足，则这个乌龟壳不能放这个钢卷组
			if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end() && tortoiseShell->width_lonth.find(group->nom_roll_width)->second >= samewidth_limit)
				continue;
			// 遍历这个乌龟壳里的钢卷组
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups_temp.begin();
			for (; iter3 != tortoiseShell->m_groups_temp.end(); iter3++)
			{
				// 乌龟壳里的钢卷组的宽度
				int width = iter3->first.first;
				Group *group2 = iter3->second;
				// 这个钢卷组的计划类型
				int	plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == 2)
					break;
			}
			// 如果1）顺利的查找到了这个乌龟壳里的最后一个钢卷组也没触发break，则说明准备放入的钢卷组可以放入本乌龟壳中，那么放入吧
			if (iter3 == tortoiseShell->m_groups_temp.end())
			{
				// 计算这个宽度的钢卷组在这个乌龟壳中的已有总长度（不算即将加入的这个钢卷组）
				double lonth = 0;
				if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end())
					lonth = tortoiseShell->width_lonth.find(group->nom_roll_width)->second;
				// 如果钢卷组内的公里数大于最大同宽公里数限制，则分割成小钢卷组
				if (group->roll_len >= samewidth_limit - lonth)
				{
					// 创建小钢卷组
					Group *group_new = new Group(group, samewidth_limit - lonth);
					// 将小钢卷组插入到当前乌龟壳的临时钢卷组变量中
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// 更新乌龟壳中钢卷组的同宽公里数
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				}
				// 否则，直接将整个钢卷组加入到乌龟壳中
				else
				{
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					// 将小钢卷组插入到当前乌龟壳的末尾
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// 更新乌龟壳中钢卷组的同宽公里数
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
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
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
			// 否则，直接将整个钢卷组加入到乌龟壳中
			else
			{
				// 创建小钢卷组
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				// 创建乌龟壳
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// 更新乌龟壳的排程过程中记录变量（目前乌龟壳中最后一个钢卷组的额定轧制宽度、目前最后一个钢卷组宽度的同宽公里数）
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
		}
		// 如果大钢卷组为空，即全部放入小钢卷组，则删除之
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup1.erase(iter);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region 按照宽度分配位置
	//////////////////////////////////////////////////////////////////////////
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// 逆序遍历分配到乌龟壳中，但尚未分配具体位置的钢卷组
		for (map<pair<int, int>, Group*>::reverse_iterator iter2 = tortoiseShell->m_groups_temp.rbegin(); iter2 != tortoiseShell->m_groups_temp.rend(); iter2++)
		{
			Group *group = iter2->second;
			// 上一个钢卷组分配的末位置
			int end_located = tortoiseShell->m_groups.rbegin()->first.second;
			tortoiseShell->m_groups.insert(make_pair(make_pair(end_located, end_located + group->roll_len), group));
		}
		tortoiseShell->m_groups_temp.clear();
	}
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion
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