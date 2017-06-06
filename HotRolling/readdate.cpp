#include "readdate.h"

void ReadDate::readdate()
{
	try
	{
		Environment::Initialize();//环境初始化
		Connection con("127.0.0.1/orcl", "scott", "tiger");//连接数据库（IP地址/服务名，“用户名”，“密码“）
		Statement st(con);//创建数据集

#pragma region 初始化钢卷数据
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIPHR21 t order by nom_roll_width DESC");//选择表
			Resultset rs = st.GetResultset();

			while (rs.Next())
			{

				if (rs.Get<ostring>(39) == "1" && rs.Get<ostring>(29) == "0")		//将有烫辊材标记（不包括DHCR）的钢卷按十二组标准组成钢卷组放入map
				{
					SteelCoil *PRESteelCoil = new SteelCoil(rs.Get<ostring>(36), rs.Get<ostring>(9), rs.Get<double>(48), rs.Get<double>(49), rs.Get<double>(57), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(29), rs.Get<ostring>(39), rs.Get<ostring>(55), rs.Get<ostring>(53), rs.Get<ostring>(54), rs.Get<ostring>(80), rs.Get<ostring>(81)
						, rs.Get<ostring>(10), rs.Get<int>(11), rs.Get<ostring>(12), rs.Get<int>(13), rs.Get<ostring>(14), rs.Get<ostring>(15), rs.Get<ostring>(16), rs.Get<double>(20), rs.Get<double>(18), rs.Get<ostring>(22), rs.Get<ostring>(23), rs.Get<ostring>(24), rs.Get<ostring>(25), rs.Get<ostring>(26), rs.Get<ostring>(27), rs.Get<ostring>(28)
						, rs.Get<ostring>(30), rs.Get<ostring>(31), rs.Get<ostring>(32), rs.Get<ostring>(33), rs.Get<ostring>(34), rs.Get<ostring>(35), rs.Get<ostring>(37), rs.Get<ostring>(38), rs.Get<int>(40), rs.Get<int>(41), rs.Get<ostring>(42), rs.Get<ostring>(43), rs.Get<ostring>(44), rs.Get<ostring>(45), rs.Get<ostring>(46), rs.Get<ostring>(47)
						, rs.Get<int>(56), rs.Get<int>(19), rs.Get<double>(58), rs.Get<int>(59), rs.Get<ostring>(60), rs.Get<int>(61), rs.Get<ostring>(62), rs.Get<ostring>(63), rs.Get<double>(64), rs.Get<double>(65), rs.Get<double>(66), rs.Get<double>(67), rs.Get<int>(68), rs.Get<int>(69), rs.Get<int>(70), rs.Get<int>(71)
						, rs.Get<int>(72), rs.Get<int>(73), rs.Get<int>(74), rs.Get<int>(75), rs.Get<int>(76), rs.Get<int>(77), rs.Get<int>(78), rs.Get<int>(79), rs.Get<int>(82), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3),
						rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8), rs.Get<double>(17));

					SteelCoil::indata(SteelCoil::s_SteelCoil, -rs.Get<double>(49), rs.Get<double>(48), rs.Get<ostring>(55), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(80), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(53), PRESteelCoil);
				}
				else
				{
					SteelCoil *nonPRE_DHCRSteelCoil = new SteelCoil(rs.Get<ostring>(36), rs.Get<ostring>(9), rs.Get<double>(48), rs.Get<double>(49), rs.Get<double>(57), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(29), rs.Get<ostring>(39), rs.Get<ostring>(55), rs.Get<ostring>(53), rs.Get<ostring>(54), rs.Get<ostring>(80), rs.Get<ostring>(81)
						, rs.Get<ostring>(10), rs.Get<int>(11), rs.Get<ostring>(12), rs.Get<int>(13), rs.Get<ostring>(14), rs.Get<ostring>(15), rs.Get<ostring>(16), rs.Get<double>(20), rs.Get<double>(18), rs.Get<ostring>(22), rs.Get<ostring>(23), rs.Get<ostring>(24), rs.Get<ostring>(25), rs.Get<ostring>(26), rs.Get<ostring>(27), rs.Get<ostring>(28)
						, rs.Get<ostring>(30), rs.Get<ostring>(31), rs.Get<ostring>(32), rs.Get<ostring>(33), rs.Get<ostring>(34), rs.Get<ostring>(35), rs.Get<ostring>(37), rs.Get<ostring>(38), rs.Get<int>(40), rs.Get<int>(41), rs.Get<ostring>(42), rs.Get<ostring>(43), rs.Get<ostring>(44), rs.Get<ostring>(45), rs.Get<ostring>(46), rs.Get<ostring>(47)
						, rs.Get<int>(56), rs.Get<int>(19), rs.Get<double>(58), rs.Get<int>(59), rs.Get<ostring>(60), rs.Get<int>(61), rs.Get<ostring>(62), rs.Get<ostring>(63), rs.Get<double>(64), rs.Get<double>(65), rs.Get<double>(66), rs.Get<double>(67), rs.Get<int>(68), rs.Get<int>(69), rs.Get<int>(70), rs.Get<int>(71)
						, rs.Get<int>(72), rs.Get<int>(73), rs.Get<int>(74), rs.Get<int>(75), rs.Get<int>(76), rs.Get<int>(77), rs.Get<int>(78), rs.Get<int>(79), rs.Get<int>(82), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3),
						rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8), rs.Get<double>(17));

					SteelCoil::indata(SteelCoil::s_SteelCoil, -rs.Get<double>(49), rs.Get<double>(48), rs.Get<ostring>(55), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(80), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(53), nonPRE_DHCRSteelCoil);
				}
			}

			/*-----------输出每个钢卷组内的钢卷--------------*/

			for (map<pair<pair<pair < pair<pair<pair<pair<pair<pair<pair<pair<pair<double, double>, string>, string>, int>, int>, int>, string>, int>, int>, int>, int>, string>, vector<SteelCoil*>>::iterator iter = SteelCoil::s_SteelCoil.begin(); iter != SteelCoil::s_SteelCoil.end(); iter++)
			{
				cout << -(*iter).first.first.first.first.first.first.first.first.first.first.first.first.first << endl;
				for (vector<SteelCoil*>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++)
				{
					cout << (*iter1)->mat_no << endl;
				}
			}
			cout << endl << endl;
			int s_GroupCount = SteelCoil::s_SteelCoil.size();
			cout << "所有钢卷组的个数:" << "  " << s_GroupCount << endl;//钢卷组个数
			cout << endl;

			/*-------------输出每个钢卷组内的钢卷---------------*/
		}
		//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region 初始化乌龟壳
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIP00SI04");// 选择表
			Resultset rs = st.GetResultset();
			// 读取计划类型组合方式
			while (rs.Next())
			{
				pair<string, string> temp;
				temp = make_pair(rs.Get<ostring>(13), rs.Get<ostring>(14));
				TortoiseShell::plantype.insert(make_pair(temp, rs.Get<ostring>(15)));
			}
		}
		//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region 读取热轧计划模型输入流向设定表
		//////////////////////////////////////////////////////////////////////////
		{
			ostring rowid;
			st.Execute("select * from TIPHR22");// 选择表
			Resultset rs = st.GetResultset();

			while (rs.Next())
			{
				pair<double, string> temp;
				temp = make_pair(rs.Get<double>(10), rs.Get<ostring>(11));
				TortoiseShell::flowrule.insert(make_pair(temp, rs.Get<double>(14)));
			}
		}
		//////////////////////////////////////////////////////////////////////////
		#pragma endregion
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();
}