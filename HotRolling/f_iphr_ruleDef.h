/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: IPS_��������� TIP00SI01
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_���������
/// <para>�洢��������Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// ���������
class ruleDef
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
	string						RULE_DESC;				// ��������
	int							RULE_SCORE;				// �������
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
	ruleDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, int value12, string value13, int value14);
	//
	// ժҪ:
	//     ����������
	~ruleDef();
	//
	// ժҪ:
	//     �ͷ�����static�ġ�
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

	



};