/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �����̹��Ĺ����
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �����̹��Ĺ����
/// <para>�洢�̹��Ĺ����Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////

// �����̹��Ĺ����
class tangguncai
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
	short						MAX_NUM;				// ������
	int							MAX_KM;					// �������
	short						ROLL_WIDTH_MINUS;		// ���ƿ�Ȳ�
	short						HARD_GROUP_MINUS;		// Ӳ�����
	short						SAME_WIDTH_NUM;			// ͬ�����
	short						SAME_WIDTH_KM;			// ͬ�����ƹ�����
	double						SAME_WIDTH;			    // ͬ���巶Χ
	short						NOHARD_PRE_FROM;		// ��Ӳ���̹���λ����
	short						NOHARD_PRE_TO;			// ��Ӳ���̹���λ��ֹ
	string						MAX_HARD_GROUP;			// ���Ӳ����
	short						AFFT_TEMP_PRE_FROM;		// �������¶��̹���λ����
	short						AFFT_TEMP_PRE_TO;		// �������¶��̹���λ��ֹ
	short						AFFT_TEMP_MIN;			// �����¶�����
	short						SAME_WIDTH_PRE_NUM;		// �̹���ͬ�����������


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
	tangguncai(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, short value10, int value11,
		short value12, short value13, short value14, short value15, double value16, short value17, short value18, string value19, short value20, short value21, short value22, short value23);
	//
	// ժҪ:
	//     ����������
	~tangguncai();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};