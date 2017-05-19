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


class SteelCoil;	// 钢卷类
//////////////////////////////////////////////////////////////////////////

// 钢卷类
class SteelCoil
{
	
#pragma region Variables

public:// 钢卷参数
	string						REC_CREATOR;			// 记录创建责任者
	string						REC_CREATE_TIME;		// 记录创建时刻
	string						REC_REVISOR;			// 记录修改责任者
	string						REC_REVISE_TIME;		// 记录修改时刻
	string						ARCHIVE_FLAG;			// 归档标记
	string						ARCHIVE_STAMP_NO;		// 归档邮戳号
	string						COMPANY_CODE;			// 公司代码
	string						COMPANY_NAME;			// 公司(帐套)中文名称
	string						mat_no;					// 材料号（钢卷号）
	string						whole_backlog;			// 全程工序途径码
	int							whole_backlog_seq;		// 全程工序顺序号
	string						whole_backlog_code;		// 全程工序代码
	int							next_whole_backlog_seq;	// 后全程工序顺序号
	string						next_whole_backlog_code;// 后全程工序代码
	string						work_type;				// 工件类型
	string						order_no;				// 合同号
	double						slab_thick;				// 板坯厚度
	double						slab_width;				// 板坯宽度
	double						slab_len;				// 板坯长度
	double						slab_wt;				// 板坯重量
	string						st_no;					// 出钢记号(钢种)
	string						sg_sign;			    // 牌号（钢级）
	string						new_test_no;			// 新试号
	string						slab_dest;				// 钢卷去向
	string						stock_code;				// 库区代码
	string						fin_cut_time;			// 最终切断时间
	string						prec_slab_no;			// 预定钢卷号
	string						ips_pono;				// 应用制造命令号
	string						nom_hot_send_flag;		// 额定热送标记(DHCR标记)
	string						order_hot_charge_flag;	// 合同热装标记
	string						ips_cast_lot_no;		// 应用castlot号
	string						prec_roll_plan_no;		// 预定轧制计划号
	string						bg_mat_status;			// 宝钢材料状态
	string						bg_app_status;			// 宝钢材料申请状态
	string						transfer_plan_no;		// 转库计划号
	string						roll_plan_type;			// 轧制计划类型
	string						mat_status;				// 材料状态码
	string						roll_plan_no;			// 轧制计划号
	string						pre_flag;				// 烫辊材标记
	int							width_top_slab;			// 钢卷顶部宽
	int							width_bot_slab;			// 钢卷底部宽
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
	string						nom_hard_group_code;	// 额定硬度组代码
	string						nom_surf_index_code;	// 额定表面指数代码
	string						plan_type;				// 计划类型
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
	string						high_temp_flag;			// 高温标志
	string						low_temp_flag;			// 低温标志
	int							num;					// 件数
	int							zone_max_num;			// 区间最大块数
	int							zone_min_num;			// 区间最小块数
	int							zone_max_m;				// 区间最大米数
	int							zone_min_m;				// 区间最小米数
	//long						IPS_LOT_NO;				// 应用批次号
	//short						SAME_WIDTH_KM;			// 同宽轧制公里数
	//string					ROLL_START_FLAG;		// 开轧标记
	//string					TRNP_TIME;				// 运输时间

public:// 钢卷集合(宽度，厚度，计划类型 ，钢级，出炉，终轧，卷取温度，高温标记,区间最大块数，区间最小块数，区间最大米数，区间最小米数)
	static map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>,string>,int>,int>,int>,int>,string>, vector<SteelCoil*>>      s_SteelCoil;		//钢卷组map集合
	
	static int								s_SteelCoilCount;				    //钢卷个数

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
	SteelCoil(string value1, string value2, double value3, double value4, double value5, string value6, double value7, double value8, int value9, string value10, string value11, string value12, string value13, string value14, string value15, string value16,
		string value17, int value18, string value19, int value20, string value21, string value22, string value23, double value24, double value25, string value26, string value27, string value28, string value29, string value30, string value31,
		string value32, string value33, string value34, string value35, string value36, string value37, string value38, string value39, string value40, int value41, int value42, string value43, string value44, string value45, string value46,
		string value47, string value48, bool value49, int value50, double value51, int value52, string value53, int value54, string value55, string value56, double value57, double value58, double value59, double value60, int value61,
		int value62, int value63, int value64, int value65, int value66, int value67, int value68, int value69, int value70, int value71, int value72, int value73, int value74, int value75, int value76,
		int value77, string value82, string value83, string value84, string value85, string value86, string value87, string value88, string value89, double value90);
	//
	// 摘要:
	//     析构函数。
	~SteelCoil();

//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

