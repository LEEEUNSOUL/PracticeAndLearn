#include "baseballGame.h"
#include <time.h>
#include <iostream>
#include <Windows.h>
using namespace std;


baseballGame::baseballGame()
{
		srand((UINT)time(0));

		int c1 = rand() % 9 + 1;
		int c2;
		int c3;
		int p1;
		int p2;
		int p3;
		int strikeNum = 0;
		int ballNum = 0;

		int count = 10;
		//먼저 컴퓨터 숫자 3자리를 정하는 작업 먼저
		while (true)
		{
			c2 = rand() % 10;
			if (c1 == c2) continue;
			c3 = rand() % 10;
			if (c3 == c2 || c3 == c1) continue;
			break;
		}
		cout << c1 << c2 << c3 << endl;

		while (true)
		{
			cout << "첫번째 볼을 던져라 : ";
			cin >> p1;
			cout << "두번째 볼을 던져라 : ";
			cin >> p2;
			cout << "세번째 볼을 던져라 : ";
			cin >> p3;
			
			//입력이 끝났으니까 입력받은 숫자랑 컴퓨터 숫자랑 비교연산

			if (c1 == p1) strikeNum++;
			if (c1 == p2) ballNum++;
			if (c1 == p3) ballNum++;
			if (c2 == p1) ballNum++;
			if (c2 == p2) strikeNum++;
			if (c2 == p3) ballNum++;
			if (c3 == p1) ballNum++;
			if (c3 == p2) ballNum++;
			if (c3 == p3) strikeNum++;

			if (strikeNum < 1 && ballNum < 1)
			{
				cout << "아웃" << endl;
			}
			else if (strikeNum > 0 && ballNum < 1)
			{
				cout << strikeNum << " 스트라이크" << endl;
			}
			else if (strikeNum < 1 && ballNum > 0)
			{
				cout << ballNum << " 볼" << endl;
			}
			else
			{
				cout << strikeNum << " 스트라이크 " << ballNum << " 볼" << endl;
			}
			if (strikeNum >= 3)
			{
				cout << "너의 승리다" << endl;
				break;
			}
			if (count < 1)
			{
				cout << "게임오버" << endl;
				break;
			}

			//한 번 사용한 스트라이크 와 볼 변수는 0으로 초기화
			strikeNum = ballNum = 0;
			cout << count << " 기회 남았다" << endl;
			count--;
		}





}


baseballGame::~baseballGame()
{
}
