/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: IPS_规则集定义类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_规则集定义类
/// <para>存储规则集定义信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// IPS_规则集定义类
class rulesetDef
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
	string						RULE_DIV;				// 规则区分
	string						RULE_TYPE;				// 规则类型
	int							RULE_NO;				// 规则号
	string						RULE_SET_DESC;			// 规则集描述
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
	rulesetDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, int value10, string value11, string value12, int value13, string value14);
	//
	// 摘要:
	//     析构函数。
	~rulesetDef();
	//
	// 摘要:
	//     释放所有static的。
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};