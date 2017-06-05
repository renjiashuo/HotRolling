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
#include "Group.h"
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
	//this->m_TortoiseShellflow10_WT = 0;
	this->m_TortoiseShell_DHCR = 0;
	this->m_TortoiseShell_len1 = 0;
	this->m_TortoiseShell_WT1 = 0;
	this->m_TortoiseShellflow10_WT1 = 0;
	this->m_TortoiseShell_DHCR1 = 0;
	this->penalty = 0;
	
	//this->m_tang_len = 0;
	// �ų̹����м�¼�ı���
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
	// ��ʼ���ڹ���ڵĸ־���
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
	#pragma region �����־����map����
	//////////////////////////////////////////////////////////////////////////
	const double samewidth_limit = 500000.0;			// ͬ����������
	const double max_TortoiseShell_len = 50000;		// �ڹ���������裩	
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
			// ���ø־�������룬��û�����ڳ�ͻ������У����ܷ�����ڹ��
			//map<pair<int, int>, Group*>::reverse_iterator riter = tortoiseShell->m_main_groups.rbegin();
			tortoiseShell->m_main_groups.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_main_groups.size() + 1), group));
			// iter_nowָ��շ��룬���Ƚϵĸ־���
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
				// �����һ��Լ�������㣬��ɾ���˸־��飬�����ô˸־��������һ���ڹ��
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
			// ����������������������������˸־���ɾ��������������ж�
			tortoiseShell->m_main_groups.erase(iter_now);			
			// ��������ڹ����ĸ־���(�����)
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_main_groups.begin();
			for (; iter3 != tortoiseShell->m_main_groups.end(); iter3++)
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
			if (iter3 == tortoiseShell->m_main_groups.end())
			{
				// �����ڹ��
				bool mark = tortoiseShell->addMainGroup(group);
				// �������ɹ��������ڹ�Ǳ������ص�׼������ĸ־���ı���
				if (mark)
					break;
				else continue;
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

	#pragma region �ڹ�Ǽ���
	//////////////////////////////////////////////////////////////////////////
	// �����Ѿ����ɵ��ڹ�Ǽ���ÿ���ڹ�����и־���������ĳ����־�����������DHCR��ǵĸ־��������ڹ���ܳ���
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �����ڹ���ڵĸ־�����Ϣ
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// �����־����ڸ־���Ϣ
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
	// ���������ڹ�����и־���������ĳ����־�����������DHCR��ǵĸ־��������ڹ���ܳ���
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
	#pragma region �����Ѿ����ɵ��ڹ�ǣ��������̫�̣���ɾ�������ڹ��
	//////////////////////////////////////////////////////////////////////////
	
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); )
	{
		TortoiseShell *tortoiseShell = iter->second;
		if (tortoiseShell->m_TortoiseShell_len > 5000)
		{
			iter++;
			continue;
		}
		// �����ڹ���ڵĸ־�����Ϣ
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end();)
		{
			Group *group = iter2->second;
			// ��ɾ���ĸ־������map������
			Group::s_least.insert(make_pair(Group::s_least.size()+1, group));			
			iter2 = tortoiseShell->m_main_groups.erase(iter2);
		}		
		iter = s_mapSetOfTortoiseShell.erase(iter);		
		s_TortoiseShellCount--;
	}
	// ɾ���ڹ��֮�󣬸����ڹ�Ǵ���
	map<int, TortoiseShell*> temp;
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		temp.insert(make_pair(temp.size() + 1, iter->second));
	}
	swap(s_mapSetOfTortoiseShell, temp);
	
	// ����ʼ���kpi��������kpi����
	best_kpi = computekpi(s_mapSetOfTortoiseShell);	
	// �����µ��ڹ�ǣ���ɾ���־������
	TortoiseShell *tortoiseShell = new TortoiseShell();
	for (map<int, Group*>::iterator iter3 = Group::s_least.begin(); iter3 != Group::s_least.end(); iter3++)
	{
		Group *group = iter3->second;
		// ��һ���־�������ĩλ��
		int end_located = 0;
		if (!tortoiseShell->m_main_groups.empty())// ��Ϊ�� ִ��
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
	cout << "�ڹ��������  " << s_TortoiseShellCount << endl;
	map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.find(s_mapSetOfTortoiseShell.size());
	s_mapSetOfTortoiseShell.erase(iter);
	// �����ʱ�ڹ�ǵı�š����ڹ����ĸ־����ź͸־�����־�ĸ־��
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
	cout << "�־�������   "<<i << endl;// �վ���
	cout << "С�վ���������	" << Group::s_mapSetOfsmallGroup.size() << endl;
	cout << endl;
	cout << "s_mapSetOfGroup�����ﻹʣ " << Group::s_mapSetOfGroup.size() << " ���־���" << endl<<endl;
	cout << "KPI=" << best_kpi << endl;
}

void TortoiseShell::showResultFile()
{
	string filename_result = "result.csv";
	ofstream fout(filename_result);
	fout << "�־��," << "����," << "�ж�ʱ��," << "�������," << "�ƻ�����," << "����ƺ��," << "����ƿ��," << "���¯�¶�," << "������¶�," << "���ȡ�¶�," << "�ƻ���," << "���±��" << endl;
	// �����ڹ��
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		// �ڹ��
		TortoiseShell *tortoiseShell = iter->second;
		int tortoiseShellNo = iter->first;
		fout << tortoiseShellNo << endl;
		// �����ڹ���ڵĸ־���
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
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
				string  high_temp_flag = steelCoil->high_temp_flag;			// ���±��
				fout << mat_no << "," << flow << "," << fin_cut_time << "," << (int)must_do_flag << "," << plan_type << "," << nom_roll_thick << "," << nom_roll_width << "," << nom_heat_temp << "," << nom_afft_temp << "," << nom_coil_temp << "," << plan_no << "," << high_temp_flag << endl;
			}
		}
	}
}

void TortoiseShell::showResultSQL()
{
	try
	{
		Environment::Initialize();// ������ʼ��
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");// �������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);// �������ݼ�
		ostring rowid;
		st.Execute("Delete from TIPHR25 where 1=1");// ɾ��������������
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
					// ģ���ʴ���
					string str_MOD_STAMP_NO = "1";
					// Ӧ�����κ�
					int int_IPS_LOT_NO = (int)steelCoil->roll_end_time_double / (24 * 60);
					char char_IPS_LOT_NO[10];
					sprintf(char_IPS_LOT_NO, "%d", int_IPS_LOT_NO);
					string str_IPS_LOT_NO = char_IPS_LOT_NO;
					// �ƻ���
					char char_PLAN_NO[10];
					sprintf(char_PLAN_NO, "%d", tortoiseShellNo);
					string str_PLAN_NO = char_PLAN_NO;
					// ���Ϻ�
					string str_MAT_NO = steelCoil->mat_no;
					// �ƻ�ִ��˳���
					string str_PLAN_EXEC_SEQ_NO = str_PLAN_NO;
					// �ƻ��������
					string str_PLAN_BACKLOG_CODE = steelCoil->next_whole_backlog_code;
					// ����˳���
					int int_ROLL_SEQ_NO = seqNo++;
					char char_ROLL_SEQ_NO[10];
					sprintf(char_ROLL_SEQ_NO, "%d", int_ROLL_SEQ_NO);
					string str_ROLL_SEQ_NO = char_ROLL_SEQ_NO;
					// �ƻ���ʼʱ��
					int int_PLAN_START_TIME = steelCoil->roll_begin_time_double * 60;
					string str_PLAN_START_TIME = DatetimeToString(int_PLAN_START_TIME + tNow);
					// ��������
					string str_WORK_TYPE = steelCoil->work_type;
					// ���ݿ�������
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
	// ��ȡ�����ƻ�ģ�����������趨��
	try
	{
		Environment::Initialize();// ������ʼ��
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");// �������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);// �������ݼ�
		ostring rowid;
		st.Execute("select * from TIPHR22");// ѡ���
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
	// ��������
	const double max_TortoiseShell_len = 30000;// �ڹ���������
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
	int THICK_FORWARD_penalty = 700;		// �����������
	int THICK_BACKWARD_penalty = 600;		// ��ȷ�������
	int HARD_JUMP_panalty = 600;			// Ӳ����Ծ�����
	int WIDTH_FORWARD_penalty = 700;		// �����������
	int WIDTH_BACKWARD_penalty = 600;		// ��ȷ�������
	int HEAT_TEMP_JUMP_penalty = 600;		// ��¯�¶���Ծ�����
	int AFFT_TEMP_JUMP_penalty = 700;		// �����¶���Ծ�����	
	int COIL_TEMP_JUMP_penalty = 700;		// ��ȡ�¶���Ծ�����
	double Scheduling_quality_deno = 18000;	// �����ų������ķ�ĸ
	double all_penalty = 0;	
	double flowrateall = 0;
	// ��������ƥ����
	for (int i = 1; i <= actualflow.size() / 2; i++)
	{
		double flowrate = (actualflow.find(make_pair(i, "10"))->second / flowrule.find(make_pair(i, "10"))->second + actualflow.find(make_pair(i, "11"))->second / flowrule.find(make_pair(i, "11"))->second) / 2;
		flowrateall += flowrate;
	}
	// �����ź��ڹ�ǵ����и־���������ĳ����־�����������DHCR��ǵĸ־��������ڹ���ܳ���
	for (map<int, TortoiseShell*>::iterator iter = NEW_TortoiseShell.begin(); iter != NEW_TortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �����ڹ���ڵĸ־�����Ϣ
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// �����־����ڸ־���Ϣ
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
	// ����
	if (assigned_wt > allsteelcCoil_wt)
		system("pause");
	//////////////////////////////////////////////////////////////////////////

	// ���㷣�֣���KPI�е��ų�����.�ȱ��������ڹ��
	for (map<int, TortoiseShell*>::iterator iter = NEW_TortoiseShell.begin(); iter != NEW_TortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �����ڹ���ڵĸ־�����Ϣ
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			map<pair<int, int>, Group*>::iterator iter_after = iter2;
			iter_after++;
			if (iter_after != tortoiseShell->m_main_groups.end())
			{
				// ��ȷ���
				if (iter_after->second->nom_roll_thick > iter2->second->nom_roll_thick)// ����
				{
					if (iter2->second->nom_roll_thick*0.5 < (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) && (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) < iter2->second->nom_roll_thick*0.8)
						tortoiseShell->penalty += 0.5*THICK_BACKWARD_penalty;
					else if (iter2->second->nom_roll_thick*0.8 < (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) && (iter_after->second->nom_roll_thick - iter2->second->nom_roll_thick) < iter2->second->nom_roll_thick)
						tortoiseShell->penalty += THICK_BACKWARD_penalty;
				}
				else if (iter_after->second->nom_roll_thick < iter2->second->nom_roll_thick)// ����
				{
					if (iter2->second->nom_roll_thick*0.5 < (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick) && (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick)< iter2->second->nom_roll_thick*0.8)
						tortoiseShell->penalty += 0.5*THICK_FORWARD_penalty;
					else if (iter2->second->nom_roll_thick*0.8 < (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick) && (iter2->second->nom_roll_thick - iter_after->second->nom_roll_thick) < iter2->second->nom_roll_thick)
						tortoiseShell->penalty += THICK_FORWARD_penalty;
				}
				else
					continue;
				// ��ȷ���
				if (iter_after->second->nom_roll_width > iter2->second->nom_roll_width)// ����
				{
					if (1< (iter_after->second->nom_roll_width - iter2->second->nom_roll_width) && (iter_after->second->nom_roll_width - iter2->second->nom_roll_width)< 50)
						tortoiseShell->penalty += 0.5*WIDTH_BACKWARD_penalty;
					else if (50 < (iter_after->second->nom_roll_width - iter2->second->nom_roll_width) && (iter_after->second->nom_roll_width - iter2->second->nom_roll_width) < 100)
						tortoiseShell->penalty += WIDTH_BACKWARD_penalty;
				}
				else if (iter_after->second->nom_roll_width < iter2->second->nom_roll_width)// ����
				{
					if (50 < (iter2->second->nom_roll_width - iter_after->second->nom_roll_width) && (iter2->second->nom_roll_width - iter_after->second->nom_roll_width) < 100)
						tortoiseShell->penalty += 0.5*WIDTH_FORWARD_penalty;
					else if (100< (iter2->second->nom_roll_width - iter_after->second->nom_roll_width) && (iter2->second->nom_roll_width - iter_after->second->nom_roll_width)< 300)
						tortoiseShell->penalty += WIDTH_FORWARD_penalty;
				}
				else
					continue;
				// Ӳ�ȹ����
				if (abs(iter_after->second->nom_hard_group_code[0] - iter2->second->nom_hard_group_code[0])==1)
					tortoiseShell->penalty += 0.5*HARD_JUMP_panalty;
				else if (abs(iter_after->second->nom_hard_group_code[0] - iter2->second->nom_hard_group_code[0]) == 2 || abs(iter_after->second->nom_hard_group_code[0] - iter2->second->nom_hard_group_code[0]) == 3)
					tortoiseShell->penalty += HARD_JUMP_panalty;				
				// ��¯�¶ȹ����
				if (5 < abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) && abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) < 10)
					tortoiseShell->penalty += 0.5*HEAT_TEMP_JUMP_penalty;
				else if (10 < abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) && abs(iter_after->second->nom_heat_temp - iter2->second->nom_heat_temp) < 99)
					tortoiseShell->penalty += HEAT_TEMP_JUMP_penalty;
				else
					continue;				
				// �����¶ȹ����
				if (5 < abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp) && abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp)< 10)
					tortoiseShell->penalty += 0.5*AFFT_TEMP_JUMP_penalty;
				else if (10 < abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp) && abs(iter_after->second->nom_afft_temp - iter2->second->nom_afft_temp) < 99)
					tortoiseShell->penalty += AFFT_TEMP_JUMP_penalty;
				else
					continue;
				// ��ȡ�¶ȹ����
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
		//cout << "��"<<i<<"���ڹ�ǵķ���Ϊ��" << tortoiseShell->penalty << endl;
		i++;
	}
	
	
	flow_rate = flowrateall/(actualflow.size()/2);															// ����ƥ����
	order_rate = assigned_wt / allsteelcCoil_wt;															// ��ͬ�ƻ�������
	rollingkm_rate = (rollingkm / s_mapSetOfTortoiseShell.size()) / max_TortoiseShell_len;					// ���ƹ�����
	DHCR_rate = assigned_DHCR / m_DHCR;																		// DHCR����
	Scheduling_quality = all_penalty / Scheduling_quality_deno;												// �ų�����
	double KPI = flow_rate*0.3 + order_rate*0.3 + rollingkm_rate*0.2 + DHCR_rate*0.1 -Scheduling_quality*0.1;
	//double KPI = flow_rate*0.1 + order_rate*0.1 + rollingkm_rate*0.5 + DHCR_rate*0.1 - Scheduling_quality*0.2;
	cout << "����ƥ����: " << flow_rate << "   " << "��ͬ�ƻ�������: " << order_rate << "    " << "���ƹ�����: " << rollingkm_rate << "   " << "DHCR����: " << DHCR_rate << "   " << "�ų�����: " << Scheduling_quality<< endl;
	cout << " KPI: " << KPI << endl;
	// ��ʼ��ÿ���ڹ�ǵ���ز���
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
	// �����ӲԼ��
	int MAX_NUM = 999;					// ������
	int MAX_KM = 2147483647;			// �������
	int ROLL_WIDTH_MINUS = 100;			// ���ƿ�Ȳ�
	//int	HARD_GROUP_MINUS = 100;		// Ӳ�����
	int	SAME_WIDTH_NUM = 100;			// ͬ�����
	int SAME_WIDTH_KM = 500000;			// ͬ�����ƹ�����
	double SAME_WIDTH = 0;				// ͬ���巶Χ

	// ����ڹ���Ѵﵽ������||�Ѵﵽ�������||��������Ȳ���޷����䣬����false
	if (steelCoilNum > MAX_NUM || steelCoilLenth > MAX_KM || m_main_groups.rbegin()->second->nom_roll_width - group->nom_roll_width >= ROLL_WIDTH_MINUS)
		return false;

	// �ܷ���ĸ־����
	int canSaveNum = group->m_SteelCoil.size();

	// ����ͬ������빫����
	int sameWidthNum = 0;
	int sameWidthKm = 0;
	// ��������������ø־����ڵ�����Ĳ���
	for (map<pair<int, int>, Group*>::reverse_iterator iter = m_main_groups.rbegin(); iter != m_main_groups.rend(); iter++)
	{
		Group* group2 = iter->second;
		// ������ƿ�Ȳ�С��ͬ���巶Χ������Ϊ��ͬ��
		if (group2->nom_roll_width - group->nom_roll_width <= SAME_WIDTH + 0.01)
		{
			// ����ͬ������빫����
			sameWidthNum += group2->m_SteelCoil.size();
			sameWidthKm += group2->roll_len;
		}
		else
			break;
	}
	// ������Է����������ͬ��ʣ��ɷſ���������¿ɷ������
	if (canSaveNum > SAME_WIDTH_NUM - sameWidthNum)
		canSaveNum = SAME_WIDTH_NUM - sameWidthNum;
	int partWidthKm = 0;// ��¼Ҫ�����ͬ������
	// ������������ĸ־���
	for (int i = 0; i < group->m_SteelCoil.size(); i++)
	{
		// ����Ҫ�����ͬ������
		partWidthKm += (*group->m_SteelCoil[i]).nom_roll_width;
		// ���Ҫ�����ͬ����������ʣ��ɷţ�������ܷ���Ŀ���
		if (partWidthKm > SAME_WIDTH_KM - sameWidthKm)
		{
			if (canSaveNum > i)
				canSaveNum = i;
			break;
		}
	}

	// ���ݸ��¾���¾�Լ�������������������
	if (coil_flag == 0)// �����һ���ǵ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_low_temp_coil_num - low_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_low_temp_coil_num - low_temp_coil_num;
			}
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			// �������3�θ��¾��򲻿ɷ�
			if (high_num == 3)
				return false;
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_high_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_high_temp_coil_num;
			}
		}
	}
	else// �����һ���Ǹ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_low_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_low_temp_coil_num;
			}
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_high_temp_coil_num - high_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_high_temp_coil_num - high_temp_coil_num;
			}
		}
	}

	// ��������λ����Լ���������������
	int partZoneNum = steelCoilNum;		// ��¼Ҫ���������λ�������
	int partZoneKm = steelCoilLenth;	// ��¼Ҫ���������λ���乫����
	// ������������ĸ־���
	for (int i = 0; i < group->m_SteelCoil.size(); i++)
	{
		// ���Ҫ����ĸ־��������λ����Լ�����򲻿ɷ���
		if (partZoneKm >(*group->m_SteelCoil[i]).zone_min_m || partZoneNum > (*group->m_SteelCoil[i]).zone_min_num)
		{
			if (canSaveNum > i)
				canSaveNum = i;
			break;
		}
		// ����Ҫ�����ͬ������
		partZoneNum++;
		partZoneKm += (*group->m_SteelCoil[i]).nom_roll_width;
	}

	// ����ɷ���־���Ϊ0���򲻿ɷ���
	if (canSaveNum == 0)
		return false;

	// ����ɷ���ĸ־���С�ڸ־����ڵĸ־�������ָ��С�־���
	Group *group_new = NULL;
	if (canSaveNum < group->m_SteelCoil.size())
	{
		// ����С�־���
		group_new = new Group(group, canSaveNum);
	}

	// ����ֱ�ӽ������־�����뵽�ڹ����
	else
	{
		// ����С�վ���
		group_new = new Group(group, (int)group->m_SteelCoil.size());
	}
	// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
	m_main_groups.insert(make_pair(make_pair(steelCoilLenth, steelCoilLenth + group_new->roll_len), group_new));
	// �����ڹ��ʵʱ����
	steelCoilNum += canSaveNum;
	steelCoilLenth += group_new->roll_len;
	if (coil_flag == 0)// �����һ���ǵ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			low_temp_coil_num += canSaveNum;
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			high_num++;
			coil_flag = 1;
			low_temp_coil_num = 0;
			high_temp_coil_num = canSaveNum;
		}
	}
	else// �����һ���Ǹ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			coil_flag = 0;
			low_temp_coil_num = canSaveNum;
			high_temp_coil_num = 0;
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			high_temp_coil_num += canSaveNum;
		}
	}

	return true;
}

