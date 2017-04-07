/*************************************************
版权:
作者: 任家硕、徐巍
日期: 2017-03-22
功能: 乌龟壳类
修改历史:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// 乌龟壳类
/// <para>存储乌龟壳信息</para>
/// </summary>
===========================================================</remark>*/

#include "TortoiseShell.h"
#include "global.h"


#pragma region TortoiseShell成员函数
//////////////////////////////////////////////////////////////////////////

void TortoiseShell::shell()
{
	const int samewidth_limit = 500000;//同宽公里数限制
	/*-----------------------计划类型组合约束-----------------*/
	//(0:不能相邻组合；1:任意组合；2:计划内不能组合；3:可组合且有先后顺序限制)
	map<pair<int, int>, int> plantype;
	pair<int, int>a = make_pair(1, 2);
	pair<int, int>b = make_pair(1, 3);
	pair<int, int>c = make_pair(1, 4);
	pair<int, int>d = make_pair(2, 3);
	pair<int, int>e = make_pair(2, 4);
	pair<int, int>f = make_pair(3, 4);
	plantype.insert(make_pair(a, 2));
	plantype.insert(make_pair(b, 1));
	plantype.insert(make_pair(c, 0));
	plantype.insert(make_pair(d, 1));
	plantype.insert(make_pair(e, 1));
	plantype.insert(make_pair(f, 1));
	for (map<pair<int, int>, int> ::iterator iter = plantype.begin(); iter != plantype.end(); iter++)
	{
		cout << iter->first.first <<"  "<< iter->first.second <<"  "<< iter->second<<endl;
	}
	/*-----------------------计划类型组合约束-----------------*/


}


#pragma region 辅助函数
//////////////////////////////////////////////////////////////////////////
TortoiseShell::TortoiseShell()
{
}


TortoiseShell::~TortoiseShell()
{
}

////////////////////////////////////////////////////////////////////////
#pragma endregion

////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region Group静态变量
//////////////////////////////////////////////////////////////////////////
map<string, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<string, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion