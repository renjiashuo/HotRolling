/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: IPS_������������� TIP00SI02
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_��������������
/// <para>�洢IPS_�������������Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// IPS_�������������
class ruleparaDef
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
	string						RULE_APPLIC_MODUEL;		// ����Ӧ��ģ��
	string						RULE_DIV;				// ��������
	string						RULE_TYPE;				// ��������
	int							RULE_NO;				// �����
	int							RULE_PARA_NO;			// ���������
	string						RULE_PARA_VAL;			// �������ֵ
	string						RULE_PARA_VAL_FLAG;		// �������ֵ���
	string						RULE_PARA_DESC;			// �����������
	string						RULE_PARA_SOURCE;		// �������Դֵ
	string						RULE_PARA_TYPE;			// �����������
	string						FORWARD_BACK_FLAG;		// ����������
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
	ruleparaDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, int value12, int value13, string value14, string value15, string value16, string value17, string value18, string value19);
	//
	// ժҪ:
	//     ����������
	~ruleparaDef();
	//
	// ժҪ:
	//     �ͷ�����static�ġ�
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

