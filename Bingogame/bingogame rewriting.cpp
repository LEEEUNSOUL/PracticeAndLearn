#include <iostream>
#include <time.h>

using namespace std; 

int main()
{
			srand(time(NULL));

			int number[25];
			int dest, temp, sour; //���� �˰���
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

					//���� 5���� ���� �۾� 
					for (int i = 0; i < 25; i++)
					{
						if (number[i] == 35) cout << char(number[i]) << "\t";
						else cout << number[i] << "\t";

						if ((i + 1) % 5 == 0) cout << endl << endl;
					}


					cout << "���ڸ� �Է��Ͻÿ� : ";
					cin >> playerNum;

					cout << endl;
					cout << endl;

					//�Է��� ���� 25�� �߿��� � �Ͱ� ��Ī�� �� ���ΰ�? 
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
						//���η� ������ �� ���� ī��Ʈ upup
						if (number[i]== 35 &&
							number[i*5+1] == 35 &&
							number[i*5+2] == 35 &&
							number[i*5+3] == 35 &&
							number[i*5+4] == 35
							)
						{
							bingocount++; 
						}

						//���η� ������ �� ���� ī��Ʈ upup
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
						//�밢�� ������ �� ���� ī��Ʈ upup
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