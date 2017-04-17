/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 钢卷组类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 钢卷组类
/// <para>存储操作钢卷组信息</para>
/// </summary>
===========================================================</remark>*/

#include "Group.h"
#include "SteelCoil.h"

#pragma region Group成员函数
//////////////////////////////////////////////////////////////////////////
Group::Group(int value1, string value2, string value3, double value4, double value5, int value6, int value7, int value8, vector<SteelCoil*>&value9)
{
	group_no = value1;
	plan_type = value2;
	st_no = value3;
	nom_roll_thick = value4;
	nom_roll_width = value5;
	nom_heat_temp = value6;
	nom_afft_temp = value7;
	nom_coil_temp = value8;
	m_SteelCoil = value9;
	roll_len = 0;
	for (int i = 0; i < m_SteelCoil.size(); i++)
		roll_len += m_SteelCoil[i]->roll_len;
}

Group::Group(Group *group, int n)
{
	// 初始化相同遍历
	this->group_no = s_mapSetOfsmallGroup.size() + 1;
	this->plan_type = group->plan_type;
	this->st_no = group->st_no;
	this->nom_roll_thick = group->nom_roll_thick;
	this->nom_roll_width = group->nom_roll_width;
	this->nom_heat_temp = group->nom_heat_temp;
	this->nom_afft_temp = group->nom_afft_temp;
	this->nom_coil_temp = group->nom_coil_temp;
	// 转移钢卷到新的钢卷组中
	vector<SteelCoil*>::iterator iter = group->m_SteelCoil.begin();
	advance(iter, n);
	this->m_SteelCoil.insert(this->m_SteelCoil.begin(), group->m_SteelCoil.begin(), iter);
	group->m_SteelCoil.erase(group->m_SteelCoil.begin(), iter);
	// 计算轧制长度
	roll_len = 0;
	for (iter = m_SteelCoil.begin(); iter != m_SteelCoil.end(); iter++)
	{
		SteelCoil *steelCoil = *iter;
		roll_len += steelCoil->roll_len;
	}
	// 将新的钢卷组放入小钢卷组map中
	Group::s_mapSetOfsmallGroup.insert(make_pair(this->group_no, this));
}

Group::Group(Group *group, double lonth)
{
	// 初始化相同遍历
	this->group_no = s_mapSetOfsmallGroup.size() + 1;
	this->plan_type = group->plan_type;
	this->st_no = group->st_no;
	this->nom_roll_thick = group->nom_roll_thick;
	this->nom_roll_width = group->nom_roll_width;
	this->nom_heat_temp = group->nom_heat_temp;
	this->nom_afft_temp = group->nom_afft_temp;
	this->nom_coil_temp = group->nom_coil_temp;
	// 转移钢卷到新的钢卷组中
	roll_len = 0;	// 轧制长度
	for (vector<SteelCoil*>::iterator iter = group->m_SteelCoil.begin(); iter != group->m_SteelCoil.end();)
	{
		// 钢卷组内每一个钢卷
		SteelCoil *steelCoil = *iter;
		// 如果新钢卷组的长度加下一个钢卷的长度小于等于需要的长度
		if (roll_len + steelCoil->roll_len <= lonth)
		{
			// 更新新钢卷组长度
			roll_len += steelCoil->roll_len;
			// 更新原钢卷组长度
			group->roll_len -= steelCoil->roll_len;
			// 转移钢卷
			this->m_SteelCoil.insert(this->m_SteelCoil.end(), iter, iter+1);
			iter = group->m_SteelCoil.erase(iter);
		}
		else
			break;
	}
	Group::s_mapSetOfsmallGroup.insert(make_pair(this->group_no, this));
}

void indata(map<int, Group*>&m_data, int a, Group* b)
{
	m_data.insert(make_pair(a, b));
}

void Group::vec_group()
{
	int i = 1;
	/*for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_DHCRSteelCoil.begin(); iter != SteelCoil::s_DHCRSteelCoil.end(); iter++)
	{				
		Group* newgroup = new Group(i, (*iter).first.first.first.first.first.first.first, (*iter).first.first.first.first.first.first.second, (*iter).first.first.first.first.first.second, (*iter).first.first.first.first.second, (*iter).first.first.first.second, (*iter).first.first.second, (*iter).first.second,iter->second);
		indata(Group::s_mapSetOfGroup, i, newgroup);
		i++;
	}*/
	for (map<pair<pair < pair<pair<pair<pair<string, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_nonpre_DHCR_flagSteelCoil.begin(); iter != SteelCoil::s_nonpre_DHCR_flagSteelCoil.end(); iter++)
	{
		Group* newgroup1 = new Group(i, (*iter).first.first.first.first.first.first.first, (*iter).first.first.first.first.first.first.second, (*iter).first.first.first.first.first.second, (*iter).first.first.first.first.second, (*iter).first.first.first.second, (*iter).first.first.second, (*iter).first.second, iter->second);
		indata(Group::s_mapSetOfGroup, i, newgroup1);
		i++;
	}
	for (map<pair<pair < pair<pair<pair<pair<string, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_pre_flagSteelCoil.begin(); iter != SteelCoil::s_pre_flagSteelCoil.end(); iter++)
	{
		Group* newgroup2 = new Group(i, (*iter).first.first.first.first.first.first.first, (*iter).first.first.first.first.first.first.second, (*iter).first.first.first.first.first.second, (*iter).first.first.first.first.second, (*iter).first.first.first.second, (*iter).first.first.second, (*iter).first.second, iter->second);
		indata(Group::s_mapSetOfGroup1, i, newgroup2);
		i++;
	}

	/*------------------------------输出钢卷组的参数----------------------------*/
	for (map<int, Group*> ::iterator iter = s_mapSetOfGroup.begin(); iter != s_mapSetOfGroup.end(); iter++)
	{
		cout << iter->first<<"  ";
		cout << iter->second->plan_type << "  " << iter->second->st_no << "  " << iter->second->nom_roll_thick << "  " << iter->second->nom_roll_width << "  " << iter->second->nom_afft_temp << "  " << iter->second->nom_coil_temp << "  " << iter->second->nom_heat_temp << "   " << iter->second->m_SteelCoil.size() << endl;

	}
	cout << endl << endl;
	for (map<int, Group*>::iterator iter = s_mapSetOfGroup1.begin(); iter != s_mapSetOfGroup1.end(); iter++)
	{
		cout << iter->first <<"  ";
		cout << iter->second->plan_type << "  " << iter->second->st_no<< "  " << iter->second->nom_roll_thick << "  " << iter->second->nom_roll_width << "  " << iter->second->nom_afft_temp << "  " << iter->second->nom_coil_temp << "  " << iter->second->nom_heat_temp << "   " << iter->second->m_SteelCoil.size() << endl;
	}
	cout << endl << endl;
	/*------------------------------输出钢卷组的参数----------------------------*/


	/*-----------读取钢卷组集合里的钢卷组里的钢卷的长度（或者其他属性）--------------*/
	for (map<int, Group*> ::iterator iter = s_mapSetOfGroup.begin(); iter != s_mapSetOfGroup.end(); iter++)
	{
		for (vector<SteelCoil*>::iterator iter1 = (*iter).second->m_SteelCoil.begin(); iter1 != (*iter).second->m_SteelCoil.end(); iter1++)
		{
			cout << (*iter1)->roll_len << endl;
		}		
	}
	cout << endl << endl;
	/*-----------读取钢卷组集合里的钢卷组里的钢卷的长度（或者其他属性）--------------*/

}
#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////

Group::~Group()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group静态变量
//////////////////////////////////////////////////////////////////////////
map<int, Group*>		Group::s_mapSetOfGroup = map<int, Group*>();
map<int, Group*>		Group::s_mapSetOfGroup1 = map<int, Group*>();
map<int, Group*>     Group::s_mapSetOfsmallGroup = map<int, Group*>();
int						Group::s_GroupCount = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion