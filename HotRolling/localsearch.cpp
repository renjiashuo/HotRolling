#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h" 

using namespace std;

void TortoiseShell::localsearch()
{
	#pragma region Variables
	int Chosen_Position_No;					//定义 Chosen_Position_No          为选中的钢卷组的位置号
	int Chosen_Shell;							//定义 Chosen_Shell                为随机抓取的shell编号
	int Chosen_Position_Start;					//定义 Chosen_Position_Start       为选中的钢卷组的 起始 公里数
	int Chosen_Position_End;					//定义 Chosen_Position_End         为选中的 终止 公里数
	int Chosen_Width = 0;						//定义 Chosen_Width                为选取的钢卷组的宽度

	int Another_Position_No;					//定义 Another_Position_No          为选第二个钢卷组的位置号
	int Another_Shell;							//定义 Another_Shell                为第二个乌龟壳的编号
	int Another_Position_Start = 0;			//定义 Another_Position_Start       为第二个shell的轧制公里数起始	
	int Another_Position_End = 0;				//定义 Another_Position_End         为第二个shell的轧制公里数终止
	int Another_Width = 0;						//定义 Another_Width                为第二个乌龟壳的钢卷组的宽度

	vector <int> vec_Chosen_Position_Start;		//定义 Group_Position_Start        容器存放选中的乌龟壳的所有group的 起始 位置
	vector <int> vec_Chosen_Position_End;		//定义 Group_Position_Start        容器存放选中的乌龟壳的所有group的 终止 位置
	vector <int> vec_Another_Position_Start;	//定义 map_Another_Position_Start  容器存放选第二个乌龟壳的所有group的 起始 位置
	vector <int> vec_Another_Position_End;		//定义 map_Another_Position_End    容器存放选第二个乌龟壳的所有group的 终止 位置
	//map<序号,[起始公里数，终止公里数，Group*] >
	map<int, pair< pair< int, int >, Group* >>	map_Candidate_Group;
	map<pair<int, int>, Group*>			m_temp;							// 临时容器，优化时，判断轧制位区间等用。
	map<pair<int, int>, Group*>			m_temp1;						// 临时容器，优化时，判断轧制位区间等用。
	map<pair<int, int>, Group*>			temp;							// 存放Chosen_Shell里选中的钢卷组
	map<pair<int, int>, Group*>			temp1;							// 存放Another_Shell里选中的钢卷组
	#pragma endregion

	// 设置迭代最大代数
	//int Max_Gen = 1000;
	//srand((unsigned)time(NULL));			//设置时间种子
	double D_value = 0.1;					//定义相似宽度为相差+/- 10%
	#pragma region  迭代过程
	for (Chosen_Shell = 1; Chosen_Shell < s_mapSetOfTortoiseShell.size(); Chosen_Shell++)
	{
		cout << "Chosen_Shell:" << Chosen_Shell << endl;
		vec_Chosen_Position_Start.clear();
		vec_Chosen_Position_End.clear();
		#pragma region 随机选取 Chosen_Shell，获取其所有宽度，放入 Vector 中 <vec_Chosen_Position>     
		/************获取Chosen_Shell所有位置信息**********/
		//Chosen_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;												//随机数范围（1——s_mapSetOfTortoiseShell.size()）
		map<pair<int, int>, Group*> ::iterator iterChosen_Position = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();	//iter01——读取选中shell里的group位置信息，并放入group_position容器中
		for (; iterChosen_Position != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iterChosen_Position++)
		{
			vec_Chosen_Position_Start.push_back(iterChosen_Position->first.first);	//存放选中的乌龟壳的所有钢卷组起始位置
			vec_Chosen_Position_End.push_back(iterChosen_Position->first.second);	//存放选中的乌龟壳的所有钢卷组终止位置
		}
		/**************************************************/
		#pragma endregion
		for (Chosen_Position_No = 0; Chosen_Position_No < vec_Chosen_Position_Start.size(); Chosen_Position_No++)
		{
			cout << "\tChosen_Position_No:" << Chosen_Position_No << endl;
			#pragma region 随机获取第 Chosen_Position_No 块钢卷组的 Chosen_Position 信息
			/**********获取Chosen_Position所有位置信息*********/
			//Chosen_Position_No = (rand() % (vec_Chosen_Position_Start.size()));
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
			for (Another_Shell = Chosen_Shell + 1; Another_Shell <= s_mapSetOfTortoiseShell.size(); Another_Shell++)
			{
				cout << "\t\tAnother_Shell:" << Another_Shell << endl;
				#pragma region 选取AnotherShell，Another_Shell的编号与Chosen_Shell不同
				//Another_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;
				//while (Another_Shell == Chosen_Shell)
				//{
				//	Another_Shell = (rand() % s_mapSetOfTortoiseShell.size()) + 1;
				//}
				#pragma endregion
				#pragma region 获取 Another_Shell 的所有位置信息，并放入 map 中 <map_Another_Position>


				vec_Another_Position_Start.clear();
				vec_Another_Position_End.clear();
				/************获取Another_Shell所有位置信息**********/
				map<pair<int, int>, Group*> ::iterator iterAnother_Position = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
				for (; iterAnother_Position != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterAnother_Position++)
				{
					vec_Another_Position_Start.push_back(iterAnother_Position->first.first);
					vec_Another_Position_End.push_back(iterAnother_Position->first.second);
				}
				/**************************************************/
				#pragma endregion

				map_Candidate_Group.clear();
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
					// 如果这两个组宽度相差D_value，则为与之前匹配的目标,放入候选map
					if (abs(Another_Group_Width - Chosen_Width) <= D_value * Chosen_Width)
					{
						map_Candidate_Group.insert(make_pair(AG_NO, make_pair(make_pair(iterCandidate->first.first, iterCandidate->first.second), iterCandidate->second)));
						AG_NO++;
					}
				}

				if (map_Candidate_Group.size() == 0)	//如果候选map是空的，说明没有找到可匹配的Group，进行下一代
					continue;
				// 随机选取一个钢卷组
				int Another_Candidate_No;
				for (Another_Candidate_No = 0; Another_Candidate_No < map_Candidate_Group.size(); Another_Candidate_No++)
				{
					cout << "\t\t\tAnother_Candidate_No:" << Another_Candidate_No << endl;
					temp.clear();
					temp1.clear();
					m_temp.clear();
					m_temp1.clear();
					//Another_Candidate_No = (rand() % map_Candidate_Group.size());							//随机选取候选map中的Group
					Another_Width = map_Candidate_Group[Another_Candidate_No].second->nom_roll_width;		//获取宽度信息	
					Another_Position_Start = map_Candidate_Group[Another_Candidate_No].first.first;			//获取位置信息
					Another_Position_End = map_Candidate_Group[Another_Candidate_No].first.second;
					// 获取钢卷组计划类型
					string Another_plan_type = map_Candidate_Group[Another_Candidate_No].second->plan_type;
					/**************************************************/
					#pragma endregion

					#pragma region 判断硬约束是否满足,检查该钢卷如果放入，有没有相邻冲突，如果有，则不能放入该乌龟壳
					// 将Chosen_Shell里的选中钢卷组放入一个中间map里，并在Chosen_Shell里删除它			 		 
					map<pair<int, int>, Group*> ::iterator iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
					temp.insert(make_pair(make_pair(iter->first.first, iter->first.second), iter->second));
					iter = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter);

					// 将Another_Shell里选中的钢卷组放入Chosen_Shell里，键值不改变，只改变value值
					map<pair<int, int>, Group*> ::iterator iter1 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));

					s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(Chosen_Position_Start, Chosen_Position_End), iter1->second));
					string plan_type = Another_plan_type;

					// 判断硬约束，iter_now指向刚放入，待比较的钢卷组
					map<pair<int, int>, Group*> ::iterator iter3 = temp.begin();
					map<pair<int, int>, Group*>::iterator iter_now = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
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
						iter_now = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now++);
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
						s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now++);
						s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter3->second));
						continue;
					}

					// 满足上面的条件，继续下面的判断
					s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter_now++);
					s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter3->second));

					// 将Another_Shell里的选中钢卷组放入一个中间map里，并在Another_Shell里删除它		 	 
					map<pair<int, int>, Group*> ::iterator iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
					temp1.insert(make_pair(make_pair(iter2->first.first, iter2->first.second), iter2->second));
					iter2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter2);

					// 将Chosen_Shell里选中的钢卷组放入Aother_Shell里，键值不改变，只改变value值	
					map<pair<int, int>, Group*> ::iterator iter4 = temp1.begin();
					s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(Another_Position_Start, Another_Position_End), iter3->second));
					string plan_type1 = Chosen_plan_type;

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
						s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1++);
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
						s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1++);
						s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
						continue;
					}

					// 若满足上面的条件，继续下面的判断
					s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter_now1++);
					s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));

					//////////////////////////////////////////////////////////////////////////
					#pragma endregion

					#pragma region 两个钢卷组，两个乌龟壳，互换位置后，看是否互斥
					//////////////////////////////////////////////////////////////////////////							 		
					// 判断是否互斥 Another_Shell->Chosen_Shell
					map<pair<int, int>, Group*> ::iterator iterChosen1 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
					for (; iterChosen1 != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iterChosen1++)
					{
						Group* group = iterChosen1->second;
						string plan_type = group->plan_type;
						// 查询Chosen_Shell里的钢卷组计划类型和Another_Shell中选中钢卷组的计划类型的组合方式
						map<pair<string, string>, string>::iterator iter = plantype.find(make_pair(Another_plan_type, plan_type));
						string type = iter->second;
						if (iterChosen1->first.first != Chosen_Position_Start && type == "2")
							break;
					}
					if (iterChosen1 != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end())
						continue;


					// 判断是否互斥 Chosen_Shell->Another_Shell
					map<pair<int, int>, Group*>::iterator iterAnother2 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
					for (; iterAnother2 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iterAnother2++)
					{
						Group* group1 = iterAnother2->second;
						string plan_type1 = group1->plan_type;
						// 查询Another_Shell里的钢卷组计划类型和Chosen_Shell中选中钢卷组的计划类型的组合方式
						map<pair<string, string>, string>::iterator iter0 = plantype.find(make_pair(Chosen_plan_type, plan_type1));
						string type1 = iter0->second;
						if (iterAnother2->first.first != Another_Position_Start && type1 == "2")
							break;
					}
					if (iterAnother2 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end())
						continue;

					//////////////////////////////////////////////////////////////////////////
					#pragma endregion

					#pragma region 交换两组钢卷，判断是否满足高温卷、低温卷块数、轧制位区间限制
					// 将Another_Shell里选中的钢卷组放入Chosen_Shell里，键值不改变，只改变value值
					map<pair<int, int>, Group*> ::iterator  iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.begin();
					// 创建一个s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups的副本，还原用
					map<pair<int, int>, Group*> m_temp_second;
					for (; iter8 != s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.end(); iter8++)
					{
						m_temp_second.insert(make_pair(make_pair(iter8->first.first, iter8->first.second), iter8->second));
					}
					iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.find(make_pair(Chosen_Position_Start, Chosen_Position_End));
					iter8 = s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.erase(iter8);

					//map<pair<int, int>, Group*> ::iterator iter03 = temp.begin();
					//map<pair<int, int>, Group*> ::iterator iter01 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
					s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(iter3->first.first, iter3->first.second), iter4->second));
					swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp);
					map<pair<int, int>, Group*> ::iterator m_iter = m_temp.begin();
					// 因为是将m_temp里的钢卷组往Chosen_Shell里重新放，所以要更新排程过程中记录的变量
					s_mapSetOfTortoiseShell[Chosen_Shell]->steelCoilNum = 0;
					s_mapSetOfTortoiseShell[Chosen_Shell]->steelCoilLenth = 0;
					s_mapSetOfTortoiseShell[Chosen_Shell]->high_num = 0;
					s_mapSetOfTortoiseShell[Chosen_Shell]->high_temp_coil_num = 0;
					s_mapSetOfTortoiseShell[Chosen_Shell]->low_temp_coil_num = 0;
					s_mapSetOfTortoiseShell[Chosen_Shell]->coil_flag = 0;
					if (m_iter->second->high_temp_flag == "1")
					{
						s_mapSetOfTortoiseShell[Chosen_Shell]->high_num = 1;
						s_mapSetOfTortoiseShell[Chosen_Shell]->coil_flag = 1;
						s_mapSetOfTortoiseShell[Chosen_Shell]->high_temp_coil_num += m_iter->second->m_SteelCoil.size();
					}
					else
						s_mapSetOfTortoiseShell[Chosen_Shell]->low_temp_coil_num += m_iter->second->m_SteelCoil.size();
					// 更新乌龟壳内的钢卷组
					s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter->second->roll_len), m_iter->second));
					s_mapSetOfTortoiseShell[Chosen_Shell]->steelCoilNum = m_iter->second->m_SteelCoil.size();
					s_mapSetOfTortoiseShell[Chosen_Shell]->steelCoilLenth = m_iter->second->roll_len;
					m_iter = m_temp.erase(m_iter);

					// 如果m_temp不为空，进行下一步判断
					if (!m_temp.empty())
					{
						// 将m_temp里的钢卷组重新放入Chosen_Shell里，并考虑轧制位区间等约束
						map<pair<int, int>, Group*>::iterator iter5 = m_temp.begin();
						for (; iter5 != m_temp.end();iter5++)
						{
							Group* group = iter5->second;
							bool mark = s_mapSetOfTortoiseShell[Chosen_Shell]->addMainGroup2(group);
							// 如果分配成功，继续下一个钢卷组
							if (!mark)
								break;
						

							
						}
						//如果分配不成功，则还原，下一次迭代
						if (iter5 != m_temp.end())
						{
							// 如果不满足高温卷、低温卷块数、轧制位区间限制，则恢复到原来的乌龟壳，进行下一次迭代
							s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
							swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
							
							continue;
						}
						// 全部分配成功，则进行下一步判断
						else
						{
							// 将Chosen_Shell里选中的钢卷组放入Another_Shell里，键值不改变，只改变value值
							map<pair<int, int>, Group*> ::iterator iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
							// 创建s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups的副本，还原用
							map<pair<int, int>, Group*> m_temp1_second;
							for (; iter9 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iter9++)
							{
								m_temp1_second.insert(make_pair(make_pair(iter9->first.first, iter9->first.second), iter9->second));
							}
							iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
							iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter9);
							//				map<pair<int, int>, Group*> ::iterator iter04 = temp1.begin();
							s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter3->second));
							swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1);
							map<pair<int, int>, Group*> ::iterator m_iter1 = m_temp1.begin();

							// 因为是将m_temp里的钢卷组往Chosen_Shell里重新放，所以要更新排程过程中记录的变量
							s_mapSetOfTortoiseShell[Another_Shell]->steelCoilNum = 0;
							s_mapSetOfTortoiseShell[Another_Shell]->steelCoilLenth = 0;
							s_mapSetOfTortoiseShell[Another_Shell]->high_num = 0;
							s_mapSetOfTortoiseShell[Another_Shell]->high_temp_coil_num = 0;
							s_mapSetOfTortoiseShell[Another_Shell]->low_temp_coil_num = 0;
							s_mapSetOfTortoiseShell[Another_Shell]->coil_flag = 0;
							if (m_iter1->second->high_temp_flag == "1")
							{
								s_mapSetOfTortoiseShell[Another_Shell]->high_num = 1;
								s_mapSetOfTortoiseShell[Another_Shell]->coil_flag = 1;
								s_mapSetOfTortoiseShell[Another_Shell]->high_temp_coil_num += m_iter1->second->m_SteelCoil.size();
							}
							else
								s_mapSetOfTortoiseShell[Another_Shell]->low_temp_coil_num += m_iter1->second->m_SteelCoil.size();
							// 更新乌龟壳内的钢卷组
							s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter1->second->roll_len), m_iter1->second));
							s_mapSetOfTortoiseShell[Another_Shell]->steelCoilNum = m_iter1->second->m_SteelCoil.size();
							s_mapSetOfTortoiseShell[Another_Shell]->steelCoilLenth = m_iter1->second->roll_len;
							m_iter1 = m_temp1.erase(m_iter1);
							
							// 如果m_temp1不为空，则继续判断
							if (!m_temp1.empty())
							{
								// 将m_temp1里的钢卷组重新放入Another_Shell里，并考虑轧制位区间等约束（遍历分配到乌龟壳中）
								map<pair<int, int>, Group*>::iterator iter6 = m_temp1.begin();
								for (; iter6 != m_temp1.end();iter6++)
								{
									Group* group = iter6->second;
									bool mark = s_mapSetOfTortoiseShell[Another_Shell]->addMainGroup2(group);
									// 如果分配成功，继续下一个钢卷组
									if (!mark)
										break;
								
								
								}
								if (iter6 != m_temp1.end())
								{
									// 如果不满足高温卷、低温卷块数、轧制位区间限制，则恢复到原来的乌龟壳，进行下一次迭代
									s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
									swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
									s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.clear();
									swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1_second);
									continue;
								}
								// 如果分配成功，则分配完事，计算KPI
								else
								{
									// 计算所得解的KPI,首先要把未分配钢卷组的那个乌龟壳删掉，计算完KPI之后再把这个乌龟壳放入乌龟壳集合里
									map<int, TortoiseShell*> temp2;
									map<int, TortoiseShell*>::iterator iter7 = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
									temp2.insert(make_pair(iter7->first, iter7->second));
									s_mapSetOfTortoiseShell.erase(iter7);
									map<int, TortoiseShell*>::iterator iter07 = temp2.begin();
									double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
									// 如果kpi更优，则把解放入最优乌龟壳集合里，并把kpi值赋给best_kpi
									if (temp_kpi > best_kpi)
									{
										best_kpi = temp_kpi;
										// 插入未分配钢卷组的乌龟壳
										s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
										continue;
									}
									// 否则，继续迭代
									else
									{
										// 恢复选中的乌龟壳
										s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
										swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
										s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.clear();
										swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1_second);
										// 插入未分配钢卷组的乌龟壳
										s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
										
										continue;
									}
								}

							}
							//如果m_temp1为空，说明则chosen乌龟壳的钢卷组放入another里，肯定符合所有的约束，所有判断结束，计算KPI
							else
							{
								// 计算所得解的KPI,首先要把未分配钢卷组的那个乌龟壳删掉，计算完KPI之后再把这个乌龟壳放入乌龟壳集合里
								map<int, TortoiseShell*> temp2;
								map<int, TortoiseShell*>::iterator iter7 = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
								temp2.insert(make_pair(iter7->first, iter7->second));
								s_mapSetOfTortoiseShell.erase(iter7);
								map<int, TortoiseShell*>::iterator iter07 = temp2.begin();
								double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
								// 如果kpi更优，则把解放入最优乌龟壳集合里，并把kpi值赋给best_kpi
								if (temp_kpi > best_kpi)
								{
									best_kpi = temp_kpi;
									// 插入未分配钢卷组的乌龟壳
									s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
									continue;
								}
								// 否则，继续迭代
								else
								{
									// 恢复选中的乌龟壳
									s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
									swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
									s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.clear();
									swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1_second);
									// 插入未分配钢卷组的乌龟壳
									s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
									
									continue;
								}
							}
						}
						
					}
					// 如果m_temp为空，则Another乌龟壳的钢卷组放入chosen里，肯定符合所有的约束，然后继续判断
					else
					{
						//			
						// 将Chosen_Shell里选中的钢卷组放入Another_Shell里，键值不改变，只改变value值
						map<pair<int, int>, Group*> ::iterator iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.begin();
						// 创建s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups的副本，还原用
						map<pair<int, int>, Group*> m_temp1_second;
						for (; iter9 != s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.end(); iter9++)
						{
							m_temp1_second.insert(make_pair(make_pair(iter9->first.first, iter9->first.second), iter9->second));
						}
						iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.find(make_pair(Another_Position_Start, Another_Position_End));
						iter9 = s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.erase(iter9);
						//			map<pair<int, int>, Group*> ::iterator iter04 = temp1.begin();
						s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter3->second));
						swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1);
						map<pair<int, int>, Group*> ::iterator m_iter1 = m_temp1.begin();
						// 因为是将m_temp里的钢卷组往Chosen_Shell里重新放，所以要更新排程过程中记录的变量
						s_mapSetOfTortoiseShell[Another_Shell]->steelCoilNum = 0;
						s_mapSetOfTortoiseShell[Another_Shell]->steelCoilLenth = 0;
						s_mapSetOfTortoiseShell[Another_Shell]->high_num = 0;
						s_mapSetOfTortoiseShell[Another_Shell]->high_temp_coil_num = 0;
						s_mapSetOfTortoiseShell[Another_Shell]->low_temp_coil_num = 0;
						s_mapSetOfTortoiseShell[Another_Shell]->coil_flag = 0;
						if (m_iter1->second->high_temp_flag == "1")
						{
							s_mapSetOfTortoiseShell[Another_Shell]->high_num = 1;
							s_mapSetOfTortoiseShell[Another_Shell]->coil_flag = 1;
							s_mapSetOfTortoiseShell[Another_Shell]->high_temp_coil_num += m_iter1->second->m_SteelCoil.size();
						}
						else
							s_mapSetOfTortoiseShell[Another_Shell]->low_temp_coil_num += m_iter1->second->m_SteelCoil.size();
						// 更新乌龟壳内的钢卷组
						s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.insert(make_pair(make_pair(0, m_iter1->second->roll_len), m_iter1->second));
						s_mapSetOfTortoiseShell[Another_Shell]->steelCoilNum = m_iter1->second->m_SteelCoil.size();
						s_mapSetOfTortoiseShell[Another_Shell]->steelCoilLenth = m_iter1->second->roll_len;
						m_iter1 = m_temp1.erase(m_iter1);
						

						// 如果m_temp1不为空，则继续判断
						if (!m_temp1.empty())
						{
							// 将m_temp1里的钢卷组重新放入Another_Shell里，并考虑轧制位区间等约束（逆序遍历分配到乌龟壳中）
							map<pair<int, int>, Group*>::iterator iter6 = m_temp1.begin();
							for (; iter6 != m_temp1.end();iter6++)
							{
								Group* group = iter6->second;
								bool mark = s_mapSetOfTortoiseShell[Another_Shell]->addMainGroup2(group);
								// 如果分配成功，继续下一个钢卷组
								if (!mark)
									break;
								
							}
							// 如果分配失败，则还原，进行下一次迭代
							if (iter6 != m_temp1.end())
							{
								// 如果不满足高温卷、低温卷块数、轧制位区间限制，则恢复到原来的乌龟壳，进行下一次迭代
								s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
								swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
								s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.clear();
								swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1_second);
								
								continue;
							}
							// 否则，分配成功，计算KPI
							else
							{
								// 计算所得解的KPI,首先要把未分配钢卷组的那个乌龟壳删掉，计算完KPI之后再把这个乌龟壳放入乌龟壳集合里
								map<int, TortoiseShell*> temp2;
								map<int, TortoiseShell*>::iterator iter7 = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
								temp2.insert(make_pair(iter7->first, iter7->second));
								s_mapSetOfTortoiseShell.erase(iter7);
								map<int, TortoiseShell*>::iterator iter07 = temp2.begin();
								double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
								// 如果kpi更优，则把解放入最优乌龟壳集合里，并把kpi值赋给best_kpi
								if (temp_kpi > best_kpi)
								{
									best_kpi = temp_kpi;
									// 插入未分配钢卷组的乌龟壳
									s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
									continue;
								}
								// 否则，继续迭代
								else
								{
									// 恢复选中的乌龟壳
									s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
									swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
									s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.clear();
									swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1_second);
									// 插入未分配钢卷组的乌龟壳
									s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
									continue;
								}
							}

						}
						// 如果m_temp1为空，说明则chosen乌龟壳的钢卷组放入another里，肯定符合所有的约束，所有判断结束，计算KPI
						else
						{
							// 计算所得解的KPI,首先要把未分配钢卷组的那个乌龟壳删掉，计算完KPI之后再把这个乌龟壳放入乌龟壳集合里
							map<int, TortoiseShell*> temp2;
							map<int, TortoiseShell*>::iterator iter7 = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
							temp2.insert(make_pair(iter7->first, iter7->second));
							s_mapSetOfTortoiseShell.erase(iter7);
							map<int, TortoiseShell*>::iterator iter07 = temp2.begin();
							double temp_kpi = computekpi(s_mapSetOfTortoiseShell);
							// 如果kpi更优，则把解放入最优乌龟壳集合里，并把kpi值赋给best_kpi
							if (temp_kpi > best_kpi)
							{
								best_kpi = temp_kpi;
								// 插入未分配钢卷组的乌龟壳
								s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
								continue;
							}
							// 否则，继续迭代
							else
							{
								// 恢复选中的乌龟壳
								s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups.clear();
								swap(s_mapSetOfTortoiseShell[Chosen_Shell]->m_main_groups, m_temp_second);
								s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups.clear();
								swap(s_mapSetOfTortoiseShell[Another_Shell]->m_main_groups, m_temp1_second);
								// 插入未分配钢卷组的乌龟壳
								s_mapSetOfTortoiseShell.insert(make_pair(iter07->first, iter07->second));
								continue;
							}
						}
						
					}
				
					#pragma endregion
				}
			}
		}
	}
	#pragma endregion
}
