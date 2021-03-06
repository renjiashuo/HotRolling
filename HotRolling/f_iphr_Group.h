/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 钢卷组类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 钢卷组类
/// <para>存储操作钢卷组信息</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "f_iphr_global.h"
#include "f_iphr_SteelCoil.h"

#pragma region 声明
//////////////////////////////////////////////////////////////////////////
void vec_group();


class Group;	// 钢卷组类
class SteelCoil;	// 钢卷类
//////////////////////////////////////////////////////////////////////////

// 钢卷组类
class Group
{

#pragma region Variables

public:// 钢卷组参数
	int						group_no;				// 钢卷组代码
	string					plan_type;				// 计划类型
	string					st_no;					// 出钢记号（钢种）	
	double					nom_roll_thick;			// 额定轧制厚度
	double					nom_roll_width;			// 额定轧制宽度
	int						nom_heat_temp;			// 额定出炉温度
	int						nom_afft_temp;			// 额定终轧温度
	int						nom_coil_temp;			// 额定卷取温度
	string					high_temp_flag;			// 高温标记
	string					nom_hard_group_code;	// 额定硬度组代码
	double					roll_len;				// 轧制长度
	double					slab_wt;				// 轧制重量
	int						zone_max_num;			// 区间最大块数
	int						zone_min_num;			// 区间最小块数
	int						zone_max_m;				// 区间最大米数
	int						zone_min_m;				// 区间最小米数
	vector<SteelCoil*>			m_SteelCoil;		// 存放每个钢卷组的钢卷
	//string					sg_sign;				// 牌号（钢级）
	//map<int, SteelCoil*>			m_SteelCoilTime;			// 钢卷计划轧制时间，key为钢卷轧制开始时间，value为钢卷（小钢卷组的计划属性，内部的钢卷顺序，按时间排序）

public:// 钢卷组集合
	static map<int, Group*>		s_least;					// 删除钢卷组的集合
	static map<int, Group*>		s_mapSetOfGroup;			// 钢卷组的map集合，key为钢卷组代码，value为钢卷组
	static map<int, Group*>		s_mapSetOfsmallGroup;		// 小钢卷组的map集合，key是小刚卷组代码，value是钢卷组指针
	static int					s_GroupCount;				// 钢卷组个数     
#pragma endregion

	
#pragma region Functions

public:
#pragma region 辅助函数
	//////////////////////////////////////////////////////////////////////////
	//
	// 摘要:
	//     根据生成的钢卷组，生成钢卷组类对象，将钢卷组标号放入map集合里。
	static	void vec_group();
	//
	// 摘要:
	//     构造函数。初始化一个钢卷组。
	Group(int value1, double value2, double value3, string value4, string value5, int value6, int value7, int value8, string value10, int value11, int value12, int value13, int value14, string value15, vector<SteelCoil*>&value9);
	//
	// 摘要:
	//     构造函数。将钢卷组的前n个钢卷赋给新的钢卷组。
	Group(Group *group,int n);
	//
	// 摘要:
	//     构造函数。将钢卷组的前lonth公里数的钢卷赋给新的钢卷组。
	Group(Group *group, double lonth);
	//
	// 摘要:
	//     构造函数。将钢卷组的小于lonth公里数、小于n个钢卷，最多能放的钢卷赋给新的钢卷组。
	Group(Group *group, double lonth, int n);
	//
	// 摘要:
	//     析构函数。
	~Group();
	//
	// 摘要:
	//     释放所有static的。
	static void release();
	//
	// 摘要:
	//     indata。
	static void indata(map<int, Group*>&m_data, int a, Group* b);
	
	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

