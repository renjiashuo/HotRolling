/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: IPS_规则参数定义类 TIP00SI02
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_规则参数定义表类
/// <para>存储IPS_规则参数定义信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// IPS_规则参数定义类
class ruleparaDef
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
	int							RULE_PARA_NO;			// 规则参数号
	string						RULE_PARA_VAL;			// 规则参数值
	string						RULE_PARA_VAL_FLAG;		// 规则参数值标记
	string						RULE_PARA_DESC;			// 规则参数描述
	string						RULE_PARA_SOURCE;		// 规则参数源值
	string						RULE_PARA_TYPE;			// 规则参数类型
	string						FORWARD_BACK_FLAG;		// 正反跳区分
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
	ruleparaDef(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, int value12, int value13, string value14, string value15, string value16, string value17, string value18, string value19);
	//
	// 摘要:
	//     析构函数。
	~ruleparaDef();
	//
	// 摘要:
	//     释放所有static的。
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

