#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h"
#pragma region 定义

vector <int> vec_Chosen_Position_Start;		//定义 Group_Position_Start        容器存放选中的乌龟壳的所有group的 起始 位置
vector <int> vec_Chosen_Position_End;		//定义 Group_Position_Start        容器存放选中的乌龟壳的所有group的 终止 位置
vector <int> vec_Another_Position_Start;	//定义 map_Another_Position_Start  容器存放选第二个乌龟壳的所有group的 起始 位置
vector <int> vec_Another_Position_End;		//定义 map_Another_Position_End    容器存放选第二个乌龟壳的所有group的 终止 位置

int Chosen_Position_No;					//定义 Chosen_Position_No          为选中的钢卷组的位置号
int Chosen_Shell;							//定义 Chosen_Shell                为随机抓取的shell编号
int Chosen_Position_Start;					//定义 Chosen_Position_Start       为选中的钢卷组的 起始 公里数
int Chosen_Position_End;					//定义 Chosen_Position_End         为选中的 终止 公里数
int Chosen_Position_Upper_Start;			//定义 Chosen_Position_Upper_Start 为选中位置 上一块 钢卷组 起始 公里数
int Chosen_Position_Upper_End;				//定义 Chosen_Position_Upper_End   为选中位置 上一块 钢卷组 终止 公里数
int Chosen_Position_Under_Start;			//定义 Chosen_Position_Under_Start 为选中位置 下一块 钢卷组 起始 公里数
int Chosen_Position_Under_End;				//定义 Chosen_Position_Under_End   为选中位置 下一块 钢卷组 终止 公里数
int Chosen_Width = 0;						//定义 Chosen_Width                为选取的钢卷组的宽度

int Another_Position_No;					//定义 Another_Position_No          为选第二个钢卷组的位置号
int Another_Shell;							//定义 Another_Shell                为第二个乌龟壳的编号
int Another_Position_Start = 0;			//定义 Another_Position_Start       为第二个shell的轧制公里数起始	
int Another_Position_End = 0;				//定义 Another_Position_End         为第二个shell的轧制公里数终止
int Another_Position_Upper_Start;			//定义 Another_Position_Upper_Start 为第二个选中位置 上一块 钢卷组 起始 公里数
int Another_Position_Upper_End;			//定义 Another_Position_Upper_End   为第二个选中位置 上一块 钢卷组 终止 公里数
int Another_Position_Under_Start;			//定义 Another_Position_Under_Start 为第二个选中位置 下一块 钢卷组 起始 公里数
int Another_Position_Under_End;			//定义 Another_Position_Under_End   为第二个选中位置 下一块 钢卷组 终止 公里数
int Another_Width = 0;						//定义 Another_Width                为第二个乌龟壳的钢卷组的宽度


//map<序号,[起始公里数，终止公里数，Group*] >
map<int, pair< pair< int, int >, Group* > > map_Candidate_Group;
map<pair<int, int>, Group*>			m_temp;						// 临时容器，优化时，判断轧制位区间等用。
map<pair<int, int>, Group*>			m_temp1;					// 临时容器，优化时，判断轧制位区间等用。
map<pair<int, int>, Group*>			temp;
map<pair<int, int>, Group*>			temp1;

#pragma endregion
