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
	// 乌龟壳个数+1
	s_TortoiseShellCount++;
	// 初始化基础参数
	this->m_tortoiseShellName = s_TortoiseShellCount;
	this->m_TortoiseShell_len = 0;
	this->m_TortoiseShell_WT = 0;
	this->m_TortoiseShellflow10_WT = 0;
	this->m_TortoiseShell_DHCR = 0;
	this->m_TortoiseShell_len1 = 0;
	this->m_TortoiseShell_WT1 = 0;
	this->m_TortoiseShellflow10_WT1 = 0;
	this->m_TortoiseShell_DHCR1 = 0;
	this->m_TortoiseShell_len_temp = 0;
	this->m_tang_len = 0;
	this->m_startTime = 0;
	this->m_finishTime = 0;
	this->m_timeSpan = 0;
	// 排程过程中记录的变量
	steelCoilNum = 0;
	steelCoilLenth = 0;
	high_num = 0;
	high_temp_coil_num = 0;
	low_temp_coil_num = 0;
	coil_flag = 0;
	if (group->high_temp_flag == "1")
	{
		high_num = 1;
		coil_flag = 1;
		high_temp_coil_num += group->m_SteelCoil.size();
	}
	else
		low_temp_coil_num += group->m_SteelCoil.size();
	// 初始化乌龟壳内的钢卷组
	m_main_groups.insert(make_pair(make_pair(0, group->roll_len), group));
	steelCoilNum = group->m_SteelCoil.size();
	steelCoilLenth = group->roll_len;
	
	// 初始化乌龟壳内的钢卷组
	//m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, 1), group));
	//// 待放钢卷的计划类型
	//string	plan_type = group->plan_type;
	//// 预留烫辊材(生成一个乌龟壳就放烫辊材)
	//vector<Group*> tang_temp;
	//// 上一个烫辊材的宽度
	//double width = 0;
	//// 总共预留烫辊材的个数
	//int num = 0;
	//for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	//{
	//	// 准备放入的钢卷组及其计划类型
	//	Group* group2 = iter->second;
	//	string	plan_type2 = group2->plan_type;
	//	// 如果烫辊材计划类型与初始化乌龟壳的钢卷计划类型不互斥且能相邻组合，则放入烫辊材
	//	map<pair<string, string>, string>::iterator iter2 = plantype.find(make_pair(plan_type, plan_type2));
	//	string type = iter2->second;
	//	if (type != "2" && type != "0"&& group2->nom_roll_width >= width)
	//	{
	//		width = group2->nom_roll_width;			
	//			 // 如果该钢卷组内钢卷个数大于4，则只拿出4块做烫辊材，否则全部做烫辊材
	//			if (group2->m_SteelCoil.size() > 4)
	//			{
	//				int needCount = 4;
	//				// 最多总共需要6块烫辊材
	//				if (6 - num < needCount)
	//					needCount = 6 - num;
	//				// 已预留烫辊材数量更新
	//				num += needCount;
	//				// 建立新的小钢卷组
	//				Group *group_temp = new Group(group2, needCount);
	//				tang_temp.push_back(group_temp);
	//			}
	//			else
	//			{
	//				int needCount = group2->m_SteelCoil.size();
	//				// 最多总共需要6块烫辊材
	//				if (6 - num < needCount)
	//					needCount = 6 - num;
	//				// 已预留烫辊材数量更新
	//				num += needCount;
	//				// 建立新的小钢卷组
	//				Group *group_temp = new Group(group2, needCount);
	//				tang_temp.push_back(group_temp);
	//			}
	//	}
	//	if (num >= 6)
	//		break;
	//}
	//// 将预留烫辊材分配到这个乌龟壳的前端
	//for (int i = 0; i < tang_temp.size(); i++)
	//{
	//	if (m_groups.empty())
	//		m_groups.insert(make_pair(make_pair(0, tang_temp[i]->roll_len), tang_temp[i]));
	//	else
	//		m_groups.insert(make_pair(make_pair(m_groups.rbegin()->first.second, m_groups.rbegin()->first.second + tang_temp[i]->roll_len), tang_temp[i]));
	//}
	//// 更新乌龟壳实时长度
	//for (int i = 0; i < tang_temp.size(); i++)
	//{
	//	m_tang_len += tang_temp[i]->roll_len;
	//}
	//m_TortoiseShell_len_temp = m_tang_len + group->roll_len;

}
TortoiseShell::~TortoiseShell()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion


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
			temp = make_pair(rs.Get<ostring>(13), rs.Get<ostring>(14));
			plantype.insert(make_pair(temp, rs.Get<ostring>(15)));
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
		string plan_type = group->plan_type;
		// 遍历已有乌龟壳
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// 这个乌龟壳
			TortoiseShell* tortoiseShell = iter2->second;
			// 这个乌龟壳里的第一个钢卷组及其计划类型
			Group* group2 = tortoiseShell->m_main_groups.begin()->second;
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
	const double samewidth_limit = 500000.0;			// 同宽公里数限制
	const double max_TortoiseShell_len = 50000;		// 乌龟壳最大公里是（假设）
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
			// 检查该钢卷如果放入，有没有相邻冲突，如果有，则不能放入该乌龟壳
			//Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group));
			// iter_now指向刚放入，待比较的钢卷组
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
				// 如果有一项约束不满足，则删除此钢卷组，继续用此钢卷组遍历下一个乌龟壳
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
			// 检查放入钢卷组是否满足高温卷段数，块数、低温卷块数和轧制位区间。



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
				// 放入乌龟壳
				bool mark = tortoiseShell->addMainGroup(group);
				// 如果分配成功，跳出乌龟壳遍历，回到准备放入的钢卷组的遍历
				if (mark)
					break;
				else continue;
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
			// 检查该钢卷如果放入，有没有相邻冲突，如果有，则不能放入该乌龟壳
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
				// 放入乌龟壳
				bool mark = tortoiseShell->addMainGroup(group);
				// 如果分配成功，跳出乌龟壳遍历，回到准备放入的钢卷组的遍历
				if (mark)
					break;
				else continue;
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

	//#pragma region 乌龟壳计算
	////////////////////////////////////////////////////////////////////////////
	//// 遍历已经生成的乌龟壳计算每个乌龟壳所有钢卷总重量、某流向钢卷总重量、有DHCR标记的钢卷总数、乌龟壳总长度
	//for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	//{
	//	TortoiseShell *tortoiseShell = iter->second;
	//	// 遍历乌龟壳内的钢卷组信息
	//	for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
	//	{
	//		Group *group = iter2->second;
	//		// 遍历钢卷组内钢卷信息
	//		for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
	//		{
	//			SteelCoil *steelCoil = *iter3;
	//			tortoiseShell->m_TortoiseShell_len += steelCoil->roll_len;
	//			tortoiseShell->m_TortoiseShell_WT += steelCoil->slab_wt;
	//			if (steelCoil->flow == "10")
	//				tortoiseShell->m_TortoiseShellflow10_WT += steelCoil->slab_wt;
	//			if (steelCoil->nom_hot_send_flag == "1")
	//				tortoiseShell->m_TortoiseShell_DHCR++;
	//		}
	//	}

	//}
	//// 计算所有乌龟壳所有钢卷总重量、某流向钢卷总重量、有DHCR标记的钢卷总数、乌龟壳总长度
	//for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	//{
	//	allTortoiseShell_len += (*iter).second->m_TortoiseShell_len;
	//	allsteelcCoil_wt += (*iter).second->m_TortoiseShell_WT;
	//	allflow10_wt += (*iter).second->m_TortoiseShellflow10_WT;
	//	m_DHCR += (*iter).second->m_TortoiseShell_DHCR;		
	//}
	////////////////////////////////////////////////////////////////////////////
	//#pragma endregion
}

//void TortoiseShell::DeleteBad()
//{
////#pragma region 遍历已经生成的乌龟壳计算每个乌龟壳的长度
//////////////////////////////////////////////////////////////////////////////
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		// 遍历乌龟壳内的钢卷组信息
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
//		{
//			Group *group = iter2->second;
//			// 遍历钢卷组内钢卷信息
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
//			{
//				SteelCoil *steelCoil = *iter3;
//				tortoiseShell->m_TortoiseShell_len += steelCoil->roll_len;
//			}
//		}
//
//	}
//////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//
//#pragma region 遍历已经生成的乌龟壳，将不满足高温段块数范围、低温段块数范围的钢卷重新放入未分配钢卷组中。
////////////////////////////////////////////////////////////////////////////
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		int high_num = 0;// 高温卷段数
//		int high_temp_coil_num = 0;// 这段高温卷的钢卷数
//		int low_temp_coil_num = 0;// 这段低温卷的钢卷数
//		int coil_flag = 0;// 0为低温卷，1为高温卷
//		// 遍历乌龟壳内的钢卷组信息
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
//		{
//			Group *group = iter2->second;
//			// 遍历钢卷组内钢卷信息
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); )
//			{
//				SteelCoil *steelCoil = *iter3;
//				// 如果上一个是低温卷
//				if (coil_flag == 0)
//				{
//					// 如果当前是低温卷
//					if (steelCoil->high_temp_flag == "0")
//					{
//						low_temp_coil_num++;
//						if (low_temp_coil_num > steelCoil->max_low_temp_coil_num)
//						{
//							low_temp_coil_num--;
//							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//							iter3 = group->m_SteelCoil.erase(iter3);
//							continue;
//						}
//						iter3++;
//					}
//					// 如果当前是高温卷
//					else
//					{
//						high_num++;
//						if (high_num > 3)
//						{
//							high_num--;
//							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//							iter3 = group->m_SteelCoil.erase(iter3);
//							continue;
//						}
//						low_temp_coil_num = 0;
//						high_temp_coil_num++;
//						coil_flag = 1;
//						iter3++;
//					}
//				}
//				// 如果上一个是高温卷
//				else
//				{
//					// 如果当前是低温卷
//					if (steelCoil->high_temp_flag == "0")
//					{
//						high_temp_coil_num = 0;
//						low_temp_coil_num++;
//						coil_flag = 0;
//						iter3++;
//					}
//					// 如果当前是高温卷
//					else
//					{
//						high_temp_coil_num++;
//						if (high_temp_coil_num > steelCoil->max_high_temp_coil_num)
//						{
//							high_temp_coil_num--;
//							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//							iter3 = group->m_SteelCoil.erase(iter3);
//							continue;
//						}
//						iter3++;
//					}
//				}
//			}
//		}
//	}
////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//
//#pragma region 遍历已经生成的乌龟壳，将不满足轧制位区间范围的钢卷重新放入未分配钢卷组中。
//	//////////////////////////////////////////////////////////////////////////
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		int lonth = 0;				// 钢卷累计位置
//		double del_lonth = 0;		// 删除的钢卷长度	
//		// 遍历乌龟壳内的钢卷组信息
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end();)
//		{
//			Group *group = iter2->second;
//			// 遍历钢卷组内钢卷信息
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end();)
//			{
//				SteelCoil *steelCoil = *iter3;
//				if (lonth > steelCoil->zone_min_m)
//				{
//					tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//					SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//					iter3 = group->m_SteelCoil.erase(iter3);
//					group->roll_len -= steelCoil->roll_len;
//					del_lonth += steelCoil->roll_len;
//				}
//				else
//				{
//					lonth += steelCoil->roll_len;
//					iter3++;
//				}
//			}
//		}
//	}
//			//// 如果删除了钢卷，则更新钢卷组的键值（具体位置）
//	//		if (del_lonth != 0)
//	//		{
//	//			if (iter2 != tortoiseShell->m_groups.begin())
//	//			{
//	//				map<pair<int, int>, Group*> temp;
//	//				temp.insert(make_pair(make_pair((iter2--)->first.second, iter2->first.second - del_lonth), group));
//	//				iter2=tortoiseShell->m_groups.erase(iter2);
//	//				map<pair<int, int>, Group*>::iterator iter4 = temp.begin();
//	//				tortoiseShell->m_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
//	//				temp.clear();
//	//			}
//	//			else
//	//			{
//	//				map<pair<int, int>, Group*> temp;
//	//				temp.insert(make_pair(make_pair(iter2->first.first, iter2->first.second - del_lonth), group));
//	//				iter2 = tortoiseShell->m_groups.erase(iter2);
//	//				map<pair<int, int>, Group*>::iterator iter4 = temp.begin();
//	//				tortoiseShell->m_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
//	//				temp.clear();
//	//			}
//
//	//		}
//	//		// 如果没删除钢卷，也要根据上一个钢卷组的键更改此钢卷组的键
//	//		else if (iter2 != tortoiseShell->m_groups.begin())
//	//		{
//	//			map<pair<int, int>, Group*> temp;
//	//			temp.insert(make_pair(make_pair((iter2--)->first.second, (iter2--)->first.second + group->roll_len), group));
//	//			iter2 = tortoiseShell->m_groups.erase(iter2);
//	//			map<pair<int, int>, Group*>::iterator iter4 = temp.begin();
//	//			tortoiseShell->m_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
//	//			temp.clear();
//	//		}
//	//		else
//	//			continue;
//		
//	
////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//
////#pragma region 遍历已经生成的乌龟壳，如果长度太短，则删除整个乌龟壳
////	//////////////////////////////////////////////////////////////////////////
//	
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); )
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		if (tortoiseShell->m_TortoiseShell_len > 5000)
//		{
//			iter++;
//			continue;
//		}
//		// 遍历乌龟壳内的钢卷组信息
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end();)
//		{
//			Group *group = iter2->second;
//			// 遍历钢卷组内钢卷信息
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end();)
//			{
//				SteelCoil *steelCoil = *iter3;
//				SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//				iter3 = group->m_SteelCoil.erase(iter3);
//			}
//			iter2 = tortoiseShell->m_groups.erase(iter2);
//		}
//		iter = s_mapSetOfTortoiseShell.erase(iter);
//		s_TortoiseShellCount--;
//	}
//////////////////////////////////////////////////////////////////////////////
////#pragma endregion
////}
//
////void TortoiseShell::ReFinishShell()
////{
////#pragma region 遍历未分配的钢卷
////	//////////////////////////////////////////////////////////////////////////
////	for (map<string, SteelCoil*>::iterator iter = SteelCoil::s_least.begin(); iter != SteelCoil::s_least.end(); iter++)
////	{
////		SteelCoil *steelCoil = iter->second;
////		// 遍历已经生成的乌龟壳
////		for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
////		{
////			TortoiseShell *tortoiseShell = iter2->second;
////			// 遍历乌龟壳内的钢卷组信息
////			for (map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups.begin(); iter3 != (--tortoiseShell->m_groups.end()); iter3++)
////			{
////				Group *group1 = iter3->second;
////				iter3++;
////				Group *group2 = iter3->second;
////				iter3--;
////				// 如果要分配的钢卷宽度小于等于group1的钢卷且大于group2的钢卷
////				// 尝试根据同宽范围、正跳反跳范围、高温段块数范围、低温段块数范围、轧制位区间范围是否满足来判断该钢卷可否被分配到这个位置(各个逻辑在上面的代码里均写过)
////				// 如果可以，分配(同时两层break)，如果不可以，查找下一个乌龟壳(break)。
////			}
////		}
////	}
////	//////////////////////////////////////////////////////////////////////////
////#pragma endregion
//}

void TortoiseShell::computekpi()
{
	const double max_TortoiseShell_len = 50000;// 乌龟壳最大公里数
	double flow10_wt = 0;
	double assigned_wt = 0;
	double assigned_DHCR = 0;
	double flow_rate=0;
	double DHCR_rate=0;
	double order_rate=0;
	double rollingkm_rate=0;
	double rollingkm=0;
	
	// 计算排好乌龟壳的所有钢卷总重量、某流向钢卷总重量、有DHCR标记的钢卷总数、乌龟壳总长度
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
				tortoiseShell->m_TortoiseShell_len1 += steelCoil->roll_len;
				tortoiseShell->m_TortoiseShell_WT1 += steelCoil->slab_wt;
				if (steelCoil->flow == "10")
					tortoiseShell->m_TortoiseShellflow10_WT1 += steelCoil->slab_wt;
				if (steelCoil->nom_hot_send_flag == "1")
					tortoiseShell->m_TortoiseShell_DHCR1++;
			}
		}

	}
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		rollingkm += tortoiseShell->m_TortoiseShell_len1;
		assigned_wt += tortoiseShell->m_TortoiseShell_WT1;
		flow10_wt += tortoiseShell->m_TortoiseShellflow10_WT1;
		assigned_DHCR += tortoiseShell->m_TortoiseShell_DHCR1;
	}	
	flow_rate = flow10_wt / allflow10_wt;																// 流向匹配率
	order_rate = assigned_wt / allsteelcCoil_wt;														// 合同计划兑现率
	rollingkm_rate = (rollingkm / s_mapSetOfTortoiseShell.size()) / max_TortoiseShell_len;				// 轧制公里率
	DHCR_rate = assigned_DHCR / m_DHCR;																	// DHCR比率
	cout << flow_rate << "   " << order_rate << "    " << rollingkm_rate << "   " << DHCR_rate << endl;

}

void TortoiseShell::showResult()
{
	int i = 0;
	cout << "乌龟壳总数：  " << s_TortoiseShellCount << endl;
	// 输出此时乌龟壳的编号、在乌龟壳里的钢卷组编号和钢卷组里钢卷的钢卷号
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_groups.begin(); iter3 != (*iter2).second->m_groups.end(); iter3++)
		{
			for (vector<SteelCoil*>::iterator iter4 = (*iter3).second->m_SteelCoil.begin(); iter4 != (*iter3).second->m_SteelCoil.end(); iter4++)
			{
				
				i++;
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

bool TortoiseShell::addMainGroup(Group *group)
{
	// 主体材硬约束
	int MAX_NUM = 999;				// 最大块数
	int MAX_KM = 2147483647;			// 最大公里数
	int ROLL_WIDTH_MINUS = 100;		// 轧制宽度差
	//int	HARD_GROUP_MINUS = 100;		// 硬度组差
	int	SAME_WIDTH_NUM = 100;			// 同宽块数
	int SAME_WIDTH_KM = 500000;		// 同宽轧制公里数
	double SAME_WIDTH = 0;				// 同宽定义范围

	// 如果乌龟壳已达到最大块数||已达到最大公里数||超过最大宽度差，则无法分配，返回false
	if (steelCoilNum > MAX_NUM || steelCoilLenth > MAX_KM || m_main_groups.rbegin()->second->nom_roll_width - group->nom_roll_width >= ROLL_WIDTH_MINUS)
		return false;

	// 能放入的钢卷个数
	int canSaveNum = group->m_SteelCoil.size();

	// 计算同宽块数与公里数
	int sameWidthNum = 0;
	int sameWidthKm = 0;
	// 反向迭代器遍历该钢卷组内的主体材部分
	for (map<pair<int, int>, Group*>::reverse_iterator iter = m_main_groups.rbegin(); iter != m_main_groups.rend(); iter++)
	{
		Group* group2 = iter->second;
		// 如果轧制宽度差小于同宽定义范围，则认为是同宽
		if (group2->nom_roll_width - group->nom_roll_width <= SAME_WIDTH + 0.01)
		{
			// 更新同宽块数与公里数
			sameWidthNum += group2->m_SteelCoil.size();
			sameWidthKm += group2->roll_len;
		}
		else
			break;
	}
	// 如果可以放入块数大于同宽剩余可放块数，则更新可放入块数
	if (canSaveNum > SAME_WIDTH_NUM - sameWidthNum)
		canSaveNum = SAME_WIDTH_NUM - sameWidthNum;
	int partWidthKm = 0;// 记录要放入的同宽公里数
	// 遍历即将放入的钢卷组
	for (int i = 0; i < group->m_SteelCoil.size(); i++)
	{
		// 更新要放入的同宽公里数
		partWidthKm += (*group->m_SteelCoil[i]).nom_roll_width;
		// 如果要放入的同宽公里数大于剩余可放，则更新能放入的块数
		if (partWidthKm > SAME_WIDTH_KM - sameWidthKm)
		{
			if (canSaveNum > i)
				canSaveNum = i;
			break;
		}
	}

	// 根据高温卷低温卷约束参数计算最大放入块数
	if (coil_flag == 0)// 如果上一个是低温卷
	{
		//如果当前是低温卷
		if (group->high_temp_flag == "0")
		{
			// 更新能放入的块数
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_low_temp_coil_num - low_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_low_temp_coil_num - low_temp_coil_num;
			}
		}
		// 如果当前是高温卷
		else
		{
			// 如果已有3段高温卷，则不可放
			if (high_num == 3)
				return false;
			// 更新能放入的块数
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_high_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_high_temp_coil_num;
			}
		}
	}
	else// 如果上一个是高温卷
	{
		//如果当前是低温卷
		if (group->high_temp_flag == "0")
		{
			// 更新能放入的块数
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_low_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_low_temp_coil_num;
			}
		}
		// 如果当前是高温卷
		else
		{
			// 更新能放入的块数
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_high_temp_coil_num - high_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_high_temp_coil_num - high_temp_coil_num;
			}
		}
	}

	// 根据轧制位区间约束计算最大放入块数
	int partZoneNum = steelCoilNum;// 记录要放入的轧制位区间公里数
	int partZoneKm = steelCoilLenth;// 记录要放入的轧制位区间公里数
	// 遍历即将放入的钢卷组
	for (int i = 0; i < group->m_SteelCoil.size(); i++)
	{
		// 如果要放入的钢卷大于轧制位区间约束，则不可放入
		if (partZoneKm >(*group->m_SteelCoil[i]).zone_min_m || partZoneNum > (*group->m_SteelCoil[i]).zone_min_num)
		{
			if (canSaveNum > i)
				canSaveNum = i;
			break;
		}
		// 更新要放入的同宽公里数
		partZoneNum++;
		partZoneKm += (*group->m_SteelCoil[i]).nom_roll_width;
	}

	// 如果可放入钢卷数为0，则不可放入
	if (canSaveNum == 0)
		return false;

	// 如果可放入的钢卷数小于钢卷组内的钢卷数，则分割成小钢卷组
	Group *group_new = NULL;
	if (canSaveNum < group->m_SteelCoil.size())
	{
		// 创建小钢卷组
		group_new = new Group(group, canSaveNum);
	}

	// 否则，直接将整个钢卷组加入到乌龟壳中
	else
	{
		// 创建小刚卷组
		group_new = new Group(group, (int)group->m_SteelCoil.size());
	}
	// 将小钢卷组插入到当前乌龟壳的临时钢卷组变量中
	m_main_groups.insert(make_pair(make_pair(steelCoilLenth, steelCoilLenth + group_new->roll_len), group_new));
	// 更新乌龟壳实时长度
	steelCoilNum += canSaveNum;
	steelCoilLenth += group_new->roll_len;
	if (coil_flag == 0)// 如果上一个是低温卷
	{
		//如果当前是低温卷
		if (group->high_temp_flag == "0")
		{
			low_temp_coil_num += canSaveNum;
		}
		// 如果当前是高温卷
		else
		{
			high_num++;
			coil_flag = 1;
			low_temp_coil_num = 0;
			high_temp_coil_num = canSaveNum;
		}
	}
	else// 如果上一个是高温卷
	{
		//如果当前是低温卷
		if (group->high_temp_flag == "0")
		{
			coil_flag = 0;
			low_temp_coil_num = canSaveNum;
			high_temp_coil_num = 0;
		}
		// 如果当前是高温卷
		else
		{
			high_temp_coil_num += canSaveNum;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group静态变量
//////////////////////////////////////////////////////////////////////////
map<int, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<int, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
double						TortoiseShell::allTortoiseShell_len = 0;
double						TortoiseShell::m_DHCR = 0;
double						TortoiseShell::allflow10_wt = 0;
double						TortoiseShell::allsteelcCoil_wt = 0;
map<pair<string, string>, string>		TortoiseShell::plantype = map<pair<string, string>, string>();
////////////////////////////////////////////////////////////////////////
#pragma endregion