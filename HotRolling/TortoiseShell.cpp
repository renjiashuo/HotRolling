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
	// ��ʼ����������
	this->m_tortoiseShellName = s_mapSetOfTortoiseShell.size() + 1;
	this->m_TortoiseShell_len = 0;
	this->m_startTime = 0;
	this->m_finishTime = 0;
	this->m_timeSpan = 0;
	//this->nom_roll_width = 0;
	// ��ʼ���ڹ���ڵİ�����
	//m_groups.insert(make_pair(make_pair(100000.0, 100000.0 + group->roll_len), group));
	m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, 1), group));
	// ���Ÿ־�ļƻ�����
	int	plan_type = group->plan_type;
	// Ԥ���̹���(����һ���ڹ�Ǿͷ��̹���)
	vector<Group*> tang_temp;
	// ��һ���̹��ĵĿ��
	double width = 0;
	// �ܹ�Ԥ���̹��ĵĸ���
	int num = 0;
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup1.begin(); iter != Group::s_mapSetOfGroup1.end(); iter++)
	{
		// ׼������ĸ־��鼰��ƻ�����
		Group* group2 = iter->second;
		int	plan_type2 = group2->plan_type;
		// ����̹��ļƻ��������ʼ���ڹ�ǵĸ־�ƻ�����һ����������̹���
		map<pair<int, int>, int>::iterator iter2 = plantype.find(make_pair(plan_type, plan_type2));
		int type = iter2->second;
		if (type != 2 && type != 0 && group2->nom_roll_width != width)
		{
			width = group2->nom_roll_width;
			// ����ø־����ڸ־��������3����ֻ�ó�3�����̹��ģ�����ȫ�����̹���
			if (group2->m_SteelCoil.size() > 3)
			{
				int needCount = 3;
				// ����ܹ���Ҫ6���̹���
				if (6 - num < needCount)
					needCount = 6 - num;
				// ��Ԥ���̹�����������
				num += needCount;
				// �����µ�С�־���
				Group *group_temp = new Group(group2, needCount);
				tang_temp.push_back(group_temp);
			}
			else
			{
				int needCount = group2->m_SteelCoil.size();
				// ����ܹ���Ҫ6���̹���
				if (6 - num < needCount)
					needCount = 6 - num;
				// ��Ԥ���̹�����������
				num += needCount;
				// �����µ�С�־���
				Group *group_temp = new Group(group2, needCount);
				tang_temp.push_back(group_temp);
			}
		}
		if (num >= 6)
			break;
	}
	// ��Ԥ���̹��ķ��䵽����ڹ�ǵ�ǰ��
	for (int i = 0; i < tang_temp.size(); i++)
	{
		if (m_groups.empty())
			m_groups.insert(make_pair(make_pair(0, tang_temp[i]->roll_len), tang_temp[i]));
		else
			m_groups.insert(make_pair(make_pair(m_groups.rbegin()->first.second, m_groups.rbegin()->first.second + tang_temp[i]->roll_len), tang_temp[i]));
	}
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
	const double tangwidth_limit = 100000.0;//ͬ����������
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
			Group* group2 = tortoiseShell->m_groups_temp.begin()->second;
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
	const double samewidth_limit = 500000.0;//ͬ����������

#pragma region ������DHCR��Ǻ����̹��ı�ǵĸ־����map����
	//////////////////////////////////////////////////////////////////////////
	for (map<int, Group*>::iterator iter = Group::s_mapSetOfGroup.begin(); iter != Group::s_mapSetOfGroup.end();)
	{
		// ׼������ĸ־��鼰��ƻ�����
		Group* group = iter->second;
		int	plan_type = group->plan_type;
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
			// ���ͬ�������Ƿ����㣬�������㣬������ڹ�ǲ��ܷ�����־���
			if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end() && tortoiseShell->width_lonth.find(group->nom_roll_width)->second >= samewidth_limit)
				continue;
			// ���ø־�������룬��û�����ڳ�ͻ������У����ܷ�����ڹ��
			Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_temp));
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_groups_temp.find(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_groups_temp.begin() && plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == 0)
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			if (iter_after != tortoiseShell->m_groups_temp.end() && plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second == 0)
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
				int	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == 2)
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
				int	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == 2)
					break;
			}
			// ���1��˳���Ĳ��ҵ�������ڹ��������һ���־���Ҳû����break����˵��׼������ĸ־�����Է��뱾�ڹ���У���ô�����
			if (iter3 == tortoiseShell->m_groups_temp.end())
			{
				// ���������ȵĸ־���������ڹ���е������ܳ��ȣ����㼴�����������־��飩
				double lonth = 0;
				if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end())
					lonth = tortoiseShell->width_lonth.find(group->nom_roll_width)->second;
				// ����־����ڵĹ������������ͬ���������ƣ���ָ��С�־���
				if (group->roll_len >= samewidth_limit - lonth)
				{
					// ����С�־���
					Group *group_new = new Group(group, samewidth_limit - lonth);
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
					// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// �����ڹ���и־����ͬ������
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				}
				// ����ֱ�ӽ������־�����뵽�ڹ����
				else
				{
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
					// ��С�־�����뵽��ǰ�ڹ�ǵ�ĩβ
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
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
		int	plan_type = group->plan_type;
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
			Group* group_temp = NULL;
			tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_temp));
			map<pair<int, int>, Group*>	::iterator iter_now = tortoiseShell->m_groups_temp.find(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size()));
			map<pair<int, int>, Group*>	::iterator iter_before = iter_now;
			map<pair<int, int>, Group*>	::iterator iter_after = iter_now;
			iter_before--;
			iter_after++;
			if (iter_now != tortoiseShell->m_groups_temp.begin() && plantype.find(make_pair(plan_type, iter_before->second->plan_type))->second == 0)
			{
				tortoiseShell->m_groups_temp.erase(iter_now);
				continue;
			}
			if (iter_after != tortoiseShell->m_groups_temp.end() && plantype.find(make_pair(plan_type, iter_after->second->plan_type))->second == 0)
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
				int	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == 2)
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
				int	plan_type2 = group2->plan_type;
				// �����������ƻ����͵���Ϸ�ʽ
				map<pair<int, int>, int>::iterator iter4 = plantype.find(make_pair(plan_type, plan_type2));
				int type = iter4->second;
				// ����ƻ��ڲ�����ϣ����ò��ұ��ڹ���ˣ�������һ���ڹ�ǲ���
				if (type == 2)
					break;
			}
			// ���1��˳���Ĳ��ҵ�������ڹ��������һ���־���Ҳû����break����˵��׼������ĸ־�����Է��뱾�ڹ���У���ô�����
			if (iter3 == tortoiseShell->m_groups_temp.end())
			{
				// ���������ȵĸ־���������ڹ���е������ܳ��ȣ����㼴�����������־��飩
				double lonth = 0;
				if (tortoiseShell->width_lonth.find(group->nom_roll_width) != tortoiseShell->width_lonth.end())
					lonth = tortoiseShell->width_lonth.find(group->nom_roll_width)->second;
				// ����־����ڵĹ������������ͬ���������ƣ���ָ��С�־���
				if (group->roll_len >= samewidth_limit - lonth)
				{
					// ����С�־���
					Group *group_new = new Group(group, samewidth_limit - lonth);
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
					// ��С�־�����뵽��ǰ�ڹ�ǵ���ʱ�־��������
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
					// �����ڹ���и־����ͬ������
					if (tortoiseShell->width_lonth.find(group_new->nom_roll_width) == tortoiseShell->width_lonth.end())
						tortoiseShell->width_lonth.insert(make_pair(group_new->nom_roll_width, group_new->roll_len));
					else
						tortoiseShell->width_lonth.find(group_new->nom_roll_width)->second += group_new->roll_len;
				}
				// ����ֱ�ӽ������־�����뵽�ڹ����
				else
				{
					Group *group_new = new Group(group, (int)group->m_SteelCoil.size());
					// ����ǿտյ�С�־��飬��˵��һ���־�̫��Ų����ˣ���ô������һ���ڹ��
					if (group_new->m_SteelCoil.empty())
					{
						Group::s_mapSetOfsmallGroup.erase(Group::s_mapSetOfsmallGroup.find(group_new->group_no));
						delete group_new;
						continue;
					}
					// ��С�־�����뵽��ǰ�ڹ�ǵ�ĩβ
					tortoiseShell->m_groups_temp.insert(make_pair(make_pair(group->nom_roll_width, tortoiseShell->m_groups_temp.size() + 1), group_new));
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
			if (!tortoiseShell->m_groups.empty())
				end_located = tortoiseShell->m_groups.rbegin()->first.second;
			tortoiseShell->m_groups.insert(make_pair(make_pair(end_located, end_located + group->roll_len), group));
		}
		tortoiseShell->m_groups_temp.clear();
	}
	//////////////////////////////////////////////////////////////////////////
#pragma endregion
}

void TortoiseShell::showResult()
{
	int i = 0;
	cout << "�ڹ��������  " << s_mapSetOfTortoiseShell.size() << endl;
	// �����ʱ�ڹ�ǵı�š����ڹ����ĸ־����ź͸־�����־�ĸ־��
	for (map<int, TortoiseShell*>::iterator iter2 = s_mapSetOfTortoiseShell.begin(); iter2 != s_mapSetOfTortoiseShell.end(); iter2++)
	{
		for (map<pair<int, int>, Group*>::iterator iter3 = (*iter2).second->m_groups.begin(); iter3 != (*iter2).second->m_groups.end(); iter3++)
		{
			for (vector<SteelCoil*>::iterator iter4 = (*iter3).second->m_SteelCoil.begin(); iter4 != (*iter3).second->m_SteelCoil.end(); iter4++)
			{
				
				i++;;
				cout << iter2->first << "	" << iter3->second->group_no << "	" << (*iter4)->mat_no << "    "<<(*iter4)->SteelCoil_width<<endl;
			}
		}
	}
	cout << "�־�������   "<<i << endl;// �վ���
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
		// �����ڹ���ڵİ�����
		for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_groups.begin(); iter2 != tortoiseShell->m_groups.end(); iter2++)
		{
			// �־���
			Group *group = iter2->second;
			// �����������ڵİ���
			for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
			{
				// �־�
				SteelCoil *steelCoil = *iter3;
				string	mat_no = steelCoil->mat_no;						// �־��
				string	flow = steelCoil->flow;							// ����
				string	fin_cut_time = steelCoil->fin_cut_time;				// �ж�ʱ��
				//bool		must_do_flag = steelCoil->must_do_flag;				// �������
				bool		must_do_flag = 0;				// �������
				int		plan_type = steelCoil->plan_type;					// �ƻ�����
				double	SteelCoil_thick = steelCoil->SteelCoil_thick;			// ����ƺ��
				double	SteelCoil_width = steelCoil->SteelCoil_width;			// ����ƿ��
				int		nom_heat_temp = steelCoil->nom_heat_temp;			// ���¯�¶�
				int		nom_afft_temp = steelCoil->nom_afft_temp;			// ������¶�
				int		nom_coil_temp = steelCoil->nom_coil_temp;			// ���ȡ�¶�
				string	plan_no = steelCoil->plan_no;						// �ƻ���
				fout << mat_no << "," << flow << "," << fin_cut_time << "," << (int)must_do_flag << "," << plan_type << "," << SteelCoil_thick << "," << SteelCoil_width << "," << nom_heat_temp << "," << nom_afft_temp << "," << nom_coil_temp << "," << plan_no << endl;
			}
		}
	}
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