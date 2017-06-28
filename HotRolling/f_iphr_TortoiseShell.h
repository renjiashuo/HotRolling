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

#pragma once

#include "f_iphr_global.h"
#include "f_iphr_SteelCoil.h"
#include "f_iphr_Group.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

class Group;			// �־�����
class SteelCoil;		// �־���
class TortoiseShell;	// �ڹ����
struct rule_score;		// ���ֱ�
//////////////////////////////////////////////////////////////////////////

// �ڹ����
class TortoiseShell
{

#pragma region Variables

public:// �ڹ�ǲ���
	int									penalty;					// �ڹ�Ƿ���   
	int									m_tortoiseShellName;		// �ڹ������
	double								m_TortoiseShell_len;		// �ڹ�ǳ���
	double								m_TortoiseShell_WT;			// �ڹ������
	//double								m_TortoiseShellflow10_WT;	// �ڹ��������10�־�����
	double								m_TortoiseShell_DHCR;		// �ڹ��DHCR����
	double								m_TortoiseShell_len1;		// �ڹ�ǳ���(��)
	double								m_TortoiseShell_WT1;		// �ڹ������(��)
	double								m_TortoiseShellflow10_WT1;	// �ڹ��������10�־�����(��)
	double								m_TortoiseShell_DHCR1;		// �ڹ��DHCR����(��)	

	//double							m_tang_len;					// ���䵽�ڹ������̹��ĳ���			
	map<pair<int, int>, Group*>			m_pre_groups;				// �ڹ�����̹��ĸ־�����Ϣ��key.first��key.second(��־����λ��)��valueΪ�־���
	map<pair<int, int>, Group*>			m_main_groups;				// �ڹ��������ĸ־�����Ϣ��key.first��key.second(��־����λ��)��valueΪ�־���
	map<pair<int, int>, SteelCoil*>		m_main_SteelCoil;			// �Ը־�Ϊ��λ����ڹ����ĸ־�
public:// �ų̹����м�¼����
	int									steelCoilNum;				// �ڹ���ڸ־���
	int									steelCoilLenth;				// �ڹ��Ŀǰ������
	int									high_num;					// �ڹ�������и��¾����
	int									high_temp_coil_num;			// ĩβ�������¾�ĸ־���
	int									low_temp_coil_num;			// ĩβ�������¾�ĸ־���
	int									coil_flag;					// ��һ���־�����ԣ�0Ϊ���¾�1Ϊ���¾�
	
public:// �ڹ�Ǽ���
	static map<int, TortoiseShell*>		s_mapSetOfTortoiseShell;	// �ڹ�ǵ�map���ϣ�keyΪ�ڹ�Ǵ��룬valueΪ�ڹ��
	static int							s_TortoiseShellCount;		// �ڹ�Ǹ���
	static double						allTortoiseShell_len;		// �����ڹ���ܳ���
	//static double						m_DHCR;						// ��DHCR��Ǹ־�����
	//static double						allflow10_wt;				// ����10�־�������
	static double						allsteelcCoil_wt;			// �־�����
	static double						best_kpi;					// ����kpiֵ
	static int							all_penalty;				// �����ڹ�Ƿ����ܺ�
	static double						flow_rate ;
	static double						DHCR_rate ;
	static double						order_rate ;
	static double						Scheduling_quality ;
	static double						rollingkm_rate ;
public:
	static map<pair<string, string>, string> plantype;				// �ƻ�������ϼ���
	static map<pair<double, string>, double> flowrule;				// ���ݱ��������趨����
	static map<pair<double, string>, double> actualflow;			// �ų̽��������򼯺�

#pragma endregion


#pragma region Functions

public:
	#pragma region ��������
	//////////////////////////////////////////////////////////////////////////
	//
	// ժҪ:
	//     ���캯���������������ʼ���ڹ�ǡ�
	TortoiseShell(Group *group);
	//
	// ժҪ:
	//     ���캯������ɾ���־����ʼ���ڹ�ϡ�
	TortoiseShell();
	//
	// ժҪ:
	//     ����������
	~TortoiseShell();
	//
	// ժҪ:
	//     �ͷ�����static map��ָ�롣
	static void release();
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region �ڹ�Ǽƻ����
	//////////////////////////////////////////////////////////////////////////
	//
	// ժҪ:
	//     ������ʼ�ڹ�ǡ�
	static void InitShell();
	//
	// ժҪ:
	//     ����ڹ�ǳ�ʼ�⡣
	static void FinishShell();
	//
	// ժҪ:
	//     ����������¶ο�����Χ�����¶ο�����Χ������λ���䷶Χ�ĸ־����·���δ����־����С�
	static void DeleteBad();
	//
	// ժҪ:
	//     ����KPI��
	static double computekpi();
	//
	// ժҪ:
	//     �������̨չʾ��
	static void showResult();
	//
	// ժҪ:
	//     ���������ı���
	static void showResultFile();	
	//
	// ժҪ:
	//     ���ڹ�ǵ�������һ������ģ�����ɹ�����true������ʧ�ܷ���false�������ָ־��顣
	bool addMainGroup(Group *group);
	//
	// ժҪ:
	//     ���ڹ�ǵ�������һ������ģ�����ɹ�����true������ʧ�ܷ���false���������ָ־��顣
	bool addMainGroup2(Group *group);
	//
	// ժҪ:
	//     ���������㷨���ڹ��֮��ĸ־��黥��������������Ͱ��
	static void localsearch();
	//
	// ժҪ:
	//     ���������㷨���ڹ�Ǻ�����Ͱ�ĸ־��黥��
	static void localsearch1();
	//
	// ժҪ:
	//     ���������㷨���ڹ���ڲ��ĸ־��黥��
	static void localsearch2();
	//
	// ժҪ:
	//     ���������㷨�����ڹ�����־���
	static void localsearch3();
	//
	// ժҪ:
	//     ���������㷨���ڹ�Ǽ�־���
	static void localsearch4();
	//
	// ժҪ:
	//     ����ÿ���־�������ɵ�ʱ��
	static void calculateRollingFinishTime();
	//
	// ժҪ:
	//     DatetimeToString
	static string DatetimeToString(time_t time);
	//
	// ժҪ:
	//     StringToDatetime
	static time_t StringToDatetime(string str);
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma endregion

};

