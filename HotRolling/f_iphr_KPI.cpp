/*************************************************
��Ȩ:
����: �μ�˶
����: 2017-06-21
����: �ؼ�ָ�궨��
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �ؼ�ָ�궨����
/// <para>�洢�ؼ�ָ�궨����Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_KPI.h"


#pragma region ��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
keyindicatorDef::keyindicatorDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, int value10, string value11,
	string value12,  double value13)
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
	ITEM_CODE = value11;
	ITEM_NAME = value12;
	RULE_POWER = value13;
}


keyindicatorDef::~keyindicatorDef()
{
}

void keyindicatorDef::release()
{
	keyindicatorDef::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai��̬����
//////////////////////////////////////////////////////////////////////////
int							keyindicatorDef::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion