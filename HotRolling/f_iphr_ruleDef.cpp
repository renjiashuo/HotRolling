/*************************************************
��Ȩ:
����: �μ�˶
����: 2017-06-21
����: IPS_������
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_��������
/// <para>�洢IPS_��������Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_ruleDef.h"


#pragma region ��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
ruleDef::ruleDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11,
	int value12, string value13,int value14)
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
	RULE_DIV = value10;
	RULE_TYPE = value11;
	RULE_NO = value12;
	RULE_DESC = value13;
	RULE_SCORE = value14;
}


ruleDef::~ruleDef()
{
}

void ruleDef::release()
{
	ruleDef::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai��̬����
//////////////////////////////////////////////////////////////////////////
int							ruleDef::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion