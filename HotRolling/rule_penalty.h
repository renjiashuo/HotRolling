/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: IPS_���򷣷���
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_���������
/// <para>�洢IPS_���򷣷���Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// IPS_���򷣷���
class rule_penalty
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
	int							RULE_SET_NO;			// ���򼯺�
	string						RULE_DIV;				// ��������
	string						RULE_TYPE;				// ��������
	int							RULE_NO;				// �����
	int							ZONE_MIN;				// ��������
	int							ZONE_MAX;				// ��������
	int							RULE_SCORE;				// �������
	string						RULE_SCORE_TYPE;		// ������������
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
	rule_penalty(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, int value10, string value11, string value12, int value13, int value14, int value15, int value16,string value17);
	//
	// ժҪ:
	//     ����������
	~rule_penalty();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

	

};

