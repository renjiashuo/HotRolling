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

TortoiseShell::TortoiseShell(Group *groups)
{
	// ��ʼ����������
	this->m_tortoiseShellName = s_mapSetOfTortoiseShell.size() + 1;
	this->m_TortoiseShell_len = 0;
	this->m_startTime = 0;
	this->m_finishTime = 0;
	this->m_timeSpan = 0;
	this->nom_roll_width = 0;
	// ��ʼ���ڹ���ڵİ�����
	m_groups.insert(make_pair(make_pair(100000.0, 100000.0 + groups->roll_len), groups));
}

TortoiseShell::~TortoiseShell()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region �ڹ�Ǽƻ����
//////////////////////////////////////////////////////////////////////////

void TortoiseShell::InitShell()
{
	const double samewidth_limit = 500000.0;//ͬ����������
	try
	{
		Environment::Initialize();//������ʼ��
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");//�������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);//�������ݼ�
		ostring rowid;
		st.Execute("select * from TIP00SI04");//ѡ���
		Resultset rs = st.GetResultset();
		// ��ȡ�ƻ�������Ϸ�ʽ
		while (rs.Next())
		{
			pair<int, int> temp;
			temp = make_pair(rs.Get<int>(14), rs.Get<int>(15));
			plantype.insert(make_pair(temp, rs.Get<int>(16)));
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
		int	plan_type = group->plan_type;
		// ���������ڹ��
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// ����ڹ��
			TortoiseShell* tortoiseShell = iter2->second;
			// ����ڹ����ĵ�һ���־��鼰��ƻ�����
			Group* group2 = tortoiseShell->m_groups.begin()->second;
			int	plan_type2 = group2->plan_type;
			// �������ͬ����Ϸ�ʽ�����ò�����
			if (plan_type == plan_type2)
				break;
			// �����������ƻ����͵���Ϸ�ʽ
			map<pair<int, int>, int>::iterator iter3 = plantype.find(make_pair(plan_type, plan_type2));
			int type = iter3->second;
			// �����Ϸ�ʽ����"�ƻ��ڲ��������"����˸־�����Ժ͵�ǰ�ڹ����ϡ�
			if (type != 2)
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
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
			// ����ֱ�ӽ������־�����뵽�ڹ����
			else
			{
				// ����С�־���
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
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
	const double samewidth_limit = 500000.0;//ͬ����������
	// ������DHCR��Ǻ����̹��ı�ǵĸ־����map����
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// ׼������ĸ־��鼰��ƻ�����
		Group* group = iter->second;
		int	plan_type = group->plan_type;
		// ���������ڹ��
		map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin();
		for (; iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
		{
			// ����ڹ��
			TortoiseShell* tortoiseShell = iter2->second;
			// ��������ڹ����ĸ־���
			map<pair<int, int>, Group*>::iterator iter3 = tortoiseShell->m_groups.begin();
			for (; iter3 != tortoiseShell->m_groups.end(); iter3++)
			{
				// �ڹ����ĸ־������ֹλ�ü��־���
				int begin_location = iter3->first.first;
				int end_location = iter3->first.second;
				Group *group2 = iter3->second;
				// ����־���ļƻ�����
				int	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == 2)
					break;
				// ���׼������ĸ־�����Ŀǰ�ڹ�������һ���־��鲻��������ϣ�ͬ��
				if (iter3 == --(tortoiseShell->m_groups.end()) && type == 1)
					break;;
			}
			// ���1��˳���Ĳ��ҵ�������ڹ��������һ���־���Ҳû����break��2��ͬ���������㡣��˵��׼������ĸ־�����Է��뱾�ڹ���У���ô�����
			if (iter3 == tortoiseShell->m_groups.end() && 
				((group->nom_roll_width == tortoiseShell->nom_roll_width && tortoiseShell->same_width_lonth < samewidth_limit) ||
				(group->nom_roll_width != tortoiseShell->nom_roll_width)))
			{
				// ����־����ڵĹ������������ͬ���������ƣ���ָ��С�־���
				if (group->roll_len >= samewidth_limit - tortoiseShell->nom_roll_width)
				{
					// ����С�־���
					Group *group_new = new Group(group, samewidth_limit - tortoiseShell->nom_roll_width);
					Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
					// ��С�־�����뵽��ǰ�ڹ�ǵ�ĩβ
					int end_location = tortoiseShell->m_groups.rbegin()->first.second;
					tortoiseShell->m_groups.insert(make_pair(make_pair(end_location, end_location + group->roll_len), group_new));
					// ����ø־������ڹ�������һ���־��鲻ͬ��
					if (group->nom_roll_width != tortoiseShell->nom_roll_width)
					{
						tortoiseShell->nom_roll_width = group_new->nom_roll_width;
						tortoiseShell->same_width_lonth = group_new->roll_len;
					}
					// ����
					else
					{
						tortoiseShell->same_width_lonth += group_new->roll_len;
					}
				}
				// ����ֱ�ӽ������־�����뵽�ڹ����
				else
				{
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
					// ��С�־�����뵽��ǰ�ڹ�ǵ�ĩβ
					int end_location = tortoiseShell->m_groups.rbegin()->first.second;
					tortoiseShell->m_groups.insert(make_pair(make_pair(end_location, end_location + group->roll_len), group_new));
					// ����ø־������ڹ�������һ���־��鲻ͬ��
					if (group->nom_roll_width != tortoiseShell->nom_roll_width)
					{
						tortoiseShell->nom_roll_width = group_new->nom_roll_width;
						tortoiseShell->same_width_lonth = group_new->roll_len;
					}
					// ����
					else
					{
						tortoiseShell->same_width_lonth += group_new->roll_len;
					}
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
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
			// ����ֱ�ӽ������־�����뵽�ڹ����
			else
			{
				// ����С�־���
				Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
				Group::s_mapSetOfsmallGroup.insert(make_pair(Group::s_mapSetOfsmallGroup.size() + 1, group_new));
				// �����ڹ��
				TortoiseShell *tortoiseShell = new TortoiseShell(group_new);
				s_mapSetOfTortoiseShell.insert(make_pair(tortoiseShell->m_tortoiseShellName, tortoiseShell));
				// �����ڹ�ǵ��ų̹����м�¼������Ŀǰ�ڹ�������һ���־���Ķ���ƿ�ȡ�Ŀǰ���һ���־����ȵ�ͬ��������
				tortoiseShell->nom_roll_width = group_new->nom_roll_width;
				tortoiseShell->same_width_lonth = group_new->roll_len;
			}
		}
		// �����־���Ϊ�գ���ȫ������С�־��飬��ɾ��֮
		if (group->m_SteelCoil.size() == 0)
		{
			delete group;
			iter = Group::s_mapSetOfGroup.erase(iter);
		}
	}
}

void TortoiseShell::showResult()
{
	// �����ʱ�ڹ�ǵı�š����ڹ����ĸ־����ź͸־�����־�ĸ־��
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_groups.begin(); iter3 != (*iter2).second->m_groups.end(); iter3++)
		{
			for (vector<SteelCoil*>::iterator iter4 = (*iter3).second->m_SteelCoil.begin(); iter4 != (*iter3).second->m_SteelCoil.end(); iter4++)
			{
				cout << iter2->first << "	" << iter3->second->group_no << "	" << (*iter4)->mat_no << endl;
			}
		}
	}
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

//////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group��̬����
//////////////////////////////////////////////////////////////////////////
map<int, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<int, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
map<pair<int, int>, int>		TortoiseShell::plantype = map<pair<int, int>, int>();
////////////////////////////////////////////////////////////////////////
#pragma endregion