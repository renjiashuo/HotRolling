#include"common.h"
#include "global.h"
#include"SteelCoil.h"
#include"Group.h"
#include"TortoiseShell.h"
int main()
{	
	//////////////////////////////////////////////////////////////////////////
	// 监视用
	SteelCoil::s_pre_flagSteelCoil;
	SteelCoil::s_nonpre_flagSteelCoil;
	SteelCoil::s_DHCRSteelCoil;
	Group::s_mapSetOfGroup;
	Group::s_mapSetOfGroup1;
	Group::s_mapSetOfsmallGroup;
	TortoiseShell::s_mapSetOfTortoiseShell;
	//////////////////////////////////////////////////////////////////////////

	//datacheck();	// 数据校验

	SteelCoil::SteelCoilgroup();	// 初始化钢卷数据
	Group::vec_group();			// 初始化钢卷组数据
	TortoiseShell::InitShell();		// 初始化乌龟壳
	TortoiseShell::FinishShell();	// 完成乌龟壳初始解
	TortoiseShell::showResult();	// 输出到控制台

	system("pause");
	return 0;
}