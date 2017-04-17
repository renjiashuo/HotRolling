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
	// 初始化乌龟壳内的钢卷组
	//m_groups.insert(make_pair(make_pair(100000.0, 100000.0 + group->roll_len), group));
	m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, 1), group));
	// 待放钢卷的计划类型
	string	plan_type = group->plan_type;
	// 预留烫辊材(生成一个乌龟壳就放烫辊材)
	vector<Group*> tang_temp;
	// 上一个烫辊材的宽度
	double width = 0;
	// 总共预留烫辊材的个数
	int num = 0;
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	{
		// 准备放入的钢卷组及其计划类型
		Group* group2 = iter->second;
		string	plan_type2 = group2->plan_type;
		// 如果烫辊材计划类型与初始化乌龟壳的钢卷计划类型不互斥且能相邻组合，则放入烫辊材
		map<pair<string, string>, string>::iterator iter2 = plantype.find(make_pair(plan_type, plan_type2));
		string type = iter2->second;
		if (type != "2" && type != "0"&& group2->nom_roll_width >= width)	
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
		Environment::Initialize();// 环境初始化
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");// 连接数据库（IP地址/服务名，“用户名”，“密码“）
		Statement st(con);// 创建数据集
		ostring rowid;
		st.Execute("select * from TIP00SI04");// 选择表
		Resultset rs = st.GetResultset();
		// 读取计划类型组合方式
		while (rs.Next())
		{
			pair<string, string> temp;
			temp = make_pair(rs.Get<string>(13), rs.Get<string>(14));
			plantype.insert(make_pair(temp, rs.Get<string>(15)));
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
		string	plan_type = group->plan_type;
		// 遍历已有乌龟壳
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// 这个乌龟壳
			TortoiseShell* tortoiseShell = iter2->second;
			// 这个乌龟壳里的第一个钢卷组及其计划类型
			Group* group2 = tortoiseShell->m_groups_temp.begin()->second;
			string	plan_type2 = group2->plan_type;
			// 如果是相同的组合方式，则不用查找了
			if (plan_type == plan_type2)
				break;
			// 查找这两个计划类型的组合方式
			map<pair<string, string>, string>::iterator iter3 = plantype.find(make_pair(plan_type, plan_type2));
			string type = iter3->second;
			// 如果组合方式不是"计划内不能种组合"，则此钢卷组可以和当前乌龟壳组合。
			if (type != "2")
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
				// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
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
				// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
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
		string	plan_type = group->plan_type;
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
			// 检查同宽公里数是否满足，若不满足，则这个乌龟壳不能放这个钢卷组，则遍历另一个乌龟壳
			if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end() && tortoiseShell->width_lonth.find(group->nom_roll_width)->second >= samewidth_limit)
				continue;
			// 检查该钢卷如果放入，有没有相邻冲突，如果有，则不能放入该乌龟壳
			//Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group));
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_groups_temp.find(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_groups_temp.begin() && 
				(plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == "0" 
				|| (*iter_now->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			if (iter_after != tortoiseShell->m_groups_temp.end() && 
				(plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second =="0"
				|| (*iter_after->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			tortoiseShell->m_groups_temp.erase(iter_now);
			// 检查这个乌龟壳里的烫辊材有没有和钢卷组冲突，如果有，则此乌龟壳不能放此钢卷组
			map<pair<int, int>, Group*>::iterator iter5 = tortoiseShell->m_groups.begin();
			for (; iter5 != tortoiseShell->m_groups.end(); iter5++)
			{
				// 乌龟壳里的钢卷组
				Group *group2 = iter5->second;
				// 这个钢卷组的计划类型
				string	plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == "2")
					break;
			}
			// 如果还没到这个乌龟壳里的最后一个钢卷组就触发了break，则说明有冲突，寻找下一个乌龟壳吧
			if (iter5 != tortoiseShell->m_groups.end())
				continue;
			// 遍历这个乌龟壳里的钢卷组(主体材)
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups_temp.begin();
			for (; iter3 != tortoiseShell->m_groups_temp.end(); iter3++)
			{
				// 乌龟壳里的钢卷组的宽度
				int width = iter3->first.first;
				Group *group2 = iter3->second;
				// 这个钢卷组的计划类型
				string	plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == "2")
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
					// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
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
					// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
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
				// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
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
				// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
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
		string	plan_type = group->plan_type;
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
			// 检查该钢卷如果放入，有没有相邻冲突，如果有，则不能放入该乌龟壳
			//Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group));
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_groups_temp.find(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_groups_temp.begin() &&
				(plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == "0"
				|| (*iter_now->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			if (iter_after != tortoiseShell->m_groups_temp.end() &&
				(plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second == "0"
				|| (*iter_after->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			tortoiseShell->m_groups_temp.erase(iter_now);
			// 检查这个乌龟壳里的烫辊材有没有和钢卷组冲突，如果有，则此乌龟壳不能放此钢卷组
			map<pair<int, int>, Group*>::iterator iter5 = tortoiseShell->m_groups.begin();
			for (; iter5 != tortoiseShell->m_groups.end(); iter5++)
			{
				// 乌龟壳里的钢卷组
				Group *group2 = iter5->second;
				// 这个钢卷组的计划类型
				string	plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == "2")
					break;
			}
			// 如果还没到这个乌龟壳里的最后一个钢卷组就触发了break，则说明有冲突，寻找下一个乌龟壳吧
			if (iter5 != tortoiseShell->m_groups.end())
				continue;
			// 遍历这个乌龟壳里的钢卷组
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups_temp.begin();
			for (; iter3 != tortoiseShell->m_groups_temp.end(); iter3++)
			{
				// 乌龟壳里的钢卷组的宽度
				int width = iter3->first.first;
				Group *group2 = iter3->second;
				// 这个钢卷组的计划类型
				string plan_type2 = group2->plan_type;
				// 查找这两个计划类型的组合方式
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// 如果计划内不能组合，则不用查找本乌龟壳了，继续下一个乌龟壳查找
				if (type == "2")
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
					// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
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
					// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
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
				// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
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
				// 如果是空空的小钢卷组，则说明一个钢卷太大放不了了，那么查找下一个乌龟壳
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
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
			int end_located = 0;
			if (!tortoiseShell->m_groups.empty())// 不为空 执行
				end_located = tortoiseShell->m_groups.rbegin()->first.second;
			tortoiseShell->m_groups.insert(make_pair(make_pair(end_located, end_located + group->roll_len), group));
		}
		tortoiseShell->m_groups_temp.clear();
	}
	//////////////////////////////////////////////////////////////////////////
#pragma endregion
}

void TortoiseShell::DeleteBad()
{
	// 遍历已经生成的乌龟壳计算每个乌龟壳的长度
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// 遍历钢卷组内钢卷信息
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			{
				SteelCoil *steelCoil = *iter3;
				tortoiseShell->m_TortoiseShell_len += steelCoil->roll_len;
			}
		}
	}
	// 遍历已经生成的乌龟壳，将不满足高温段块数范围、低温段块数范围、轧制位区间范围的钢卷重新放入未分配钢卷组中。
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		int high_num = 0;// 高温卷段数
		int high_temp_coil_num = 0;// 这段高温卷的钢卷数
		int low_temp_coil_num = 0;// 这段低温卷的钢卷数
		int coil_flag = 0;// 0为低温卷，1为高温卷
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// 遍历钢卷组内钢卷信息
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); )
			{
				SteelCoil *steelCoil = *iter3;
				// 如果上一个是低温卷
				if (coil_flag == 0)
				{
					// 如果当前是低温卷
					if (steelCoil->high_temp_flag == "0")
					{
						low_temp_coil_num++;
						if (low_temp_coil_num > steelCoil->max_low_temp_coil_num)
						{
							low_temp_coil_num--;
							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
							iter3 = group->m_SteelCoil.erase(iter3);
							continue;
						}
						iter3++;
					}
					// 如果当前是高温卷
					else
					{
						high_num++;
						if (high_num > 3)
						{
							high_num--;
							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
							iter3 = group->m_SteelCoil.erase(iter3);
							continue;
						}
						low_temp_coil_num = 0;
						high_temp_coil_num++;
						coil_flag = 1;
						iter3++;
					}
				}
				// 如果上一个是高温卷
				else
				{
					// 如果当前是低温卷
					if (steelCoil->high_temp_flag == "0")
					{
						high_temp_coil_num = 0;
						low_temp_coil_num++;
						coil_flag = 0;
						iter3++;
					}
					// 如果当前是高温卷
					else
					{
						high_temp_coil_num++;
						if (high_temp_coil_num > steelCoil->max_high_temp_coil_num)
						{
							high_temp_coil_num--;
							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
							iter3 = group->m_SteelCoil.erase(iter3);
							continue;
						}
						iter3++;
					}
				}
			}
		}
	}
	// 遍历已经生成的乌龟壳，如果长度太短，则删除整个乌龟壳
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); )
	{
		TortoiseShell *tortoiseShell = iter->second;
		if (tortoiseShell->m_TortoiseShell_len > 5000)
		{
			iter++;
			continue;
		}
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end();)
		{
			Group *group = iter2->second;
			// 遍历钢卷组内钢卷信息
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end();)
			{
				SteelCoil *steelCoil = *iter3;
				SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
				iter3 = group->m_SteelCoil.erase(iter3);
			}
			iter2 = tortoiseShell->m_groups.erase(iter2);
		}
		iter = s_mapSetOfTortoiseShell.erase(iter);
	}
}

void TortoiseShell::showResult()
{
	int i = 0;
	cout << "乌龟壳总数：  " << s_mapSetOfTortoiseShell.size() << endl;
	// 输出此时乌龟壳的编号、在乌龟壳里的钢卷组编号和钢卷组里钢卷的钢卷号
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_groups.begin(); iter3 != (*iter2).second->m_groups.end(); iter3++)
		{
			for (vector<SteelCoil*>::iterator iter4 = (*iter3).second->m_SteelCoil.begin(); iter4 != (*iter3).second->m_SteelCoil.end(); iter4++)
			{
				
				i++;;
				cout << iter2->first << "	" << iter3->second->group_no << "	" << (*iter4)->mat_no << "    "<<(*iter4)->nom_roll_width<<endl;
			}
		}
	}
	cout << "钢卷总数：   "<<i << endl;// 刚卷数
	cout << "小刚卷组总数：	" << Group::s_mapSetOfsmallGroup.size() << endl;
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

void TortoiseShell::showResultFile()
{
	string filename_result = "result.csv";
	ofstream fout(filename_result);
	fout << "钢卷号," << "流向," << "切断时间," << "必做标记," << "计划类型," << "额定轧制厚度," << "额定轧制宽度," << "额定出炉温度," << "额定终轧温度," << "额定卷取温度," << "计划号" << endl;
	// 遍历乌龟壳
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		// 乌龟壳
		TortoiseShell *tortoiseShell = iter->second;
		int tortoiseShellNo = iter->first;
		fout << tortoiseShellNo << endl;
		// 遍历乌龟壳内的钢卷组
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			// 钢卷组
			Group *group = iter2->second;
			// 遍历板坯组内的钢卷
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			{
				// 钢卷
				SteelCoil *steelCoil = *iter3;
				string	mat_no = steelCoil->mat_no;						// 钢卷号
				string	flow = steelCoil->flow;							// 流向
				string	fin_cut_time = steelCoil->fin_cut_time;				// 切断时间
				//bool		must_do_flag = steelCoil->must_do_flag;				// 必做标记
				bool		must_do_flag = 0;				// 必做标记
				string	plan_type = steelCoil->plan_type;					// 计划类型
				double	nom_roll_thick = steelCoil->nom_roll_thick;			// 额定轧制厚度
				double	nom_roll_width = steelCoil->nom_roll_width;			// 额定轧制宽度
				int		nom_heat_temp = steelCoil->nom_heat_temp;			// 额定出炉温度
				int		nom_afft_temp = steelCoil->nom_afft_temp;			// 额定终轧温度
				int		nom_coil_temp = steelCoil->nom_coil_temp;			// 额定卷取温度
				string	plan_no = steelCoil->plan_no;						// 计划号
				fout << mat_no << "," << flow << "," << fin_cut_time << "," << (int)must_do_flag << "," << plan_type << "," << nom_roll_thick << "," << nom_roll_width << "," << nom_heat_temp << "," << nom_afft_temp << "," << nom_coil_temp << "," << plan_no << endl;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group静态变量
//////////////////////////////////////////////////////////////////////////
map<int, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<int, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
map<pair<string, string>, string>		TortoiseShell::plantype = map<pair<string, string>, string>();
////////////////////////////////////////////////////////////////////////
#pragma endregion