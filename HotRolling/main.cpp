#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h"
#include "readdate.h"

int main()
{
	clock_t startTime, finishTime;
	double totalTime;
	startTime = clock();
	//////////////////////////////////////////////////////////////////////////
	// ������
	SteelCoil::s_SteelCoil;
	Group::s_mapSetOfGroup;
	Group::s_mapSetOfsmallGroup;
	TortoiseShell::s_mapSetOfTortoiseShell;
	Group::s_least;

	//////////////////////////////////////////////////////////////////////////

	ReadDate::readdate();			// ��ȡ���ݿⲢ��ʼ��
	Group::vec_group();			// ��ʼ���־�������
	TortoiseShell::InitShell();		// ��ʼ���ڹ��
	TortoiseShell::FinishShell();	// ����ڹ�ǳ�ʼ��
	TortoiseShell::DeleteBad();		// ɾ����С���ڹ��	
	TortoiseShell::localsearch();	// �Ż��㷨
	TortoiseShell::localsearch1();	// �Ż��㷨
	TortoiseShell::localsearch2();	// �Ż��㷨
	TortoiseShell::localsearch3();	// �Ż��㷨
	//TortoiseShell::localsearch4();	// �Ż��㷨
	//TortoiseShell::showResult();	// ���������̨
	TortoiseShell::computekpi();	// �������KPI
	TortoiseShell::showResultFile();// ���������ı�
	ReadDate::showResultSQL();	// ��������SQL

	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	cout << "���������ʱ��Ϊ" << totalTime << "�룡" << endl << endl;

	system("pause");
	return 0;
}