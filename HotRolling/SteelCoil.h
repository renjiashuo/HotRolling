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

struct compwidth;


class SteelCoil;	// �־���
//////////////////////////////////////////////////////////////////////////

// �־���
class SteelCoil
{
	
#pragma region Variables

public:// �־����
	string						mat_no;					// ���Ϻţ��־�ţ�
	string						whole_backlog;			// ȫ�̹���;����
	int							whole_backlog_seq;		// ȫ�̹���˳���
	string						whole_backlog_code;		// ȫ�̹������
	int							next_whole_backlog_seq;	// ��ȫ�̹���˳���
	string						next_whole_backlog_code;// ��ȫ�̹������
	string						work_type;				// ��������
	string						order_no;				// ��ͬ��
	double						SteelCoil_thick;		// �������
	double						SteelCoil_width;		// �������
	double						SteelCoil_len;			// ��������
	double						SteelCoil_wt;			// ��������
	string						st_no;					// ���ּǺ�(����)
	string						sg_sign;			    // �ƺţ��ּ���
	string						new_test_no;			// ���Ժ�
	string						SteelCoil_dest;			// �־�ȥ��
	string						stock_code;				// ��������
	string						fin_cut_time;			// �����ж�ʱ��
	string						prec_SteelCoil_no;		// Ԥ���־��
	string						ips_pono;				// Ӧ�����������
	int							nom_hot_send_flag;		// ����ͱ��(DHCR���)
	string						order_hot_charge_flag;	// ��ͬ��װ���
	string						ips_cast_lot_no;		// Ӧ��castlot��
	string						prec_roll_plan_no;		// Ԥ�����Ƽƻ���
	string						bg_mat_status;			// ���ֲ���״̬
	string						bg_app_status;			// ���ֲ�������״̬
	string						transfer_plan_no;		// ת��ƻ���
	string						roll_plan_type;			// ���Ƽƻ�����
	string						mat_status;				// ����״̬��
	string						roll_plan_no;			// ���Ƽƻ���
	int							pre_flag;				// �̹��ı��
	int							width_top_SteelCoil;	// �־�����
	int							width_bot_SteelCoil;	// �־�ײ���
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
	int							nom_hard_group_code;	// �Ӳ�������
	int							nom_surf_index_code;	// �����ָ������
	int							plan_type;				// �ƻ�����
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
	int							high_temp_flag;			// ���±�־
	int							low_temp_flag;			// ���±�־
	int							num;					// ����
	int							zone_max_num;			// ����������
	int							zone_min_num;			// ������С����
	int							zone_max_m;				// �����������
	int							zone_min_m;				// ������С����

public:// �־���
	//static map<string, SteelCoil*>	  s_mapSetOfSteelCoil;		//�־��map���ϣ�keyΪ�־�ţ�valueΪ�־�
	//static map<string, SteelCoil*>      s_hightempSteelCoil;	    //���¸־��map���ϣ�keyΪ�־�ţ�valueΪ�־�
	//static map<string, SteelCoil*>      s_lowtempSteelCoil;       //���¸־��map���ϣ�keyΪ�־�ţ�valueΪ�־�
	//static map<string, SteelCoil*>      s_coldSteelCoil;          //��־��map���ϣ�keyΪ�־�ţ�valueΪ�־�
	//static map<string, SteelCoil*>      s_hotSteelCoil;           //�ȸ־��map���ϣ�keyΪ�־�ţ�valueΪ�־�
	static map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>      s_pre_flagSteelCoil;		//���̹��ı�ǵĸ־���map����
	static map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>      s_nonpre_flagSteelCoil;	//���̹��ı�ǵĸ־���map����
	static map<pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>, int>, vector<SteelCoil*>>      s_DHCRSteelCoil;			//��DHCR��ǵĸ־���map����
	
	//static map< pair<pair < pair<pair<pair<pair<int, string>, double>, double>, int>, int>,int>, vector<SteelCoil*>>     s_mapSetOfSteelCoilgroup;  //���־����ֶ����� �ƻ����� �� �ּ�����ȣ���ȣ���¯����������ȡ�¶ȣ����������vector��
	static int					s_SteelCoilCount;				    //�־����

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
	SteelCoil(string value2, double value3, double value4, double value5, string value6, double value7, double value8, int value9, int value10, int value11, int value12, int value13, int value14, int value15);
	//
	// ժҪ:
	//     ����������
	~SteelCoil();

//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};

