#include "f_iphr_global.h"
#include "f_iphr_SteelCoil.h"
#include "f_iphr_Group.h"
#include "f_iphr_TortoiseShell.h"
#include "f_iphr_readdate.h"

int main()
{
	clock_t startTime, finishTime;
	double totalTime;
	startTime = clock();
	//////////////////////////////////////////////////////////////////////////
	// 监视用
	SteelCoil::s_SteelCoil;
	Group::s_mapSetOfGroup;
	Group::s_mapSetOfsmallGroup;
	TortoiseShell::s_mapSetOfTortoiseShell;
	Group::s_least;

	//////////////////////////////////////////////////////////////////////////

	ReadDate::readdate();			// 读取数据库并初始化
	Group::vec_group();			// 初始化钢卷组数据
	TortoiseShell::InitShell();		// 初始化乌龟壳
	TortoiseShell::FinishShell();	// 完成乌龟壳初始解
	TortoiseShell::DeleteBad();		// 删除过小的乌龟壳	
	TortoiseShell::localsearch();	// 优化算法
	TortoiseShell::localsearch1();	// 优化算法
	TortoiseShell::localsearch2();	// 优化算法
	TortoiseShell::localsearch3();	// 优化算法
	//TortoiseShell::localsearch4();	// 优化算法
	//TortoiseShell::showResult();	// 输出到控制台
	TortoiseShell::computekpi();	// 输出最优KPI
	TortoiseShell::showResultFile();// 结果输出到文本
	ReadDate::showResultSQL();	// 结果输出到SQL

	finishTime = clock();
	totalTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
	cout << "程序的运行时间为" << totalTime << "秒！" << endl << endl;

	system("pause");
	return 0;
}