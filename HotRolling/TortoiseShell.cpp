/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �ڹ����
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �ڹ����
/// <para>�洢�ڹ����Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "TortoiseShell.h"
#include "global.h"


#pragma region TortoiseShell��Ա����
//////////////////////////////////////////////////////////////////////////

#pragma region ��������
//////////////////////////////////////////////////////////////////////////

TortoiseShell::TortoiseShell(Group *group)
{
	// �ڹ�Ǹ���+1
	s_TortoiseShellCount++;
	// ��ʼ����������
	this->m_tortoiseShellName = s_TortoiseShellCount;
	this->m_TortoiseShell_len = 0;
	this->m_TortoiseShell_WT = 0;
	this->m_TortoiseShellflow10_WT = 0;
	this->m_TortoiseShell_DHCR = 0;
	this->m_TortoiseShell_len1 = 0;
	this->m_TortoiseShell_WT1 = 0;
	this->m_TortoiseShellflow10_WT1 = 0;
	this->m_TortoiseShell_DHCR1 = 0;
	this->m_TortoiseShell_len_temp = 0;
	this->m_tang_len = 0;
	this->m_startTime = 0;
	this->m_finishTime = 0;
	this->m_timeSpan = 0;
	// ��ʼ���ڹ���ڵĸ־���
	m_main_groups.insert(make_pair(make_pair(0, group->roll_len), group));
	
	// ��ʼ���ڹ���ڵĸ־���
	//m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, 1), group));
	//// ���Ÿ־�ļƻ�����
	//string	plan_type = group->plan_type;
	//// Ԥ���̹���(����һ���ڹ�Ǿͷ��̹���)
	//vector<Group*> tang_temp;
	//// ��һ���̹��ĵĿ��
	//double width = 0;
	//// �ܹ�Ԥ���̹��ĵĸ���
	//int num = 0;
	//for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	//{
	//	// ׼������ĸ־��鼰��ƻ�����
	//	Group* group2 = iter->second;
	//	string	plan_type2 = group2->plan_type;
	//	// ����̹��ļƻ��������ʼ���ڹ�ǵĸ־�ƻ����Ͳ���������������ϣ�������̹���
	//	map<pair<string, string>, string>::iterator iter2 = plantype.find(make_pair(plan_type, plan_type2));
	//	string type = iter2->second;
	//	if (type != "2" && type != "0"&& group2->nom_roll_width >= width)
	//	{
	//		width = group2->nom_roll_width;			
	//			 // ����ø־����ڸ־��������4����ֻ�ó�4�����̹��ģ�����ȫ�����̹���
	//			if (group2->m_SteelCoil.size() > 4)
	//			{
	//				int needCount = 4;
	//				// ����ܹ���Ҫ6���̹���
	//				if (6 - num < needCount)
	//					needCount = 6 - num;
	//				// ��Ԥ���̹�����������
	//				num += needCount;
	//				// �����µ�С�־���
	//				Group *group_temp = new Group(group2, needCount);
	//				tang_temp.push_back(group_temp);
	//			}
	//			else
	//			{
	//				int needCount = group2->m_SteelCoil.size();
	//				// ����ܹ���Ҫ6���̹���
	//				if (6 - num < needCount)
	//					needCount = 6 - num;
	//				// ��Ԥ���̹�����������
	//				num += needCount;
	//				// �����µ�С�־���
	//				Group *group_temp = new Group(group2, needCount);
	//				tang_temp.push_back(group_temp);
	//			}
	//	}
	//	if (num >= 6)
	//		break;
	//}
	//// ��Ԥ���̹��ķ��䵽����ڹ�ǵ�ǰ��
	//for (int i = 0; i < tang_temp.size(); i++)
	//{
	//	if (m_groups.empty())
	//		m_groups.insert(make_pair(make_pair(0, tang_temp[i]->roll_len), tang_temp[i]));
	//	else
	//		m_groups.insert(make_pair(make_pair(m_groups.rbegin()->first.second, m_groups.rbegin()->first.second + tang_temp[i]->roll_len), tang_temp[i]));
	//}
	//// �����ڹ��ʵʱ����
	//for (int i = 0; i < tang_temp.size(); i++)
	//{
	//	m_tang_len += tang_temp[i]->roll_len;
	//}
	//m_TortoiseShell_len_temp = m_tang_len + group->roll_len;

}
TortoiseShell::~TortoiseShell()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion


