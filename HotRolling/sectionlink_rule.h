/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: ���νӹ�����
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_���νӹ������
/// <para>�洢���νӹ�����Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// ���νӹ�����
class sectionlink_rule
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
	string						SECTION_NO1;			// �ֶκ�1
	string						SECTION_NO2;			// �ֶκ�2
	string						MIX_MODE;				// ��Ϸ�ʽ
	int							PRIOR_SEQ_NO;			// ����˳��
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
	sectionlink_rule(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, int value12, string value13, string value14, string value15,int value16);
	//
	// ժҪ:
	//     ����������
	~sectionlink_rule();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};