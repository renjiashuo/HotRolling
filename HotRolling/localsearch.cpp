#include"common.h"
#include "global.h"
#include"SteelCoil.h"
#include"Group.h"
#include"TortoiseShell.h"
#include <ctime> // for gettimeofday() 
#include <stdlib.h>     // for random() 
#include <time.h> // for gettimeofday() 
#include"localsearch.h"
using namespace std;


 void TortoiseShell::localsearch()
 {
	 // ���õ���������
	 int Max_Gen = 50;
	 srand((unsigned)time(NULL));		//����ʱ������
	 double D_value = 0.1;					//�������ƿ��Ϊ���+/- 10%
#pragma region  ��������
	 for (int i = 0; i <= Max_Gen; i++)
	 {
		 vec_Chosen_Position_Start.clear();
		 vec_Chosen_Position_End.clear();
		 vec_Another_Position_Start.clear();
		 vec_Another_Position_End.clear();
		 map_Candidate_Group.clear();
		 temp.clear();
		 temp1.clear();
#pragma region ���ѡȡ Chosen_Shell����ȡ�����п�ȣ����� Vector �� <vec_Chosen_Position>     
		 /************��ȡChosen_Shell����λ����Ϣ**********/
		 Chosen_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;												//�������Χ��1����s_mapSetOfTortoiseShell.size()��
		 map<pair<int, int>, Group*> ::iterator iterChosen_Position = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();	//iter01������ȡѡ��shell���groupλ����Ϣ��������group_position������
		 for (; iterChosen_Position != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iterChosen_Position++)
		 {
			 vec_Chosen_Position_Start.push_back(iterChosen_Position->first.first);	//���ѡ�е��ڹ�ǵ����и־�����ʼλ��
			 vec_Chosen_Position_End.push_back(iterChosen_Position->first.second);	//���ѡ�е��ڹ�ǵ����и־�����ֹλ��
		 }
		 /**************************************************/
#pragma endregion

#pragma region �����ȡ�� Chosen_Position_No ��־���� Chosen_Position ��Ϣ
		 /**********��ȡChosen_Position����λ����Ϣ*********/
		 Chosen_Position_No = (rand() % (vec_Chosen_Position_Start.size()));
		 Chosen_Position_Start = vec_Chosen_Position_Start[Chosen_Position_No];
		 Chosen_Position_End = vec_Chosen_Position_End[Chosen_Position_No];
		 /**************************************************/
#pragma endregion

#pragma region ��ȡ�� Chosen_Position_No ��Group�� Chosen_Width ��Ϣ
		 /**********��ȡ�־����ȣ�Chosen_Width��**********/
		 map<pair<int, int>, Group*> ::iterator iterChosen = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
		 Chosen_Width = iterChosen->second->nom_roll_width;
		 // ��ȡ��һ��ѡȡ�ĸ־���ļƻ�����
		 string Chosen_plan_type = iterChosen->second->plan_type;
		 /**************************************************/
#pragma endregion

#pragma region ѡȡAnotherShell��Another_Shell�ı����Chosen_Shell��ͬ

		 Another_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;
		 while (Another_Shell == Chosen_Shell)
		 {
			 Another_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;
		 }

#pragma endregion

#pragma region ��ȡ Another_Shell ������λ����Ϣ�������� map �� <map_Another_Position>

		 /************��ȡAnother_Shell����λ����Ϣ**********/	
		 map<pair<int, int>, Group*> ::iterator iterAnother_Position = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();	//iter01������ȡѡ��shell���groupλ����Ϣ��������group_position������
		 for (; iterAnother_Position != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterAnother_Position++)
		 {
			 vec_Another_Position_Start.push_back( iterAnother_Position->first.first);
			 vec_Another_Position_End.push_back(iterAnother_Position->first.second);			
		 }
	 /**************************************************/
	#pragma endregion

#pragma region �� Another_Shell ���ҵ����ƿ�ȵ�Another_Group�������ѡȡһ���־���
		 /********�ڵڶ����ڹ���ҵ����ƿ�ȵĸ־���********/
		 //1.��Ѱ���п�ȷ���Ҫ���Group�������ѡ map <map_Candidate_Group>
		 //2.�����к�ѡGroup�����ѡ��Group����ȡ ��ȡ���ֹλ����Ϣ
		 //3.��Chosen_Groupƥ�䣨���ʾͽ��������������ʾͽ�����һ����//Ҫ��Ҫ������λ���
		 /*1*/
		 int AG_NO = 0;
		 map<pair<int, int>, Group*> ::iterator iterCandidate = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 for (; iterCandidate != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterCandidate++)
		 {
			 int Another_Group_Width = iterCandidate->second->nom_roll_width;
			 if (abs(Another_Group_Width - Chosen_Width) <= D_value * Chosen_Width)
			 {
				 map_Candidate_Group.insert(make_pair(AG_NO, make_pair(make_pair(iterCandidate->first.first, iterCandidate->first.second), iterCandidate->second)));
				 AG_NO++;
			 }									//����������������D_value����Ϊ��֮ǰƥ���Ŀ��,�����ѡmap	
			 else
				 continue;
		 }
		 if (map_Candidate_Group.size() == 0)	//�����ѡmap�ǿյģ�˵��û���ҵ���ƥ���Group��������һ��
			 continue;
		 // ���ѡȡһ���־���
		 int Another_Candidate_No;
		 Another_Candidate_No = (rand() % map_Candidate_Group.size());							//���ѡȡ��ѡmap�е�Group
		 Another_Width = map_Candidate_Group[Another_Candidate_No].second->nom_roll_width;		//��ȡ�����Ϣ	
		 Another_Position_Start = map_Candidate_Group[Another_Candidate_No].first.first;		//��ȡλ����Ϣ
		 Another_Position_End = map_Candidate_Group[Another_Candidate_No].first.second;
/**************************************************/
#pragma endregion

#pragma region �ж�ӲԼ���Ƿ�����,���ø־�������룬��û�����ڳ�ͻ������У����ܷ�����ڹ��
		 // ��Chosen_Shell���ѡ�и־������һ���м�map�����Chosen_Shell��ɾ����	
		 		 
		 map<pair<int, int>, Group*> ::iterator iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
		 iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
		 temp.insert(make_pair(make_pair(iter->first.first, iter->first.second), iter->second));
		 iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter);
		 // ��Another_Shell��ѡ�еĸ־������Chosen_Shell���ֵ���ı䣬ֻ�ı�valueֵ
		 map<pair<int, int>, Group*> ::iterator iter1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 iter1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
		 map<pair<int, int>, Group*> ::iterator iter3 = temp.begin();
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter1->second));		
		 string plan_type = iter1->second->plan_type;
		 // �ж�ӲԼ����iter_nowָ��շ��룬���Ƚϵĸ־���	 
		 map<pair<int, int>, Group*>::iterator iter_now = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(iter3->first.first, iter3->first.second));
		 map<pair<int, int>, Group*>::iterator iter_before = iter_now;
		 map<pair<int, int>, Group*>::iterator iter_after = iter_now;
		 iter_before--;
		 iter_after++;
		 if (iter_now != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin() &&
			 (plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == "0"
			 || (*iter_now->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
			 || abs((*iter_now->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
			 || abs((*iter_now->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
			 || abs((*iter_now->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
			 || abs((*iter_now->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
			 ))
		 {
			 // �����һ��Լ�������㣬��ɾ���˸־���
			 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now);
			 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter3->second));			
			 continue;
		 }
		 if (iter_after != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end() &&
			 (plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second == "0"
			 || (*iter_after->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
			 || abs((*iter_after->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
			 || abs((*iter_after->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
			 || abs((*iter_after->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
			 || abs((*iter_after->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
			 ))
		 {
			 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now);
			 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter3->second));			
			 continue;
		 }
		 // ����������������������������˸־���ɾ��������������ж�
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now);
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter3->second));
		
		// ��Another_Shell���ѡ�и־������һ���м�map�����Another_Shell��ɾ����		 	 
		 map<pair<int, int>, Group*> ::iterator iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
		 temp1.insert(make_pair(make_pair(iter2->first.first, iter2->first.second), iter2->second));
		 iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter2);
		 // ��Chosen_Shell��ѡ�еĸ־������Aother_Shell���ֵ���ı䣬ֻ�ı�valueֵ	
		 map<pair<int, int>, Group*> ::iterator iter4 = temp1.begin();
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter3->second));
		 string plan_type1 = iter3->second->plan_type;
		 // �ж�ӲԼ����iter_nowָ��շ��룬���Ƚϵĸ־���	 
		 map<pair<int, int>, Group*>::iterator iter_now1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(iter4->first.first, iter4->first.second));
		 map<pair<int, int>, Group*>::iterator iter_before1 = iter_now1;
		 map<pair<int, int>, Group*>::iterator iter_after1 = iter_now1;
		 iter_before1--;
		 iter_after1++;
		 if (iter_now1 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin() &&
			 (plantype.find(make_pair(plan_type1, iter_before1->second->plan_type))->second == "0"
			 || (*iter_now1->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before1->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now1->second->m_SteelCoil.begin())->thick_forward_max
			 || abs((*iter_now1->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before1->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now1->second->m_SteelCoil.begin())->heat_temp_jump_max
			 || abs((*iter_now1->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before1->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now1->second->m_SteelCoil.begin())->afft_temp_jump_max
			 || abs((*iter_now1->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before1->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now1->second->m_SteelCoil.begin())->coil_temp_jump_max
			 || abs((*iter_now1->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before1->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now1->second->m_SteelCoil.begin())->hard_group_jump_max
			 ))
		 {
			 // �����һ��Լ�������㣬��ɾ���˸־���
			 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1);
			 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));			
			 continue;
		 }
		 if (iter_after1 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end() &&
			 (plantype.find(make_pair(plan_type1, iter_after1->second->plan_type))->second == "0"
			 || (*iter_after1->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now1->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now1->second->m_SteelCoil.begin())->thick_forward_max
			 || abs((*iter_after1->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now1->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now1->second->m_SteelCoil.begin())->heat_temp_jump_max
			 || abs((*iter_after1->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now1->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now1->second->m_SteelCoil.begin())->afft_temp_jump_max
			 || abs((*iter_after1->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now1->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now1->second->m_SteelCoil.begin())->coil_temp_jump_max
			 || abs((*iter_after1->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now1->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now1->second->m_SteelCoil.begin())->hard_group_jump_max
			 ))
		 {
			 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1);
			 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));			
			 continue;
		 }
		 // ����������������������������˸־���ɾ��������������ж�
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1);
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
	
 //////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region �����־��飬�����ڹ�ǣ�����λ�ú󣬿��Ƿ񻥳�
 //////////////////////////////////////////////////////////////////////////							 
			 // ��ȡ�־���ļƻ�����
			 map<pair<int, int>, Group*> ::iterator iterAnother1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
			 iterAnother1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
			 string Another_plan_type = iterAnother1->second->plan_type;
			// �ж��Ƿ񻥳� Another_Shell->Chosen_Shell
			 map<pair<int, int>, Group*> ::iterator iterChosen1 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
			 for (; iterChosen1 != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iterChosen1++)
			 {
				 Group* group = iterChosen1->second;
				 string plan_type = group->plan_type;
				 // ��ѯChosen_Shell��ĸ־���ƻ����ͺ�Another_Shell��ѡ�и־���ļƻ����͵���Ϸ�ʽ
				 map<pair<string, string>, string>::iterator iter = plantype.find(make_pair(Another_plan_type, plan_type));
				 string type = iter->second;
				 if (iterChosen1->first.first != Chosen_Position_Start)
				 {
					 // ������⣬��ȡmap_Candidate_Group�����һ���־��飬�����ж�
					 if (type == "2")
					 {
						 break;
					 }						
					 else
						 continue;
				 }
				 else
					 continue;
			 }
			 if (iterChosen1 != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end())
				 continue;
		
		 // �ж��Ƿ񻥳� Chosen_Shell->Another_Shell
		 map<pair<int, int>, Group*>::iterator iterAnother2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 for (; iterAnother2 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterAnother2++)
		 {
			 Group* group = iterAnother2->second;
			 string plan_type1 = group->plan_type;
			 // ��ѯAnother_Shell��ĸ־���ƻ����ͺ�Chosen_Shell��ѡ�и־���ļƻ����͵���Ϸ�ʽ
			 map<pair<string, string>, string>::iterator iter = plantype.find(make_pair(Chosen_plan_type, plan_type1));
			 string type1 = iter->second;
			 if (iterAnother2->first.first != Another_Position_Start)
			 {
				 if (type1 == "2")
					 break;
				 else
					 continue;
			 }
			 else
				 continue;
		 }
		 if (iterAnother2 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end())
			 continue;
 //////////////////////////////////////////////////////////////////////////
#pragma endregion
		 	
#pragma region ��������־��ж��Ƿ�������¾����¾����������λ��������
		 // ��Another_Shell��ѡ�еĸ־������Chosen_Shell���ֵ���ı䣬ֻ�ı�valueֵ
		 map<pair<int, int>, Group*> ::iterator iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
		 iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
		 iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter8);
		 map<pair<int, int>, Group*> ::iterator iter03 = temp.begin();
		 map<pair<int, int>, Group*> ::iterator iter01 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter03->first.first, iter03->first.second), iter01->second));
		 swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp);
		 map<pair<int, int>, Group*> ::iterator m_iter = m_temp.begin();
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter->second->roll_len),m_iter->second));
		 // ��m_temp��ĸ־������·���Chosen_Shell�����������λ�����Լ��������������䵽�ڹ���У�
		 map<pair<int, int>, Group*>::iterator iter5 = m_temp.begin();
		 for (; iter5 != m_temp.end();)
		 {
			 Group* group = iter5->second;
			 bool mark = s_mapSetOfTortoiseShell[Chosen_Shell]->addMainGroup(group);
			 // �������ɹ���������һ���־���
			 if (mark)
			 {
				 ++iter5;
				continue;
			 }				 
			 else
				 break;
		 }
		 if (iter5 != m_temp.end())
			 continue;

		 // ��Chosen_Shell��ѡ�еĸ־������Another_Shell���ֵ���ı䣬ֻ�ı�valueֵ
		 map<pair<int, int>, Group*> ::iterator iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
		 iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter9);
		 map<pair<int, int>, Group*> ::iterator iter04 = temp1.begin();
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter04->first.first, iter04->first.second), iter03->second));
		 swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1);
		 map<pair<int, int>, Group*> ::iterator m_iter1 = m_temp1.begin();
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter1->second->roll_len), m_iter1->second));
		 // ��m_temp1��ĸ־������·���Another_Shell�����������λ�����Լ��������������䵽�ڹ���У�
		 map<pair<int, int>, Group*>::iterator iter6 = m_temp1.begin();
		 for (; iter6 != m_temp1.end(); iter6++)
		 {
			 Group* group = iter6->second;
			 bool mark = s_mapSetOfTortoiseShell[Another_Shell]->addMainGroup(group);
			 // �������ɹ���������һ���־���
			 if (mark)
				 continue;
			 else
				 break;
		 }
		 if (iter6 != m_temp.end())
			 continue;

		 // �������ý��KPI,����Ҫ��δ����־�����Ǹ��ڹ��ɾ����������KPI֮���ٰ�����ڹ�Ƿ����ڹ�Ǽ�����
		 map<int, TortoiseShell*> temp2;
		 map<int, TortoiseShell*>::iterator iter7 = temp2.begin();
		 iter7 = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
		 temp2.insert(make_pair(iter7->first, iter7->second));
		 s_mapSetOfTortoiseShell.erase(iter7);
		 double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
		 // ���kpi���ţ���ѽ���������ڹ�Ǽ��������kpiֵ����best_kpi
		 if (temp_kpi > best_kpi)
		 {
			 best_kpi = temp_kpi;
			 swap(s_mapSetOfTortoiseShell, s_bestSetOfTortoiseShell);
			 s_mapSetOfTortoiseShell.insert(make_pair(iter7->first, iter7->second));
			 continue;
		 }
		 // ���򣬼�������
		 else
		 {
			 s_mapSetOfTortoiseShell.insert(make_pair(iter7->first, iter7->second));
			 continue;
		 }
			 
#pragma endregion
	 }
#pragma endregion
 }