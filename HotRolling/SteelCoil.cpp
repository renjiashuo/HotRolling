/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 钢卷类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 钢卷类
/// <para>存储操作钢卷信息</para>
/// </summary>
===========================================================</remark>*/

#include "SteelCoil.h"
#include <iostream>
#include "ocilib.hpp"

using namespace ocilib;
using namespace std;

#pragma region SteelCoil成员函数
//////////////////////////////////////////////////////////////////////////
//struct compwidth
//{
//	bool operator()(const pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>&A, const pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>&B)const
//	{
//		if (A.first.first.first.second != B.first.first.first.second)
//			return A.first.first.first.second > B.first.first.first.second;
//		//return false;
//	}
//};
SteelCoil::SteelCoil(string value1, string value2, double value3, double value4, double value5, string value6, double value7, double value8, int value9, string value10, string value11, string value12, string value13, string value14, string value15, string value16,
	string value17, int value18, string value19, int value20, string value21, string value22, string value23, double value24, double value25, string value26, string value27, string value28, string value29, string value30, string value31,
	string value32, string value33, string value34, string value35, string value36, string value37, string value38, string value39, string value40, int value41, int value42, string value43, string value44, string value45, string value46,
	string value47, string value48, bool value49, int value50, double value51, int value52, string value53, int value54, string value55, string value56, double value57, double value58, double value59, double value60, int value61,
	int value62, int value63, int value64, int value65, int value66, int value67, int value68, int value69, int value70, int value71, int value72, int value73, int value74, int value75, int value76,
	int value77,  string value82, string value83, string value84, string value85, string value86, string value87, string value88, string value89, double value90)
{
	roll_plan_type = value1;
	mat_no = value2;
	nom_roll_thick = value3;
	nom_roll_width = value4;
	roll_len = value5;
	st_no = value6;
	nom_heat_temp = value7;
	nom_afft_temp = value8;
	nom_coil_temp = value9;
	nom_hot_send_flag = value10;
	pre_flag = value11;
	plan_type = value12;
	nom_hard_group_code = value13;
	nom_surf_index_code = value14;
	high_temp_flag = value15;
	low_temp_flag = value16;

	whole_backlog = value17;
	whole_backlog_seq = value18;
	whole_backlog_code = value19;
	next_whole_backlog_seq = value20;
	next_whole_backlog_code = value21;
	work_type = value22;
	order_no = value23;
	slab_wt = value24;
	slab_width = value25;
	sg_sign = value26;
	new_test_no = value27;
	slab_dest = value28;
	stock_code = value29;
	fin_cut_time = value30;
	prec_slab_no = value31;

	ips_pono = value32;
	order_hot_charge_flag = value33;
	ips_cast_lot_no = value34;
	prec_roll_plan_no = value35;
	bg_mat_status = value36;
	bg_app_status = value37;
	transfer_plan_no = value38;
	mat_status = value39;
	roll_plan_no = value40;
	width_top_slab = value41;
	width_bot_slab = value42;
	adjust_width_mark = value43;
	stock_stay_time = value44;
	in_stock_time = value45;
	roll_end_time = value46;

	hold_cause_code = value47;
	hr_plan_date = value48;
	must_do_flag = value49;
	slab_len = value50;
	roll_time = value51;
	order_pri = value52;
	plan_no = value53;
	mat_seq_no = value54;
	flow = value55;
	mod_stamp_no = value56;
	thick_forward_max = value57;
	thick_forward_min = value58;
	thick_backward_max = value59;
	thick_backward_min = value60;
	heat_temp_jump_max = value61;

	heat_temp_jump_min = value62;
	afft_temp_jump_max = value63;
	afft_temp_jump_min = value64;
	coil_temp_jump_max = value65;
	coil_temp_jump_min = value66;
	hard_group_jump_max = value67;
	hard_group_jump_min = value68;
	max_high_temp_coil_num = value69;
	min_high_temp_coil_num = value70;
	min_low_temp_coil_num = value71;
	max_low_temp_coil_num = value72;
	num = value73;
	zone_max_num = value74;
	zone_min_num = value75;
	zone_max_m = value76;

	zone_min_m = value77;
	
	REC_CREATOR = value82;
	REC_CREATE_TIME = value83;
	REC_REVISOR = value84;
	REC_REVISE_TIME = value85;
	ARCHIVE_FLAG = value86;
	ARCHIVE_STAMP_NO = value87;
	COMPANY_CODE = value88;
	COMPANY_NAME = value89;
	slab_thick = value90;
	







}/*---------将七组同规格的钢卷分组放入指定vector里，再放入map----------*/

void indata(map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>> &m_data, double a, double b, string c, string d, int e, int f, int g, string k, int i, int j, int m, int n,string p, SteelCoil* h)
{
	if (m_data.find(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(a, b), c), d), e), f), g), k),i),j),m),n),p)) == m_data.end())
	{
		vector<SteelCoil*> temp;
		temp.push_back(h);
		m_data.insert(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(a, b), c), d), e), f), g), k), i), j), m), n),p), temp));
	}
	else
	{
		m_data.find(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(a, b), c), d), e), f), g), k), i), j), m), n),p))->second.push_back(h);
	}
}

void SteelCoil::SteelCoilgroup()
{
	try
	{
		Environment::Initialize();//环境初始化
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");//连接数据库（IP地址/服务名，“用户名”，“密码“）
		Statement st(con);//创建数据集
		ostring rowid;
		st.Execute("select * from TIPHRM01 t order by nom_roll_width DESC");//选择表
		Resultset rs = st.GetResultset();
		
		while (rs.Next())
		{
				
			if (rs.Get<ostring>(39) == "1" && rs.Get<ostring>(29)=="0")		//将有烫辊材标记（不包括DHCR）的钢卷按十二组标准组成钢卷组放入map
			{
				SteelCoil *PRESteelCoil = new SteelCoil(rs.Get<ostring>(36),rs.Get<ostring>(9), rs.Get<double>(48), rs.Get<double>(49), rs.Get<double>(57), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(29), rs.Get<ostring>(39), rs.Get<ostring>(55), rs.Get<ostring>(53), rs.Get<ostring>(54), rs.Get<ostring>(80), rs.Get<ostring>(81)
					, rs.Get<ostring>(10), rs.Get<int>(11), rs.Get<ostring>(12), rs.Get<int>(13), rs.Get<ostring>(14), rs.Get<ostring>(15), rs.Get<ostring>(16), rs.Get<double>(20), rs.Get<double>(18), rs.Get<ostring>(22), rs.Get<ostring>(23), rs.Get<ostring>(24), rs.Get<ostring>(25), rs.Get<ostring>(26), rs.Get<ostring>(27), rs.Get<ostring>(28)
					, rs.Get<ostring>(30), rs.Get<ostring>(31), rs.Get<ostring>(32), rs.Get<ostring>(33), rs.Get<ostring>(34), rs.Get<ostring>(35), rs.Get<ostring>(37), rs.Get<ostring>(38), rs.Get<int>(40), rs.Get<int>(41), rs.Get<ostring>(42), rs.Get<ostring>(43), rs.Get<ostring>(44), rs.Get<ostring>(45), rs.Get<ostring>(46), rs.Get<ostring>(47)
					, rs.Get<int>(56), rs.Get<int>(19), rs.Get<double>(58), rs.Get<int>(59), rs.Get<ostring>(60), rs.Get<int>(61), rs.Get<ostring>(62), rs.Get<ostring>(63), rs.Get<double>(64), rs.Get<double>(65), rs.Get<double>(66), rs.Get<double>(67), rs.Get<int>(68), rs.Get<int>(69), rs.Get<int>(70), rs.Get<int>(71)
					, rs.Get<int>(72), rs.Get<int>(73), rs.Get<int>(74), rs.Get<int>(75), rs.Get<int>(76), rs.Get<int>(77), rs.Get<int>(78), rs.Get<int>(79), rs.Get<int>(82), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3),
					rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8), rs.Get<double>(17));

				indata(SteelCoil::s_SteelCoil, -rs.Get<double>(49), rs.Get<double>(48), rs.Get<ostring>(55), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(80), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(53), PRESteelCoil);
			}
			else
			{
				SteelCoil *nonPRE_DHCRSteelCoil = new SteelCoil(rs.Get<ostring>(36), rs.Get<ostring>(9), rs.Get<double>(48), rs.Get<double>(49), rs.Get<double>(57), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(29), rs.Get<ostring>(39), rs.Get<ostring>(55), rs.Get<ostring>(53), rs.Get<ostring>(54), rs.Get<ostring>(80), rs.Get<ostring>(81)
					, rs.Get<ostring>(10), rs.Get<int>(11), rs.Get<ostring>(12), rs.Get<int>(13), rs.Get<ostring>(14), rs.Get<ostring>(15), rs.Get<ostring>(16), rs.Get<double>(20), rs.Get<double>(18), rs.Get<ostring>(22), rs.Get<ostring>(23), rs.Get<ostring>(24), rs.Get<ostring>(25), rs.Get<ostring>(26), rs.Get<ostring>(27), rs.Get<ostring>(28)
					, rs.Get<ostring>(30), rs.Get<ostring>(31), rs.Get<ostring>(32), rs.Get<ostring>(33), rs.Get<ostring>(34), rs.Get<ostring>(35), rs.Get<ostring>(37), rs.Get<ostring>(38), rs.Get<int>(40), rs.Get<int>(41), rs.Get<ostring>(42), rs.Get<ostring>(43), rs.Get<ostring>(44), rs.Get<ostring>(45), rs.Get<ostring>(46), rs.Get<ostring>(47)
					, rs.Get<int>(56), rs.Get<int>(19), rs.Get<double>(58), rs.Get<int>(59), rs.Get<ostring>(60), rs.Get<int>(61), rs.Get<ostring>(62), rs.Get<ostring>(63), rs.Get<double>(64), rs.Get<double>(65), rs.Get<double>(66), rs.Get<double>(67), rs.Get<int>(68), rs.Get<int>(69), rs.Get<int>(70), rs.Get<int>(71)
					, rs.Get<int>(72), rs.Get<int>(73), rs.Get<int>(74), rs.Get<int>(75), rs.Get<int>(76), rs.Get<int>(77), rs.Get<int>(78), rs.Get<int>(79), rs.Get<int>(82), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3),
					rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8), rs.Get<double>(17));

				indata(SteelCoil::s_SteelCoil, -rs.Get<double>(49), rs.Get<double>(48), rs.Get<ostring>(55), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(80), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(53), nonPRE_DHCRSteelCoil);
			}
		}
		
		/*-----------输出每个钢卷组内的钢卷--------------*/
		
		for (map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>,string>, vector<SteelCoil*>>::iterator iter = s_SteelCoil.begin(); iter != s_SteelCoil.end(); iter++)
		{
			cout << -(*iter).first.first.first.first.first.first.first.first.first.first.first.first.first << endl;
			for (vector<SteelCoil*>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++)
			{
				cout << (*iter1)->mat_no << endl;
			}
		}
		cout << endl << endl;
		int s_GroupCount =s_SteelCoil.size();
		cout << "所有钢卷组的个数:" << "  " << s_GroupCount << endl;//钢卷组个数
		cout << endl ;

		/*-------------输出每个钢卷组内的钢卷---------------*/	
	}

catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();	
}

#pragma region 辅助函数
		//////////////////////////////////////////////////////////////////////////
		SteelCoil::~SteelCoil()
		{
			
		}
		////////////////////////////////////////////////////////////////////////
#pragma endregion

		////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region SteelCoil静态变量
//////////////////////////////////////////////////////////////////////////
int					SteelCoil::s_SteelCoilCount = 0;
map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>>    SteelCoil::s_SteelCoil = map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>>();

////////////////////////////////////////////////////////////////////////
#pragma endregion