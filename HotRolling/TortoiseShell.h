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
	int									m_tortoiseShellName;		// 乌龟壳名称
	double								m_TortoiseShell_len;		// 乌龟壳长度
	double								m_TortoiseShell_WT;			// 乌龟壳重量
	double								m_TortoiseShellflow10_WT;	// 乌龟壳重流向10钢卷重量
	double								m_TortoiseShell_DHCR;		// 乌龟壳DHCR个数
	double								m_TortoiseShell_len1;		// 乌龟壳长度(后)
	double								m_TortoiseShell_WT1;		// 乌龟壳重量(后)
	double								m_TortoiseShellflow10_WT1;	// 乌龟壳重流向10钢卷重量(后)
	double								m_TortoiseShell_DHCR1;		// 乌龟壳DHCR个数(后)		
	//double							m_tang_len;					// 分配到乌龟壳里的烫辊材长度			
	map<pair<int, int>, Group*>			m_pre_groups;				// 乌龟壳内烫辊材钢卷组信息，key.first，key.second(存钢卷组的位置)，value为钢卷组
	map<pair<int, int>, Group*>			m_main_groups;				// 乌龟壳内主体材钢卷组信息，key.first，key.second(存钢卷组的位置)，value为钢卷组
	
public:// 排程过程中记录变量
	int									steelCoilNum;				// 乌龟壳内钢卷数
	int									steelCoilLenth;				// 乌龟壳目前公里数
	int									high_num;					// 乌龟壳内已有高温卷段数
	int									high_temp_coil_num;			// 末尾连续高温卷的钢卷数
	int									low_temp_coil_num;			// 末尾连续低温卷的钢卷数
	int									coil_flag;					// 上一个钢卷的属性，0为低温卷，1为高温卷
	
public:// 乌龟壳集合
	static map<int, TortoiseShell*>		s_mapSetOfTortoiseShell;	// 乌龟壳的map集合，key为乌龟壳代码，value为乌龟壳
	static map<int, TortoiseShell*>		s_bestSetOfTortoiseShell;	// 盛放最优乌龟壳
	static int							s_TortoiseShellCount;		// 乌龟壳个数
	static double						allTortoiseShell_len;		// 所有乌龟壳总长度
	static double						m_DHCR;						// 有DHCR标记钢卷总数
	static double						allflow10_wt;				// 流向10钢卷总重量
	static double						allsteelcCoil_wt;			// 钢卷总重
	static double						best_kpi;					// 最优kpi值
public:
	static map<pair<string, string>, string> plantype;				// 计划类型组合集合

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
	//     构造函数。给删除钢卷组初始化乌龟肯。
	TortoiseShell();
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
	//     将不满足高温段块数范围、低温段块数范围、轧制位区间范围的钢卷重新放入未分配钢卷组中。
	static void DeleteBad();
	//
	// 摘要:
	//     计算KPI。
	static double computekpi(map<int, TortoiseShell*> &NEW_TortoiseShell);
	//
	// 摘要:
	//     结果控制台展示。
	static void showResult();
	//
	// 摘要:
	//     结果输出到文本。
	static void showResultFile();	
	//
	// 摘要:
	//     向乌龟壳的最后添加一个主体材，分配成功返回true，分配失败返回false。
	 bool addMainGroup(Group *group);
	//
	// 摘要:
	//     局域搜索算法
	static void localsearch();
	//////////////////////////////////////////////////////////////////////////
	#pragma endregion

	#pragma endregion

};

