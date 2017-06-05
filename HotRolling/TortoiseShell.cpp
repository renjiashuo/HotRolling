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
	//this->m_TortoiseShellflow10_WT = 0;
	this->m_TortoiseShell_DHCR = 0;
	this->m_TortoiseShell_len1 = 0;
	this->m_TortoiseShell_WT1 = 0;
	this->m_TortoiseShellflow10_WT1 = 0;
	this->m_TortoiseShell_DHCR1 = 0;
	this->penalty = 0;
	
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
				/*if (steelCoil->flow == "10")
					tortoiseShell->m_TortoiseShellflow10_WT += steelCoil->slab_wt;*/
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
		//allflow10_wt += (*iter).second->m_TortoiseShellflow10_WT;
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
	////////////////////////////////////////////////////////////////////////////
	#pragma endregion
}

void TortoiseShell::showResult()
{
	int i = 0;
	cout << "乌龟壳总数：  " << s_TortoiseShellCount << endl;
	map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
	s_mapSetOfTortoiseShell.erase(iter);
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
	cout << "s_mapSetOfGroup集合里还剩 " << Group::s_mapSetOfGroup.size() << " 个钢卷组" << endl<<endl;
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

void TortoiseShell::showResultSQL()
{
	try
	{
		Environment::Initialize();// 环境初始化
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");// 连接数据库（IP地址/服务名，“用户名”，“密码“）
		Statement st(con);// 创建数据集
		ostring rowid;
		st.Execute("Delete from TIPHR25 where 1=1");// 删除表中所有数据
		//st.Execute("insert into TIPHR25 (MOD_STAMP_NO ,IPS_LOT_NO ,PLAN_NO ,MAT_NO ) values(2,3,5,4)");
		string str1 = "insert into TIPHR25 (MOD_STAMP_NO ,IPS_LOT_NO ,PLAN_NO ,MAT_NO, PLAN_EXEC_SEQ_NO, PLAN_BACKLOG_CODE, ROLL_SEQ_NO, PLAN_START_TIME, WORK_TYPE ) values(";
		string str2 = ")";
		string tNowStr = "20170421080000";
		time_t tNow = StringToDatetime(tNowStr);
		for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
		{
			int tortoiseShellNo = iter->first;
			TortoiseShell *tortoiseShell = iter->second;
			int seqNo = 1;
			for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
			{
				Group *group = iter2->second;
				for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
				{
					SteelCoil *steelCoil = *iter3;
					// 模型邮戳号
					string str_MOD_STAMP_NO = "1";
					// 应用批次号
					int int_IPS_LOT_NO = (int)steelCoil->roll_end_time_double / (24 * 60);
					char char_IPS_LOT_NO[10];
					sprintf(char_IPS_LOT_NO, "%d", int_IPS_LOT_NO);
					string str_IPS_LOT_NO = char_IPS_LOT_NO;
					// 计划号
					char char_PLAN_NO[10];
					sprintf(char_PLAN_NO, "%d", tortoiseShellNo);
					string str_PLAN_NO = char_PLAN_NO;
					// 材料号
					string str_MAT_NO = steelCoil->mat_no;
					// 计划执行顺序号
					string str_PLAN_EXEC_SEQ_NO = str_PLAN_NO;
					// 计划工序代码
					string str_PLAN_BACKLOG_CODE = steelCoil->next_whole_backlog_code;
					// 轧制顺序号
					int int_ROLL_SEQ_NO = seqNo++;
					char char_ROLL_SEQ_NO[10];
					sprintf(char_ROLL_SEQ_NO, "%d", int_ROLL_SEQ_NO);
					string str_ROLL_SEQ_NO = char_ROLL_SEQ_NO;
					// 计划开始时刻
					int int_PLAN_START_TIME = steelCoil->roll_begin_time_double * 60;
					string str_PLAN_START_TIME = DatetimeToString(int_PLAN_START_TIME + tNow);
					// 工件类型
					string str_WORK_TYPE = steelCoil->work_type;
					// 数据库语句完成
					string str = str1 + str_MOD_STAMP_NO + "," + str_IPS_LOT_NO + "," + str_PLAN_NO + ",'" + str_MAT_NO + "'," + str_PLAN_EXEC_SEQ_NO + ",'" + str_PLAN_BACKLOG_CODE + "'," + str_ROLL_SEQ_NO + ",'" + str_PLAN_START_TIME + "'," + str_WORK_TYPE + str2;
					st.Execute(str);
				}
			}
		}
		con.Commit();
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();
}

double TortoiseShell::computekpi(map<int, TortoiseShell*>&NEW_TortoiseShell)
{
	calculateRollingFinishTime();
	// 读取热轧计划模型输入流向设定表
	try
	{
		Environment::Initialize();// 环境初始化
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");// 连接数据库（IP地址/服务名，“用户名”，“密码“）
		Statement st(con);// 创建数据集
		ostring rowid;
		st.Execute("select * from TIPHR22");// 选择表
		Resultset rs = st.GetResultset();
		
		while (rs.Next())
		{
			pair<double, string> temp;
			temp = make_pair(rs.Get<double>(10), rs.Get<ostring>(11));
			flowrule.insert(make_pair(temp, rs.Get<double>(14)));
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();
	// 变量定义
	const double max_TortoiseShell_len = 30000;// 乌龟壳最大公里数
	//double flow10_wt=0 ;
	double assigned_wt=0 ;
	double assigned_DHCR = 0;
	double rollingkm = 0;
	double flow_rate = 0;
	double DHCR_rate = 0;
	double order_rate = 0;
	double Scheduling_quality = 0;
	double rollingkm_rate = 0;	
	double m_TortoiseShell_len1 = 0;
	double m_TortoiseShell_WT1 = 0;
	double m_TortoiseShellflow10_WT1 = 0;
	double m_TortoiseShell_DHCR1 = 0;
	int THICK_FORWARD_penalty = 700;		// 厚度正跳罚分
	int THICK_BACKWARD_penalty = 600;		// 厚度反跳罚分
	int HARD_JUMP_panalty = 600;			// 硬度跳跃公差罚分
	int WIDTH_FORWARD_penalty = 700;		// 宽度正跳罚分
	int WIDTH_BACKWARD_penalty = 600;		// 宽度反跳罚分
	int HEAT_TEMP_JUMP_penalty = 600;		// 出炉温度跳跃公差罚分
	int AFFT_TEMP_JUMP_penalty = 700;		// 终轧温度跳跃公差罚分	
	int COIL_TEMP_JUMP_penalty = 700;		// 卷取温度跳跃公差罚分
	double Scheduling_quality_deno = 18000;	// 计算排程质量的分母
	double all_penalty = 0;	
	double flowrateall = 0;
	// 计算流向匹配率
	for (int i = 1; i <= actualflow.size() / 2; i++)
	{
		double flowrate = (actualflow.find(make_pair(i, "10"))->second / flowrule.find(make_pair(i, "10"))->second + actualflow.find(make_pair(i, "11"))->second / flowrule.find(make_pair(i, "11"))->second) / 2;
		flowrateall += flowrate;
	}
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
				/*if (steelCoil->flow == "10")
					tortoiseShell->m_TortoiseShellflow10_WT1 += steelCoil->slab_wt;*/
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
		//flow10_wt += tortoiseShell->m_TortoiseShellflow10_WT1;
		assigned_DHCR += tortoiseShell->m_TortoiseShell_DHCR1;
	}

	//////////////////////////////////////////////////////////////////////////
	// 测试
	if (assigned_wt > allsteelcCoil_wt)
		system("pause");
	//////////////////////////////////////////////////////////////////////////

	// 计算罚分，即KPI中的排程质量.先遍历所有乌龟壳
	for (map<int, TortoiseShell*>::iterator iter = NEW_TortoiseShell.begin(); iter != NEW_TortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// 遍历乌龟壳内的钢卷组信息
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			map<pair<int, int>, Group*>::iterator iter_after = iter2;
			iter_after++;
			if (iter_after != tortoiseShell->m_main_groups.end())
			{
				// 厚度罚分
				if (iter_after->second->nom_roll_thick > iter2->second->nom_roll_thick)// 反跳
				{
					if (iter2->second->nom_roll_thick*0.5 < (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) && (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) < iter2->second->nom_roll_thick*0.8)
						tortoiseShell->penalty += 0.5*THICK_BACKWARD_penalty;
					else if (iter2->second->nom_roll_thick*0.8 < (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) && (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) < iter2->second->nom_roll_thick)
						tortoiseShell->penalty += THICK_BACKWARD_penalty;
				}
				else if (iter_after->second->nom_roll_thick < iter2->second->nom_roll_thick)// 正跳
				{
					if (iter2->second->nom_roll_thick*0.5 < (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick) && (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick)< iter2->second->nom_roll_thick*0.8)
						tortoiseShell->penalty += 0.5*THICK_FORWARD_penalty;
					else if (iter2->second->nom_roll_thick*0.8 < (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick) && (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick) < iter2->second->nom_roll_thick)
						tortoiseShell->penalty += THICK_FORWARD_penalty;
				}
				else
					continue;
				// 宽度罚分
				if (iter_after->second->nom_roll_width > iter2->second->nom_roll_width)// 反跳
				{
					if (1< (iter_after->second->nom_roll_width - iter2->second->nom_roll_width) && (iter_after->second->nom_roll_width - iter2->second->nom_roll_width)< 50)
						tortoiseShell->penalty += 0.5*WIDTH_BACKWARD_penalty;
					else if (50 < (iter_after->second->nom_roll_width - iter2->second->nom_roll_width) && (iter_after->second->nom_roll_width - iter2->second->nom_roll_width) < 100)
						tortoiseShell->penalty += WIDTH_BACKWARD_penalty;
				}
				else if (iter_after->second->nom_roll_width < iter2->second->nom_roll_width)// 正跳
				{
					if (50 < (iter2->second->nom_roll_width - iter_after->second->nom_roll_width) && (iter2->second->nom_roll_width - iter_after->second->nom_roll_width) < 100)
						tortoiseShell->penalty += 0.5*WIDTH_FORWARD_penalty;
					else if (100< (iter2->second->nom_roll_width - iter_after->second->nom_roll_width) && (iter2->second->nom_roll_width - iter_after->second->nom_roll_width)< 300)
						tortoiseShell->penalty += WIDTH_FORWARD_penalty;
				}
				else
					continue;
				// 硬度公差罚分
				if (abs(iter_after->second->nom_hard_group_code[0] - iter2->second->nom_hard_group_code[0])==1)
					tortoiseShell->penalty += 0.5*HARD_JUMP_panalty;
				else if (abs(iter_after->second->nom_hard_group_code[0] - iter2->second->nom_hard_group_code[0]) == 2 || abs(iter_after->second->nom_hard_group_code[0] - iter2->second->nom_hard_group_code[0]) == 3)
					tortoiseShell->penalty += HARD_JUMP_panalty;				
				// 出炉温度公差罚分
				if (5 < abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) && abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) < 10)
					tortoiseShell->penalty += 0.5*HEAT_TEMP_JUMP_penalty;
				else if (10 < abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) && abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) < 99)
					tortoiseShell->penalty += HEAT_TEMP_JUMP_penalty;
				else
					continue;				
				// 终轧温度公差罚分
				if (5 < abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp) && abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp)< 10)
					tortoiseShell->penalty += 0.5*AFFT_TEMP_JUMP_penalty;
				else if (10 < abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp) && abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp) < 99)
					tortoiseShell->penalty += AFFT_TEMP_JUMP_penalty;
				else
					continue;
				// 卷取温度公差罚分
				if (5 < abs(iter_after->second->nom_coil_temp - iter2->second->nom_coil_temp) && abs(iter_after->second->nom_coil_temp - iter2->second->nom_coil_temp) < 10)
					tortoiseShell->penalty += 0.5*COIL_TEMP_JUMP_penalty;
				else if (10 < abs(iter_after->second->nom_coil_temp - iter2->second->nom_coil_temp) && abs(iter_after->second->nom_coil_temp - iter2->second->nom_coil_temp) < 99)
					tortoiseShell->penalty += COIL_TEMP_JUMP_penalty;
				else
					continue;				
			}
			else
				break;			
		}
		
	}
	int i = 1;
	for (map<int, TortoiseShell*>::iterator iter = NEW_TortoiseShell.begin(); iter != NEW_TortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		all_penalty += tortoiseShell->penalty;
		//cout << "第"<<i<<"个乌龟壳的罚分为：" << tortoiseShell->penalty << endl;
		i++;
	}
	
	
	flow_rate = flowrateall/(actualflow.size()/2);															// 流向匹配率
	order_rate = assigned_wt / allsteelcCoil_wt;															// 合同计划兑现率
	rollingkm_rate = (rollingkm / s_mapSetOfTortoiseShell.size()) / max_TortoiseShell_len;					// 轧制公里率
	DHCR_rate = assigned_DHCR / m_DHCR;																		// DHCR比率
	Scheduling_quality = all_penalty / Scheduling_quality_deno;												// 排程质量
	double KPI = flow_rate*0.3 + order_rate*0.3 + rollingkm_rate*0.2 + DHCR_rate*0.1 -Scheduling_quality*0.1;
	//double KPI = flow_rate*0.1 + order_rate*0.1 + rollingkm_rate*0.5 + DHCR_rate*0.1 - Scheduling_quality*0.2;
	cout << "流向匹配率: " << flow_rate << "   " << "合同计划兑现率: " << order_rate << "    " << "轧制公里率: " << rollingkm_rate << "   " << "DHCR比率: " << DHCR_rate << "   " << "排程质量: " << Scheduling_quality<< endl;
	cout << " KPI: " << KPI << endl;
	// 初始化每个乌龟壳的相关参数
	for (map<int, TortoiseShell*>::iterator iter0 = NEW_TortoiseShell.begin(); iter0 != NEW_TortoiseShell.end(); iter0++)
	{
		 TortoiseShell *tortoiseShell = iter0->second;
		 tortoiseShell->m_TortoiseShell_len1=0;
		 tortoiseShell->m_TortoiseShell_WT1=0;
		 tortoiseShell->m_TortoiseShellflow10_WT1=0;
		 tortoiseShell->m_TortoiseShell_DHCR1=0;
		 tortoiseShell->penalty = 0;		 
	}
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

bool TortoiseShell::addMainGroup2(Group *group)
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

	// 如果可放入的钢卷数小于钢卷组内的钢卷数，则不可放入
	if (canSaveNum < group->m_SteelCoil.size())
		return false;

	// 否则，直接将整个钢卷组加入到乌龟壳中
	// 将小钢卷组插入到当前乌龟壳的临时钢卷组变量中
	m_main_groups.insert(make_pair(make_pair(steelCoilLenth, steelCoilLenth + group->roll_len), group));
	// 更新乌龟壳实时长度
	steelCoilNum += canSaveNum;
	steelCoilLenth += group->roll_len;
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

void TortoiseShell::calculateRollingFinishTime()
{
	double nowTime = 0;	
	// 遍历乌龟壳
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// 遍历乌龟壳内的钢卷组
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// 遍历钢卷组内的钢卷
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			
			{
				SteelCoil *steelCoil = *iter3;
				steelCoil->roll_begin_time_double = nowTime;
				nowTime += steelCoil->roll_time;
				steelCoil->roll_end_time_double = nowTime;								
			}
		}
	}
	// 根据计算好的轧制时间，计算天数(向上取整)
	int day = ceil(nowTime / (24 * 60));	
	int i = 1;
	nowTime = 0;
	double WT_10 = 0;
	double WT_11 = 0;
		// 遍历乌龟壳
		for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
		{
			TortoiseShell *tortoiseShell = iter->second;
			// 遍历乌龟壳内的钢卷组
			for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
			{
				Group *group = iter2->second;
				// 遍历钢卷组内的钢卷
				for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
				{
					SteelCoil *steelCoil = *iter3;
					steelCoil->roll_begin_time_double = nowTime;
					nowTime += steelCoil->roll_time;
					steelCoil->roll_end_time_double = nowTime;
					for (; i <= day;)
					{
						if (nowTime >= (i - 1) * 1440 && nowTime <= i * 1440)
						{
							if (steelCoil->flow == "10")
								WT_10 += steelCoil->slab_wt;
							else
								WT_11 += steelCoil->slab_wt;
							break;
						}
						else
						{
							actualflow.insert(make_pair(make_pair(i, "10"), WT_10));
							actualflow.insert(make_pair(make_pair(i, "11"), WT_11));
							WT_10 = 0;
							WT_11 = 0;
							i++;
							continue;
						}						
					}					
				}
			}
		}
		// 将不足一天的各流向的钢卷重量插入map
		{
			actualflow.insert(make_pair(make_pair(i, "10"), WT_10));
			actualflow.insert(make_pair(make_pair(i, "11"), WT_11));
		}
	}

