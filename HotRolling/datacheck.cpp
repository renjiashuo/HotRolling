#include <iostream>
#include "ocilib.hpp"

/* requires script demo/products.sql */

using namespace ocilib;

int datacheck()
{
	int flag = 0;
	try
	{
		Environment::Initialize();//������ʼ��
		Connection con("127.0.0.1/orcl", "scott", "tiger");//�������ݿ⣨IP��ַ/�����������û������������롱��
		Statement st(con);//�������ݼ�
		ostring rowid;
		st.Execute("select * from TIPHRM01");//ѡ���
		Resultset rs = st.GetResultset();
		int hard_group = 0;
		int surf_index = 0;
		int slab_thick = 0;
		int low_temp = 0;
		int row = 0;
		//int counthot = 0;
		while (rs.Next())//�����һ�������ݣ�����
		{
			row++;//��ȡ�������
			if (rs.Get<ostring>(39) == "1")
			{				
				if (rs.Get<ostring>(53) > "3")
				{
					hard_group++;
				}
				if (rs.Get<ostring>(54)>"4" || rs.Get<ostring>(54)<"2")
				{
					surf_index++;
				}
				if (rs.Get<double>(48) <230)
				{
					slab_thick++;
				}
			}
			if (rs.Get<ostring>(81) == "1")
			{
				low_temp++;
			}
		}
		std::cout << "�������Ϊ��" << row << std::endl;
		if (hard_group != 0)
		{
			std::cout << "���Ӳ�����������" << std::endl;
			std::cout << "��" << hard_group << "������" << std::endl;
			flag = 1;
			getchar();
		}

		if (surf_index != 0)
		{
			std::cout << "����ָ����������" << std::endl;
			std::cout << "��" << surf_index << "������" << std::endl;
			getchar();
			flag = 1;
		}

		if (slab_thick != 0)
		{
			std::cout << "�־��ȳ�������" << std::endl;
			std::cout << "��" << slab_thick << "������" << std::endl;
			getchar();
			flag = 1;
		}

		if (low_temp<10)
		{
			std::cout << "���±�ǲ���" << std::endl;
			std::cout << "����ֻ��" << low_temp << "����±��" << std::endl;
			getchar();
			flag = 1;
		}

		if (hard_group == 0 && surf_index == 0 && slab_thick == 0 && low_temp >= 10)
			std::cout << "������������" << std::endl;
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	Environment::Cleanup();
	if (flag = 1)//���κ�һ�����ݴ����˳�����
		exit(0);
	
	return EXIT_SUCCESS;
}

