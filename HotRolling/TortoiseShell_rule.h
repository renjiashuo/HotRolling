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

#include "global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 热轧轧制单元总量基准类
class TortoiseShell_rule
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
	string						WHOLE_BACKLOG_CODE;		// 全程工序代码
	double						MIN_KM;					// 最小公里数
	double						MAX_KM;					// 最大公里数
	double						MIN_WT;					// 最小重量
	double						MAX_WT;					// 最大重量
	double						MIN_NUM;				// 最小块数
	double						MAX_NUM;				// 最大块数


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
	TortoiseShell_rule(string value1, string value2, string value3, string value4, string value5, string value6, string value7, 
		string value8, string value9, double value10, double value11, double value12, double value13, double value14, double value15);
	//
	// 摘要:
	//     析构函数。
	~TortoiseShell_rule();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};