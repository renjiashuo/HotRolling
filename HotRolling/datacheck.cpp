#include <iostream>
#include "ocilib.hpp"

/* requires script demo/products.sql */

using namespace ocilib;

int datacheck()
{
	int flag = 0;
	try
	{
		Environment::Initialize();//环境初始化
		Connection con("127.0.0.1/orcl", "scott", "tiger");//连接数据库（IP地址/服务名，“用户名”，“密码”）
		Statement st(con);//创建数据集
		ostring rowid;
		st.Execute("select * from TIPHRM01");//选择表
		Resultset rs = st.GetResultset();
		int hard_group = 0;
		int surf_index = 0;
		int slab_thick = 0;
		int low_temp = 0;
		int row = 0;
		//int counthot = 0;
		while (rs.Next())//如果下一行有数据，继续
		{
			row++;//获取表的行数
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
		std::cout << "表的行数为：" << row << std::endl;
		if (hard_group != 0)
		{
			std::cout << "最大硬度组出现问题" << std::endl;
			std::cout << "有" << hard_group << "个问题" << std::endl;
			flag = 1;
			getchar();
		}

		if (surf_index != 0)
		{
			std::cout << "表面指数出现问题" << std::endl;
			std::cout << "有" << surf_index << "个问题" << std::endl;
			getchar();
			flag = 1;
		}

		if (slab_thick != 0)
		{
			std::cout << "钢卷厚度出现问题" << std::endl;
			std::cout << "有" << slab_thick << "个问题" << std::endl;
			getchar();
			flag = 1;
		}

		if (low_temp<10)
		{
			std::cout << "低温标记不足" << std::endl;
			std::cout << "现在只有" << low_temp << "块低温标记" << std::endl;
			getchar();
			flag = 1;
		}

		if (hard_group == 0 && surf_index == 0 && slab_thick == 0 && low_temp >= 10)
			std::cout << "所有数据正常" << std::endl;
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	Environment::Cleanup();
	if (flag = 1)//有任何一项数据错误，退出程序
		exit(0);
	
	return EXIT_SUCCESS;
}

