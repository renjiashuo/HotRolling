/*************************************************
版权:
作者: 任家硕
日期: 2017-03-22
功能: 主体材类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 乌龟壳类
/// <para>存储主体材信息</para>
/// </summary>
===========================================================</remark>*/

#include "TortoiseShell.h"
#include "global.h"
#include "zhuticai.h"


#pragma region TortoiseShell成员函数
//////////////////////////////////////////////////////////////////////////




#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
zhuticai::zhuticai(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, short value10, int value11,
	short value12, short value13, short value14, short value15, double value16)
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
	MAX_NUM = value10;
	MAX_KM = value11;
	ROLL_WIDTH_MINUS = value12;
	HARD_GROUP_MINUS = value13;
	SAME_WIDTH_NUM = value14;
	SAME_WIDTH_KM = value15;
	SAME_WIDTH = value16;
}


zhuticai::~zhuticai()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai静态变量
//////////////////////////////////////////////////////////////////////////
int							zhuticai::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion