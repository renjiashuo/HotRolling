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
	int						group_no;			// �־������
	int						plan_type;			// �ƻ�����
	string					st_no;				// ���ּǺţ����֣�	
	double					nom_roll_thick;		// ����ƺ��
	double					nom_roll_width;		// ����ƿ��
	int						nom_heat_temp;		// ���¯�¶�
	int						nom_afft_temp;		// ������¶�
	int						nom_coil_temp;		// ���ȡ�¶�
	//double					roll_len;         // ���Ƴ���
	vector<SteelCoil*>		m_SteelCoil;        //���ÿ���־���ĸ־�
	//string					sg_sign;			// �ƺţ��ּ���
	//map<string, SteelCoil*>			m_SteelCoil;				// �����־�keyΪ�־�ţ�valueΪ�־�
	map<int, SteelCoil*>			m_SteelCoilTime;			// �־�ƻ�����ʱ�䣬keyΪ�־����ƿ�ʼʱ�䣬valueΪ�־�С�־���ļƻ����ԣ��ڲ��ĸ־�˳�򣬰�ʱ������

public:// �־��鼯��
	static map<int, Group*>	s_mapSetOfGroup;			// ��DHCR��Ǻ����̹��ı�ǵĸ־����map���ϣ�keyΪ�־�����룬valueΪ�־���
	static map<int, Group*>	s_mapSetOfGroup1;			// ���̹��ı�ǵĸ־����map����,keyΪ�־�����룬valueΪ�־���
	static map<string, Group*>  s_mapSetOfsmallGroup;		// С�־����map���ϣ�key��С�վ�����룬value�Ǹ־���ָ��
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
	//     ���캯����
Group(int value1, int value2, string value3, double value4, double value5, int value6, int value7, int value8,vector<SteelCoil*>&value9);
	//
	// ժҪ:
	//     ����������
	~Group();
	
	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

