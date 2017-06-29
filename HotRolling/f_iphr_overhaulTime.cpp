/*************************************************
版权:
作者: 任家硕
日期: 2017-06-21
功能: IPS_定检修时间设定
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_定检修时间设定类
/// <para>存储IPS_定检修时间设定信息</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_overhaulTime.h"


#pragma region 成员函数
//////////////////////////////////////////////////////////////////////////




#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
overhaulTime::overhaulTime(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, string value12)
{
	REC_CREATOR = value1;
	REC_CREATE_TIME = value2;
	REC_REVISOR = value3;
	REC_REVISE_TIME = value4;
	ARCHIVE_FLAG = value5;
	ARCHIVE_TIME = value6;	
	WHOLE_BACKLOG_CODE = value7;
	UNIT_CODE = value8;
	CONS_TYPE = value9;
	S_DATETIME = value10;
	E_DATETIME = value11;
	LINE_DIF = value12;

}


overhaulTime::~overhaulTime()
{
}

void overhaulTime::release()
{
	overhaulTime::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai静态变量
//////////////////////////////////////////////////////////////////////////
int							overhaulTime::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion