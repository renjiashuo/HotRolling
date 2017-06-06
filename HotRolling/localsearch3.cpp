#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h" 

using namespace std;
// 往乌龟壳里插钢卷组
void TortoiseShell::localsearch3()
{
#pragma region Variables	
	int Chosen_Shell;							// 第一个乌龟壳编号               
	int Another_Shell;							// 第二个乌龟壳编号               	
	map<double, TortoiseShell*> temp;			// 存放放钢卷组过程中更好的kpi及乌龟壳
	
#pragma endregion
	// 选择第一个乌龟壳
	for (Chosen_Shell = 1; Chosen_Shell < s_mapSetOfTortoiseShell.size(); Chosen_Shell++)
	{
		// 此乌龟壳
		TortoiseShell* tortoiseShell = s_mapSetOfTortoiseShell[Chosen_Shell];
		map<pair<int, int>, Group*>	 groups_backups = tortoiseShell->m_main_groups; // 第一个乌龟壳内钢卷组顺序备份
		// 选择第二个乌龟壳
		for (Another_Shell = Chosen_Shell + 1; Another_Shell <= s_mapSetOfTortoiseShell.size(); Another_Shell++)
		{
			// 此乌龟壳
			TortoiseShell* An_tortoiseShell = s_mapSetOfTortoiseShell[Another_Shell];
			map<pair<int, int>, Group*>	 An_groups_backups = An_tortoiseShell->m_main_groups; // 第二个乌龟壳内钢卷组顺序备份
			// 遍历第二个乌龟壳里的钢卷组
			map<pair<int, int>, Group*>::iterator iter = An_groups_backups.begin();
			for (; iter != An_groups_backups.end(); iter++)
			{
				// 此钢卷组
				Group* group = iter->second;
				string plan_type = group->plan_type;
				// 判断此钢卷组是否和第一个乌龟壳里的钢卷组互斥
				map<pair<int, int>, Group*>::iterator iter0 = groups_backups.begin();
				for (; iter0 != groups_backups.end(); iter0++)
				{
					string plan_type1 = iter0->second->plan_type;
					// 查询计划类型组合方式
					map<pair<string, string>, string>::iterator iter3 = plantype.find(make_pair(plan_type, plan_type1));
					string type = iter3->second;
					// 如果计划类型为2，则找下一个钢卷组
					if (type == "2")
						break;
				}
				// 如果存在互斥，则取第二个乌龟壳的下一个钢卷组
				if (iter0 != groups_backups.end())
					continue;
				// 遍历第一个乌龟壳里的钢卷组
				map<pair<int, int>, Group*>::iterator iter1 = groups_backups.begin();
				for (; iter1 != groups_backups.end(); iter1++)
				{
					// 将此钢卷组放迭代器iter1前面
					if (iter1 == groups_backups.begin())
					{
						// 存储新的钢卷组顺序
						queue<Group*> groupInTurn;
						// 将选中钢卷组放入队列
						groupInTurn.push(group);
						// 将剩下的钢卷组放入队列中
						while (!tortoiseShell->m_main_groups.empty())
						{
							groupInTurn.push(tortoiseShell->m_main_groups.begin()->second);
							tortoiseShell->m_main_groups.erase(tortoiseShell->m_main_groups.begin());
						}
						// 向乌龟壳中放入第一个钢卷组
						Group *groupFiirst = groupInTurn.front();
						groupInTurn.pop();
						tortoiseShell->m_main_groups.insert(make_pair(make_pair(0, groupFiirst->roll_len), groupFiirst));
						// 因为是将groupInTurn里的钢卷组重新放入tortoiseShell->m_main_groups，所以要更新排程过程中记录的变量
						tortoiseShell->steelCoilNum = 0;
						tortoiseShell->steelCoilLenth = 0;
						tortoiseShell->high_num = 0;
						tortoiseShell->high_temp_coil_num = 0;
						tortoiseShell->low_temp_coil_num = 0;
						tortoiseShell->coil_flag = 0;
						if (groupFiirst->high_temp_flag == "1")
						{
							tortoiseShell->high_num = 1;
							tortoiseShell->coil_flag = 1;
							tortoiseShell->high_temp_coil_num += groupFiirst->m_SteelCoil.size();
						}
						else
							tortoiseShell->low_temp_coil_num += groupFiirst->m_SteelCoil.size();
						tortoiseShell->steelCoilNum = groupFiirst->m_SteelCoil.size();
						tortoiseShell->steelCoilLenth = groupFiirst->roll_len;
						// 将钢卷组按照新的顺序放入乌龟壳并检查是否可行
						while (!groupInTurn.empty())
						{
							// 上一个钢卷组
							Group *groupLast = tortoiseShell->m_main_groups.rbegin()->second;
							// 提取下一个钢卷组
							Group *groupNext = groupInTurn.front();
							groupInTurn.pop();
							// 如果不满足这些硬约束，那么不可行
							if (plantype.find(make_pair(groupLast->plan_type, groupNext->plan_type))->second == "0"
								|| abs((*groupLast->m_SteelCoil.begin())->nom_roll_thick - (*groupNext->m_SteelCoil.rbegin())->nom_roll_thick) > (*groupNext->m_SteelCoil.begin())->thick_forward_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_heat_temp - (*groupNext->m_SteelCoil.rbegin())->nom_heat_temp) > (*groupNext->m_SteelCoil.begin())->heat_temp_jump_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_afft_temp - (*groupNext->m_SteelCoil.rbegin())->nom_afft_temp) > (*groupNext->m_SteelCoil.begin())->afft_temp_jump_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_coil_temp - (*groupNext->m_SteelCoil.rbegin())->nom_coil_temp) > (*groupNext->m_SteelCoil.begin())->coil_temp_jump_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_hard_group_code[0] - (*groupNext->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*groupNext->m_SteelCoil.begin())->hard_group_jump_max)
							{
								break;
							}
							// 向乌龟壳的末尾放入这个钢卷组
							bool mark = tortoiseShell->addMainGroup2(groupNext);
							// 如果分配成功，跳出乌龟壳遍历，回到准备放入的钢卷组的遍历
							if (!mark)
								break;
						}
						// 如果groupInTurn中有剩余，则说明没有成功安排完毕,还原，下一个位置
						if (!groupInTurn.empty())
						{
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							continue;
						}
						// 否则放入成功，计算KPI
						else
						{
							// 先删除垃圾桶
							pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
							s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
							double temp_kpi = computekpi();
							temp.insert(make_pair(temp_kpi, tortoiseShell));
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							// 重新放入垃圾桶
							s_mapSetOfTortoiseShell.insert(trash);
							continue;
						}

					}
					else
					{
						// 存储新的钢卷组顺序
						queue<Group*> groupInTurn;
						// 将欲插入位置的前半部分的钢卷组先放入队列中
						map<pair<int, int>, Group*>::iterator iter4 = groups_backups.begin();
						for (; iter4 !=iter1; iter4++)
						{
							groupInTurn.push(iter4->second);
						}
						// 将选中钢卷组放入队列
						groupInTurn.push(group);
						// 将欲插入位置的后半部分的钢卷组放入队列中	
						map<pair<int, int>, Group*>::iterator iter5 = iter1;
						for (; iter5 != groups_backups.end(); iter5++)
						{
							groupInTurn.push(iter5->second);
						}
						// 向乌龟壳中放入第一个钢卷组
						Group *groupFiirst = groupInTurn.front();
						groupInTurn.pop();
						tortoiseShell->m_main_groups.clear();
						tortoiseShell->m_main_groups.insert(make_pair(make_pair(0, groupFiirst->roll_len), groupFiirst));
						// 因为是将groupInTurn里的钢卷组重新放入tortoiseShell->m_main_groups，所以要更新排程过程中记录的变量
						tortoiseShell->steelCoilNum = 0;
						tortoiseShell->steelCoilLenth = 0;
						tortoiseShell->high_num = 0;
						tortoiseShell->high_temp_coil_num = 0;
						tortoiseShell->low_temp_coil_num = 0;
						tortoiseShell->coil_flag = 0;
						if (groupFiirst->high_temp_flag == "1")
						{
							tortoiseShell->high_num = 1;
							tortoiseShell->coil_flag = 1;
							tortoiseShell->high_temp_coil_num += groupFiirst->m_SteelCoil.size();
						}
						else
							tortoiseShell->low_temp_coil_num += groupFiirst->m_SteelCoil.size();
						tortoiseShell->steelCoilNum = groupFiirst->m_SteelCoil.size();
						tortoiseShell->steelCoilLenth = groupFiirst->roll_len;
						// 将钢卷组按照新的顺序放入乌龟壳并检查是否可行
						while (!groupInTurn.empty())
						{
							// 上一个钢卷组
							Group *groupLast = tortoiseShell->m_main_groups.rbegin()->second;
							// 提取下一个钢卷组
							Group *groupNext = groupInTurn.front();
							groupInTurn.pop();
							// 如果不满足这些硬约束，那么不可行
							if (plantype.find(make_pair(groupLast->plan_type, groupNext->plan_type))->second == "0"
								|| abs((*groupLast->m_SteelCoil.begin())->nom_roll_thick - (*groupNext->m_SteelCoil.rbegin())->nom_roll_thick) > (*groupNext->m_SteelCoil.begin())->thick_forward_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_heat_temp - (*groupNext->m_SteelCoil.rbegin())->nom_heat_temp) > (*groupNext->m_SteelCoil.begin())->heat_temp_jump_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_afft_temp - (*groupNext->m_SteelCoil.rbegin())->nom_afft_temp) > (*groupNext->m_SteelCoil.begin())->afft_temp_jump_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_coil_temp - (*groupNext->m_SteelCoil.rbegin())->nom_coil_temp) > (*groupNext->m_SteelCoil.begin())->coil_temp_jump_max
								|| abs((*groupLast->m_SteelCoil.begin())->nom_hard_group_code[0] - (*groupNext->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*groupNext->m_SteelCoil.begin())->hard_group_jump_max)
							{
								break;
							}
							// 向乌龟壳的末尾放入这个钢卷组
							bool mark = tortoiseShell->addMainGroup2(groupNext);
							// 如果分配成功，跳出乌龟壳遍历，回到准备放入的钢卷组的遍历
							if (!mark)
								break;							
						}
						// 如果groupInTurn中有剩余，则说明没有成功安排完毕,还原，下一个位置
						if (!groupInTurn.empty())
						{
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							continue;
						}
						// 否则放入成功，计算KPI
						else
						{
							// 先删除垃圾桶
							pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
							s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
							double temp_kpi = computekpi();
							temp.insert(make_pair(temp_kpi, tortoiseShell));
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							// 重新放入垃圾桶
							s_mapSetOfTortoiseShell.insert(trash);
							continue;
						}
					}					
				}
				// 将选中钢卷组放入第一个乌龟壳最后				
				// 存储新的钢卷组顺序
				queue<Group*> groupInTurn;
				map<pair<int, int>, Group*>::iterator iter6 = groups_backups.begin();
				for (; iter6 != groups_backups.end(); iter6++)
				{
					groupInTurn.push(iter6->second);
				}
				groupInTurn.push(group);
				// 向乌龟壳中放入第一个钢卷组
				Group *groupFiirst = groupInTurn.front();
				groupInTurn.pop();
				tortoiseShell->m_main_groups.clear();
				tortoiseShell->m_main_groups.insert(make_pair(make_pair(0, groupFiirst->roll_len), groupFiirst));
				// 因为是将groupInTurn里的钢卷组重新放入tortoiseShell->m_main_groups，所以要更新排程过程中记录的变量
				tortoiseShell->steelCoilNum = 0;
				tortoiseShell->steelCoilLenth = 0;
				tortoiseShell->high_num = 0;
				tortoiseShell->high_temp_coil_num = 0;
				tortoiseShell->low_temp_coil_num = 0;
				tortoiseShell->coil_flag = 0;
				if (groupFiirst->high_temp_flag == "1")
				{
					tortoiseShell->high_num = 1;
					tortoiseShell->coil_flag = 1;
					tortoiseShell->high_temp_coil_num += groupFiirst->m_SteelCoil.size();
				}
				else
					tortoiseShell->low_temp_coil_num += groupFiirst->m_SteelCoil.size();
				tortoiseShell->steelCoilNum = groupFiirst->m_SteelCoil.size();
				tortoiseShell->steelCoilLenth = groupFiirst->roll_len;
				// 将钢卷组按照新的顺序放入乌龟壳并检查是否可行
				while (!groupInTurn.empty())
				{
					// 上一个钢卷组
					Group *groupLast = tortoiseShell->m_main_groups.rbegin()->second;
					// 提取下一个钢卷组
					Group *groupNext = groupInTurn.front();
					groupInTurn.pop();
					// 如果不满足这些硬约束，那么不可行
					if (plantype.find(make_pair(groupLast->plan_type, groupNext->plan_type))->second == "0"
						|| abs((*groupLast->m_SteelCoil.begin())->nom_roll_thick - (*groupNext->m_SteelCoil.rbegin())->nom_roll_thick) > (*groupNext->m_SteelCoil.begin())->thick_forward_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_heat_temp - (*groupNext->m_SteelCoil.rbegin())->nom_heat_temp) > (*groupNext->m_SteelCoil.begin())->heat_temp_jump_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_afft_temp - (*groupNext->m_SteelCoil.rbegin())->nom_afft_temp) > (*groupNext->m_SteelCoil.begin())->afft_temp_jump_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_coil_temp - (*groupNext->m_SteelCoil.rbegin())->nom_coil_temp) > (*groupNext->m_SteelCoil.begin())->coil_temp_jump_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_hard_group_code[0] - (*groupNext->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*groupNext->m_SteelCoil.begin())->hard_group_jump_max)
					{
						break;
					}
					// 向乌龟壳的末尾放入这个钢卷组
					bool mark = tortoiseShell->addMainGroup2(groupNext);
					// 如果分配成功，跳出乌龟壳遍历，回到准备放入的钢卷组的遍历
					if (!mark)
						break;
				}
				if (!groupInTurn.empty())
				{
					tortoiseShell->m_main_groups.clear();
					tortoiseShell->m_main_groups = groups_backups;
					// 遍历存放kpi的map，寻找更好的kpi
					for (map<double, TortoiseShell*>::iterator iter7 = temp.begin(); iter7 != temp.end(); iter7++)
					{
						if (iter7->first > best_kpi)
						{
							best_kpi = iter7->first;
							cout << "流向匹配率: " << flow_rate << "   " << "合同计划兑现率: " << order_rate << "    " << "轧制公里率: " << rollingkm_rate << "   " << "DHCR比率: " << DHCR_rate << "   " << "排程质量: " << Scheduling_quality << endl;
							cout << " KPI: " << best_kpi << endl;
							s_mapSetOfTortoiseShell[Chosen_Shell] = iter7->second;
						}
						else
							continue;
					}
					continue;
				}
				else
				{
					// 先删除垃圾桶
					pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
					s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
					double temp_kpi = computekpi();
					temp.insert(make_pair(temp_kpi, tortoiseShell));
					tortoiseShell->m_main_groups.clear();
					tortoiseShell->m_main_groups = groups_backups;
					for (map<double, TortoiseShell*>::iterator iter7 = temp.begin(); iter7 != temp.end(); iter7++)
					{
						if (iter7->first > best_kpi)
						{
							best_kpi = iter7->first;
							cout << "流向匹配率: " << flow_rate << "   " << "合同计划兑现率: " << order_rate << "    " << "轧制公里率: " << rollingkm_rate << "   " << "DHCR比率: " << DHCR_rate << "   " << "排程质量: " << Scheduling_quality << endl;
							cout << " KPI: " << best_kpi << endl;
							s_mapSetOfTortoiseShell[Chosen_Shell] = iter7->second;
						}
						else
							continue;
					}
					// 重新放入垃圾桶
					s_mapSetOfTortoiseShell.insert(trash);
					continue;
				}				
			}
		}
	}
}