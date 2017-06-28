#include "f_iphr_readdate.h"

void ReadDate::readdate()
{
	try
	{
		Environment::Initialize();//������ʼ��
		Connection con("127.0.0.1/orcl", "scott", "tiger");//�������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);//�������ݼ�

#pragma region ��ʼ���־�����
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIPHR21 t order by nom_roll_width DESC");//ѡ���
			Resultset rs = st.GetResultset();

			while (rs.Next())
			{

				if (rs.Get<ostring>(39) == "1" && rs.Get<ostring>(29) == "0")		//�����̹��ı�ǣ�������DHCR���ĸ־�ʮ�����׼��ɸ־������map
				{
					SteelCoil *PRESteelCoil = new SteelCoil(rs.Get<ostring>(36), rs.Get<ostring>(9), rs.Get<double>(48), rs.Get<double>(49), rs.Get<double>(57), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(29), rs.Get<ostring>(39), rs.Get<ostring>(55), rs.Get<ostring>(53), rs.Get<ostring>(54), rs.Get<ostring>(80), rs.Get<ostring>(81)
						, rs.Get<ostring>(10), rs.Get<int>(11), rs.Get<ostring>(12), rs.Get<int>(13), rs.Get<ostring>(14), rs.Get<ostring>(15), rs.Get<ostring>(16), rs.Get<double>(20), rs.Get<double>(18), rs.Get<ostring>(22), rs.Get<ostring>(23), rs.Get<ostring>(24), rs.Get<ostring>(25), rs.Get<ostring>(26), rs.Get<ostring>(27), rs.Get<ostring>(28)
						, rs.Get<ostring>(30), rs.Get<ostring>(31), rs.Get<ostring>(32), rs.Get<ostring>(33), rs.Get<ostring>(34), rs.Get<ostring>(35), rs.Get<ostring>(37), rs.Get<ostring>(38), rs.Get<int>(40), rs.Get<int>(41), rs.Get<ostring>(42), rs.Get<ostring>(43), rs.Get<ostring>(44), rs.Get<ostring>(45), rs.Get<ostring>(46), rs.Get<ostring>(47)
						, rs.Get<int>(56), rs.Get<int>(19), rs.Get<double>(58), rs.Get<int>(59), rs.Get<ostring>(60), rs.Get<int>(61), rs.Get<ostring>(62), rs.Get<ostring>(63), rs.Get<double>(64), rs.Get<double>(65), rs.Get<double>(66), rs.Get<double>(67), rs.Get<int>(68), rs.Get<int>(69), rs.Get<int>(70), rs.Get<int>(71)
						, rs.Get<int>(72), rs.Get<int>(73), rs.Get<int>(74), rs.Get<int>(75), rs.Get<int>(76), rs.Get<int>(77), rs.Get<int>(78), rs.Get<int>(79), rs.Get<int>(82), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3),
						rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8), rs.Get<double>(17), rs.Get<int>(87), rs.Get<short>(88), rs.Get<ostring>(89), rs.Get<ostring>(90), rs.Get<ostring>(91), rs.Get<ostring>(92), rs.Get<int>(93), rs.Get<int>(94), rs.Get<ostring>(95), rs.Get<int>(96));

					SteelCoil::indata(SteelCoil::s_SteelCoil, -rs.Get<double>(49), rs.Get<double>(48), rs.Get<ostring>(55), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(80), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(53), PRESteelCoil);
				}
				else
				{
					SteelCoil *nonPRE_DHCRSteelCoil = new SteelCoil(rs.Get<ostring>(36), rs.Get<ostring>(9), rs.Get<double>(48), rs.Get<double>(49), rs.Get<double>(57), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(29), rs.Get<ostring>(39), rs.Get<ostring>(55), rs.Get<ostring>(53), rs.Get<ostring>(54), rs.Get<ostring>(80), rs.Get<ostring>(81)
						, rs.Get<ostring>(10), rs.Get<int>(11), rs.Get<ostring>(12), rs.Get<int>(13), rs.Get<ostring>(14), rs.Get<ostring>(15), rs.Get<ostring>(16), rs.Get<double>(20), rs.Get<double>(18), rs.Get<ostring>(22), rs.Get<ostring>(23), rs.Get<ostring>(24), rs.Get<ostring>(25), rs.Get<ostring>(26), rs.Get<ostring>(27), rs.Get<ostring>(28)
						, rs.Get<ostring>(30), rs.Get<ostring>(31), rs.Get<ostring>(32), rs.Get<ostring>(33), rs.Get<ostring>(34), rs.Get<ostring>(35), rs.Get<ostring>(37), rs.Get<ostring>(38), rs.Get<int>(40), rs.Get<int>(41), rs.Get<ostring>(42), rs.Get<ostring>(43), rs.Get<ostring>(44), rs.Get<ostring>(45), rs.Get<ostring>(46), rs.Get<ostring>(47)
						, rs.Get<int>(56), rs.Get<int>(19), rs.Get<double>(58), rs.Get<int>(59), rs.Get<ostring>(60), rs.Get<int>(61), rs.Get<ostring>(62), rs.Get<ostring>(63), rs.Get<double>(64), rs.Get<double>(65), rs.Get<double>(66), rs.Get<double>(67), rs.Get<int>(68), rs.Get<int>(69), rs.Get<int>(70), rs.Get<int>(71)
						, rs.Get<int>(72), rs.Get<int>(73), rs.Get<int>(74), rs.Get<int>(75), rs.Get<int>(76), rs.Get<int>(77), rs.Get<int>(78), rs.Get<int>(79), rs.Get<int>(82), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3),
						rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8), rs.Get<double>(17), rs.Get<int>(87), rs.Get<short>(88), rs.Get<ostring>(89), rs.Get<ostring>(90), rs.Get<ostring>(91), rs.Get<ostring>(92), rs.Get<int>(93), rs.Get<int>(94), rs.Get<ostring>(95), rs.Get<int>(96));

					SteelCoil::indata(SteelCoil::s_SteelCoil, -rs.Get<double>(49), rs.Get<double>(48), rs.Get<ostring>(55), rs.Get<ostring>(21), rs.Get<int>(50), rs.Get<int>(51), rs.Get<int>(52), rs.Get<ostring>(80), rs.Get<int>(83), rs.Get<int>(84), rs.Get<int>(85), rs.Get<int>(86), rs.Get<ostring>(53), nonPRE_DHCRSteelCoil);
				}
			}

			/*-----------���ÿ���־����ڵĸ־�--------------*/

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
			cout << "���и־���ĸ���:" << "  " << s_GroupCount << endl;//�־������
			cout << endl;

			/*-------------���ÿ���־����ڵĸ־�---------------*/
		}
		//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region ��ʼ���ڹ��
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIP00SI04");// ѡ���
			Resultset rs = st.GetResultset();
			// ��ȡ�ƻ�������Ϸ�ʽ
			while (rs.Next())
			{
				pair<string, string> temp;
				temp = make_pair(rs.Get<ostring>(13), rs.Get<ostring>(14));
				TortoiseShell::plantype.insert(make_pair(temp, rs.Get<ostring>(15)));
			}
		}
		//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region ��ȡ�����ƻ�ģ�����������趨��
		//////////////////////////////////////////////////////////////////////////
		{
			ostring rowid;
			st.Execute("select * from TIPHR22");// ѡ���
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

#pragma region ��ȡ�������Ƶ�Ԫ������׼��
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIPHRBA");// ѡ���
			Resultset rs = st.GetResultset();

			while (rs.Next())
			{
				TortoiseShellRule *Rollingplan = new TortoiseShellRule(rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3), rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8),
					rs.Get<ostring>(9), rs.Get<double>(10), rs.Get<double>(11), rs.Get<double>(12), rs.Get<double>(13), rs.Get<double>(14), rs.Get<double>(15));
			}
		}
		//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region ��ȡ��������Ĺ�̻�׼��
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIPHRBB");// ѡ���
			Resultset rs = st.GetResultset();

			while (rs.Next())
			{
				zhuticai *Zhuticai = new zhuticai(rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3), rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8),
					rs.Get<ostring>(9), rs.Get<short>(10), rs.Get<int>(11), rs.Get<short>(12), rs.Get<short>(13), rs.Get<short>(14), rs.Get<short>(15), rs.Get<double>(16));
			}
		}
		//////////////////////////////////////////////////////////////////////////
#pragma endregion

#pragma region ��ȡ�����̹��Ĺ�̻�׼��
		//////////////////////////////////////////////////////////////////////////
		{
			st.Execute("select * from TIPHRB2");// ѡ���
			Resultset rs = st.GetResultset();

			while (rs.Next())
			{
				tangguncai *Tangguncai = new tangguncai(rs.Get<ostring>(1), rs.Get<ostring>(2), rs.Get<ostring>(3), rs.Get<ostring>(4), rs.Get<ostring>(5), rs.Get<ostring>(6), rs.Get<ostring>(7), rs.Get<ostring>(8),
					rs.Get<ostring>(9), rs.Get<short>(10), rs.Get<int>(11), rs.Get<short>(12), rs.Get<short>(13), rs.Get<short>(14), rs.Get<short>(15), rs.Get<double>(16), rs.Get<short>(17), rs.Get<short>(18), rs.Get<ostring>(19),
					rs.Get<short>(20), rs.Get<short>(21), rs.Get<short>(22), rs.Get<short>(23));
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

void ReadDate::showResultSQL()
{
	try
	{
		Environment::Initialize();//������ʼ��
		Connection con("127.0.0.1/orcl", "scott", "tiger");//�������ݿ⣨IP��ַ/�����������û������������롰��
		Statement st(con);//�������ݼ�
		st.Execute("Delete from TIPHR25 where 1=1");// ɾ��������������
		//st.Execute("insert into TIPHR25 (MOD_STAMP_NO ,IPS_LOT_NO ,PLAN_NO ,MAT_NO ) values(2,3,5,4)");
		string str1 = "insert into TIPHR25 (MOD_STAMP_NO ,IPS_LOT_NO ,PLAN_NO ,MAT_NO, PLAN_EXEC_SEQ_NO, PLAN_BACKLOG_CODE, ROLL_SEQ_NO, PLAN_START_TIME,PLAN_END_TIME, WORK_TYPE ) values(";
		string str2 = ")";
		string tNowStr = "20170421080000";
		string tFirstDayStr = tNowStr.substr(0, 8) + "000000";
		time_t tNow = TortoiseShell::StringToDatetime(tNowStr);
		time_t tFirstDay = TortoiseShell::StringToDatetime(tNowStr) - TortoiseShell::StringToDatetime(tFirstDayStr);
		tFirstDay /= 60;
		for (map<int, TortoiseShell*>::iterator iter = TortoiseShell::s_mapSetOfTortoiseShell.begin(); iter != TortoiseShell::s_mapSetOfTortoiseShell.end(); iter++)
		{
			int tortoiseShellNo = iter->first;
			TortoiseShell *tortoiseShell = iter->second;
			int seqNo = 1;
			for (map<pair<int, int>, Group*>::iterator iter2 = tortoiseShell->m_main_groups.begin(); iter2 != tortoiseShell->m_main_groups.end(); iter2++)
			{
				Group *group = iter2->second;
				for (vector<SteelCoil*>::iterator iter3 = group->m_SteelCoil.begin(); iter3 != group->m_SteelCoil.end(); iter3++)
				{
					SteelCoil *steelCoil = *iter3;
					// ģ���ʴ���
					string str_MOD_STAMP_NO = steelCoil->mod_stamp_no;
					// Ӧ�����κ�
					int int_IPS_LOT_NO = (int)(steelCoil->roll_begin_time_double + tFirstDay + (tortoiseShellNo - 1) * 10) / (24 * 60) + 1;
					char char_IPS_LOT_NO[10];
					sprintf(char_IPS_LOT_NO, "%d", int_IPS_LOT_NO);
					string str_IPS_LOT_NO = char_IPS_LOT_NO;
					// �ƻ���
					char char_PLAN_NO[10];
					sprintf(char_PLAN_NO, "%d", tortoiseShellNo);
					string str_PLAN_NO = char_PLAN_NO;
					if (str_PLAN_NO.size() == 1)
						str_PLAN_NO = "00" + str_PLAN_NO;
					else if (str_PLAN_NO.size() == 2)
						str_PLAN_NO = "0" + str_PLAN_NO;
					// ���Ϻ�
					string str_MAT_NO = steelCoil->mat_no;
					// �ƻ�ִ��˳���
					string str_PLAN_EXEC_SEQ_NO = str_PLAN_NO;
					// �ƻ��������
					string str_PLAN_BACKLOG_CODE = steelCoil->next_whole_backlog_code;
					// ����˳���
					int int_ROLL_SEQ_NO = seqNo++;
					char char_ROLL_SEQ_NO[10];
					sprintf(char_ROLL_SEQ_NO, "%d", int_ROLL_SEQ_NO);
					string str_ROLL_SEQ_NO = char_ROLL_SEQ_NO;
					// �ƻ���ʼʱ��
					int int_PLAN_START_TIME = steelCoil->roll_begin_time_double * 60;
					string str_PLAN_START_TIME = TortoiseShell::DatetimeToString(int_PLAN_START_TIME + tNow + (tortoiseShellNo - 1) * 600);
					// �ƻ�����ʱ��
					int int_PLAN_END_TIME = steelCoil->roll_end_time_double * 60;
					string str_PLAN_END_TIME = TortoiseShell::DatetimeToString(int_PLAN_END_TIME + tNow + (tortoiseShellNo - 1) * 600);
					// ��������
					string str_WORK_TYPE = steelCoil->work_type;
					// ���ݿ�������
					string str = str1 + "'" + str_MOD_STAMP_NO + "'," + str_IPS_LOT_NO + "," + str_PLAN_NO + ",'" + str_MAT_NO + "'," + str_PLAN_EXEC_SEQ_NO + ",'" + str_PLAN_BACKLOG_CODE + "'," + str_ROLL_SEQ_NO + ",'" + str_PLAN_START_TIME + "','" + str_PLAN_END_TIME + "'," + str_WORK_TYPE + str2;
					st.Execute(str);
				}
			}
		}
		con.Commit();	// �ύ���ݿ����
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	Environment::Cleanup();
}