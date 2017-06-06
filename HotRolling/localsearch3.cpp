#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h" 

using namespace std;
// ���ڹ�����־���
void TortoiseShell::localsearch3()
{
#pragma region Variables	
	int Chosen_Shell;							// ��һ���ڹ�Ǳ��               
	int Another_Shell;							// �ڶ����ڹ�Ǳ��               	
	map<double, TortoiseShell*> temp;			// ��ŷŸ־�������и��õ�kpi���ڹ��
	
#pragma endregion
	// ѡ���һ���ڹ��
	for (Chosen_Shell = 1; Chosen_Shell < s_mapSetOfTortoiseShell.size(); Chosen_Shell++)
	{
		// ���ڹ��
		TortoiseShell* tortoiseShell = s_mapSetOfTortoiseShell[Chosen_Shell];
		map<pair<int, int>, Group*>	 groups_backups = tortoiseShell->m_main_groups; // ��һ���ڹ���ڸ־���˳�򱸷�
		// ѡ��ڶ����ڹ��
		for (Another_Shell = Chosen_Shell + 1; Another_Shell <= s_mapSetOfTortoiseShell.size(); Another_Shell++)
		{
			// ���ڹ��
			TortoiseShell* An_tortoiseShell = s_mapSetOfTortoiseShell[Another_Shell];
			map<pair<int, int>, Group*>	 An_groups_backups = An_tortoiseShell->m_main_groups; // �ڶ����ڹ���ڸ־���˳�򱸷�
			// �����ڶ����ڹ����ĸ־���
			map<pair<int, int>, Group*>::iterator iter = An_groups_backups.begin();
			for (; iter != An_groups_backups.end(); iter++)
			{
				// �˸־���
				Group* group = iter->second;
				string plan_type = group->plan_type;
				// �жϴ˸־����Ƿ�͵�һ���ڹ����ĸ־��黥��
				map<pair<int, int>, Group*>::iterator iter0 = groups_backups.begin();
				for (; iter0 != groups_backups.end(); iter0++)
				{
					string plan_type1 = iter0->second->plan_type;
					// ��ѯ�ƻ�������Ϸ�ʽ
					map<pair<string, string>, string>::iterator iter3 = plantype.find(make_pair(plan_type, plan_type1));
					string type = iter3->second;
					// ����ƻ�����Ϊ2��������һ���־���
					if (type == "2")
						break;
				}
				// ������ڻ��⣬��ȡ�ڶ����ڹ�ǵ���һ���־���
				if (iter0 != groups_backups.end())
					continue;
				// ������һ���ڹ����ĸ־���
				map<pair<int, int>, Group*>::iterator iter1 = groups_backups.begin();
				for (; iter1 != groups_backups.end(); iter1++)
				{
					// ���˸־���ŵ�����iter1ǰ��
					if (iter1 == groups_backups.begin())
					{
						// �洢�µĸ־���˳��
						queue<Group*> groupInTurn;
						// ��ѡ�и־���������
						groupInTurn.push(group);
						// ��ʣ�µĸ־�����������
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
						// ���groupInTurn����ʣ�࣬��˵��û�гɹ��������,��ԭ����һ��λ��
						if (!groupInTurn.empty())
						{
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							continue;
						}
						// �������ɹ�������KPI
						else
						{
							// ��ɾ������Ͱ
							pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
							s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
							double temp_kpi = computekpi();
							temp.insert(make_pair(temp_kpi, tortoiseShell));
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							// ���·�������Ͱ
							s_mapSetOfTortoiseShell.insert(trash);
							continue;
						}

					}
					else
					{
						// �洢�µĸ־���˳��
						queue<Group*> groupInTurn;
						// ��������λ�õ�ǰ�벿�ֵĸ־����ȷ��������
						map<pair<int, int>, Group*>::iterator iter4 = groups_backups.begin();
						for (; iter4 !=iter1; iter4++)
						{
							groupInTurn.push(iter4->second);
						}
						// ��ѡ�и־���������
						groupInTurn.push(group);
						// ��������λ�õĺ�벿�ֵĸ־�����������	
						map<pair<int, int>, Group*>::iterator iter5 = iter1;
						for (; iter5 != groups_backups.end(); iter5++)
						{
							groupInTurn.push(iter5->second);
						}
						// ���ڹ���з����һ���־���
						Group *groupFiirst = groupInTurn.front();
						groupInTurn.pop();
						tortoiseShell->m_main_groups.clear();
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
						// ���groupInTurn����ʣ�࣬��˵��û�гɹ��������,��ԭ����һ��λ��
						if (!groupInTurn.empty())
						{
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							continue;
						}
						// �������ɹ�������KPI
						else
						{
							// ��ɾ������Ͱ
							pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
							s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
							double temp_kpi = computekpi();
							temp.insert(make_pair(temp_kpi, tortoiseShell));
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_groups = groups_backups;
							// ���·�������Ͱ
							s_mapSetOfTortoiseShell.insert(trash);
							continue;
						}
					}					
				}
				// ��ѡ�и־�������һ���ڹ�����				
				// �洢�µĸ־���˳��
				queue<Group*> groupInTurn;
				map<pair<int, int>, Group*>::iterator iter6 = groups_backups.begin();
				for (; iter6 != groups_backups.end(); iter6++)
				{
					groupInTurn.push(iter6->second);
				}
				groupInTurn.push(group);
				// ���ڹ���з����һ���־���
				Group *groupFiirst = groupInTurn.front();
				groupInTurn.pop();
				tortoiseShell->m_main_groups.clear();
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
				if (!groupInTurn.empty())
				{
					tortoiseShell->m_main_groups.clear();
					tortoiseShell->m_main_groups = groups_backups;
					// �������kpi��map��Ѱ�Ҹ��õ�kpi
					for (map<double, TortoiseShell*>::iterator iter7 = temp.begin(); iter7 != temp.end(); iter7++)
					{
						if (iter7->first > best_kpi)
						{
							best_kpi = iter7->first;
							cout << "����ƥ����: " << flow_rate << "   " << "��ͬ�ƻ�������: " << order_rate << "    " << "���ƹ�����: " << rollingkm_rate << "   " << "DHCR����: " << DHCR_rate << "   " << "�ų�����: " << Scheduling_quality << endl;
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
					// ��ɾ������Ͱ
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
							cout << "����ƥ����: " << flow_rate << "   " << "��ͬ�ƻ�������: " << order_rate << "    " << "���ƹ�����: " << rollingkm_rate << "   " << "DHCR����: " << DHCR_rate << "   " << "�ų�����: " << Scheduling_quality << endl;
							cout << " KPI: " << best_kpi << endl;
							s_mapSetOfTortoiseShell[Chosen_Shell] = iter7->second;
						}
						else
							continue;
					}
					// ���·�������Ͱ
					s_mapSetOfTortoiseShell.insert(trash);
					continue;
				}				
			}
		}
	}
}