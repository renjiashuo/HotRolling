/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-06-19
功能: 热轧冷热坯定义基准类  TIPHRE3
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 热轧冷热坯定义基准类
/// <para>存储热轧冷热坯定义基准信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 热轧冷热坯定义基准
class coldHotSlab
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
	string						STORE_AREA;				// 存储区域
	double						MIN_CUT_HOUR;			// 最小切断时
	double						MAX_CUT_HOUR;			// 最大切断时
	string						COLD_HOT_FLAG;			// 冷热标志
	


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
	coldHotSlab(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
		string value8, string value9, string value10, double value11, double value12, string value13);
	//
	// 摘要:
	//     析构函数。
	~coldHotSlab();
	//
	// 摘要:
	//     释放所有static的。
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};