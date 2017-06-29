/*************************************************
版权:
作者: 任家硕
日期: 2017-06-21
功能: IPS_规则定义
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_规则定义类
/// <para>存储IPS_规则定义信息</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_ruleDef.h"


#pragma region 成员函数
//////////////////////////////////////////////////////////////////////////




#pragma region 辅助函数
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

#pragma region zhuticai静态变量
//////////////////////////////////////////////////////////////////////////
int							ruleDef::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion