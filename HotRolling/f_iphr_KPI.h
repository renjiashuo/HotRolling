/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �ؼ�ָ�궨���� TIP00SI06
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �ؼ�ָ�궨����
/// <para>�洢�ؼ�ָ�궨����Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// �ؼ�ָ�궨����
class keyindicatorDef
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
	string						ITEM_CODE;				// ��Ŀ����
	string						ITEM_NAME;				// ��Ŀ����
	double						RULE_POWER;				// ����Ȩ��
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
	keyindicatorDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, int value10, string value11, string value12, double value13);
	//
	// ժҪ:
	//     ����������
	~keyindicatorDef();
	//
	// ժҪ:
	//     �ͷ�����static�ġ�
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion
};