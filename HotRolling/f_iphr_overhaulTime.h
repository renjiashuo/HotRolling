/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-06-19
����: IPS_������ʱ���趨��  TIP00SI11
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_������ʱ���趨��
/// <para>�洢IPS_������ʱ���趨��Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// IPS_������ʱ���趨��
class overhaulTime
{
#pragma region Variables
public:
	string						REC_CREATOR;			// ��¼����������
	string						REC_CREATE_TIME;		// ��¼����ʱ��
	string						REC_REVISOR;			// ��¼�޸�������
	string						REC_REVISE_TIME;		// ��¼�޸�ʱ��
	string						ARCHIVE_FLAG;			// �鵵���
	string						ARCHIVE_TIME;			// �鵵ʱ��	
	string						WHOLE_BACKLOG_CODE;		// ȫ�̹������
	string						UNIT_CODE;				// �������
	string						CONS_TYPE;				// �������
	string						S_DATETIME;				// ��ʼʱ��
	string						E_DATETIME;				// ����ʱ��
	string						LINE_DIF;				// ��������



public:
	static	int		row;								// ������

#pragma endregion


#pragma region Functions

public:
#pragma region ��������
	//////////////////////////////////////////////////////////////////////////

	//
	// ժҪ:
	//     ���캯����
	overhaulTime(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
		string value8, string value9, string value10, string value11, string value12);
	//
	// ժҪ:
	//     ����������
	~overhaulTime();
	//
	// ժҪ:
	//     �ͷ�����static�ġ�
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};