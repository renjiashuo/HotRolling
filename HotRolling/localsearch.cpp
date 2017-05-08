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
	 // 设置迭代最大代数
	 int Max_Gen = 50;
	 srand((unsigned)time(NULL));		//设置时间种子
	 double D_value = 0.1;					//定义相似宽度为相差+/- 10%
#pragma region  迭代过程
	 for (int i = 0; i <= Max_Gen; i++)
	 {
		 vec_Chosen_Position_Start.clear();
		 vec_Chosen_Position_End.clear();
		 vec_Another_Position_Start.clear();
		 vec_Another_Position_End.clear();
		 map_Candidate_Group.clear();
		 temp.clear();
		 temp1.clear();
#pragma region 随机选取 Chosen_Shell，获取其所有宽度，放入 Vector 中 <vec_Chosen_Position>     
		 /************获取Chosen_Shell所有位置信息**********/
		 Chosen_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;												//随机数范围（1——s_mapSetOfTortoiseShell.size()）
		 map<pair<int, int>, Group*> ::iterator iterChosen_Position = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();	//iter01——读取选中shell里的group位置信息，并放入group_position容器中
		 for (; iterChosen_Position != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iterChosen_Position++)
		 {
			 vec_Chosen_Position_Start.push_back(iterChosen_Position->first.first);	//存放选中的乌龟壳的所有钢卷组起始位置
			 vec_Chosen_Position_End.push_back(iterChosen_Position->first.second);	//存放选中的乌龟壳的所有钢卷组终止位置
		 }
		 /**************************************************/
#pragma endregion

#pragma region 随机获取第 Chosen_Position_No 块钢卷组的 Chosen_Position 信息
		 /**********获取Chosen_Position所有位置信息*********/
		 Chosen_Position_No = (rand() % (vec_Chosen_Position_Start.size()));
		 Chosen_Position_Start = vec_Chosen_Position_Start[Chosen_Position_No];
		 Chosen_Position_End = vec_Chosen_Position_End[Chosen_Position_No];
		 /**************************************************/
#pragma endregion

#pragma region 获取第 Chosen_Position_No 块Group的 Chosen_Width 信息
		 /**********获取钢卷组宽度（Chosen_Width）**********/
		 map<pair<int, int>, Group*> ::iterator iterChosen = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
		 Chosen_Width = iterChosen->second->nom_roll_width;
		 // 获取第一个选取的钢卷组的计划类型
		 string Chosen_plan_type = iterChosen->second->plan_type;
		 /**************************************************/
#pragma endregion

#pragma region 选取AnotherShell，Another_Shell的编号与Chosen_Shell不同

		 Another_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;
		 while (Another_Shell == Chosen_Shell)
		 {
			 Another_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;
		 }

#pragma endregion

#pragma region 获取 Another_Shell 的所有位置信息，并放入 map 中 <map_Another_Position>

		 /************获取Another_Shell所有位置信息**********/	
		 map<pair<int, int>, Group*> ::iterator iterAnother_Position = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();	//iter01——读取选中shell里的group位置信息，并放入group_position容器中
		 for (; iterAnother_Position != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterAnother_Position++)
		 {
			 vec_Another_Position_Start.push_back( iterAnother_Position->first.first);
			 vec_Another_Position_End.push_back(iterAnother_Position->first.second);			
		 }
	 /**************************************************/
	#pragma endregion

#pragma region 在 Another_Shell 中找到相似宽度的Another_Group，并随机选取一个钢卷组
		 /********在第二个乌龟壳找到相似宽度的钢卷组********/
		 //1.搜寻所有宽度符合要求的Group，存入候选 map <map_Candidate_Group>
		 //2.在所有候选Group中随机选出Group并获取 宽度、起止位置信息
		 //3.与Chosen_Group匹配（合适就交换看看，不合适就进行下一代）//要不要多给几次机会
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
			 }									//如果这两个组宽度相差D_value，则为与之前匹配的目标,放入候选map	
			 else
				 continue;
		 }
		 if (map_Candidate_Group.size() == 0)	//如果候选map是空的，说明没有找到可匹配的Group，进行下一代
			 continue;
		 // 随机选取一个钢卷组
		 int Another_Candidate_No;
		 Another_Candidate_No = (rand() % map_Candidate_Group.size());							//随机选取候选map中的Group
		 Another_Width = map_Candidate_Group[Another_Candidate_No].second->nom_roll_width;		//获取宽度信息	
		 Another_Position_Start = map_Candidate_Group[Another_Candidate_No].first.first;		//获取位置信息
		 Another_Position_End = map_Candidate_Group[Another_Candidate_No].first.second;
