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
Group::Group(int value1, double value2, double value3, string value4, string value5, int value6, int value7, int value8, string value10, int value11, int value12, int value13, int value14,string value15, vector<SteelCoil*>&value9)
{
	group_no = value1;
	plan_type = value4;
	st_no = value5;
	nom_roll_thick = value3;
	nom_roll_width = value2;
	nom_heat_temp = value6;
	nom_afft_temp = value7;
	nom_coil_temp = value8;
	m_SteelCoil = value9;
	high_temp_flag = value10;
	zone_max_num = value11;
	zone_min_num = value12;
	zone_max_m = value13;
	zone_min_m = value14;
	nom_hard_group_code = value15;
	roll_len = 0;
	slab_wt = 0;
	for (int i = 0; i < m_SteelCoil.size(); i++)
	{
		roll_len += m_SteelCoil[i]->roll_len;
		slab_wt += m_SteelCoil[i]->slab_wt;
	}
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
	this->high_temp_flag = group->high_temp_flag;
	this->zone_max_m = group->zone_max_m;
	this->zone_max_num = group->zone_max_num;
	this->zone_min_m = group->zone_min_m;
	this->zone_min_num = group->zone_min_num;
	this->slab_wt = group->slab_wt;
	this->roll_len = group->roll_len;
	this->nom_hard_group_code = group->nom_hard_group_code;
	// 转移钢卷到新的钢卷组中
	vector<SteelCoil*>::iterator iter = group->m_SteelCoil.begin();
	advance(iter, n);
	this->m_SteelCoil.insert(this->m_SteelCoil.begin(), group->m_SteelCoil.begin(), iter);
	group->m_SteelCoil.erase(group->m_SteelCoil.begin(), iter);
	// 计算新钢卷组轧制长度
	roll_len = 0;
	for (iter = m_SteelCoil.begin(); iter != m_SteelCoil.end(); iter++)
	{
		SteelCoil *steelCoil = *iter;
		roll_len += steelCoil->roll_len;
	}
	// 计算新钢卷组轧制重量
	slab_wt = 0;
	for (iter = m_SteelCoil.begin(); iter != m_SteelCoil.end(); iter++)
	{
		SteelCoil *steelCoil = *iter;
		slab_wt += steelCoil->slab_wt;
	}
	// 更新原钢卷组轧制长度
	group->roll_len -= this->roll_len;
	// 更新原钢卷组轧制重量
	group->slab_wt -= this->slab_wt;
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
	this->high_temp_flag = group->high_temp_flag;
	this->zone_max_m = group->zone_max_m;
	this->zone_max_num = group->zone_max_num;
	this->zone_min_m = group->zone_min_m;
	this->zone_min_num = group->zone_min_num;
	this->slab_wt = group->slab_wt;
	this->roll_len = group->roll_len;
	this->nom_hard_group_code = group->nom_hard_group_code;
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
			// 更新新钢卷组的重量
			slab_wt += steelCoil->slab_wt;
			// 更新原钢卷组的重量
			group->slab_wt -= steelCoil->slab_wt;
			// 转移钢卷
			this->m_SteelCoil.insert(this->m_SteelCoil.end(), iter, iter+1);
			iter = group->m_SteelCoil.erase(iter);
		}
		else
			break;
	}
	Group::s_mapSetOfsmallGroup.insert(make_pair(this->group_no, this));
}

void Group::indata(map<int, Group*>&m_data, int a, Group* b)
{
	m_data.insert(make_pair(a, b));
}

void Group::vec_group()
{
	int i = 1;
	for (map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>,string>, vector<SteelCoil*> >::iterator iter = SteelCoil::s_SteelCoil.begin(); iter != SteelCoil::s_SteelCoil.end(); iter++)
	{
		Group* newgroup1 = new Group(i, -(*iter).first.first.first.first.first.first.first.first.first.first.first.first.first, (*iter).first.first.first.first.first.first.first.first.first.first.first.first.second, (*iter).first.first.first.first.first.first.first.first.first.first.first.second, (*iter).first.first.first.first.first.first.first.first.first.first.second, (*iter).first.first.first.first.first.first.first.first.first.second, (*iter).first.first.first.first.first.first.first.first.second, (*iter).first.first.first.first.first.first.first.second, (*iter).first.first.first.first.first.first.second, (*iter).first.first.first.first.first.second, (*iter).first.first.first.first.second, (*iter).first.first.first.second, (*iter).first.first.second, (*iter).first.second, iter->second);
		indata(Group::s_mapSetOfGroup, i, newgroup1);
		i++;
	}

	/*------------------------------输出钢卷组的参数----------------------------*/
	for (map<int, Group*> ::iterator iter = s_mapSetOfGroup.begin(); iter != s_mapSetOfGroup.end(); iter++)
	{
		cout << iter->first<<"  ";
		cout << iter->second->plan_type << "	" << iter->second->st_no << "	" << iter->second->nom_roll_thick << "		" << iter->second->nom_roll_width << "		" << iter->second->nom_afft_temp << "		" << iter->second->nom_coil_temp << "		" << iter->second->nom_heat_temp << "		" << iter->second->high_temp_flag<<"	  "<<iter->second->m_SteelCoil.size() << endl;

	}
	cout << endl << endl;
	/*------------------------------输出钢卷组的参数----------------------------*/

	/*-----------读取钢卷组集合里的钢卷组里的钢卷的长度（或者其他属性）--------------*/
	/*for (map<int, Group*> ::iterator iter = s_mapSetOfGroup.begin(); iter != s_mapSetOfGroup.end(); iter++)
	{
		for (vector<SteelCoil*>::iterator iter1 = (*iter).second->m_SteelCoil.begin(); iter1 != (*iter).second->m_SteelCoil.end(); iter1++)
		{
			cout << (*iter1)->high_temp_flag<< endl;
		}		
	}
	cout << endl << endl;*/
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
map<int, Group*>		Group::s_mapSetOfsmallGroup = map<int, Group*>();
map<int, Group*>		Group::s_least = map<int, Group*>();
int						Group::s_GroupCount = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion