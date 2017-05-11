
#include "global.h"
#include"SteelCoil.h"
#include"Group.h"
#include"TortoiseShell.h"
int main()
{	
	//////////////////////////////////////////////////////////////////////////
	// 监视用
	SteelCoil::s_SteelCoil;
	Group::s_mapSetOfGroup;
	Group::s_mapSetOfsmallGroup;
	TortoiseShell::s_mapSetOfTortoiseShell;
	Group::s_least;

	//////////////////////////////////////////////////////////////////////////

	SteelCoil::SteelCoilgroup();	// 初始化钢卷数据
	Group::vec_group();				// 初始化钢卷组数据
	TortoiseShell::InitShell();		// 初始化乌龟壳
	TortoiseShell::FinishShell();	// 完成乌龟壳初始解
	TortoiseShell::DeleteBad();		// 删除过小的乌龟壳
	TortoiseShell::localsearch();	// 优化算法
	TortoiseShell::showResult();	// 输出到控制台
	TortoiseShell::showResultFile();// 结果输出到文本

	

	
	system("pause");
	return 0;
}