#pragma endregion

#pragma region �ڹ�Ǽƻ����
//////////////////////////////////////////////////////////////////////////
void TortoiseShell::InitShell()
{
	const double samewidth_limit = 500000.0;//ͬ����������
	const double tangwidth_limit = 100000.0;//ͬ����������
	try
	{
		Environment::Initialize();// ������ʼ��
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");// �������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);// �������ݼ�
		ostring rowid;
		st.Execute("select * from TIP00SI04");// ѡ���
		Resultset rs = st.GetResultset();
		// ��ȡ�ƻ�������Ϸ�ʽ
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

	#pragma region ������ʼ�ڹ��
	//////////////////////////////////////////////////////////////////////////
	// ������DHCR��Ǻ����̹��ı�ǵĸ־����map����
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// һ���־��鼰��ƻ�����
		Group* group = iter->second;
		string plan_type = group->plan_type;
		// ���������ڹ��
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// ����ڹ��
			TortoiseShell* tortoiseShell = iter2->second;
			// ����ڹ����ĵ�һ���־��鼰��ƻ�����
			Group* group2 = tortoiseShell->m_main_groups.begin()->second;
			string	plan_type2 = group2->plan_type;
			// �������ͬ����Ϸ�ʽ�����ò�����
			if (plan_type == plan_type2)
				break;
			// �����������ƻ����͵���Ϸ�ʽ
			map<pair<string, string>, string>::iterator iter3 = plantype.find(make_pair(plan_type, plan_type2));
			string type = iter3->second;
			// �����Ϸ�ʽ����"�ƻ��ڲ��������"����˸־�����Ժ͵�ǰ�ڹ����ϡ�
			if (type != "2")
				break;
		}
		// ��������������ڹ�ǣ����ֶ�������ϣ���ô���һ���µ��ڹ�ǣ����ҷ���ø־���
		if (iter2 == s_mapSetOfTortoiseShell.end())
		{
			// ����־����ڵĹ������������ͬ���������ƣ���ָ��С�־���
			if (group->roll_len >= samewidth_limit)
			{
				// ����С�־���
				Group *group_new = new Group(group, samewidth_limit);
				// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				//tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				//tortoiseShell->same_width_lonth = group_new->roll_len;
			}
			// ����ֱ�ӽ������־�����뵽�ڹ����
			else
			{
				// ����С�־���
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				//tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				//tortoiseShell->same_width_lonth = group_new->roll_len;
			}
		}
		// �����־���Ϊ�գ���ȫ������С�־��飬��ɾ��֮
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
		}
		// �����־��鲻Ϊ�գ���ָ����һ��
		else
			iter++;
	}
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion
}

