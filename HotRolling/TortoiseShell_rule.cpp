/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-06-19
����: �������Ƶ�Ԫ������׼��
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �������Ƶ�Ԫ������׼��
/// <para>�洢���Ƶ�Ԫ������׼��Ϣ</para>
/// </summary>
===========================================================</remark>*/
#pragma once

#include "TortoiseShell.h"
#include "global.h"
#include "TortoiseShell_rule.h"

#pragma region TortoiseShell��Ա����
//////////////////////////////////////////////////////////////////////////




#pragma region ��������
//////////////////////////////////////////////////////////////////////////
TortoiseShell_rule::TortoiseShell_rule(string value1, string value2, string value3, string value4, string value5, string value6, string value7, 
		string value8, string value9, double value10, double value11, double value12, double value13, double value14, double value15)
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
	MIN_KM = value10;	
	MAX_KM = value11;
	MIN_WT = value12;
	MAX_WT = value13;
	MIN_NUM = value14;
	MAX_NUM = value15;
	
}


TortoiseShell_rule::~TortoiseShell_rule()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region zhuticai��̬����
//////////////////////////////////////////////////////////////////////////
int							TortoiseShell_rule::row = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion