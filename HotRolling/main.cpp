#include"common.h"
#include "global.h"
#include"SteelCoil.h"
#include"Group.h"
#include"TortoiseShell.h"
int main()
{	
	//////////////////////////////////////////////////////////////////////////
	// ������
	SteelCoil::s_pre_flagSteelCoil;
	SteelCoil::s_nonpre_flagSteelCoil;
	SteelCoil::s_DHCRSteelCoil;
	Group::s_mapSetOfGroup;
	Group::s_mapSetOfGroup1;
	Group::s_mapSetOfsmallGroup;
	TortoiseShell::s_mapSetOfTortoiseShell;
	//////////////////////////////////////////////////////////////////////////

	//datacheck();	// ����У��

	SteelCoil::SteelCoilgroup();	// ��ʼ���־�����
	Group::vec_group();			// ��ʼ���־�������
	TortoiseShell::InitShell();		// ��ʼ���ڹ��
	TortoiseShell::FinishShell();	// ����ڹ�ǳ�ʼ��
	TortoiseShell::showResult();	// ���������̨

	system("pause");
	return 0;
}