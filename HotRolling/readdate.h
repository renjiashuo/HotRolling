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

#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h"
#include "TortoiseShell_rule.h"
#include "zhuticai.h"
#include "tangguncai.h"

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