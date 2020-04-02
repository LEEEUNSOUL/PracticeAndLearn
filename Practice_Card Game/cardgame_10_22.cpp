#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));

	int card[52];			  // 일단 카드가 52장
	int shape[3], number[3];  // 우리는 매번 3장의 카드만 보여주기
	int dest, sour, temp;
	int betting;
	int money = 100;
	int turn = 2;			  // 카드 2장을 먼저 뽑아놓고 시작

	for (int i = 0; i < 52; i++)
	{
		card[i] = i;		  // 일단 카드 52장을 초기화해서 숫자값을 넣어줌
	}

	for (int i = 0; i < 777; i++) // 카드 52장 전체를 셔플
	{
		dest = rand() % 52;
		sour = rand() % 52;
		
		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}

	while (true)
	{
		for (int i = 0; i < 3; i++)	// 카드 3장을 고를 것임
		{
			shape[i] = card[i + turn - 2] / 13;
			//문양이 4개이므로, 숫자들을 [0 ~ 12], [13 ~ 25], [26 ~ 38], [39 ~ 51]로 분류
			//13으로 나눴을 때의 몫이  ㄴ12/13=0,  ㄴ25/13= 1 ㄴ38/13 =2 ㄴ51/13=3

			number[i] = card[i + turn - 2] % 13;
			// 카드에 적힌 숫자는 13으로 나눴을 때의 나머지값을 보고 판단할 것
			//  -->  여기까지, 3장의 카드를 컴퓨터가 고른 것이 된다


			// 고른 카드 3장 중에 2장만 보여주고 넘어가라. 0, 1만 보여준다는 뜻
			if (i == 2) break;	


			switch (shape[i])
			{
			case 0:
				cout << "♠";	break;
			case 1:
				cout << "◆";	break;
			case 2:
				cout << "♥";	break;
			case 3:
				cout << "♣";	break;
			}

			switch (number[i]) //어떤 카드 한장을 뽑았을 때 숫자가 0이면~A 숫자가 10이면~J
			{
			case 0:
				cout << "A\t";	break;
			case 10:
				cout << "J\t";	break;
			case 11:
				cout << "Q\t";	break;
			case 12:
				cout << "K\t";	break;
			default:
				cout << number[i] + 1 << "\t"; // 숫자는 A, J, Q, K의 경우를 제외하고는 +1 되어 출력
				break;
			}

		}


		cout << endl;

		cout << endl << "총 소지금 : " << money << endl << endl;
		cout << "얼마를 베팅할까? : ";
		cin >> betting;


		if (betting < 1)
		{
			cout << "최소 1만원 이상 거시오." << endl;				continue;
		}

		if (betting > money)
		{
			cout << "소지금보다 많이 베팅할 수 없습니다." << endl;		continue;
		}


		if ((number[0] < number[2] && number[2] < number[1]) ||
			(number[1] < number[2] && number[2] < number[0]))
		{
			money += betting;
			cout << endl << betting << " 만 원을 획득했습니다. Congratulations! :)" << endl << endl;
		}
		else
		{
			money -= betting;
			cout << endl << betting << " 만 원을 잃었습니다. Try Again! :(" << endl << endl;
		}


		if (money < 1)
		{
			cout << endl << "가진 돈을 모두 잃었습니다. Game Over..." << endl << endl << endl;	break;
		}

		//예외처리 
		if (turn + 3 <= 52)
		{
			turn += 3;	// 매 회마다 3장의 카드를 스킵해서 중복을 막을 것
		}

		else
		{
			turn = 2;
			for (int i = 0; i < 777; i++)
			{
				dest = rand() % 52;
				sour = rand() % 52;
				// 카드 52장 전체를 다시 셔플
				temp = card[dest];
				card[dest] = card[sour];
				card[sour] = temp;
			}
		}
		cout << " ------------------------------- " << endl << endl;
	}

	return 0;
}