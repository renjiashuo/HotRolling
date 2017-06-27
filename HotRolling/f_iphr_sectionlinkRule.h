/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 段衔接规则类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_段衔接规则表类
/// <para>存储段衔接规则信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 段衔接规则类
class sectionlinkRule
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
	string						RULE_DIV;				// 规则区分
	string						RULE_TYPE;				// 规则类型
	int							RULE_NO;				// 规则号
	string						SECTION_NO1;			// 分段号1
	string						SECTION_NO2;			// 分段号2
	string						MIX_MODE;				// 组合方式
	int							PRIOR_SEQ_NO;			// 优先顺序
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
	sectionlinkRule(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, int value12, string value13, string value14, string value15,int value16);
	//
	// 摘要:
	//     析构函数。
	~sectionlinkRule();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};