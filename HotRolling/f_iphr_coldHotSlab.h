/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-06-19
����: ���������������׼��  TIPHRE3
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// ���������������׼��
/// <para>�洢���������������׼��Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// ���������������׼
class coldHotSlab
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
	string						STORE_AREA;				// �洢����
	double						MIN_CUT_HOUR;			// ��С�ж�ʱ
	double						MAX_CUT_HOUR;			// ����ж�ʱ
	string						COLD_HOT_FLAG;			// ���ȱ�־
	


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
	coldHotSlab(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
		string value8, string value9, string value10, double value11, double value12, string value13);
	//
	// ժҪ:
	//     ����������
	~coldHotSlab();
	//
	// ժҪ:
	//     �ͷ�����static�ġ�
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};