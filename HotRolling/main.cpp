
#include "global.h"
#include"SteelCoil.h"
#include"Group.h"
#include"TortoiseShell.h"
int main()
{	
	//////////////////////////////////////////////////////////////////////////
	// ������
	SteelCoil::s_SteelCoil;
	Group::s_mapSetOfGroup;
	Group::s_mapSetOfsmallGroup;
	TortoiseShell::s_mapSetOfTortoiseShell;
	Group::s_least;

	//////////////////////////////////////////////////////////////////////////

	SteelCoil::SteelCoilgroup();	// ��ʼ���־�����
	Group::vec_group();				// ��ʼ���־�������
	TortoiseShell::InitShell();		// ��ʼ���ڹ��
	TortoiseShell::FinishShell();	// ����ڹ�ǳ�ʼ��
	TortoiseShell::DeleteBad();		// ɾ����С���ڹ��
	TortoiseShell::localsearch();	// �Ż��㷨
	TortoiseShell::showResult();	// ���������̨
	TortoiseShell::showResultFile();// ���������ı�

	

	
	system("pause");
	return 0;
}