/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-06-06
����: ���ݶ�ȡ��
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// ���ݶ�ȡ��
/// <para>���ݶ�ȡ����</para>
/// </summary>
===========================================================</remark>*/

#pragma once

#include "f_iphr_global.h"
#include "f_iphr_SteelCoil.h"
#include "f_iphr_Group.h"
#include "f_iphr_TortoiseShell.h"
#include "f_iphr_TortoiseShellRule.h"
#include "f_iphr_zhuticai.h"
#include "f_iphr_tangguncai.h"

#pragma region ����
//////////////////////////////////////////////////////////////////////////
class ReadDate;
//////////////////////////////////////////////////////////////////////////

// ���ݶ�ȡ��
class ReadDate
{

#pragma region Variables

public:// ����ȫ�ֱ���
   
#pragma endregion


#pragma region Functions

public:
#pragma region ��������
	//////////////////////////////////////////////////////////////////////////
	//
	// ժҪ:
	//     ��ȡ���ݡ�
	static void readdate();
	//
	// ժҪ:
	//     �����������ݿ⡣
	static void showResultSQL();

	//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma endregion

};