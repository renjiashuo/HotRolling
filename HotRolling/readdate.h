/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-06-06
功能: 数据读取类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 数据读取类
/// <para>数据读取操作</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h"
#include "TortoiseShell_rule.h"
#include "zhuticai.h"
#include "tangguncai.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////
class ReadDate;
//////////////////////////////////////////////////////////////////////////

// 数据读取类
class ReadDate
{

#pragma region Variables

public:// 公共全局变量
   
#pragma endregion


#pragma region Functions

public:
#pragma region 辅助函数
	//////////////////////////////////////////////////////////////////////////
	//
	// 摘要:
	//     读取数据。
	static void readdate();
	//
	// 摘要:
	//     结果输出到数据库。
	static void showResultSQL();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};