/*************************************************
��Ȩ:
����: �μ�˶
����: 2017-03-22
����: �����ƻ�ģ�ͳ������п�����
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �����ƻ�ģ�ͳ������п�����
/// <para>�洢�����ƻ�ģ�ͳ������п�����Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_proRuncon.h"


#pragma region ��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
proRuncon::proRuncon(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, string value11,
	string value12, string value13, string value14, string value15, string value16, int value17, string value18, string value19, int value20, int value21, double value22, string value23,double value24)
{
	REC_CREATOR = value1;
	REC_CREATE_TIME = value2;
	REC_REVISOR = value3;
	REC_REVISE_TIME = value4;
	ARCHIVE_FLAG = value5;
	ARCHIVE_STAMP_NO = value6;
	MOD_STAMP_NO = value7;
	PROGRAM_NAME = value8;
	WHOLE_BACKLOG_CODE = value9;
	PLAN_MAKER = value10;
	PLANNED_START_TIME = value11;
	PLAN_CLASS = value12;
	PROC_STATUS = value13;
	HALF_PLAN_FLAG = value14;
	CURR_PLAN_NO = value15;
	ROLL_CHG_FLAG = value16;
	PLAN_FUR_NUM = value17;
	USE_PRE_FLAG = value18;
	CON_SLAB_FLAG = value19;
	PLAN_NUM = value20;
	MUST_DO_FLAG = value21;
	RETURN_ERROR_CODE = value22;
	RETURN_ERROR_MSG = value23;
	RULE_SET_NO = value24;
}


proRuncon::~proRuncon()
{
}

void proRuncon::release()
{
	proRuncon::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region tangguncai��̬����
//////////////////////////////////////////////////////////////////////////
int							proRuncon::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion