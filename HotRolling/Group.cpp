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
Group::Group(int value1, int value2, string value3, double value4, double value5, int value6, int value7, int value8, vector<SteelCoil*>&value9)
{
	group_no = value1;
	plan_type = value2;
	st_no = value3;
	nom_roll_thick = value4;
	nom_roll_width = value5;
	//roll_len = value6;
	nom_heat_temp = value6;
	nom_afft_temp = value7;
	nom_coil_temp = value8;
	m_SteelCoil = value9;
	//m_SteelCoil = value10;
}
void indata(map<int, Group*>&m_data, int a, Group* b)
{
	m_data.insert(make_pair(a, b));
}

void Group::vec_group()
{
	int i = 1;
	for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_DHCRSteelCoil.begin(); iter != SteelCoil::s_DHCRSteelCoil.end(); iter++)
	{				
		Group* newgroup = new Group(i, (*iter).first.first.first.first.first.first.first, (*iter).first.first.first.first.first.first.second, (*iter).first.first.first.first.first.second, (*iter).first.first.first.first.second, (*iter).first.first.first.second, (*iter).first.first.second, (*iter).first.second,iter->second);
		indata(Group::s_mapSetOfGroup, i, newgroup);
		i++;
	}
	for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_nonpre_flagSteelCoil.begin(); iter != SteelCoil::s_nonpre_flagSteelCoil.end(); iter++)
	{
		Group* newgroup1 = new Group(i, (*iter).first.first.first.first.first.first.first, (*iter).first.first.first.first.first.first.second, (*iter).first.first.first.first.first.second, (*iter).first.first.first.first.second, (*iter).first.first.first.second, (*iter).first.first.second, (*iter).first.second, iter->second);
		indata(Group::s_mapSetOfGroup, i, newgroup1);
		i++;
	}
	for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_pre_flagSteelCoil.begin(); iter != SteelCoil::s_pre_flagSteelCoil.end(); iter++)
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
			cout << (*iter1)->SteelCoil_len << endl;
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
map<string, Group*>     Group::s_mapSetOfsmallGroup = map<string, Group*>();
int						Group::s_GroupCount = 0;

////////////////////////////////////////////////////////////////////////
#pragma endregion