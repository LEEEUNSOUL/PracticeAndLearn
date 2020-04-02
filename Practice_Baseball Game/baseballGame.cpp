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
		//���� ��ǻ�� ���� 3�ڸ��� ���ϴ� �۾� ����
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
			cout << "ù��° ���� ������ : ";
			cin >> p1;
			cout << "�ι�° ���� ������ : ";
			cin >> p2;
			cout << "����° ���� ������ : ";
			cin >> p3;
			
			//�Է��� �������ϱ� �Է¹��� ���ڶ� ��ǻ�� ���ڶ� �񱳿���

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
				cout << "�ƿ�" << endl;
			}
			else if (strikeNum > 0 && ballNum < 1)
			{
				cout << strikeNum << " ��Ʈ����ũ" << endl;
			}
			else if (strikeNum < 1 && ballNum > 0)
			{
				cout << ballNum << " ��" << endl;
			}
			else
			{
				cout << strikeNum << " ��Ʈ����ũ " << ballNum << " ��" << endl;
			}
			if (strikeNum >= 3)
			{
				cout << "���� �¸���" << endl;
				break;
			}
			if (count < 1)
			{
				cout << "���ӿ���" << endl;
				break;
			}

			//�� �� ����� ��Ʈ����ũ �� �� ������ 0���� �ʱ�ȭ
			strikeNum = ballNum = 0;
			cout << count << " ��ȸ ���Ҵ�" << endl;
			count--;
		}





}


baseballGame::~baseballGame()
{
}
