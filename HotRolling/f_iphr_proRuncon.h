/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 热轧计划模型程序运行控制类 TIPHR09
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 热轧计划模型程序运行控制表类
/// <para>存储热轧计划模型程序运行控制信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 关键指标定义类
class proRuncon
{
#pragma region Variables
public:
	string						REC_CREATOR;			// 记录创建责任者
	string						REC_CREATE_TIME;		// 记录创建时刻
	string						REC_REVISOR;			// 记录修改责任者
	string						REC_REVISE_TIME;		// 记录修改时刻
	string						ARCHIVE_FLAG;			// 归档标记
	string						ARCHIVE_STAMP_NO;		// 归档邮戳号
	string						MOD_STAMP_NO;			// 模型邮戳号
	string						PROGRAM_NAME;			// 程序名
	string						WHOLE_BACKLOG_CODE;		// 全程工序代码
	string						PLAN_MAKER;				// 计划责任者
	string						PLANNED_START_TIME;		// 计划开始时间
	string						PLAN_CLASS;				// 计划分类
	string						PROC_STATUS;			// 处理状态
	string						HALF_PLAN_FLAG;			//不完整计划标记
	string						CURR_PLAN_NO;			//当前计划号
	string						ROLL_CHG_FLAG;			//支撑辊更换标记
	int							PLAN_FUR_NUM;			//计划加热炉开炉数
	string						USE_PRE_FLAG;			//使用烫辊材标记
	string						CON_SLAB_FLAG;			//交接板坯使用标记
	int							PLAN_NUM;				//计划个数
	int							MUST_DO_FLAG;			//必做标记
	double						RETURN_ERROR_CODE;		//返回出错代码
	string						RETURN_ERROR_MSG;		//返回出错信息
	double						RULE_SET_NO;			//规则集号

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
	proRuncon(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11, string value12, string value13,
		string value14, string value15, string value16,int value17,string value18,string value19,int value20,int value21,double value22,string value23,double value24);
	//
	// 摘要:
	//     析构函数。
	~proRuncon();
	//
	// 摘要:
	//     释放所有static的。
	static void release();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion
};