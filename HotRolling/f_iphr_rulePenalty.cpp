/*************************************************
��Ȩ:
����: �μ�˶
����: 2017-06-21
����: IPS_���򷣷���
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_���򷣷���
/// <para>�洢IPS_���򷣷���Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_rulePenalty.h"


#pragma region ��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
rulePenalty::rulePenalty(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, int value10, string value11,
	string value12, int value13, int value14, int value15, int value16,string value17)
{
	REC_CREATOR = value1;
	REC_CREATE_TIME = value2;
	REC_REVISOR = value3;
	REC_REVISE_TIME = value4;
	ARCHIVE_FLAG = value5;
	ARCHIVE_STAMP_NO = value6;
	COMPANY_CODE = value7;
	COMPANY_NAME = value8;
	RULE_APPLIC_MODUEL = value9;
	RULE_SET_NO = value10;
	RULE_DIV = value11;
	RULE_TYPE = value12;
	RULE_NO = value13;
	ZONE_MIN = value14;
	ZONE_MAX = value15;
	RULE_SCORE = value16;
	RULE_SCORE_TYPE = value17;
}


rulePenalty::~rulePenalty()
{
}

void rulePenalty::release()
{
	rulePenalty::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai��̬����
//////////////////////////////////////////////////////////////////////////
int							rulePenalty::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion