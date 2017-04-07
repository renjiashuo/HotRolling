/*************************************************
版权: 
作者: 任家硕
日期: 2017-03-22
功能: 钢卷类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 钢卷类
/// <para>存储操作钢卷信息</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "global.h"
#include "ocilib.hpp"
using namespace ocilib;

#pragma region 声明
//////////////////////////////////////////////////////////////////////////

struct compwidth;


class SteelCoil;	// 钢卷类
//////////////////////////////////////////////////////////////////////////

// 钢卷类
class SteelCoil
{
	
#pragma region Variables

public:// 钢卷参数
	string						mat_no;					// 材料号（钢卷号）
	string						whole_backlog;			// 全程工序途径码
	int							whole_backlog_seq;		// 全程工序顺序号
	string						whole_backlog_code;		// 全程工序代码
	int							next_whole_backlog_seq;	// 后全程工序顺序号
	string						next_whole_backlog_code;// 后全程工序代码
	string						work_type;				// 工件类型
	string						order_no;				// 合同号
	double						SteelCoil_thick;		// 板坯厚度
	double						SteelCoil_width;		// 板坯宽度
	double						SteelCoil_len;			// 板坯长度
	double						SteelCoil_wt;			// 板坯重量
	string						st_no;					// 出钢记号(钢种)
	string						sg_sign;			    // 牌号（钢级）
	string						new_test_no;			// 新试号
	string						SteelCoil_dest;			// 钢卷去向
	string						stock_code;				// 库区代码
	string						fin_cut_time;			// 最终切断时间
	string						prec_SteelCoil_no;		// 预定钢卷号
	string						ips_pono;				// 应用制造命令号
	int							nom_hot_send_flag;		// 额定热送标记(DHCR标记)
	string						order_hot_charge_flag;	// 合同热装标记
	string						ips_cast_lot_no;		// 应用castlot号
	string						prec_roll_plan_no;		// 预定轧制计划号
	string						bg_mat_status;			// 宝钢材料状态
	string						bg_app_status;			// 宝钢材料申请状态
	string						transfer_plan_no;		// 转库计划号
	string						roll_plan_type;			// 轧制计划类型
	string						mat_status;				// 材料状态码
	string						roll_plan_no;			// 轧制计划号
	int							pre_flag;				// 烫辊材标记
	int							width_top_SteelCoil;	// 钢卷顶部宽
	int							width_bot_SteelCoil;	// 钢卷底部宽
	string						adjust_width_mark;		// 调宽标记
	string						stock_stay_time;		// 在库时间
	string						in_stock_time;			// 入库时刻
	string						roll_end_time;			// 轧制结束时刻
	string						hold_cause_code;		// 封锁原因代码
	string						hr_plan_date;			// 热轧计划日期
	double						nom_roll_thick;			// 额定轧制厚度
	double						nom_roll_width;			// 额定轧制宽度
	int							nom_heat_temp;			// 额定出炉温度
	int							nom_afft_temp;			// 额定终轧温度
	int							nom_coil_temp;			// 额定卷取温度
	int							nom_hard_group_code;	// 额定硬度组代码
	int							nom_surf_index_code;	// 额定表面指数代码
	int							plan_type;				// 计划类型
	bool						must_do_flag;			// 必做标记
	int							roll_len;				// 轧制长度
	double						roll_time;				// 轧制时间
	int							order_pri;				// 合同优先级
	string						plan_no;				// 计划号
	int							mat_seq_no;				// 材料顺序号
	string						flow;					// 流向
	string						mod_stamp_no;			// 模型邮戳号
	double						thick_forward_max;		// 厚差正跳最大值
	double						thick_forward_min;		// 厚差正跳最小值
	double						thick_backward_max;		// 厚差反跳最大值
	double						thick_backward_min;		// 厚差反跳最小值
	int							heat_temp_jump_max;		// 出炉温度跳跃上限
	int							heat_temp_jump_min;		// 出炉温度跳跃下限
	int							afft_temp_jump_max;		// 终轧温度跳跃上限
	int							afft_temp_jump_min;		// 终轧温度跳跃下限
	int							coil_temp_jump_max;		// 卷取温度跳跃上限
	int							coil_temp_jump_min;		// 卷取温度跳跃下限
	int							hard_group_jump_max;	// 硬度组跳跃上限
	int							hard_group_jump_min;	// 硬度组跳跃下限
	int							max_high_temp_coil_num;	// 每段最大高温卷数
	int							min_high_temp_coil_num;	// 每段最小高温卷数
	int							min_low_temp_coil_num;	// 每段最小低温卷数
	int							max_low_temp_coil_num;	// 每段最大低温卷数
	int							high_temp_flag;			// 高温标志
	int							low_temp_flag;			// 低温标志
	int							num;					// 件数
	int							zone_max_num;			// 区间最大块数
	int							zone_min_num;			// 区间最小块数
	int							zone_max_m;				// 区间最大米数
	int							zone_min_m;				// 区间最小米数

public:// 钢卷集合
	//static map<string, SteelCoil*>	  s_mapSetOfSteelCoil;		//钢卷的map集合，key为钢卷号，value为钢卷
	//static map<string, SteelCoil*>      s_hightempSteelCoil;	    //高温钢卷的map集合，key为钢卷号，value为钢卷
	//static map<string, SteelCoil*>      s_lowtempSteelCoil;       //低温钢卷的map集合，key为钢卷号，value为钢卷
	//static map<string, SteelCoil*>      s_coldSteelCoil;          //冷钢卷的map集合，key为钢卷号，value为钢卷
	//static map<string, SteelCoil*>      s_hotSteelCoil;           //热钢卷的map集合，key为钢卷号，value为钢卷
	static map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>      s_pre_flagSteelCoil;		//有烫辊材标记的钢卷组map集合
	static map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>      s_nonpre_flagSteelCoil;	//无烫辊材标记的钢卷组map集合
	static map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>      s_DHCRSteelCoil;			//有DHCR标记的钢卷组map集合
	
	//static map< pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>,int>, vector<SteelCoil*>>     s_mapSetOfSteelCoilgroup;  //将钢卷按个字段排序： 计划类型 ， 钢级，厚度，宽度，出炉，终轧，卷取温度，将结果存在vector中
	static int					s_SteelCoilCount;				    //钢卷个数

#pragma endregion


#pragma region Functions

public:
#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
	//
	// 摘要:
	//      根据读取的数据，按计划类型,钢级,厚度,宽度,出炉温度,终轧温度,卷取温度进行钢卷组处理。
	static void SteelCoilgroup();
	//
	// 摘要:
	//     构造函数。
	SteelCoil(string value2, double value3, double value4, double value5, string value6, double value7, double value8, int value9, int value10, int value11, int value12, int value13, int value14, int value15);
	//
	// 摘要:
	//     析构函数。
	~SteelCoil();

//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

