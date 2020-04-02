#include <iostream>
#include <time.h>

using namespace std; 

int main()
{
			srand(time(NULL));

			int number[25];
			int dest, temp, sour; //셔플 알고리즘
			int playerNum;
			int bingocount = 0; 
			
			int num = 35; 
		

			for (int i =0 ; i < 25; i++)
			{
				number[i] = i + 1;
			}

			cout << endl;

			for (int i = 0; i < 100; i++)
			{
				dest = rand() % 25;
				sour = rand() % 25;

				temp = number[dest];
				number[dest] = number[sour];
				number[sour] = temp;
			}


				
				while (true)
				{
					system("cls");
				
					
					cout << "<<<<<<<<<<<<<<<bingo game start!>>>>>>>>>>>>>>" << endl;
					cout << endl;
					cout << "bingocount : " << bingocount << endl;

					//숫자 5개씩 끊는 작업 
					for (int i = 0; i < 25; i++)
					{
						if (number[i] == 35) cout << char(number[i]) << "\t";
						else cout << number[i] << "\t";

						if ((i + 1) % 5 == 0) cout << endl << endl;
					}


					cout << "숫자를 입력하시오 : ";
					cin >> playerNum;

					cout << endl;
					cout << endl;

					//입력한 숫자 25개 중에서 어떤 것과 매칭이 될 것인가? 
					for (int i = 0; i < 25; i++)
					{
						if (playerNum == number[i])
						{
							number[i] = num;
						}
					}

					bingocount = 0; 

					for (int i = 0; i < 25; i++)
					{
						//가로로 빙고일 때 빙고 카운트 upup
						if (number[i]== 35 &&
							number[i*5+1] == 35 &&
							number[i*5+2] == 35 &&
							number[i*5+3] == 35 &&
							number[i*5+4] == 35
							)
						{
							bingocount++; 
						}

						//세로로 빙고일 때 빙고 카운트 upup
						if (number[i] == 35 &&
							number[5 + i] == 35 &&
							number[10 + i] == 35 &&
							number[15 + i] == 35 &&
							number[20 + i] == 35
							)
						{
							bingocount++;
						}
					}
						//대각선 빙고일 때 빙고 카운트 upup
						if (number[0] == 35 &&
							number[6] == 35 &&
							number[12] == 35 &&
							number[18] == 35 &&
							number[24] == 35
							)
						{
							bingocount++;
						}
						
						if (number[4] == 35 &&
							number[8] == 35 &&
							number[12] == 35 &&
							number[16] == 35 &&
							number[20] == 35
							)
						{
							bingocount++;
						}

						if (bingocount > 4)
						{
							cout << "success!!" << endl;
							break; 
						}

				}



	return 0; 
}