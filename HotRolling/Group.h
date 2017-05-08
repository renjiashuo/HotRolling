/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �־�����
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �־�����
/// <para>�洢�����־�����Ϣ</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "global.h"
#include "SteelCoil.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////
void vec_group();


class Group;	// �־�����
class SteelCoil;	// �־���
//////////////////////////////////////////////////////////////////////////

// �־�����
class Group
{

#pragma region Variables

public:// �־������
	int						group_no;				// �־������
	string					plan_type;				// �ƻ�����
	string					st_no;					// ���ּǺţ����֣�	
	double					nom_roll_thick;			// ����ƺ��
	double					nom_roll_width;			// ����ƿ��
	int						nom_heat_temp;			// ���¯�¶�
	int						nom_afft_temp;			// ������¶�
	int						nom_coil_temp;			// ���ȡ�¶�
	string					high_temp_flag;			// ���±��
	double					roll_len;				// ���Ƴ���
	double					slab_wt;				// ��������
	int						zone_max_num;			// ����������
	int						zone_min_num;			// ������С����
	int						zone_max_m;				// �����������
	int						zone_min_m;				// ������С����
	vector<SteelCoil*>			m_SteelCoil;			// ���ÿ���־���ĸ־�
	//string					sg_sign;				// �ƺţ��ּ���
	//map<int, SteelCoil*>			m_SteelCoilTime;			// �־�ƻ�����ʱ�䣬keyΪ�־����ƿ�ʼʱ�䣬valueΪ�־�С�־���ļƻ����ԣ��ڲ��ĸ־�˳�򣬰�ʱ������

public:// �־��鼯��
	static map<double, Group*>  s_least;					// ɾ���־���ļ���
	static map<int, Group*>	s_mapSetOfGroup;			// �־����map���ϣ�keyΪ�־�����룬valueΪ�־���
	static map<int, Group*>	s_mapSetOfsmallGroup;		// С�־����map���ϣ�key��С�վ�����룬value�Ǹ־���ָ��
	static int				s_GroupCount;				// �־������     
#pragma endregion

	
#pragma region Functions

public:
#pragma region ��������
	//////////////////////////////////////////////////////////////////////////
	//
	// ժҪ:
	//     �������ɵĸ־��飬���ɸ־�������󣬽��־����ŷ���map�����
	static	void vec_group();
	//
	// ժҪ:
	//     ���캯������ʼ��һ���־��顣
	Group(int value1, double value2, double value3, string value4, string value5, int value6, int value7, int value8, string value10, int value11, int value12, int value13, int value14, vector<SteelCoil*>&value9);
	//
	// ժҪ:
	//     ���캯�������־����ǰn���־����µĸ־��顣
	Group(Group *group,int n);
	//
	// ժҪ:
	//     ���캯�������־����ǰlonth�������ĸ־����µĸ־��顣
	Group(Group *group, double lonth);
	//
	// ժҪ:
	//     ����������
	~Group();
	
	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

