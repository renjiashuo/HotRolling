/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-06-19
功能: 热轧轧制单元总量基准类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 热轧轧制单元总量基准类
/// <para>存储轧制单元总量基准信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_TortoiseShellRule.h"

#pragma region TortoiseShell成员函数
//////////////////////////////////////////////////////////////////////////




#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
TortoiseShellRule::TortoiseShellRule(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
	string value8, string value9, double value10, double value11, double value12, double value13, double value14, double value15)
{
	REC_CREATOR = value1;
	REC_CREATE_TIME = value2;
	REC_REVISOR = value3;
	REC_REVISE_TIME = value4;
	ARCHIVE_FLAG = value5;
	ARCHIVE_STAMP_NO = value6;
	COMPANY_CODE = value7;
	COMPANY_NAME = value8;
	WHOLE_BACKLOG_CODE = value9;
	MIN_KM = value10;	
	MAX_KM = value11;
	MIN_WT = value12;
	MAX_WT = value13;
	MIN_NUM = value14;
	MAX_NUM = value15;
	
}


TortoiseShellRule::~TortoiseShellRule()
{
}

void TortoiseShellRule::release()
{
	TortoiseShellRule::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai静态变量
//////////////////////////////////////////////////////////////////////////
int							TortoiseShellRule::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion