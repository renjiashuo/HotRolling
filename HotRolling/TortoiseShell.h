/*************************************************
��Ȩ:
����: �μ�˶
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
	string							m_tortoiseShellName;		// �ڹ������
	double							m_TortoiseShell_len;		//�ڹ�ǳ���
	int								m_startTime;				// �ڹ�ǿ�ʼʱ��
	int								m_finishTime;				// �ڹ�ǽ���ʱ��
	int								m_timeSpan;				    // �ڹ����ʱ�䣨���ӣ�
	map<pair<int, int>, Group*>		m_groups;				    // �ڹ���ڸ־�����Ϣ��key.first��key.second(��־����λ��)��valueΪ�־���
	
public:// �ڹ�Ǽ���
	static map<string, TortoiseShell*>	s_mapSetOfTortoiseShell;	// �ڹ�ǵ�map���ϣ�keyΪ�ڹ�Ǵ��룬valueΪ�ڹ��
	static int						s_TortoiseShellCount;		   // �ڹ�Ǹ���

#pragma endregion


#pragma region Functions

public:
#pragma region ��������
	//////////////////////////////////////////////////////////////////////////
	static void shell();
	//
	// ժҪ:
	//     ���캯����
	TortoiseShell();
	//
	// ժҪ:
	//     ����������
	~TortoiseShell();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

