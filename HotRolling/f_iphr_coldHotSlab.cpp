/*************************************************
��Ȩ:
����: �μ�˶
����: 2017-06-21
����: ���������������׼
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// ���������������׼��
/// <para>�洢���������������׼��Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "f_iphr_TortoiseShell.h"
#include "f_iphr_global.h"
#include "f_iphr_coldHotSlab.h"


#pragma region ��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
coldHotSlab::coldHotSlab(string value1, string value2, string value3, string value4, string value5, string value6, string value7, string value8, string value9, string value10, double value11,
	double value12, string value13)
{
	REC_CREATOR = value1;
	REC_CREATE_TIME = value2;
	REC_REVISOR = value3;
	REC_REVISE_TIME = value4;
	ARCHIVE_FLAG = value5;
	ARCHIVE_STAMP_NO = value6;
	COMPANY_CODE = value7;
	COMPANY_NAME = value8;
	WHOLE_BACKLOG_CODE = value9;
	STORE_AREA = value10;
	MIN_CUT_HOUR = value11;
	MAX_CUT_HOUR = value12;
	COLD_HOT_FLAG = value13;
	
}


coldHotSlab::~coldHotSlab()
{
}

void coldHotSlab::release()
{
	coldHotSlab::row = 0;
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai��̬����
//////////////////////////////////////////////////////////////////////////
int							coldHotSlab::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion