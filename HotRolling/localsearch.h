#include "global.h"
#include "SteelCoil.h"
#include "Group.h"
#include "TortoiseShell.h"
#pragma region ����

vector <int> vec_Chosen_Position_Start;		//���� Group_Position_Start        �������ѡ�е��ڹ�ǵ�����group�� ��ʼ λ��
vector <int> vec_Chosen_Position_End;		//���� Group_Position_Start        �������ѡ�е��ڹ�ǵ�����group�� ��ֹ λ��
vector <int> vec_Another_Position_Start;	//���� map_Another_Position_Start  �������ѡ�ڶ����ڹ�ǵ�����group�� ��ʼ λ��
vector <int> vec_Another_Position_End;		//���� map_Another_Position_End    �������ѡ�ڶ����ڹ�ǵ�����group�� ��ֹ λ��

int Chosen_Position_No;					//���� Chosen_Position_No          Ϊѡ�еĸ־����λ�ú�
int Chosen_Shell;							//���� Chosen_Shell                Ϊ���ץȡ��shell���
int Chosen_Position_Start;					//���� Chosen_Position_Start       Ϊѡ�еĸ־���� ��ʼ ������
int Chosen_Position_End;					//���� Chosen_Position_End         Ϊѡ�е� ��ֹ ������
int Chosen_Position_Upper_Start;			//���� Chosen_Position_Upper_Start Ϊѡ��λ�� ��һ�� �־��� ��ʼ ������
int Chosen_Position_Upper_End;				//���� Chosen_Position_Upper_End   Ϊѡ��λ�� ��һ�� �־��� ��ֹ ������
int Chosen_Position_Under_Start;			//���� Chosen_Position_Under_Start Ϊѡ��λ�� ��һ�� �־��� ��ʼ ������
int Chosen_Position_Under_End;				//���� Chosen_Position_Under_End   Ϊѡ��λ�� ��һ�� �־��� ��ֹ ������
int Chosen_Width = 0;						//���� Chosen_Width                Ϊѡȡ�ĸ־���Ŀ��

int Another_Position_No;					//���� Another_Position_No          Ϊѡ�ڶ����־����λ�ú�
int Another_Shell;							//���� Another_Shell                Ϊ�ڶ����ڹ�ǵı��
int Another_Position_Start = 0;			//���� Another_Position_Start       Ϊ�ڶ���shell�����ƹ�������ʼ	
int Another_Position_End = 0;				//���� Another_Position_End         Ϊ�ڶ���shell�����ƹ�������ֹ
int Another_Position_Upper_Start;			//���� Another_Position_Upper_Start Ϊ�ڶ���ѡ��λ�� ��һ�� �־��� ��ʼ ������
int Another_Position_Upper_End;			//���� Another_Position_Upper_End   Ϊ�ڶ���ѡ��λ�� ��һ�� �־��� ��ֹ ������
int Another_Position_Under_Start;			//���� Another_Position_Under_Start Ϊ�ڶ���ѡ��λ�� ��һ�� �־��� ��ʼ ������
int Another_Position_Under_End;			//���� Another_Position_Under_End   Ϊ�ڶ���ѡ��λ�� ��һ�� �־��� ��ֹ ������
int Another_Width = 0;						//���� Another_Width                Ϊ�ڶ����ڹ�ǵĸ־���Ŀ��


//map<���,[��ʼ����������ֹ��������Group*] >
map<int, pair< pair< int, int >, Group* > > map_Candidate_Group;
map<pair<int, int>, Group*>			m_temp;						// ��ʱ�������Ż�ʱ���ж�����λ������á�
map<pair<int, int>, Group*>			m_temp1;					// ��ʱ�������Ż�ʱ���ж�����λ������á�
map<pair<int, int>, Group*>			temp;
map<pair<int, int>, Group*>			temp1;

#pragma endregion
