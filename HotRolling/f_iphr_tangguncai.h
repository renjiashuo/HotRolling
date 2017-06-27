/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 热轧烫辊材规程类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 热轧烫辊材规程类
/// <para>存储烫辊材规程信息</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "f_iphr_global.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

// 热轧烫辊材规程类
class tangguncai
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
	short						MAX_NUM;				// 最大块数
	int							MAX_KM;					// 最大公里数
	short						ROLL_WIDTH_MINUS;		// 轧制宽度差
	short						HARD_GROUP_MINUS;		// 硬度组差
	short						SAME_WIDTH_NUM;			// 同宽块数
	short						SAME_WIDTH_KM;			// 同宽轧制公里数
	double						SAME_WIDTH;			    // 同宽定义范围
	short						NOHARD_PRE_FROM;		// 低硬度烫辊材位置起
	short						NOHARD_PRE_TO;			// 低硬度烫辊材位置止
	string						MAX_HARD_GROUP;			// 最大硬度组
	short						AFFT_TEMP_PRE_FROM;		// 高终轧温度烫辊材位置起
	short						AFFT_TEMP_PRE_TO;		// 高终轧温度烫辊材位置止
	short						AFFT_TEMP_MIN;			// 终轧温度下限
	short						SAME_WIDTH_PRE_NUM;		// 烫辊材同宽度连续块数


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
	tangguncai(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, short value10, int value11,
		short value12, short value13, short value14, short value15, double value16, short value17, short value18, string value19, short value20, short value21, short value22, short value23);
	//
	// 摘要:
	//     析构函数。
	~tangguncai();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion



};