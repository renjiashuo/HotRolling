/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 关键指标定义类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 关键指标定义类
/// <para>存储关键指标定义信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 关键指标定义类
class keyindicator_def
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
	string						RULE_APPLIC_MODUEL;		// 规则应用模块
	int							RULE_SET_NO;			// 规则集号
	string						ITEM_CODE;				// 项目代码
	string						ITEM_NAME;				// 项目名称
	double						RULE_POWER;				// 规则权重
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
	keyindicator_def(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, int value10, string value11, string value12, double value13);
	//
	// 摘要:
	//     析构函数。
	~keyindicator_def();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion
};