/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-06-19
����: �������Ƶ�Ԫ��������׼��  TIPHRB8
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �������Ƶ�Ԫ��������׼��
/// <para>�洢�������Ƶ�Ԫ��������׼��Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// �������Ƶ�Ԫ��������׼��
class rollingKm
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
	string						WHOLE_BACKLOG_CODE;	// ȫ�̹������
	string						PLAN_TYPE;			// �ƻ�����
	string						SURF_INDEX_CODE;		// ����ָ������
	double						MAX_KM;				// �������
	



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
	rollingKm(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
		string value8, string value9, string value10, string value11, double value12);
	//
	// ժҪ:
	//     ����������
	~rollingKm();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};