void TortoiseShell::FinishShell()
{
	const double samewidth_limit = 500000.0;			// ͬ����������
	const double max_TortoiseShell_len = 50000;		// �ڹ��������ǣ����裩
#pragma region ������DHCR��Ǻ����̹��ı�ǵĸ־����map����
	//////////////////////////////////////////////////////////////////////////
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// ׼������ĸ־��鼰��ƻ�����
		Group* group = iter->second;
		string	plan_type = group->plan_type;
		// �����־���Ϊ�գ���ȫ������С�־��飬��ɾ��֮
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
			continue;
		}
		// ���������ڹ��
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// ����ڹ��
			TortoiseShell* tortoiseShell = iter2->second;
			// ���ͬ�������Ƿ����㣬�������㣬������ڹ�ǲ��ܷ�����־��飬�������һ���ڹ��
			if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end() && tortoiseShell->width_lonth.find(group->nom_roll_width)->second >= samewidth_limit)
				continue;
			// ���ø־�������룬��û�����ڳ�ͻ������У����ܷ�����ڹ��
			//Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group));
			// iter_nowָ��շ��룬���Ƚϵĸ־���
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_groups_temp.find(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_groups_temp.begin() && 
				(plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == "0" 
				|| (*iter_now->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				// �����һ��Լ�������㣬��ɾ���˸־��飬�����ô˸־��������һ���ڹ��
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}			
			if (iter_after != tortoiseShell->m_groups_temp.end() && 
				(plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second =="0"
				|| (*iter_after->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			tortoiseShell->m_groups_temp.erase(iter_now);
			// ������־����Ƿ�������¾���������������¾����������λ���䡣



			// �������ڹ������̹�����û�к͸־����ͻ������У�����ڹ�ǲ��ܷŴ˸־���
			map<pair<int, int>, Group*>::iterator iter5 = tortoiseShell->m_groups.begin();
			for (; iter5 != tortoiseShell->m_groups.end(); iter5++)
			{
				// �ڹ����ĸ־���
				Group *group2 = iter5->second;
				// ����־���ļƻ�����
				string	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == "2")
					break;
			}
			// �����û������ڹ��������һ���־���ʹ�����break����˵���г�ͻ��Ѱ����һ���ڹ�ǰ�
			if (iter5 != tortoiseShell->m_groups.end())
				continue;
			// ��������ڹ����ĸ־���(�����)
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups_temp.begin();
			for (; iter3 != tortoiseShell->m_groups_temp.end(); iter3++)
			{
				// �ڹ����ĸ־���Ŀ��
				int width = iter3->first.first;
				Group *group2 = iter3->second;
				// ����־���ļƻ�����
				string	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == "2")
					break;
			}
			// ���1��˳���Ĳ��ҵ�������ڹ��������һ���־���Ҳû����break����˵��׼������ĸ־�����Է��뱾�ڹ���У���ô�����
			if (iter3 == tortoiseShell->m_groups_temp.end())
			{
				if (tortoiseShell->m_TortoiseShell_len_temp >= max_TortoiseShell_len)
					continue;
				// ���������ȵĸ־���������ڹ���е������ܳ��ȣ����㼴�����������־��飩
				double lonth = 0;
				if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end())
					lonth = tortoiseShell->width_lonth.find(group->nom_roll_width)->second;
				// ����־����ڵĹ������������ͬ���������ƻ��ߴ����ڹ������������ƣ���ָ��С�־���
				if ((group->roll_len >= samewidth_limit - lonth) || (tortoiseShell->m_TortoiseShell_len_temp + group->roll_len > max_TortoiseShell_len))
				{
					double lenth = ((samewidth_limit - lonth) < (max_TortoiseShell_len - tortoiseShell->m_TortoiseShell_len_temp) ? (samewidth_limit - lonth) : (max_TortoiseShell_len - tortoiseShell->m_TortoiseShell_len_temp));
					// ����С�־���
					Group *group_new = new Group(group, lenth);
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}										
						// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
						tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group_new->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
						// �����ڹ��ʵʱ����
						tortoiseShell->m_TortoiseShell_len_temp += group_new->roll_len;
						// �����ڹ���и־����ͬ������
						if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
							tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
						else
							tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;										
				}			
				// ����ֱ�ӽ������־�����뵽�ڹ����
				else
				{
					// ����С�վ���
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}					
						// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
						tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group_new->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
						// �����ڹ��ʵʱ����
						tortoiseShell->m_TortoiseShell_len_temp += group_new->roll_len;
						// �����ڹ���и־����ͬ������
						if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
							tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
						else
							tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				}				
				// �����ڹ�Ǳ������ص�׼������ĸ־���ı���
				break;
			}
		}
		// ��������������ڹ�ǣ����ֶ�������ϣ���ô���һ���µ��ڹ�ǣ����ҷ���ø־���
		if (iter2 == s_mapSetOfTortoiseShell.end())
		{
			// ����־����ڵĹ������������ͬ���������ƣ���ָ��С�־���
			if (group->roll_len >= samewidth_limit)
			{
				// ����С�־���
				Group *group_new = new Group(group, samewidth_limit);
				// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
			// ����ֱ�ӽ������־�����뵽�ڹ����
			else
			{
				// ����С�־���
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
		}
		// �����־���Ϊ�գ���ȫ������С�־��飬��ɾ��֮
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
		}
	}
	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region �������̹��ı�ǵĸ־����map����
	//////////////////////////////////////////////////////////////////////////
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end();)
	{
		// ׼������ĸ־��鼰��ƻ�����
		Group* group = iter->second;
		string	plan_type = group->plan_type;
		// �����־���Ϊ�գ���ȫ������С�־��飬��ɾ��֮
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup1.erase(iter);
			continue;
		}
		// ���������ڹ��
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// ����ڹ��
			TortoiseShell* tortoiseShell = iter2->second;
			// ���ͬ�������Ƿ����㣬�������㣬������ڹ�ǲ��ܷ�����־���
			if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end() && tortoiseShell->width_lonth.find(group->nom_roll_width)->second >= samewidth_limit)
				continue;
			// ���ø־�������룬��û�����ڳ�ͻ������У����ܷ�����ڹ��
			//Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group));
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_groups_temp.find(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_groups_temp.begin() &&
				(plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == "0"
				|| (*iter_now->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_before->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_before->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_now->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_before->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			if (iter_after != tortoiseShell->m_groups_temp.end() &&
				(plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second == "0"
				|| (*iter_after->second->m_SteelCoil.begin())->nom_roll_thick - (*iter_now->second->m_SteelCoil.rbegin())->nom_roll_thick > (*iter_now->second->m_SteelCoil.begin())->thick_forward_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_heat_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_heat_temp) > (*iter_now->second->m_SteelCoil.begin())->heat_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_afft_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_afft_temp) > (*iter_now->second->m_SteelCoil.begin())->afft_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_coil_temp - (*iter_now->second->m_SteelCoil.rbegin())->nom_coil_temp) > (*iter_now->second->m_SteelCoil.begin())->coil_temp_jump_max
				|| abs((*iter_after->second->m_SteelCoil.begin())->nom_hard_group_code[0] - (*iter_now->second->m_SteelCoil.rbegin())->nom_hard_group_code[0]) > (*iter_now->second->m_SteelCoil.begin())->hard_group_jump_max
				))
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			tortoiseShell->m_groups_temp.erase(iter_now);
			// �������ڹ������̹�����û�к͸־����ͻ������У�����ڹ�ǲ��ܷŴ˸־���
			map<pair<int, int>, Group*>::iterator iter5 = tortoiseShell->m_groups.begin();
			for (; iter5 != tortoiseShell->m_groups.end(); iter5++)
			{
				// �ڹ����ĸ־���
				Group *group2 = iter5->second;
				// ����־���ļƻ�����
				string	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == "2")
					break;
			}
			// �����û������ڹ��������һ���־���ʹ�����break����˵���г�ͻ��Ѱ����һ���ڹ�ǰ�
			if (iter5 != tortoiseShell->m_groups.end())
				continue;
			// ��������ڹ����ĸ־���
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups_temp.begin();
			for (; iter3 != tortoiseShell->m_groups_temp.end(); iter3++)
			{
				// �ڹ����ĸ־���Ŀ��
				int width = iter3->first.first;
				Group *group2 = iter3->second;
				// ����־���ļƻ�����
				string plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<string, string>, string>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				string type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == "2")
					break;
			}
			// ���1��˳���Ĳ��ҵ�������ڹ��������һ���־���Ҳû����break����˵��׼������ĸ־�����Է��뱾�ڹ���У���ô�����
			if (iter3 == tortoiseShell->m_groups_temp.end())
			{
				if (tortoiseShell->m_TortoiseShell_len_temp >= max_TortoiseShell_len)
					continue;
				// ���������ȵĸ־���������ڹ���е������ܳ��ȣ����㼴�����������־��飩
				double lonth = 0;
				if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end())
					lonth = tortoiseShell->width_lonth.find(group->nom_roll_width)->second;
				// ����־����ڵĹ������������ͬ���������ƻ��ߴ����ڹ������������ƣ���ָ��С�־���
				if ((group->roll_len >= samewidth_limit - lonth) || (tortoiseShell->m_TortoiseShell_len_temp + group->roll_len > max_TortoiseShell_len))
				{
					double lenth = ((samewidth_limit - lonth) < (max_TortoiseShell_len - tortoiseShell->m_TortoiseShell_len_temp) ? (samewidth_limit - lonth) : (max_TortoiseShell_len - tortoiseShell->m_TortoiseShell_len_temp));
					// ����С�־���
					Group *group_new = new Group(group, lenth);
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
					// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group_new->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// �����ڹ��ʵʱ����
					tortoiseShell->m_TortoiseShell_len_temp += group_new->roll_len;
					// �����ڹ���и־����ͬ������
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				}
					
				// ����ֱ�ӽ������־�����뵽�ڹ����
				else
				{
					// ����С�վ���
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
					// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group_new->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// �����ڹ��ʵʱ����
					tortoiseShell->m_TortoiseShell_len_temp += group_new->roll_len;
					// �����ڹ���и־����ͬ������
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;					
				}				
				// �����ڹ�Ǳ������ص�׼������ĸ־���ı���
				break;
			}
		}
		// ��������������ڹ�ǣ����ֶ�������ϣ���ô���һ���µ��ڹ�ǣ����ҷ���ø־���
		if (iter2 == s_mapSetOfTortoiseShell.end())
		{
			// ����־����ڵĹ������������ͬ���������ƣ���ָ��С�־���
			if (group->roll_len >= samewidth_limit)
			{
				// ����С�־���
				Group *group_new = new Group(group, samewidth_limit);
				// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
			// ����ֱ�ӽ������־�����뵽�ڹ����
			else
			{
				// ����С�־���
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
				if (group_new->m_SteelCoil.empty())
				{
					Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
					delete group_new;
					continue;
				}
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
					tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
				else
					tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
			}
		}
		// �����־���Ϊ�գ���ȫ������С�־��飬��ɾ��֮
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup1.erase(iter);
		}
	}
	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region ���տ�ȷ���λ��
	//////////////////////////////////////////////////////////////////////////
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// ����������䵽�ڹ���У�����δ�������λ�õĸ־���
		for (map<pair<int, int>, Group*>::reverse_iterator iter2 = tortoiseShell->m_groups_temp.rbegin(); iter2 != tortoiseShell->m_groups_temp.rend(); iter2++)
		{
			Group *group = iter2->second;
			// ��һ���־�������ĩλ��
			int end_located = 0;
			if (!tortoiseShell->m_groups.empty())// ��Ϊ�� ִ��
				end_located = tortoiseShell->m_groups.rbegin()->first.second;
			tortoiseShell->m_groups.insert(make_pair(make_pair(end_located, end_located + group->roll_len), group));
		}
		tortoiseShell->m_groups_temp.clear();
	}
	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region �ڹ�Ǽ���
	//////////////////////////////////////////////////////////////////////////
	// �����Ѿ����ɵ��ڹ�Ǽ���ÿ���ڹ�����и־���������ĳ����־�����������DHCR��ǵĸ־��������ڹ���ܳ���
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �����ڹ���ڵĸ־�����Ϣ
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// �����־����ڸ־���Ϣ
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
	// ���������ڹ�����и־���������ĳ����־�����������DHCR��ǵĸ־��������ڹ���ܳ���
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		allTortoiseShell_len += (*iter).second->m_TortoiseShell_len;
		allsteelcCoil_wt += (*iter).second->m_TortoiseShell_WT;
		allflow10_wt += (*iter).second->m_TortoiseShellflow10_WT;
		m_DHCR += (*iter).second->m_TortoiseShell_DHCR;		
	}
}
//////////////////////////////////////////////////////////////////////////
#pragma endregion

//void TortoiseShell::DeleteBad()
//{
////#pragma region �����Ѿ����ɵ��ڹ�Ǽ���ÿ���ڹ�ǵĳ���
//////////////////////////////////////////////////////////////////////////////
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		// �����ڹ���ڵĸ־�����Ϣ
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
//		{
//			Group *group = iter2->second;
//			// �����־����ڸ־���Ϣ
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
//			{
//				SteelCoil *steelCoil = *iter3;
//				tortoiseShell->m_TortoiseShell_len += steelCoil->roll_len;
//			}
//		}
//
//	}
//////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//
//#pragma region �����Ѿ����ɵ��ڹ�ǣ�����������¶ο�����Χ�����¶ο�����Χ�ĸ־����·���δ����־����С�
////////////////////////////////////////////////////////////////////////////
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		int high_num = 0;// ���¾����
//		int high_temp_coil_num = 0;// ��θ��¾�ĸ־���
//		int low_temp_coil_num = 0;// ��ε��¾�ĸ־���
//		int coil_flag = 0;// 0Ϊ���¾�1Ϊ���¾�
//		// �����ڹ���ڵĸ־�����Ϣ
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
//		{
//			Group *group = iter2->second;
//			// �����־����ڸ־���Ϣ
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); )
//			{
//				SteelCoil *steelCoil = *iter3;
//				// �����һ���ǵ��¾�
//				if (coil_flag == 0)
//				{
//					// �����ǰ�ǵ��¾�
//					if (steelCoil->high_temp_flag == "0")
//					{
//						low_temp_coil_num++;
//						if (low_temp_coil_num > steelCoil->max_low_temp_coil_num)
//						{
//							low_temp_coil_num--;
//							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//							iter3 = group->m_SteelCoil.erase(iter3);
//							continue;
//						}
//						iter3++;
//					}
//					// �����ǰ�Ǹ��¾�
//					else
//					{
//						high_num++;
//						if (high_num > 3)
//						{
//							high_num--;
//							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//							iter3 = group->m_SteelCoil.erase(iter3);
//							continue;
//						}
//						low_temp_coil_num = 0;
//						high_temp_coil_num++;
//						coil_flag = 1;
//						iter3++;
//					}
//				}
//				// �����һ���Ǹ��¾�
//				else
//				{
//					// �����ǰ�ǵ��¾�
//					if (steelCoil->high_temp_flag == "0")
//					{
//						high_temp_coil_num = 0;
//						low_temp_coil_num++;
//						coil_flag = 0;
//						iter3++;
//					}
//					// �����ǰ�Ǹ��¾�
//					else
//					{
//						high_temp_coil_num++;
//						if (high_temp_coil_num > steelCoil->max_high_temp_coil_num)
//						{
//							high_temp_coil_num--;
//							tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//							SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//							iter3 = group->m_SteelCoil.erase(iter3);
//							continue;
//						}
//						iter3++;
//					}
//				}
//			}
//		}
//	}
////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//
//#pragma region �����Ѿ����ɵ��ڹ�ǣ�������������λ���䷶Χ�ĸ־����·���δ����־����С�
//	//////////////////////////////////////////////////////////////////////////
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		int lonth = 0;				// �־��ۼ�λ��
//		double del_lonth = 0;		// ɾ���ĸ־���	
//		// �����ڹ���ڵĸ־�����Ϣ
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end();)
//		{
//			Group *group = iter2->second;
//			// �����־����ڸ־���Ϣ
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end();)
//			{
//				SteelCoil *steelCoil = *iter3;
//				if (lonth > steelCoil->zone_min_m)
//				{
//					tortoiseShell->m_TortoiseShell_len -= steelCoil->roll_len;
//					SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//					iter3 = group->m_SteelCoil.erase(iter3);
//					group->roll_len -= steelCoil->roll_len;
//					del_lonth += steelCoil->roll_len;
//				}
//				else
//				{
//					lonth += steelCoil->roll_len;
//					iter3++;
//				}
//			}
//		}
//	}
//			//// ���ɾ���˸־�����¸־���ļ�ֵ������λ�ã�
//	//		if (del_lonth != 0)
//	//		{
//	//			if (iter2 != tortoiseShell->m_groups.begin())
//	//			{
//	//				map<pair<int, int>, Group*> temp;
//	//				temp.insert(make_pair(make_pair((iter2--)->first.second, iter2->first.second - del_lonth), group));
//	//				iter2=tortoiseShell->m_groups.erase(iter2);
//	//				map<pair<int, int>, Group*>::iterator iter4 = temp.begin();
//	//				tortoiseShell->m_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
//	//				temp.clear();
//	//			}
//	//			else
//	//			{
//	//				map<pair<int, int>, Group*> temp;
//	//				temp.insert(make_pair(make_pair(iter2->first.first, iter2->first.second - del_lonth), group));
//	//				iter2 = tortoiseShell->m_groups.erase(iter2);
//	//				map<pair<int, int>, Group*>::iterator iter4 = temp.begin();
//	//				tortoiseShell->m_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
//	//				temp.clear();
//	//			}
//
//	//		}
//	//		// ���ûɾ���־�ҲҪ������һ���־���ļ����Ĵ˸־���ļ�
//	//		else if (iter2 != tortoiseShell->m_groups.begin())
//	//		{
//	//			map<pair<int, int>, Group*> temp;
//	//			temp.insert(make_pair(make_pair((iter2--)->first.second, (iter2--)->first.second + group->roll_len), group));
//	//			iter2 = tortoiseShell->m_groups.erase(iter2);
//	//			map<pair<int, int>, Group*>::iterator iter4 = temp.begin();
//	//			tortoiseShell->m_groups.insert(make_pair(make_pair(iter4->first.first, iter4->first.second), iter4->second));
//	//			temp.clear();
//	//		}
//	//		else
//	//			continue;
//		
//	
////////////////////////////////////////////////////////////////////////////
//#pragma endregion
//
////#pragma region �����Ѿ����ɵ��ڹ�ǣ��������̫�̣���ɾ�������ڹ��
////	//////////////////////////////////////////////////////////////////////////
//	
//	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); )
//	{
//		TortoiseShell *tortoiseShell = iter->second;
//		if (tortoiseShell->m_TortoiseShell_len > 5000)
//		{
//			iter++;
//			continue;
//		}
//		// �����ڹ���ڵĸ־�����Ϣ
//		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end();)
//		{
//			Group *group = iter2->second;
//			// �����־����ڸ־���Ϣ
//			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end();)
//			{
//				SteelCoil *steelCoil = *iter3;
//				SteelCoil::s_least.insert(make_pair(steelCoil->mat_no, steelCoil));
//				iter3 = group->m_SteelCoil.erase(iter3);
//			}
//			iter2 = tortoiseShell->m_groups.erase(iter2);
//		}
//		iter = s_mapSetOfTortoiseShell.erase(iter);
//		s_TortoiseShellCount--;
//	}
//////////////////////////////////////////////////////////////////////////////
////#pragma endregion
////}
//
////void TortoiseShell::ReFinishShell()
////{
////#pragma region ����δ����ĸ־�
////	//////////////////////////////////////////////////////////////////////////
////	for (map<string, SteelCoil*>::iterator iter = SteelCoil::s_least.begin(); iter != SteelCoil::s_least.end(); iter++)
////	{
////		SteelCoil *steelCoil = iter->second;
////		// �����Ѿ����ɵ��ڹ��
////		for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
////		{
////			TortoiseShell *tortoiseShell = iter2->second;
////			// �����ڹ���ڵĸ־�����Ϣ
////			for (map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups.begin(); iter3 != (--tortoiseShell->m_groups.end()); iter3++)
////			{
////				Group *group1 = iter3->second;
////				iter3++;
////				Group *group2 = iter3->second;
////				iter3--;
////				// ���Ҫ����ĸ־���С�ڵ���group1�ĸ־��Ҵ���group2�ĸ־�
////				// ���Ը���ͬ��Χ������������Χ�����¶ο�����Χ�����¶ο�����Χ������λ���䷶Χ�Ƿ��������жϸø־�ɷ񱻷��䵽���λ��(�����߼�������Ĵ������д��)
////				// ������ԣ�����(ͬʱ����break)����������ԣ�������һ���ڹ��(break)��
////			}
////		}
////	}
////	//////////////////////////////////////////////////////////////////////////
////#pragma endregion
//}

void TortoiseShell::computekpi()
{
	const double max_TortoiseShell_len = 50000;// �ڹ���������
	double flow10_wt = 0;
	double assigned_wt = 0;
	double assigned_DHCR = 0;
	double flow_rate=0;
	double DHCR_rate=0;
	double order_rate=0;
	double rollingkm_rate=0;
	double rollingkm=0;
	
	// �����ź��ڹ�ǵ����и־���������ĳ����־�����������DHCR��ǵĸ־��������ڹ���ܳ���
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �����ڹ���ڵĸ־�����Ϣ
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// �����־����ڸ־���Ϣ
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
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		rollingkm += tortoiseShell->m_TortoiseShell_len1;
		assigned_wt += tortoiseShell->m_TortoiseShell_WT1;
		flow10_wt += tortoiseShell->m_TortoiseShellflow10_WT1;
		assigned_DHCR += tortoiseShell->m_TortoiseShell_DHCR1;
	}	
	flow_rate = flow10_wt / allflow10_wt;																// ����ƥ����
	order_rate = assigned_wt / allsteelcCoil_wt;														// ��ͬ�ƻ�������
	rollingkm_rate = (rollingkm / s_mapSetOfTortoiseShell.size()) / max_TortoiseShell_len;				// ���ƹ�����
	DHCR_rate = assigned_DHCR / m_DHCR;																	// DHCR����
	cout << flow_rate << "   " << order_rate << "    " << rollingkm_rate << "   " << DHCR_rate << endl;

}

void TortoiseShell::showResult()
{
	int i = 0;
	cout << "�ڹ��������  " << s_TortoiseShellCount << endl;
	// �����ʱ�ڹ�ǵı�š����ڹ����ĸ־����ź͸־�����־�ĸ־��
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_groups.begin(); iter3 != (*iter2).second->m_groups.end(); iter3++)
		{
			for (vector<SteelCoil*>::iterator iter4 = (*iter3).second->m_SteelCoil.begin(); iter4 != (*iter3).second->m_SteelCoil.end(); iter4++)
			{
				
				i++;
				cout << iter2->first << "	" << iter3->second->group_no << "	" << (*iter4)->mat_no << "    "<<(*iter4)->nom_roll_width<<endl;
			}
		}
	}
	cout << "�־�������   "<<i << endl;// �վ���
	cout << "С�վ���������	" << Group::s_mapSetOfsmallGroup.size() << endl;
	cout << endl << endl;
	// ÿ���־���ʣ�µĸվ���
	cout << "ÿ���־���ʣ�µĸվ����� " << endl;
	for (map<int, Group*> ::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end(); iter++)
	{
		cout << iter->first << "       ";
		cout << iter->second->m_SteelCoil.size() << endl;
	}
	cout << endl;
	for (map<int, Group*> ::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	{
		cout << iter->first << "      ";
		cout << iter->second->m_SteelCoil.size() << endl;
	}

	cout << endl;
	cout << "s_mapSetOfGroup�����ﻹʣ " << Group::s_mapSetOfGroup.size() << " ���־���" << endl;
	cout << endl;
	cout << "s_mapSetOfGroup1�����ﻹʣ " << Group::s_mapSetOfGroup1.size() << " ���־���" << endl;
	cout << endl << endl;
}

