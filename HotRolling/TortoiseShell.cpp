/*************************************************
��Ȩ:
����: �μ�˶����Ρ
����: 2017-03-22
����: �ڹ����
�޸���ʷ:

**************************************************/

/*<remark>=========================================================
/// <summary>
/// �ڹ����
/// <para>�洢�ڹ����Ϣ</para>
/// </summary>
===========================================================</remark>*/

#include "TortoiseShell.h"
#include "global.h"


#pragma region TortoiseShell��Ա����
//////////////////////////////////////////////////////////////////////////

void TortoiseShell::shell()
{
	const int samewidth_limit = 500000;//ͬ����������
	/*-----------------------�ƻ��������Լ��-----------------*/
	//(0:����������ϣ�1:������ϣ�2:�ƻ��ڲ�����ϣ�3:����������Ⱥ�˳������)
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
	/*-----------------------�ƻ��������Լ��-----------------*/


}


#pragma region ��������
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

#pragma region Group��̬����
//////////////////////////////////////////////////////////////////////////
map<string, TortoiseShell*>		TortoiseShell::s_mapSetOfTortoiseShell = map<string, TortoiseShell*>();
int							TortoiseShell::s_TortoiseShellCount = 0;
////////////////////////////////////////////////////////////////////////
#pragma endregion