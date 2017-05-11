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
#include "Group.h"
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
	//this->m_tang_len = 0;
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
}
TortoiseShell::TortoiseShell()
{
	
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
	#pragma region 遍历钢卷组的map集合
	//////////////////////////////////////////////////////////////////////////
	const double samewidth_limit = 500000.0;			// 同宽公里数限制
	const double max_TortoiseShell_len = 50000;		// 乌龟壳最大公里（假设）	
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
			//map<pair<int, int>, Group*>::reverse_iterator riter = tortoiseShell->m_main_groups.rbegin();
			tortoiseShell->m_main_groups.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_main_groups.size() + 1), group));
			// iter_now指向刚放入，待比较的钢卷组
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_main_groups.find(make_pair(group->nom_roll_width, tortoiseShell->m_main_groups.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_main_groups.begin() &&
				(plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == "0"
				|| (*iter_now->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				// 如果有一项约束不满足，则删除此钢卷组，继续用此钢卷组遍历下一个乌龟壳
				tortoiseShell->m_main_groups.erase(iter_now);
				continue;
			}
			 if (iter_after != tortoiseShell->m_main_groups.end() && 
				(plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second =="0"
				|| (*iter_after->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_main_groups.erase(iter_now);
				continue;
			}
			// 不管满不满足上面的条件，都将此钢卷组删掉，继续下面的判断
			tortoiseShell->m_main_groups.erase(iter_now);			
			// 遍历这个乌龟壳里的钢卷组(主体材)
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_main_groups.begin();
			for (; iter3 != tortoiseShell->m_main_groups.end(); iter3++)
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
			if (iter3 == tortoiseShell->m_main_groups.end())
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


	#pragma region 乌龟壳计算
	//////////////////////////////////////////////////////////////////////////
	// 遍历已经生成的乌龟壳计算每个乌龟壳所有钢卷总重量、某流向钢卷总重量、有DHCR标记的钢卷总数、乌龟壳总长度
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// 遍历钢卷组内钢卷信息
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			{
				SteelCoil *steelCoil = *iter3;
				tortoiseShell->m_TortoiseShell_len += steelCoil->roll_len;
				tortoiseShell->m_TortoiseShell_WT += steelCoil->slab_wt;
				if (steelCoil->flow == "10")
					tortoiseShell->m_TortoiseShellflow10_WT += steelCoil->slab_wt;
				if (steelCoil->nom_hot_send_flag == "1")
					tortoiseShell->m_TortoiseShell_DHCR++;
			}
		}

	}
	// 计算所有乌龟壳所有钢卷总重量、某流向钢卷总重量、有DHCR标记的钢卷总数、乌龟壳总长度
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		allTortoiseShell_len += (*iter).second->m_TortoiseShell_len;
		allsteelcCoil_wt += (*iter).second->m_TortoiseShell_WT;
		allflow10_wt += (*iter).second->m_TortoiseShellflow10_WT;
		m_DHCR += (*iter).second->m_TortoiseShell_DHCR;		
	}
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion
}

void TortoiseShell::DeleteBad()
{
	#pragma region 遍历已经生成的乌龟壳，如果长度太短，则删除整个乌龟壳
	//////////////////////////////////////////////////////////////////////////
	
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); )
	{
		TortoiseShell *tortoiseShell = iter->second;
		if (tortoiseShell->m_TortoiseShell_len > 5000)
		{
			iter++;
			continue;
		}
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end();)
		{
			Group *group = iter2->second;
			// 将删除的钢卷组放入map集合里
			Group::s_least.insert(make_pair(Group::s_least.size()+1, group));			
			iter2 = tortoiseShell->m_main_groups.erase(iter2);
		}		
		iter = s_mapSetOfTortoiseShell.erase(iter);		
		s_TortoiseShellCount--;
	}
	// 删除乌龟壳之后，更新乌龟壳代码
	map<int, TortoiseShell*> temp;
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		temp.insert(make_pair(temp.size() + 1, iter->second));
	}
	swap(s_mapSetOfTortoiseShell, temp);
	
	// 将初始解的kpi赋给最优kpi变量
	best_kpi = computekpi(s_mapSetOfTortoiseShell);	
	// 生成新的乌龟壳，将删除钢卷组放入
	TortoiseShell *tortoiseShell = new TortoiseShell();
	for (map<int, Group*>::iterator iter3 = Group::s_least.begin(); iter3 != Group::s_least.end(); iter3++)
	{
		Group *group = iter3->second;
		// 上一个钢卷组分配的末位置
		int end_located = 0;
		if (!tortoiseShell->m_main_groups.empty())// 不为空 执行
			end_located = tortoiseShell->m_main_groups.rbegin()->first.second;
		tortoiseShell->m_main_groups.insert(make_pair(make_pair(end_located, end_located + group->roll_len), group));
	}
	s_mapSetOfTortoiseShell.insert(make_pair(s_mapSetOfTortoiseShell.size()+1, tortoiseShell));
	// 检查乌龟壳里是否有空的钢卷组
	for (map<int, TortoiseShell*>::iterator iter11 = s_mapSetOfTortoiseShell.begin(); iter11 != s_mapSetOfTortoiseShell.end(); iter11++)
	{
		for (map<pair<int, int>, Group*>::iterator iter22 = (*iter11).second->m_main_groups.begin(); iter22 != (*iter11).second->m_main_groups.end(); iter22++)
		{
			if (iter22->second->m_SteelCoil.size() == 0)
				std::cout << "有钢卷组为空" << endl;
		}
	}
	////////////////////////////////////////////////////////////////////////////
	#pragma endregion
}

