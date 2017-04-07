#include"common.h"
#include "global.h"
#include"SteelCoil.h"
#include"Group.h"
#include"TortoiseShell.h"
int main()
{	
	SteelCoil::SteelCoilgroup();
	Group::vec_group();	
	TortoiseShell::shell();
	datacheck();
	system("pause");
	return 0;
}