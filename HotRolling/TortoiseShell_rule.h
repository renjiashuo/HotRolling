/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-06-19
����: �������Ƶ�Ԫ������׼��
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �������Ƶ�Ԫ������׼��
/// <para>�洢���Ƶ�Ԫ������׼��Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// �������Ƶ�Ԫ������׼��
class TortoiseShell_rule
{
#pragma region Variables
public:
	string						REC_CREATOR;			// ��¼����������
	string						REC_CREATE_TIME;		// ��¼����ʱ��
	string						REC_REVISOR;			// ��¼�޸�������
	string						REC_REVISE_TIME;		// ��¼�޸�ʱ��
	string						ARCHIVE_FLAG;			// �鵵���
	string						ARCHIVE_STAMP_NO;		// �鵵�ʴ���
	string						COMPANY_CODE;			// ��˾����
	string						COMPANY_NAME;			// ��˾(����)��������
	string						WHOLE_BACKLOG_CODE;		// ȫ�̹������
	double						MIN_KM;					// ��С������
	double						MAX_KM;					// �������
	double						MIN_WT;					// ��С����
	double						MAX_WT;					// �������
	double						MIN_NUM;				// ��С����
	double						MAX_NUM;				// ������


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
	TortoiseShell_rule(string value1, string value2, string value3, string value4, string value5, string value6, string value7, 
		string value8, string value9, double value10, double value11, double value12, double value13, double value14, double value15);
	//
	// ժҪ:
	//     ����������
	~TortoiseShell_rule();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};