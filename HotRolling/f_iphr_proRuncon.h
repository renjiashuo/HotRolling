/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �����ƻ�ģ�ͳ������п����� TIPHR09
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �����ƻ�ģ�ͳ������п��Ʊ���
/// <para>�洢�����ƻ�ģ�ͳ������п�����Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// �ؼ�ָ�궨����
class proRuncon
{
#pragma region Variables
public:
	string						REC_CREATOR;			// ��¼����������
	string						REC_CREATE_TIME;		// ��¼����ʱ��
	string						REC_REVISOR;			// ��¼�޸�������
	string						REC_REVISE_TIME;		// ��¼�޸�ʱ��
	string						ARCHIVE_FLAG;			// �鵵���
	string						ARCHIVE_STAMP_NO;		// �鵵�ʴ���
	string						MOD_STAMP_NO;			// ģ���ʴ���
	string						PROGRAM_NAME;			// ������
	string						WHOLE_BACKLOG_CODE;		// ȫ�̹������
	string						PLAN_MAKER;				// �ƻ�������
	string						PLANNED_START_TIME;		// �ƻ���ʼʱ��
	string						PLAN_CLASS;				// �ƻ�����
	string						PROC_STATUS;			// ����״̬
	string						HALF_PLAN_FLAG;			//�������ƻ����
	string						CURR_PLAN_NO;			//��ǰ�ƻ���
	string						ROLL_CHG_FLAG;			//֧�Ź��������
	int							PLAN_FUR_NUM;			//�ƻ�����¯��¯��
	string						USE_PRE_FLAG;			//ʹ���̹��ı��
	string						CON_SLAB_FLAG;			//���Ӱ���ʹ�ñ��
	int							PLAN_NUM;				//�ƻ�����
	int							MUST_DO_FLAG;			//�������
	double						RETURN_ERROR_CODE;		//���س������
	string						RETURN_ERROR_MSG;		//���س�����Ϣ
	double						RULE_SET_NO;			//���򼯺�

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
	proRuncon(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, string value12, string value13,
		string value14, string value15, string value16,int value17,string value18,string value19,int value20,int value21,double value22,string value23,double value24);
	//
	// ժҪ:
	//     ����������
	~proRuncon();
	//
	// ժҪ:
	//     �ͷ�����static�ġ�
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion
};