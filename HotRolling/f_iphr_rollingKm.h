/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-06-19
功能: 热轧轧制单元公里数基准类  TIPHRB8
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 热轧轧制单元公里数基准类
/// <para>存储热轧轧制单元公里数基准信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 热轧轧制单元公里数基准类
class rollingKm
{
#pragma region Variables
public:
	string						REC_CREATOR;			// 记录创建责任者
	string						REC_CREATE_TIME;		// 记录创建时刻
	string						REC_REVISOR;			// 记录修改责任者
	string						REC_REVISE_TIME;		// 记录修改时刻
	string						ARCHIVE_FLAG;			// 归档标记
	string						ARCHIVE_STAMP_NO;		// 归档邮戳号
	string						COMPANY_CODE;			// 公司代码
	string						COMPANY_NAME;			// 公司(帐套)中文名称
	string						WHOLE_BACKLOG_CODE;	// 全程工序代码
	string						PLAN_TYPE;			// 计划类型
	string						SURF_INDEX_CODE;		// 表面指数代码
	double						MAX_KM;				// 最大公里数
	



public:
	static	int		row;								// 表行数

#pragma endregion


#pragma region Functions

public:
#pragma region 辅助函数
	//////////////////////////////////////////////////////////////////////////

	//
	// 摘要:
	//     构造函数。
	rollingKm(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
		string value8, string value9, string value10, string value11, double value12);
	//
	// 摘要:
	//     析构函数。
	~rollingKm();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};