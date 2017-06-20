/*************************************************
版权:
作者: 任家硕
日期: 2017-03-22
功能: 乌龟壳类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 乌龟壳类
/// <para>存储乌龟壳信息</para>
/// </summary>
===========================================================</remark>*/

#include "TortoiseShell.h"
#include "global.h"
#include"tangguncai.h"


#pragma region TortoiseShell成员函数
//////////////////////////////////////////////////////////////////////////




#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
tangguncai::tangguncai(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, short value10, int value11,
	short value12, short value13, short value14, short value15, double value16, short value17, short value18, string value19, short value20, short value21, short value22, short value23)
{
	REC_CREATOR=value1;			
	REC_CREATE_TIME=value2;		
	REC_REVISOR=value3;			
	REC_REVISE_TIME=value4;
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
	NOHARD_PRE_FROM = value17;
	NOHARD_PRE_TO = value18;
	MAX_HARD_GROUP = value19;
	AFFT_TEMP_PRE_FROM = value20;
	AFFT_TEMP_PRE_TO = value21;
	AFFT_TEMP_MIN = value22;
	SAME_WIDTH_PRE_NUM = value23;
}


tangguncai::~tangguncai()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region tangguncai静态变量
//////////////////////////////////////////////////////////////////////////
int							tangguncai::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion