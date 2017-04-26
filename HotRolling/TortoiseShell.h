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

#include "global.h"
#include "SteelCoil.h"
#include "Group.h"

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
	int									m_tortoiseShellName;		// �ڹ������
	double								m_TortoiseShell_len;		// �ڹ�ǳ���
	double								m_TortoiseShell_WT;		// �ڹ������
	double								m_TortoiseShellflow10_WT;	// �ڹ��������10�־�����
	double								m_TortoiseShell_DHCR;		// �ڹ��DHCR����
	double								m_TortoiseShell_len1;		// �ڹ�ǳ���(��)
	double								m_TortoiseShell_WT1;		// �ڹ������(��)
	double								m_TortoiseShellflow10_WT1;	// �ڹ��������10�־�����(��)
	double								m_TortoiseShell_DHCR1;		// �ڹ��DHCR����(��)
	double								m_TortoiseShell_len_temp;	// �ڹ��ʵʱ����		
	double								m_tang_len;				// ���䵽�ڹ������̹��ĳ���
	int									m_startTime;				// �ڹ�ǿ�ʼʱ��
	int									m_finishTime;				// �ڹ�ǽ���ʱ��
	int									m_timeSpan;				// �ڹ����ʱ�䣨���ӣ�			
	map<pair<int, int>, Group*>				m_groups_temp;			// �ڹ������ʱ����ĸ־�����Ϣ��key.first��ȣ�key.second���ظ���ţ�valueΪ�־���
	map<pair<int, int>, Group*>				m_groups;					// �ڹ���ڸ־�����Ϣ��key.first��key.second(��־����λ��)��valueΪ�־���
	map<pair<int, int>, Group*>				m_pre_groups;				// �ڹ�����̹��ĸ־�����Ϣ��key.first��key.second(��־����λ��)��valueΪ�־���
	map<pair<int, int>, Group*>				m_main_groups;			// �ڹ��������ĸ־�����Ϣ��key.first��key.second(��־����λ��)��valueΪ�־���
	
public:// �ų̹����м�¼����
	map<double, double>					width_lonth;				// Ŀǰ�ڹ����ÿ�����ƿ�ȶ�Ӧ���Ѵ��ڵĹ�������ֻ������ģ����̹��ģ�
	//double							nom_roll_width;				// Ŀǰ�ڹ�������һ���־���Ķ���ƿ��
	//double							same_width_lonth;			// Ŀǰ���һ���־����ȵ�ͬ������
	
public:// �ڹ�Ǽ���
	static map<int, TortoiseShell*>		s_mapSetOfTortoiseShell;	// �ڹ�ǵ�map���ϣ�keyΪ�ڹ�Ǵ��룬valueΪ�ڹ��
	static int							s_TortoiseShellCount;		// �ڹ�Ǹ���
	static double						allTortoiseShell_len;		// �����ڹ���ܳ���
	static double						m_DHCR;						// ��DHCR��Ǹ־�����
	static double						allflow10_wt;				// ����10�־�������
	static double						allsteelcCoil_wt;			// �־�����
public:// �ƻ��������
	static map<pair<string, string>, string> plantype;

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
	//     ����������
	~TortoiseShell();
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
	//     ���·���δ����ɹ��ĸ־�
	static void ReFinishShell();
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
	//     ����KPI��
	static void computekpi();
	//
	// ժҪ:
	//     ���ڹ�ǵ�������һ������ġ�
	void addMainGroup(Group *group);
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma endregion

};