void TortoiseShell::showResultFile()
{
	string filename_result = "result.csv";
	ofstream fout(filename_result);
	fout << "�־��," << "����," << "�ж�ʱ��," << "�������," << "�ƻ�����," << "����ƺ��," << "����ƿ��," << "���¯�¶�," << "������¶�," << "���ȡ�¶�," << "�ƻ���" << endl;
	// �����ڹ��
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		// �ڹ��
		TortoiseShell *tortoiseShell = iter->second;
		int tortoiseShellNo = iter->first;
		fout << tortoiseShellNo << endl;
		// �����ڹ���ڵĸ־���
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			// �־���
			Group *group = iter2->second;
			// �����������ڵĸ־�
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			{
				// �־�
				SteelCoil *steelCoil = *iter3;
				string	mat_no = steelCoil->mat_no;						// �־��
				string	flow = steelCoil->flow;							// ����
				string	fin_cut_time = steelCoil->fin_cut_time;				// �ж�ʱ��
				//bool		must_do_flag = steelCoil->must_do_flag;				// �������
				bool		must_do_flag = 0;				// �������
				string	plan_type = steelCoil->plan_type;					// �ƻ�����
				double	nom_roll_thick = steelCoil->nom_roll_thick;			// ����ƺ��
				double	nom_roll_width = steelCoil->nom_roll_width;			// ����ƿ��
				int		nom_heat_temp = steelCoil->nom_heat_temp;			// ���¯�¶�
				int		nom_afft_temp = steelCoil->nom_afft_temp;			// ������¶�
				int		nom_coil_temp = steelCoil->nom_coil_temp;			// ���ȡ�¶�
				string	plan_no = steelCoil->plan_no;						// �ƻ���
				fout << mat_no << "," << flow << "," << fin_cut_time << "," << (int)must_do_flag << "," << plan_type << "," << nom_roll_thick << "," << nom_roll_width << "," << nom_heat_temp << "," << nom_afft_temp << "," << nom_coil_temp << "," << plan_no << endl;
			}
		}
	}
}

void TortoiseShell::addMainGroup(Group *group)
{
	int begin_len = 0;
	if (!m_main_groups.empty())
		begin_len = m_main_groups.rbegin()->first.second;
	m_main_groups.insert(make_pair(make_pair(begin_len, begin_len + group->roll_len), group));
	m_TortoiseShell_len += group->roll_len;
	m_TortoiseShell_WT += group->slab_wt;

}



////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group��̬����
//////////////////////////////////////////////////////////////////////////
map<int, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<int, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
double						TortoiseShell::allTortoiseShell_len = 0;
double						TortoiseShell::m_DHCR = 0;
double						TortoiseShell::allflow10_wt = 0;
double						TortoiseShell::allsteelcCoil_wt = 0;
map<pair<string, string>, string>		TortoiseShell::plantype = map<pair<string, string>, string>();
////////////////////////////////////////////////////////////////////////
#pragma endregion