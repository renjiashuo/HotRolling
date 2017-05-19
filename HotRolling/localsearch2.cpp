#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h" 

using namespace std;
// 乌龟壳内部钢卷组的交换
void TortoiseShell::localsearch2()
{
	pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
	s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
	// 遍历乌龟壳
	//for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end();)
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != --s_mapSetOfTortoiseShell.end();)
	{
		TortoiseShell *tortoiseShell = iter->second;
		map<pair<int, int>, Group*>	 groups_backups = tortoiseShell->m_main_groups; // 乌龟壳内钢卷组顺序备份
		// 改进标记，若一个乌龟壳被改进，则从头重新遍历这个乌龟壳
		bool mark = false;
		// 遍历乌龟壳内的钢卷组,从第1个到第n-1个
		map<pair<int, int>, Group*>::iterator iter2 = groups_backups.begin();
		map<pair<int, int>, Group*>::iterator iter2_end_1 = groups_backups.end();
		--iter2_end_1;
		for (; iter2 != iter2_end_1; ++iter2)
		{
			int start1 = iter2->first.first;
			int end1 = iter2->first.second;
			Group *group1 = iter2->second;
			// 遍历乌龟壳内的钢卷组,从第i+1个到第n个
			map<pair<int, int>, Group*>::iterator iter3 = iter2;
			++iter3;
			for (; iter3 != groups_backups.end(); ++iter3)
			{
				int start2 = iter3->first.first;
				int end2 = iter3->first.second;
				Group *group2 = iter3->second;
				// 改变钢卷组的顺序
				map<pair<int, int>, Group*>::iterator iter2erase = tortoiseShell->m_main_groups.find(make_pair(start1, end1));
				map<pair<int, int>, Group*>::iterator iter3erase = tortoiseShell->m_main_groups.find(make_pair(start2, end2));
				tortoiseShell->m_main_groups.erase(iter2erase);
				tortoiseShell->m_main_groups.erase(iter3erase);
				tortoiseShell->m_main_groups.insert(make_pair(make_pair(start1, end1), group2));
				tortoiseShell->m_main_groups.insert(make_pair(make_pair(start2, end2), group1));
				// 存储新的钢卷组顺序
				queue<Group*> groupInTurn;
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
				// 如果groupInTurn中有剩余，则说明没有成功安排完毕，进行下一次localsearch
				if (!groupInTurn.empty())
				{
					tortoiseShell->m_main_groups.clear();
					tortoiseShell->m_main_groups = groups_backups;
				}
				// 否则，说明localsearch成功，计算kpi并比较是否接受
				else
				{
					double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
					// 如果kpi更优，则把解放入最优乌龟壳集合里，并把kpi值赋给best_kpi
					if (temp_kpi > best_kpi)
					{
						best_kpi = temp_kpi;
						groups_backups.clear();
						groups_backups = tortoiseShell->m_main_groups;
						mark = true;
					}
					// 否则恢复
					else
					{
						tortoiseShell->m_main_groups.clear();
						tortoiseShell->m_main_groups = groups_backups;
					}
				}
				if (mark)
					break;
			}
			if (mark)
				break;
		}
		if (!mark)
			++iter;
	}
	s_mapSetOfTortoiseShell.insert(trash);
}