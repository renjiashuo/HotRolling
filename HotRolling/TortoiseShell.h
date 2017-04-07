/*************************************************
版权:
作者: 任家硕
日期: 2017-03-22
功能: 乌龟壳类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 乌龟壳类
/// <para>存储乌龟壳信息</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "global.h"
#include "SteelCoil.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

class Group;			// 钢卷组类
class SteelCoil;		// 钢卷类
class TortoiseShell;	// 乌龟壳类
struct rule_score;		// 罚分表
//////////////////////////////////////////////////////////////////////////

// 乌龟壳类
class TortoiseShell
{

#pragma region Variables

public:// 乌龟壳参数
	string							m_tortoiseShellName;		// 乌龟壳名称
	double							m_TortoiseShell_len;		//乌龟壳长度
	int								m_startTime;				// 乌龟壳开始时刻
	int								m_finishTime;				// 乌龟壳结束时刻
	int								m_timeSpan;				    // 乌龟壳总时间（分钟）
	map<pair<int, int>, Group*>		m_groups;				    // 乌龟壳内钢卷组信息，key.first，key.second(存钢卷组的位置)，value为钢卷组
	
public:// 乌龟壳集合
	static map<string, TortoiseShell*>	s_mapSetOfTortoiseShell;	// 乌龟壳的map集合，key为乌龟壳代码，value为乌龟壳
	static int						s_TortoiseShellCount;		   // 乌龟壳个数

#pragma endregion


#pragma region Functions

public:
#pragma region 辅助函数
	//////////////////////////////////////////////////////////////////////////
	static void shell();
	//
	// 摘要:
	//     构造函数。
	TortoiseShell();
	//
	// 摘要:
	//     析构函数。
	~TortoiseShell();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

