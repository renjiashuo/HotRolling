/*************************************************
版权:
作者: 任家硕、徐巍
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
#include "Group.h"

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
	int								m_tortoiseShellName;		// 乌龟壳名称
	double							m_TortoiseShell_len;		// 乌龟壳长度
	int								m_startTime;				// 乌龟壳开始时刻
	int								m_finishTime;				// 乌龟壳结束时刻
	int								m_timeSpan;				// 乌龟壳总时间（分钟）
	map<pair<int, int>, Group*>			m_groups_temp;			// 乌龟壳内钢卷组信息，key.first宽度，key.second不重复编号，value为钢卷组
	map<pair<int, int>, Group*>			m_groups;					// 乌龟壳内钢卷组信息，key.first，key.second(存钢卷组的位置)，value为钢卷组
	
public:// 排程过程中记录变量
	map<double, double>				width_lonth;				// 目前乌龟壳中每种轧制宽度对应的已存在的公里数
	//double							nom_roll_width;			// 目前乌龟壳中最后一个钢卷组的额定轧制宽度
	//double							same_width_lonth;			// 目前最后一个钢卷组宽度的同宽公里数
	
public:// 乌龟壳集合
	static map<int, TortoiseShell*>		s_mapSetOfTortoiseShell;	// 乌龟壳的map集合，key为乌龟壳代码，value为乌龟壳
	static int						s_TortoiseShellCount;		// 乌龟壳个数

public:// 计划类型组合
	static map<pair<int, int>, int> plantype;

#pragma endregion


#pragma region Functions

public:
	#pragma region 辅助函数
	//////////////////////////////////////////////////////////////////////////
	//
	// 摘要:
	//     构造函数。给定板坯组初始化乌龟壳。
	TortoiseShell(Group *group);
	//
	// 摘要:
	//     析构函数。
	~TortoiseShell();
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma region 乌龟壳计划相关
	//////////////////////////////////////////////////////////////////////////
	//
	// 摘要:
	//     创建初始乌龟壳。
	static void InitShell();
	//
	// 摘要:
	//     完成乌龟壳初始解。
	static void FinishShell();
	//
	// 摘要:
	//     结果控制台展示。
	static void showResult();
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma endregion

};