void TortoiseShell::showResult()
{
	int i = 0;
	cout << "乌龟壳总数：  " << s_TortoiseShellCount << endl;
	// 输出此时乌龟壳的编号、在乌龟壳里的钢卷组编号和钢卷组里钢卷的钢卷号
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_main_groups.begin(); iter3 != (*iter2).second->m_main_groups.end(); iter3++)
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
	cout << endl;
	cout << "s_mapSetOfGroup集合里还剩 " << Group::s_mapSetOfGroup.size() << " 个钢卷组" << endl;
	cout << "KPI=" << best_kpi << endl;
}

void TortoiseShell::showResultFile()
{
	string filename_result = "result.csv";
	ofstream fout(filename_result);
	fout << "钢卷号," << "流向," << "切断时间," << "必做标记," << "计划类型," << "额定轧制厚度," << "额定轧制宽度," << "额定出炉温度," << "额定终轧温度," << "额定卷取温度," << "计划号," << "高温标记" << endl;
	// 遍历乌龟壳
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		// 乌龟壳
		TortoiseShell *tortoiseShell = iter->second;
		int tortoiseShellNo = iter->first;
		fout << tortoiseShellNo << endl;
		// 遍历乌龟壳内的钢卷组
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
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
				string  high_temp_flag = steelCoil->high_temp_flag;			// 高温标记
				fout << mat_no << "," << flow << "," << fin_cut_time << "," << (int)must_do_flag << "," << plan_type << "," << nom_roll_thick << "," << nom_roll_width << "," << nom_heat_temp << "," << nom_afft_temp << "," << nom_coil_temp << "," << plan_no << "," << high_temp_flag << endl;
			}
		}
	}
}

double TortoiseShell::computekpi(map<int, TortoiseShell*>&NEW_TortoiseShell)
{
	const double max_TortoiseShell_len = 30000;// 乌龟壳最大公里数
	double flow10_wt = 0;
	double assigned_wt = 0;
	double assigned_DHCR = 0;
	double rollingkm = 0;
	double flow_rate = 0;
	double DHCR_rate = 0;
	double order_rate = 0;
	double rollingkm_rate = 0;	
	double m_TortoiseShell_len1 = 0;
	double m_TortoiseShell_WT1 = 0;
	double m_TortoiseShellflow10_WT1 = 0;
	double m_TortoiseShell_DHCR1 = 0;
	// 计算排好乌龟壳的所有钢卷总重量、某流向钢卷总重量、有DHCR标记的钢卷总数、乌龟壳总长度
	for (map<int, TortoiseShell*>::iterator iter = NEW_TortoiseShell.begin(); iter != NEW_TortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
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
	for (map<int, TortoiseShell*>::iterator iter = NEW_TortoiseShell.begin(); iter != NEW_TortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		rollingkm += tortoiseShell->m_TortoiseShell_len1;
		assigned_wt += tortoiseShell->m_TortoiseShell_WT1;
		flow10_wt += tortoiseShell->m_TortoiseShellflow10_WT1;
		assigned_DHCR += tortoiseShell->m_TortoiseShell_DHCR1;
	}
	flow_rate = flow10_wt / allflow10_wt;																	// 流向匹配率
	order_rate = assigned_wt / allsteelcCoil_wt;															// 合同计划兑现率
	rollingkm_rate = (rollingkm / s_mapSetOfTortoiseShell.size()) / max_TortoiseShell_len;					// 轧制公里率
	DHCR_rate = assigned_DHCR / m_DHCR;																		// DHCR比率
	cout << flow_rate << "   " << order_rate << "    " << rollingkm_rate << "   " << DHCR_rate << endl;
	double KPI = flow_rate*0.3 + order_rate*0.3 + rollingkm_rate*0.2 + DHCR_rate*0.1;
	return KPI;
}

bool TortoiseShell::addMainGroup(Group *group)
{
	// 主体材硬约束
	int MAX_NUM = 999;					// 最大块数
	int MAX_KM = 2147483647;			// 最大公里数
	int ROLL_WIDTH_MINUS = 100;			// 轧制宽度差
	//int	HARD_GROUP_MINUS = 100;		// 硬度组差
	int	SAME_WIDTH_NUM = 100;			// 同宽块数
	int SAME_WIDTH_KM = 500000;			// 同宽轧制公里数
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
	int partZoneNum = steelCoilNum;		// 记录要放入的轧制位区间块数
	int partZoneKm = steelCoilLenth;	// 记录要放入的轧制位区间公里数
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
int								TortoiseShell::s_TortoiseShellCount = 0;
double							TortoiseShell::allTortoiseShell_len = 0;
double							TortoiseShell::m_DHCR = 0;
double							TortoiseShell::allflow10_wt = 0;
double							TortoiseShell::allsteelcCoil_wt = 0;
double							TortoiseShell::best_kpi=0;
map<pair<string, string>, string>		TortoiseShell::plantype = map<pair<string, string>, string>();
////////////////////////////////////////////////////////////////////////
#pragma endregion