/**************************************************/
#pragma endregion

#pragma region 判断硬约束是否满足,检查该钢卷如果放入，有没有相邻冲突，如果有，则不能放入该乌龟壳
		 // 将Chosen_Shell里的选中钢卷组放入一个中间map里，并在Chosen_Shell里删除它	
		 		 
		 map<pair<int, int>, Group*> ::iterator iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
		 iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
		 temp.insert(make_pair(make_pair(iter->first.first, iter->first.second), iter->second));
		 iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter);
		 // 将Another_Shell里选中的钢卷组放入Chosen_Shell里，键值不改变，只改变value值
		 map<pair<int, int>, Group*> ::iterator iter1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 iter1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
		 map<pair<int, int>, Group*> ::iterator iter3 = temp.begin();
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter1->second));		
		 string plan_type = iter1->second->plan_type;
		 // 判断硬约束，iter_now指向刚放入，待比较的钢卷组	 
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
			 // 如果有一项约束不满足，则删除此钢卷组
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
		 // 不管满不满足上面的条件，都将此钢卷组删掉，继续下面的判断
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now);
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter3->second));
		
		// 将Another_Shell里的选中钢卷组放入一个中间map里，并在Another_Shell里删除它		 	 
		 map<pair<int, int>, Group*> ::iterator iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
		 temp1.insert(make_pair(make_pair(iter2->first.first, iter2->first.second), iter2->second));
		 iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter2);
		 // 将Chosen_Shell里选中的钢卷组放入Aother_Shell里，键值不改变，只改变value值	
		 map<pair<int, int>, Group*> ::iterator iter4 = temp1.begin();
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter3->second));
		 string plan_type1 = iter3->second->plan_type;
		 // 判断硬约束，iter_now指向刚放入，待比较的钢卷组	 
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
			 // 如果有一项约束不满足，则删除此钢卷组
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
		 // 不管满不满足上面的条件，都将此钢卷组删掉，继续下面的判断
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1);
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
	
 //////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region 两个钢卷组，两个乌龟壳，互换位置后，看是否互斥
 //////////////////////////////////////////////////////////////////////////							 
			 // 获取钢卷组的计划类型
			 map<pair<int, int>, Group*> ::iterator iterAnother1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
			 iterAnother1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
			 string Another_plan_type = iterAnother1->second->plan_type;
			// 判断是否互斥 Another_Shell->Chosen_Shell
			 map<pair<int, int>, Group*> ::iterator iterChosen1 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
			 for (; iterChosen1 != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iterChosen1++)
			 {
				 Group* group = iterChosen1->second;
				 string plan_type = group->plan_type;
				 // 查询Chosen_Shell里的钢卷组计划类型和Another_Shell中选中钢卷组的计划类型的组合方式
				 map<pair<string, string>, string>::iterator iter = plantype.find(make_pair(Another_plan_type, plan_type));
				 string type = iter->second;
				 if (iterChosen1->first.first != Chosen_Position_Start)
				 {
					 // 如果互斥，则取map_Candidate_Group里的另一个钢卷组，继续判断
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
		
		 // 判断是否互斥 Chosen_Shell->Another_Shell
		 map<pair<int, int>, Group*>::iterator iterAnother2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 for (; iterAnother2 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterAnother2++)
		 {
			 Group* group = iterAnother2->second;
			 string plan_type1 = group->plan_type;
			 // 查询Another_Shell里的钢卷组计划类型和Chosen_Shell中选中钢卷组的计划类型的组合方式
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
		 	
#pragma region 交换两组钢卷，判断是否满足高温卷、低温卷块数、轧制位区间限制
		 // 将Another_Shell里选中的钢卷组放入Chosen_Shell里，键值不改变，只改变value值
		 map<pair<int, int>, Group*> ::iterator iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
		 iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
		 iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter8);
		 map<pair<int, int>, Group*> ::iterator iter03 = temp.begin();
		 map<pair<int, int>, Group*> ::iterator iter01 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter03->first.first, iter03->first.second), iter01->second));
		 swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp);
		 map<pair<int, int>, Group*> ::iterator m_iter = m_temp.begin();
		 s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter->second->roll_len),m_iter->second));
		 // 将m_temp里的钢卷组重新放入Chosen_Shell里，并考虑轧制位区间等约束（逆序遍历分配到乌龟壳中）
		 map<pair<int, int>, Group*>::iterator iter5 = m_temp.begin();
		 for (; iter5 != m_temp.end();)
		 {
			 Group* group = iter5->second;
			 bool mark = s_mapSetOfTortoiseShell[Chosen_Shell]->addMainGroup(group);
			 // 如果分配成功，继续下一个钢卷组
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

		 // 将Chosen_Shell里选中的钢卷组放入Another_Shell里，键值不改变，只改变value值
		 map<pair<int, int>, Group*> ::iterator iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
		 iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
		 iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter9);
		 map<pair<int, int>, Group*> ::iterator iter04 = temp1.begin();
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter04->first.first, iter04->first.second), iter03->second));
		 swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1);
		 map<pair<int, int>, Group*> ::iterator m_iter1 = m_temp1.begin();
		 s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter1->second->roll_len), m_iter1->second));
		 // 将m_temp1里的钢卷组重新放入Another_Shell里，并考虑轧制位区间等约束（逆序遍历分配到乌龟壳中）
		 map<pair<int, int>, Group*>::iterator iter6 = m_temp1.begin();
		 for (; iter6 != m_temp1.end(); iter6++)
		 {
			 Group* group = iter6->second;
			 bool mark = s_mapSetOfTortoiseShell[Another_Shell]->addMainGroup(group);
			 // 如果分配成功，继续下一个钢卷组
			 if (mark)
				 continue;
			 else
				 break;
		 }
		 if (iter6 != m_temp.end())
			 continue;

		 // 计算所得解的KPI,首先要把未分配钢卷组的那个乌龟壳删掉，计算完KPI之后再把这个乌龟壳放入乌龟壳集合里
		 map<int, TortoiseShell*> temp2;
		 map<int, TortoiseShell*>::iterator iter7 = temp2.begin();
		 iter7 = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
		 temp2.insert(make_pair(iter7->first, iter7->second));
		 s_mapSetOfTortoiseShell.erase(iter7);
		 double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
		 // 如果kpi更优，则把解放入最优乌龟壳集合里，并把kpi值赋给best_kpi
		 if (temp_kpi > best_kpi)
		 {
			 best_kpi = temp_kpi;
			 swap(s_mapSetOfTortoiseShell, s_bestSetOfTortoiseShell);
			 s_mapSetOfTortoiseShell.insert(make_pair(iter7->first, iter7->second));
			 continue;
		 }
		 // 否则，继续迭代
		 else
		 {
			 s_mapSetOfTortoiseShell.insert(make_pair(iter7->first, iter7->second));
			 continue;
		 }
			 
#pragma endregion
	 }
#pragma endregion
 }