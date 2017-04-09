/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �־���
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �־���
/// <para>�洢�����־���Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "SteelCoil.h"
#include <iostream>
#include "ocilib.hpp"

using namespace ocilib;
using namespace std;

#pragma region SteelCoil��Ա����
//////////////////////////////////////////////////////////////////////////
struct compwidth
{
	bool operator()(const pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>&A, const pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>&B)const
	{
		if (A.first.first.first.second != B.first.first.first.second)
			return A.first.first.first.second > B.first.first.first.second;
		//return false;
	}
};
SteelCoil::SteelCoil(string value2, double value3, double value4, double value5, string value6, double value7, double value8, int value9, int value10, int value11, int value12, int value13, int value14, int value15)
{
	mat_no = value2;
	SteelCoil_thick = value3;
	SteelCoil_width = value4;
	SteelCoil_len = value5;
	st_no = value6;
	nom_heat_temp = value7;
	nom_afft_temp = value8;
	nom_coil_temp = value9;
	nom_hot_send_flag = value10;
	pre_flag = value11;
	plan_type = value12;
	nom_hard_group_code = value13;
	nom_surf_index_code = value14;
	low_temp_flag = value15;

}/*---------������ͬ���ĸ־�������ָ��vector��ٷ���map----------*/

void indata(map<pair<pair<pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>> &m_data, int a, string b, double c, double d, int e, int f, int g, SteelCoil* h)
{
	if (m_data.find(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(a,b),c),d),e),f),g)) == m_data.end())
	{
		vector<SteelCoil*> temp;
		temp.push_back(h);
		m_data.insert(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(a, b), c), d), e), f), g), temp));
	}
	else
	{
		m_data.find(make_pair(make_pair(make_pair(make_pair(make_pair(make_pair(a, b), c), d), e), f), g))->second.push_back(h);
	}
}

void SteelCoil::SteelCoilgroup()
{
	try
	{
		Environment::Initialize();//������ʼ��
		Connection con(" 127.0.0.1/orcl", "scott", "tiger");//�������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);//�������ݼ�
		ostring rowid;
		st.Execute("select * from DATA1 t order by SLAB_WIDTH DESC");//ѡ���
		Resultset rs = st.GetResultset();
		
		while (rs.Next())
		{
			if (rs.Get<int>(30) == 1)//����DHCR��ǵĸ־������׼��ɸ־������map
			{
				SteelCoil *DHCRSteelCoil = new SteelCoil(rs.Get<ostring>(10), rs.Get<double>(18), rs.Get<double>(19), rs.Get<double>(20), rs.Get<ostring>(22), rs.Get<int>(51), rs.Get<int>(52), rs.Get<int>(53), rs.Get<int>(30), rs.Get<int>(40), rs.Get<int>(56), rs.Get<int>(54), rs.Get<int>(55), rs.Get<int>(82));
				indata(SteelCoil::s_DHCRSteelCoil, rs.Get<int>(56), rs.Get<ostring>(22), rs.Get<double>(18), rs.Get<double>(19), rs.Get<int>(51), rs.Get<int>(52), rs.Get<int>(53), DHCRSteelCoil);
				//SteelCoil::s_DHCRSteelCoil.insert(make_pair(DHCRSteelCoil->mat_no, DHCRSteelCoil));
			}		
			if (rs.Get<int>(40) == 1 && rs.Get<int>(30)==0)//�����̹��ı�ǣ�������DHCR���ĸ־������׼��ɸ־������map
			{
				SteelCoil *PRESteelCoil = new SteelCoil(rs.Get<ostring>(10), rs.Get<double>(18), rs.Get<double>(19), rs.Get<double>(20), rs.Get<ostring>(22), rs.Get<int>(51), rs.Get<int>(52), rs.Get<int>(53), rs.Get<int>(30), rs.Get<int>(40), rs.Get<int>(56), rs.Get<int>(54), rs.Get<int>(55), rs.Get<int>(82));
				indata(SteelCoil::s_pre_flagSteelCoil, rs.Get<int>(56), rs.Get<ostring>(22), rs.Get<double>(18), rs.Get<double>(19), rs.Get<int>(51), rs.Get<int>(52), rs.Get<int>(53), PRESteelCoil);
				//SteelCoil::s_pre_flagSteelCoil.insert(make_pair(PRESteelCoil->mat_no, PRESteelCoil));
			}
			if (rs.Get<int>(40) == 0 && rs.Get<int>(30) == 0)//�����̹��ı�ǣ�������DHCR���ĸ־������׼��ɸ־������map
			{
				SteelCoil *nonPRESteelCoil = new SteelCoil(rs.Get<ostring>(10), rs.Get<double>(18), rs.Get<double>(19), rs.Get<double>(20), rs.Get<ostring>(22), rs.Get<int>(51), rs.Get<int>(52), rs.Get<int>(53), rs.Get<int>(30), rs.Get<int>(40), rs.Get<int>(56), rs.Get<int>(54), rs.Get<int>(55), rs.Get<int>(82));
				indata(SteelCoil::s_nonpre_flagSteelCoil, rs.Get<int>(56), rs.Get<ostring>(22), rs.Get<double>(18), rs.Get<double>(19), rs.Get<int>(51), rs.Get<int>(52), rs.Get<int>(53), nonPRESteelCoil);
				//SteelCoil::s_nonpre_flagSteelCoil.insert(make_pair(nonPRESteelCoil->mat_no, nonPRESteelCoil));
			}			
		}
		
		/*-----------���ÿ���־����ڵĸ־�--------------*/
		for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = s_DHCRSteelCoil.begin(); iter != s_DHCRSteelCoil.end(); iter++)
		{
			cout << (*iter).first.first.first.first.second << endl;//���ÿ���־���Ŀ��
			for (vector<SteelCoil*>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++)
			{
				cout << (*iter1)->mat_no << endl;
			}
		}
		cout << endl << endl;
		for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = s_pre_flagSteelCoil.begin(); iter != s_pre_flagSteelCoil.end(); iter++)
		{
			cout << (*iter).first.first.first.first.second << endl;
			for (vector<SteelCoil*>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++)
			{
				cout << (*iter1)->mat_no << endl;
			}
		}
		cout << endl << endl;
		for (map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>::iterator iter = s_nonpre_flagSteelCoil.begin(); iter != s_nonpre_flagSteelCoil.end(); iter++)
		{
			
			cout << (*iter).first.first.first.first.second << endl;
			for (vector<SteelCoil*>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++)
			{
				cout << (*iter1)->mat_no << endl;
			}
		}
		int s_GroupCount = s_DHCRSteelCoil.size() + s_nonpre_flagSteelCoil.size() + s_pre_flagSteelCoil.size();
		cout << "���и־���ĸ���:" << "  " << s_GroupCount << endl;//�־������
		cout << endl ;

		/*-------------���ÿ���־����ڵĸ־�---------------*/	
	}

catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();	
}

#pragma region ��������
		//////////////////////////////////////////////////////////////////////////
		SteelCoil::~SteelCoil()
		{
			
		}
		////////////////////////////////////////////////////////////////////////
#pragma endregion

		////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region SteelCoil��̬����
		//////////////////////////////////////////////////////////////////////////
		//map<string, SteelCoil*>		SteelCoil::s_mapSetOfSteelCoil = map<string, SteelCoil*>();
		int					SteelCoil::s_SteelCoilCount = 0;
		map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>    SteelCoil::s_pre_flagSteelCoil = map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>();
		map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>    SteelCoil::s_nonpre_flagSteelCoil = map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>();
		map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>    SteelCoil::s_DHCRSteelCoil = map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>();
		//map< pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>    SteelCoil::s_mapSetOfSteelCoilgroup = map< pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>();
////////////////////////////////////////////////////////////////////////
#pragma endregion