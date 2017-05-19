/*************************************************
��Ȩ: 
����: �μ�˶
����: 2017-03-22
����: �־���
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �־���
/// <para>�洢�����־���Ϣ</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "global.h"
#include "ocilib.hpp"
using namespace ocilib;

#pragma region ����
//////////////////////////////////////////////////////////////////////////


class SteelCoil;	// �־���
//////////////////////////////////////////////////////////////////////////

// �־���
class SteelCoil
{
	
#pragma region Variables

public:// �־����
	string						REC_CREATOR;			// ��¼����������
	string						REC_CREATE_TIME;		// ��¼����ʱ��
	string						REC_REVISOR;			// ��¼�޸�������
	string						REC_REVISE_TIME;		// ��¼�޸�ʱ��
	string						ARCHIVE_FLAG;			// �鵵���
	string						ARCHIVE_STAMP_NO;		// �鵵�ʴ���
	string						COMPANY_CODE;			// ��˾����
	string						COMPANY_NAME;			// ��˾(����)��������
	string						mat_no;					// ���Ϻţ��־�ţ�
	string						whole_backlog;			// ȫ�̹���;����
	int							whole_backlog_seq;		// ȫ�̹���˳���
	string						whole_backlog_code;		// ȫ�̹������
	int							next_whole_backlog_seq;	// ��ȫ�̹���˳���
	string						next_whole_backlog_code;// ��ȫ�̹������
	string						work_type;				// ��������
	string						order_no;				// ��ͬ��
	double						slab_thick;				// �������
	double						slab_width;				// �������
	double						slab_len;				// ��������
	double						slab_wt;				// ��������
	string						st_no;					// ���ּǺ�(����)
	string						sg_sign;			    // �ƺţ��ּ���
	string						new_test_no;			// ���Ժ�
	string						slab_dest;				// �־�ȥ��
	string						stock_code;				// ��������
	string						fin_cut_time;			// �����ж�ʱ��
	string						prec_slab_no;			// Ԥ���־��
	string						ips_pono;				// Ӧ�����������
	string						nom_hot_send_flag;		// ����ͱ��(DHCR���)
	string						order_hot_charge_flag;	// ��ͬ��װ���
	string						ips_cast_lot_no;		// Ӧ��castlot��
	string						prec_roll_plan_no;		// Ԥ�����Ƽƻ���
	string						bg_mat_status;			// ���ֲ���״̬
	string						bg_app_status;			// ���ֲ�������״̬
	string						transfer_plan_no;		// ת��ƻ���
	string						roll_plan_type;			// ���Ƽƻ�����
	string						mat_status;				// ����״̬��
	string						roll_plan_no;			// ���Ƽƻ���
	string						pre_flag;				// �̹��ı��
	int							width_top_slab;			// �־�����
	int							width_bot_slab;			// �־�ײ���
	string						adjust_width_mark;		// ������
	string						stock_stay_time;		// �ڿ�ʱ��
	string						in_stock_time;			// ���ʱ��
	string						roll_end_time;			// ���ƽ���ʱ��
	string						hold_cause_code;		// ����ԭ�����
	string						hr_plan_date;			// �����ƻ�����
	double						nom_roll_thick;			// ����ƺ��
	double						nom_roll_width;			// ����ƿ��
	int							nom_heat_temp;			// ���¯�¶�
	int							nom_afft_temp;			// ������¶�
	int							nom_coil_temp;			// ���ȡ�¶�
	string						nom_hard_group_code;	// �Ӳ�������
	string						nom_surf_index_code;	// �����ָ������
	string						plan_type;				// �ƻ�����
	bool						must_do_flag;			// �������
	int							roll_len;				// ���Ƴ���
	double						roll_time;				// ����ʱ��
	int							order_pri;				// ��ͬ���ȼ�
	string						plan_no;				// �ƻ���
	int							mat_seq_no;				// ����˳���
	string						flow;					// ����
	string						mod_stamp_no;			// ģ���ʴ���
	double						thick_forward_max;		// ����������ֵ
	double						thick_forward_min;		// ���������Сֵ
	double						thick_backward_max;		// �������ֵ
	double						thick_backward_min;		// ������Сֵ
	int							heat_temp_jump_max;		// ��¯�¶���Ծ����
	int							heat_temp_jump_min;		// ��¯�¶���Ծ����
	int							afft_temp_jump_max;		// �����¶���Ծ����
	int							afft_temp_jump_min;		// �����¶���Ծ����
	int							coil_temp_jump_max;		// ��ȡ�¶���Ծ����
	int							coil_temp_jump_min;		// ��ȡ�¶���Ծ����
	int							hard_group_jump_max;	// Ӳ������Ծ����
	int							hard_group_jump_min;	// Ӳ������Ծ����
	int							max_high_temp_coil_num;	// ÿ�������¾���
	int							min_high_temp_coil_num;	// ÿ����С���¾���
	int							min_low_temp_coil_num;	// ÿ����С���¾���
	int							max_low_temp_coil_num;	// ÿ�������¾���
	string						high_temp_flag;			// ���±�־
	string						low_temp_flag;			// ���±�־
	int							num;					// ����
	int							zone_max_num;			// ����������
	int							zone_min_num;			// ������С����
	int							zone_max_m;				// �����������
	int							zone_min_m;				// ������С����
	//long						IPS_LOT_NO;				// Ӧ�����κ�
	//short						SAME_WIDTH_KM;			// ͬ�����ƹ�����
	//string					ROLL_START_FLAG;		// �������
	//string					TRNP_TIME;				// ����ʱ��

public:// �־���(��ȣ���ȣ��ƻ����� ���ּ�����¯����������ȡ�¶ȣ����±��,������������������С�������������������������С����)
	static map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>,string>,int>,int>,int>,int>,string>, vector<SteelCoil*>>      s_SteelCoil;		//�־���map����
	
	static int								s_SteelCoilCount;				    //�־����

#pragma endregion


#pragma region Functions

public:
#pragma region ��������
//////////////////////////////////////////////////////////////////////////
	//
	// ժҪ:
	//      ���ݶ�ȡ�����ݣ����ƻ�����,�ּ�,���,���,��¯�¶�,�����¶�,��ȡ�¶Ƚ��и־��鴦��
	static void SteelCoilgroup();
	//
	// ժҪ:
	//     ���캯����
	SteelCoil(string value1, string value2, double value3, double value4, double value5, string value6, double value7, double value8, int value9, string value10, string value11, string value12, string value13, string value14, string value15, string value16,
		string value17, int value18, string value19, int value20, string value21, string value22, string value23, double value24, double value25, string value26, string value27, string value28, string value29, string value30, string value31,
		string value32, string value33, string value34, string value35, string value36, string value37, string value38, string value39, string value40, int value41, int value42, string value43, string value44, string value45, string value46,
		string value47, string value48, bool value49, int value50, double value51, int value52, string value53, int value54, string value55, string value56, double value57, double value58, double value59, double value60, int value61,
		int value62, int value63, int value64, int value65, int value66, int value67, int value68, int value69, int value70, int value71, int value72, int value73, int value74, int value75, int value76,
		int value77, string value82, string value83, string value84, string value85, string value86, string value87, string value88, string value89, double value90);
	//
	// ժҪ:
	//     ����������
	~SteelCoil();

//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

