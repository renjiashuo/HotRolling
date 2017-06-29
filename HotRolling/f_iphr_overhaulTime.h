/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-06-19
功能: IPS_定检修时间设定类  TIP00SI11
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// IPS_定检修时间设定类
/// <para>存储IPS_定检修时间设定信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// IPS_定检修时间设定类
class overhaulTime
{
#pragma region Variables
public:
	string						REC_CREATOR;			// 记录创建责任者
	string						REC_CREATE_TIME;		// 记录创建时刻
	string						REC_REVISOR;			// 记录修改责任者
	string						REC_REVISE_TIME;		// 记录修改时刻
	string						ARCHIVE_FLAG;			// 归档标记
	string						ARCHIVE_TIME;			// 归档时刻	
	string						WHOLE_BACKLOG_CODE;		// 全程工序代码
	string						UNIT_CODE;				// 机组代码
	string						CONS_TYPE;				// 检修类别
	string						S_DATETIME;				// 开始时间
	string						E_DATETIME;				// 结束时间
	string						LINE_DIF;				// 产线区分



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
	overhaulTime(string value1, string value2, string value3, string value4, string value5, string value6, string value7,
		string value8, string value9, string value10, string value11, string value12);
	//
	// 摘要:
	//     析构函数。
	~overhaulTime();
	//
	// 摘要:
	//     释放所有static的。
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};