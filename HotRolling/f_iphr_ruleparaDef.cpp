/*************************************************
��Ȩ:
����: �μ�˶
����: 2017-06-21
����: IPS_�����������
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_�������������
/// <para>�洢IPS_�������������Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_ruleparaDef.h"


#pragma region ��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
ruleparaDef::ruleparaDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11,
	int value12, int value13, string value14, string value15, string value16, string value17, string value18, string value19 )
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
	RULE_PARA_NO = value13;
	RULE_PARA_VAL = value14;
	RULE_PARA_VAL_FLAG = value15;
	RULE_PARA_DESC = value16;
	RULE_PARA_SOURCE = value17;
	RULE_PARA_TYPE = value18;
	FORWARD_BACK_FLAG = value19;
}


ruleparaDef::~ruleparaDef()
{
}

void ruleparaDef::release()
{
	ruleparaDef::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai��̬����
//////////////////////////////////////////////////////////////////////////
int							ruleparaDef::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion