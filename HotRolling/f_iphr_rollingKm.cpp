/*************************************************
版权:
作者: 任家硕
日期: 2017-06-21
功能: 热轧轧制单元公里数基准
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 热轧轧制单元公里数基准类
/// <para>存储热轧轧制单元公里数基准信息</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_rollingKm.h"


#pragma region 成员函数
//////////////////////////////////////////////////////////////////////////




#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
rollingKm::rollingKm(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11,
	double value12)
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
	PLAN_TYPE = value10;
	SURF_INDEX_CODE = value11;
	MAX_KM = value12;
	

}


rollingKm::~rollingKm()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai静态变量
//////////////////////////////////////////////////////////////////////////
int							rollingKm::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion