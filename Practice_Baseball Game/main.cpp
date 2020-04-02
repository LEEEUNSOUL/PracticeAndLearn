#include "mainGame.h"
#include "cardGame.h"
#include "baseballGame.h"

int main()
{
	while(true)
	{ 
		cout << "미니게임월드에 온걸 환영합니다" << endl;
		cout << "할 게임을 골라보세요. 1.빙고 2.카드게임 3.야구게임" << endl;
		int selectNum;
		cout << "입력 : ";
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