bool TortoiseShell::addMainGroup2(Group *group)
{
	// �����ӲԼ��
	int MAX_NUM = 999;					// ������
	int MAX_KM = 2147483647;			// �������
	int ROLL_WIDTH_MINUS = 100;			// ���ƿ�Ȳ�
	//int	HARD_GROUP_MINUS = 100;		// Ӳ�����
	int	SAME_WIDTH_NUM = 100;			// ͬ�����
	int SAME_WIDTH_KM = 500000;			// ͬ�����ƹ�����
	double SAME_WIDTH = 0;				// ͬ���巶Χ

	// ����ڹ���Ѵﵽ������||�Ѵﵽ�������||��������Ȳ���޷����䣬����false
	if (steelCoilNum > MAX_NUM || steelCoilLenth > MAX_KM || m_main_groups.rbegin()->second->nom_roll_width - group->nom_roll_width >= ROLL_WIDTH_MINUS)
		return false;

	// �ܷ���ĸ־����
	int canSaveNum = group->m_SteelCoil.size();

	// ����ͬ������빫����
	int sameWidthNum = 0;
	int sameWidthKm = 0;
	// ��������������ø־����ڵ�����Ĳ���
	for (map<pair<int, int>, Group*>::reverse_iterator iter = m_main_groups.rbegin(); iter != m_main_groups.rend(); iter++)
	{
		Group* group2 = iter->second;
		// ������ƿ�Ȳ�С��ͬ���巶Χ������Ϊ��ͬ��
		if (group2->nom_roll_width - group->nom_roll_width <= SAME_WIDTH + 0.01)
		{
			// ����ͬ������빫����
			sameWidthNum += group2->m_SteelCoil.size();
			sameWidthKm += group2->roll_len;
		}
		else
			break;
	}
	// ������Է����������ͬ��ʣ��ɷſ���������¿ɷ������
	if (canSaveNum > SAME_WIDTH_NUM - sameWidthNum)
		canSaveNum = SAME_WIDTH_NUM - sameWidthNum;
	int partWidthKm = 0;// ��¼Ҫ�����ͬ������
	// ������������ĸ־���
	for (int i = 0; i < group->m_SteelCoil.size(); i++)
	{
		// ����Ҫ�����ͬ������
		partWidthKm += (*group->m_SteelCoil[i]).nom_roll_width;
		// ���Ҫ�����ͬ����������ʣ��ɷţ�������ܷ���Ŀ���
		if (partWidthKm > SAME_WIDTH_KM - sameWidthKm)
		{
			if (canSaveNum > i)
				canSaveNum = i;
			break;
		}
	}

	// ���ݸ��¾���¾�Լ�������������������
	if (coil_flag == 0)// �����һ���ǵ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_low_temp_coil_num - low_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_low_temp_coil_num - low_temp_coil_num;
			}
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			// �������3�θ��¾��򲻿ɷ�
			if (high_num == 3)
				return false;
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_high_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_high_temp_coil_num;
			}
		}
	}
	else// �����һ���Ǹ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_low_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_low_temp_coil_num;
			}
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			// �����ܷ���Ŀ���
			if (canSaveNum > (*group->m_SteelCoil.begin())->max_high_temp_coil_num - high_temp_coil_num)
			{
				canSaveNum = (*group->m_SteelCoil.begin())->max_high_temp_coil_num - high_temp_coil_num;
			}
		}
	}

	// ��������λ����Լ���������������
	int partZoneNum = steelCoilNum;		// ��¼Ҫ���������λ�������
	int partZoneKm = steelCoilLenth;	// ��¼Ҫ���������λ���乫����
	// ������������ĸ־���
	for (int i = 0; i < group->m_SteelCoil.size(); i++)
	{
		// ���Ҫ����ĸ־��������λ����Լ�����򲻿ɷ���
		if (partZoneKm >(*group->m_SteelCoil[i]).zone_min_m || partZoneNum > (*group->m_SteelCoil[i]).zone_min_num)
		{
			if (canSaveNum > i)
				canSaveNum = i;
			break;
		}
		// ����Ҫ�����ͬ������
		partZoneNum++;
		partZoneKm += (*group->m_SteelCoil[i]).nom_roll_width;
	}

	// ����ɷ���־���Ϊ0���򲻿ɷ���
	if (canSaveNum == 0)
		return false;

	// ����ɷ���ĸ־���С�ڸ־����ڵĸ־������򲻿ɷ���
	if (canSaveNum < group->m_SteelCoil.size())
		return false;

	// ����ֱ�ӽ������־�����뵽�ڹ����
	// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
	m_main_groups.insert(make_pair(make_pair(steelCoilLenth, steelCoilLenth + group->roll_len), group));
	// �����ڹ��ʵʱ����
	steelCoilNum += canSaveNum;
	steelCoilLenth += group->roll_len;
	if (coil_flag == 0)// �����һ���ǵ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			low_temp_coil_num += canSaveNum;
		}
		// �����ǰ�Ǹ��¾�
		else
		{
			high_num++;
			coil_flag = 1;
			low_temp_coil_num = 0;
			high_temp_coil_num = canSaveNum;
		}
	}
	else// �����һ���Ǹ��¾�
	{
		//�����ǰ�ǵ��¾�
		if (group->high_temp_flag == "0")
		{
			coil_flag = 0;
			low_temp_coil_num = canSaveNum;
			high_temp_coil_num = 0;
		}
		// �����ǰ�Ǹ��¾�
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
	// �����ڹ��
	for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
	{
		TortoiseShell *tortoiseShell = iter->second;
		// �����ڹ���ڵĸ־���
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
		{
			Group *group = iter2->second;
			// �����־����ڵĸ־�
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			
			{
				SteelCoil *steelCoil = *iter3;
				steelCoil->roll_begin_time_double = nowTime;
				nowTime += steelCoil->roll_time;
				steelCoil->roll_end_time_double = nowTime;								
			}
		}
	}
	// ���ݼ���õ�����ʱ�䣬��������(����ȡ��)
	int day = ceil(nowTime / (24 * 60));	
	int i = 1;
	nowTime = 0;
	double WT_10 = 0;
	double WT_11 = 0;
		// �����ڹ��
		for (map<int, TortoiseShell*>::iterator iter = s_mapSetOfTortoiseShell.begin(); iter != s_mapSetOfTortoiseShell.end(); iter++)
		{
			TortoiseShell *tortoiseShell = iter->second;
			// �����ڹ���ڵĸ־���
			for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
			{
				Group *group = iter2->second;
				// �����־����ڵĸ־�
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
		// ������һ��ĸ�����ĸ־���������map
		{
			actualflow.insert(make_pair(make_pair(i, "10"), WT_10));
			actualflow.insert(make_pair(make_pair(i, "11"), WT_11));
		}
	}

string TortoiseShell::DatetimeToString(time_t time)
{
	tm *tm_ = localtime(&time);                // ��time_t��ʽת��Ϊtm�ṹ��
	int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
	year = tm_->tm_year + 1900;                // ��ʱ�������꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬������ʱ����intΪtm_year����1900��
	month = tm_->tm_mon + 1;                   // ��ʱ�������£�����tm�ṹ����·ݴ洢��ΧΪ0-11��������ʱ����intΪtm_mon����1��
	day = tm_->tm_mday;                        // ��ʱ�������ա�
	hour = tm_->tm_hour;                       // ��ʱ������ʱ��
	minute = tm_->tm_min;                      // ��ʱ�������֡�
	second = tm_->tm_sec;                      // ��ʱ�������롣
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// ����ʱ��ĸ���char*������
	sprintf(yearStr, "%d", year);              // �ꡣ
	sprintf(monthStr, "%d", month);            // �¡�
	sprintf(dayStr, "%d", day);                // �ա�
	sprintf(hourStr, "%d", hour);              // ʱ��
	if (hourStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		hourStr[2] = '\0';
		hourStr[1] = hourStr[0];
		hourStr[0] = '0';
	}
	sprintf(minuteStr, "%d", minute);          // �֡�
	if (minuteStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		minuteStr[2] = '\0';
		minuteStr[1] = minuteStr[0];
		minuteStr[0] = '0';
	}
	sprintf(secondStr, "%d", second);          // �롣
	if (secondStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
	{
		secondStr[2] = '\0';
		secondStr[1] = secondStr[0];
		secondStr[0] = '0';
	}
	char s[20];                                // ����������ʱ��char*������
	sprintf(s, "%s%s%s%s%s%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// ��������ʱ����ϲ���
	string str(s);                             // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
	return str;                                // ����ת������ʱ����string������
}

time_t TortoiseShell::StringToDatetime(string str)
{
	char *cha = (char*)str.data();             // ��stringת����char*��
	tm tm_;                                    // ����tm�ṹ�塣
	int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
	sscanf(cha, "%4d%2d%2d%2d%2d%2d", &year, &month, &day, &hour, &minute, &second);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
	tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
	tm_.tm_mday = day;                         // �ա�
	tm_.tm_hour = hour;                        // ʱ��
	tm_.tm_min = minute;                       // �֡�
	tm_.tm_sec = second;                       // �롣
	tm_.tm_isdst = 0;                          // ������ʱ��
	time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
	return t_;                                 // ����ֵ�� 
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group��̬����
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