string TortoiseShell::DatetimeToString(time_t time)
{
	tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
	int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
	year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
	month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
	day = tm_->tm_mday;                        // 临时变量，日。
	hour = tm_->tm_hour;                       // 临时变量，时。
	minute = tm_->tm_min;                      // 临时变量，分。
	second = tm_->tm_sec;                      // 临时变量，秒。
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
	sprintf(yearStr, "%d", year);              // 年。
	sprintf(monthStr, "%d", month);            // 月。
	sprintf(dayStr, "%d", day);                // 日。
	sprintf(hourStr, "%d", hour);              // 时。
	if (hourStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
	{
		hourStr[2] = '\0';
		hourStr[1] = hourStr[0];
		hourStr[0] = '0';
	}
	sprintf(minuteStr, "%d", minute);          // 分。
	if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
	{
		minuteStr[2] = '\0';
		minuteStr[1] = minuteStr[0];
		minuteStr[0] = '0';
	}
	sprintf(secondStr, "%d", second);          // 秒。
	if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
	{
		secondStr[2] = '\0';
		secondStr[1] = secondStr[0];
		secondStr[0] = '0';
	}
	char s[20];                                // 定义总日期时间char*变量。
	sprintf(s, "%s%s%s%s%s%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
	string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
	return str;                                // 返回转换日期时间后的string变量。
}

time_t TortoiseShell::StringToDatetime(string str)
{
	char *cha = (char*)str.data();             // 将string转换成char*。
	tm tm_;                                    // 定义tm结构体。
	int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
	sscanf(cha, "%4d%2d%2d%2d%2d%2d", &year, &month, &day, &hour, &minute, &second);// 将string存储的日期时间，转换为int临时变量。
	tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
	tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
	tm_.tm_mday = day;                         // 日。
	tm_.tm_hour = hour;                        // 时。
	tm_.tm_min = minute;                       // 分。
	tm_.tm_sec = second;                       // 秒。
	tm_.tm_isdst = 0;                          // 非夏令时。
	time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
	return t_;                                 // 返回值。 
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group静态变量
//////////////////////////////////////////////////////////////////////////
map<int, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<int, TortoiseShell*>();
int								TortoiseShell::s_TortoiseShellCount = 0;
double							TortoiseShell::allTortoiseShell_len = 0;
double							TortoiseShell::m_DHCR = 0;
double							TortoiseShell::allsteelcCoil_wt = 0;
double							TortoiseShell::best_kpi=0;
int								TortoiseShell::all_penalty=0;
map<pair<string, string>, string>		TortoiseShell::plantype = map<pair<string, string>, string>();
map<pair<double, string>, double>		TortoiseShell::flowrule = map<pair<double, string>, double>();
map<pair<double, string>, double>		TortoiseShell::actualflow = map<pair<double,string>,double >() ;
////////////////////////////////////////////////////////////////////////
#pragma endregion