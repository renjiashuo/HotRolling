#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h" 

using namespace std;
// �ڹ���ڲ��־���Ľ���
void TortoiseShell::localsearch2()
{
	pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
	s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
	// �����ڹ��
	//for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end();)
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != --s_mapSetOfTortoiseShell.end();)
	{
		TortoiseShell *tortoiseShell = iter->second;
		map<pair<int, int>, Group*>	 groups_backups = tortoiseShell->m_main_groups; // �ڹ���ڸ־���˳�򱸷�
		// �Ľ���ǣ���һ���ڹ�Ǳ��Ľ������ͷ���±�������ڹ��
		bool mark = false;
		// �����ڹ���ڵĸ־���,�ӵ�1������n-1��
		map<pair<int, int>, Group*>::iterator iter2 = groups_backups.begin();
		map<pair<int, int>, Group*>::iterator iter2_end_1 = groups_backups.end();
		--iter2_end_1;
		for (; iter2 != iter2_end_1; ++iter2)
		{
			int start1 = iter2->first.first;
			int end1 = iter2->first.second;
			Group *group1 = iter2->second;
			// �����ڹ���ڵĸ־���,�ӵ�i+1������n��
			map<pair<int, int>, Group*>::iterator iter3 = iter2;
			++iter3;
			for (; iter3 != groups_backups.end(); ++iter3)
			{
				int start2 = iter3->first.first;
				int end2 = iter3->first.second;
				Group *group2 = iter3->second;
				// �ı�־����˳��
				map<pair<int, int>, Group*>::iterator iter2erase = tortoiseShell->m_main_groups.find(make_pair(start1, end1));
				map<pair<int, int>, Group*>::iterator iter3erase = tortoiseShell->m_main_groups.find(make_pair(start2, end2));
				tortoiseShell->m_main_groups.erase(iter2erase);
				tortoiseShell->m_main_groups.erase(iter3erase);
				tortoiseShell->m_main_groups.insert(make_pair(make_pair(start1, end1), group2));
				tortoiseShell->m_main_groups.insert(make_pair(make_pair(start2, end2), group1));
				// �洢�µĸ־���˳��
				queue<Group*> groupInTurn;
				while (!tortoiseShell->m_main_groups.empty())
				{
					groupInTurn.push(tortoiseShell->m_main_groups.begin()->second);
					tortoiseShell->m_main_groups.erase(tortoiseShell->m_main_groups.begin());
				}
				// ���ڹ���з����һ���־���
				Group *groupFiirst = groupInTurn.front();
				groupInTurn.pop();
				tortoiseShell->m_main_groups.insert(make_pair(make_pair(0, groupFiirst->roll_len), groupFiirst));
				// ��Ϊ�ǽ�groupInTurn��ĸ־������·���tortoiseShell->m_main_groups������Ҫ�����ų̹����м�¼�ı���
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
				// ���־��鰴���µ�˳������ڹ�ǲ�����Ƿ����
				while (!groupInTurn.empty())
				{
					// ��һ���־���
					Group *groupLast = tortoiseShell->m_main_groups.rbegin()->second;
					// ��ȡ��һ���־���
					Group *groupNext = groupInTurn.front();
					groupInTurn.pop();
					// �����������ЩӲԼ������ô������
					if (plantype.find(make_pair(groupLast->plan_type, groupNext->plan_type))->second == "0"
						|| abs((*groupLast->m_SteelCoil.begin())->nom_roll_thick - (*groupNext->m_SteelCoil.rbegin())->nom_roll_thick) > (*groupNext->m_SteelCoil.begin())->thick_forward_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_heat_temp - (*groupNext->m_SteelCoil.rbegin())->nom_heat_temp) > (*groupNext->m_SteelCoil.begin())->heat_temp_jump_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_afft_temp - (*groupNext->m_SteelCoil.rbegin())->nom_afft_temp) > (*groupNext->m_SteelCoil.begin())->afft_temp_jump_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_coil_temp - (*groupNext->m_SteelCoil.rbegin())->nom_coil_temp) > (*groupNext->m_SteelCoil.begin())->coil_temp_jump_max
						|| abs((*groupLast->m_SteelCoil.begin())->nom_hard_group_code[0] - (*groupNext->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*groupNext->m_SteelCoil.begin())->hard_group_jump_max)
					{
						break;
					}
					// ���ڹ�ǵ�ĩβ��������־���
					bool mark = tortoiseShell->addMainGroup2(groupNext);
					// �������ɹ��������ڹ�Ǳ������ص�׼������ĸ־���ı���
					if (!mark)
						break;
				}
				// ���groupInTurn����ʣ�࣬��˵��û�гɹ�������ϣ�������һ��localsearch
				if (!groupInTurn.empty())
				{
					tortoiseShell->m_main_groups.clear();
					tortoiseShell->m_main_groups = groups_backups;
				}
				// ����˵��localsearch�ɹ�������kpi���Ƚ��Ƿ����
				else
				{
					double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
					// ���kpi���ţ���ѽ���������ڹ�Ǽ��������kpiֵ����best_kpi
					if (temp_kpi > best_kpi)
					{
						best_kpi = temp_kpi;
						groups_backups.clear();
						groups_backups = tortoiseShell->m_main_groups;
						mark = true;
					}
					// ����ָ�
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