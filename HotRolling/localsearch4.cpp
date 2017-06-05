#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h" 

using namespace std;
// ��������
void indata(map<pair<pair<pair<pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>,string>,string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>> &m_data, double a, double b, string c, string d, int e, int f, int g, string k, int i, int j, int m, int n, string p, SteelCoil* h);
void indata(map<int, Group*>&m_data, int a, Group* b);
// �ڹ��֮��־���
void TortoiseShell::localsearch4()
{
#pragma region ��������
	int Chosen_Shell;							// ��һ���ڹ�Ǳ��               
	int Another_Shell;							// �ڶ����ڹ�Ǳ��

	int start;									// ��һ���ڹ�ǵĸ־��ֵ
	int end;
	int start1;									// �ڶ����ڹ�ǵĸ־��ֵ
	int end1;
#pragma endregion

#pragma region	 �Ƚ��ڹ����ĸ־����ɸ־��ȱ����ڹ��
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �������ڹ�ǵĸ־���
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// �����־����ڵĸ־�,���־����m_main_SteelCoil
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			{
				SteelCoil *steelCoil = *iter3;
				// ��һ���־�����ĩλ��
				int end_located = 0;
				if (!tortoiseShell->m_main_SteelCoil.empty())
					end_located = tortoiseShell->m_main_SteelCoil.rbegin()->first.second;
				tortoiseShell->m_main_SteelCoil.insert(make_pair(make_pair(end_located, end_located + steelCoil->roll_len), steelCoil));
			}
		}
	}
#pragma endregion

#pragma region ��������
	// ���и־�����ѡ���һ���ڹ��
	for (Chosen_Shell = 1; Chosen_Shell < s_mapSetOfTortoiseShell.size(); Chosen_Shell++)
	{
		// ���ڹ��
		TortoiseShell* tortoiseShell = s_mapSetOfTortoiseShell[Chosen_Shell];
		map<pair<int, int>, SteelCoil*>	 SteelCoil_backups = tortoiseShell->m_main_SteelCoil;	// ��һ���ڹ���ڸ־�˳�򱸷�
		map<pair<int, int>, Group*>	 groups_backups = tortoiseShell->m_main_groups;				// ��һ���ڹ���ڸ־���˳�򱸷�
		// ѡ���һ���ڹ�ǵĵ�һ���־�
		map<pair<int, int>, SteelCoil*>::iterator iter = SteelCoil_backups.begin();
		for (; iter != SteelCoil_backups.end(); iter++)
		{
			// �˸־�
			SteelCoil* steelcoil = iter->second;
			// �˸־�ļ�ֵ
			start = iter->first.first;
			end = iter->first.second;
			string plan_type = steelcoil->plan_type;
			// ѡ��ڶ����ڹ��
			for (Another_Shell = Chosen_Shell + 1; Another_Shell <= s_mapSetOfTortoiseShell.size(); Another_Shell++)
			{
				// ���ڹ��
				TortoiseShell* An_tortoiseShell = s_mapSetOfTortoiseShell[Another_Shell];
				map<pair<int, int>,SteelCoil*>	 An_SteelCoil_backups = An_tortoiseShell->m_main_SteelCoil; // �ڶ����ڹ���ڸ־�˳�򱸷�
				map<pair<int, int>, Group*>	 An_groups_backups = An_tortoiseShell->m_main_groups;			// �ڶ����ڹ���ڸ־���˳�򱸷�
				// �����ڶ����ڹ�Ǹ־�
				map<pair<int, int>, SteelCoil*>::iterator iter1 = An_SteelCoil_backups.begin();
				for (; iter1 != An_SteelCoil_backups.end(); iter1++)
				{
					// �˸־�
					SteelCoil* An_steelcoil = iter1->second;
					// �˸־�ļ�ֵ
					start1 = iter1->first.first;
					end1 = iter1->first.second;
					string plan_type1 = An_steelcoil->plan_type;

					// �жϽ����־�֮���Ƿ񻥳�,���жϵڶ����ڹ��ѡ�еĸ־��Ƿ�͵�һ���ڹ��������и־���
					map<pair<int, int>, SteelCoil*>::iterator iter2 = tortoiseShell->m_main_SteelCoil.begin();
					for (; iter2 != tortoiseShell->m_main_SteelCoil.end(); iter2++)
					{
						string plan_type2 = iter2->second->plan_type;
						map<pair<string, string>, string>::iterator iter3 = plantype.find(make_pair(plan_type2, plan_type1));
						string type = iter3->second;
						if (type == "2" && iter2->first.first != start)
							break;
					}
					if (iter2 != tortoiseShell->m_main_SteelCoil.end())
						continue;
					// �жϵ�һ���ڹ��ѡ�еĸ־��Ƿ�͵ڶ����ڹ��������и־���
					map<pair<int, int>, SteelCoil*>::iterator iter4 = An_tortoiseShell->m_main_SteelCoil.begin();
					for (; iter4 != An_tortoiseShell->m_main_SteelCoil.end(); iter4++)
					{
						string plan_type3 = iter4->second->plan_type;
						map<pair<string, string>, string>::iterator iter5 = plantype.find(make_pair(plan_type3, plan_type));
						string type = iter5->second;
						if (type == "2" && iter4->first.first != start1)
							break;
					}
					if (iter4 != An_tortoiseShell->m_main_SteelCoil.end())
						continue;

					// �����־�����·ֳɸ־��飬Ȼ�����ڹ����ſ��Ƿ����
					// �Ƚ����־����ı��ֵ
					map<pair<int, int>, SteelCoil*>::iterator itererase = tortoiseShell->m_main_SteelCoil.find(make_pair(start, end));
					map<pair<int, int>, SteelCoil*>::iterator iter1erase = An_tortoiseShell->m_main_SteelCoil.find(make_pair(start1, end1));
					tortoiseShell->m_main_SteelCoil.erase(itererase);
					An_tortoiseShell->m_main_SteelCoil.erase(iter1erase);
					tortoiseShell->m_main_SteelCoil.insert(make_pair(make_pair(start, end), An_steelcoil));
					An_tortoiseShell->m_main_SteelCoil.insert(make_pair(make_pair(start1, end1), steelcoil));
					// ����־��飬�����ǵ�һ���ڹ�ǣ���ʮ��������һ���ĸ־���и־��黯
					map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>> temp_groups;
					map<pair<int, int>, SteelCoil*>::iterator iter6 = tortoiseShell->m_main_SteelCoil.begin();
					for (; iter6 != tortoiseShell->m_main_SteelCoil.end(); iter6++)
					{
						SteelCoil* temp_steelcoil = iter6->second;
						indata(temp_groups, -iter6->second->nom_roll_width, iter6->second->nom_roll_thick, iter6->second->plan_type, iter6->second->st_no, iter6->second->nom_heat_temp, iter6->second->nom_afft_temp, iter6->second->nom_coil_temp, iter6->second->high_temp_flag, iter6->second->zone_max_num, iter6->second->zone_min_num, iter6->second->zone_max_m, iter6->second->zone_min_m, iter6->second->nom_hard_group_code, temp_steelcoil);
					}
					// ���־�����
					int i = 1;
					map<int, Group*> temp_groups1;// ��һ���ڹ�ǵ��¸־��鼯��
					for (map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>>::iterator iter7 = temp_groups.begin(); iter7 != temp_groups.end(); iter7++)
					{
						Group* group1 = new Group(i, -(*iter7).first.first.first.first.first.first.first.first.first.first.first.first.first, (*iter7).first.first.first.first.first.first.first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.first.second, (*iter7).first.first.first.first.first.second, (*iter7).first.first.first.first.second, (*iter7).first.first.first.second, (*iter7).first.first.second, (*iter7).first.second, iter7->second);
						indata(temp_groups1, i, group1);
						i++;
					}
					// �ڶ����ڹ��
					map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>> temp_groups2;
					map<pair<int, int>, SteelCoil*>::iterator iter8 = An_tortoiseShell->m_main_SteelCoil.begin();
					for (; iter8 != An_tortoiseShell->m_main_SteelCoil.end(); iter8++)
					{
						SteelCoil* temp_steelcoil1 = iter8->second;
						indata(temp_groups2, -iter8->second->nom_roll_width, iter8->second->nom_roll_thick, iter8->second->plan_type, iter8->second->st_no, iter8->second->nom_heat_temp, iter8->second->nom_afft_temp, iter8->second->nom_coil_temp, iter8->second->high_temp_flag, iter8->second->zone_max_num, iter8->second->zone_min_num, iter8->second->zone_max_m, iter8->second->zone_min_m, iter8->second->nom_hard_group_code, temp_steelcoil1);
					}
					// ���־�����
					int j = 1;
					map<int, Group*> temp_groups3;// �ڶ����ڹ�ǵ��¸־��鼯��
					for (map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>>::iterator iter9 = temp_groups2.begin(); iter9 != temp_groups2.end(); iter9++)
					{
						Group* group2 = new Group(j, -(*iter9).first.first.first.first.first.first.first.first.first.first.first.first.first, (*iter9).first.first.first.first.first.first.first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.first.second, (*iter9).first.first.first.first.first.second, (*iter9).first.first.first.first.second, (*iter9).first.first.first.second, (*iter9).first.first.second, (*iter9).first.second, iter9->second);
						indata(temp_groups3, j, group2);
						j++;
					}

					// ���ڹ������µĸ־��飬���Ƿ���У��ȿ���һ���ڹ��
					queue<Group*> groupInTurn;
					while (!temp_groups1.empty())
					{
						groupInTurn.push(temp_groups1.begin()->second);
						temp_groups1.erase(temp_groups1.begin());
					}
					tortoiseShell->m_main_groups.clear();
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
						if (!mark)
							break;
					}
					// ���groupInTurn����ʣ�࣬��˵��û�гɹ��������,��ԭ��ѡ����һ���־���
					if (!groupInTurn.empty())
					{
						tortoiseShell->m_main_groups.clear();
						tortoiseShell->m_main_SteelCoil.clear();
						tortoiseShell->m_main_groups = groups_backups;
						tortoiseShell->m_main_SteelCoil = SteelCoil_backups;
						An_tortoiseShell->m_main_groups.clear();
						An_tortoiseShell->m_main_SteelCoil.clear();
						An_tortoiseShell->m_main_groups = An_groups_backups;
						An_tortoiseShell->m_main_SteelCoil = An_SteelCoil_backups;
						continue;
					}
					// �����ųɹ���Ȼ����ڶ����ڹ��
					else
					{
						queue<Group*> groupInTurn1;
						while (!temp_groups3.empty())
						{
							groupInTurn1.push(temp_groups3.begin()->second);
							temp_groups3.erase(temp_groups3.begin());
						}
						An_tortoiseShell->m_main_groups.clear();
						// ���ڹ���з����һ���־���
						Group *groupFiirst = groupInTurn1.front();
						groupInTurn1.pop();
						An_tortoiseShell->m_main_groups.insert(make_pair(make_pair(0, groupFiirst->roll_len), groupFiirst));
						// ��Ϊ�ǽ�groupInTurn��ĸ־������·���tortoiseShell->m_main_groups������Ҫ�����ų̹����м�¼�ı���
						An_tortoiseShell->steelCoilNum = 0;
						An_tortoiseShell->steelCoilLenth = 0;
						An_tortoiseShell->high_num = 0;
						An_tortoiseShell->high_temp_coil_num = 0;
						An_tortoiseShell->low_temp_coil_num = 0;
						An_tortoiseShell->coil_flag = 0;
						if (groupFiirst->high_temp_flag == "1")
						{
							An_tortoiseShell->high_num = 1;
							An_tortoiseShell->coil_flag = 1;
							An_tortoiseShell->high_temp_coil_num += groupFiirst->m_SteelCoil.size();
						}
						else
							An_tortoiseShell->low_temp_coil_num += groupFiirst->m_SteelCoil.size();
						An_tortoiseShell->steelCoilNum = groupFiirst->m_SteelCoil.size();
						An_tortoiseShell->steelCoilLenth = groupFiirst->roll_len;
						// ���־��鰴���µ�˳������ڹ�ǲ�����Ƿ����
						while (!groupInTurn1.empty())
						{
							// ��һ���־���
							Group *groupLast = An_tortoiseShell->m_main_groups.rbegin()->second;
							// ��ȡ��һ���־���
							Group *groupNext = groupInTurn1.front();
							groupInTurn1.pop();
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
							bool mark = An_tortoiseShell->addMainGroup2(groupNext);							
							if (!mark)
								break;
						}
						// ���groupInTurn1����ʣ�࣬��˵��û�гɹ��������,��ԭ
						if (!groupInTurn1.empty())
						{
							tortoiseShell->m_main_groups.clear();
							tortoiseShell->m_main_SteelCoil.clear();
							tortoiseShell->m_main_groups = groups_backups;
							tortoiseShell->m_main_SteelCoil = SteelCoil_backups;
							An_tortoiseShell->m_main_groups.clear();
							An_tortoiseShell->m_main_SteelCoil.clear();
							An_tortoiseShell->m_main_groups = An_groups_backups;
							An_tortoiseShell->m_main_SteelCoil = An_SteelCoil_backups;
							continue;
						}
						// �����ųɹ�������kpi
						else
						{
							// ��ɾ������Ͱ
							pair<int, TortoiseShell*> trash = make_pair(s_mapSetOfTortoiseShell.rbegin()->first, s_mapSetOfTortoiseShell.rbegin()->second);
							s_mapSetOfTortoiseShell.erase(s_mapSetOfTortoiseShell.rbegin()->first);
							double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
							if (temp_kpi > best_kpi)
							{
								best_kpi = temp_kpi;
								// ���±���
								SteelCoil_backups.clear();
								groups_backups.clear();
								An_SteelCoil_backups.clear();
								An_groups_backups.clear();
								SteelCoil_backups = tortoiseShell->m_main_SteelCoil;
								groups_backups = tortoiseShell->m_main_groups;
								An_SteelCoil_backups = An_tortoiseShell->m_main_SteelCoil;
								An_groups_backups = An_tortoiseShell->m_main_groups;
								// ���·�������Ͱ
								s_mapSetOfTortoiseShell.insert(trash);
								continue;
							}
							// ����ָ�
							else
							{
								tortoiseShell->m_main_groups.clear();
								tortoiseShell->m_main_SteelCoil.clear();
								tortoiseShell->m_main_groups = groups_backups;
								tortoiseShell->m_main_SteelCoil = SteelCoil_backups;
								An_tortoiseShell->m_main_groups.clear();
								An_tortoiseShell->m_main_SteelCoil.clear();
								An_tortoiseShell->m_main_groups = An_groups_backups;
								An_tortoiseShell->m_main_SteelCoil = An_SteelCoil_backups;
								// ���·�������Ͱ
								s_mapSetOfTortoiseShell.insert(trash);
								continue;
							}

						}
					}
				}
			}
		}
	}
#pragma endregion
}