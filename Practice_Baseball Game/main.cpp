#include "mainGame.h"
#include "cardGame.h"
#include "baseballGame.h"

int main()
{
	while(true)
	{ 
		cout << "�̴ϰ��ӿ��忡 �°� ȯ���մϴ�" << endl;
		cout << "�� ������ ��󺸼���. 1.���� 2.ī����� 3.�߱�����" << endl;
		int selectNum;
		cout << "�Է� : ";
		cin >> selectNum;

		switch (selectNum)
		{
			case 1: 
			{
				mainGame mg;
			}
			break; 


			case 2:
			{
				cardGame cg; 
			}
			break; 

			case 3:
			{
				baseballGame bg;
			}
			break;

		}
	}

	return 0; 
}