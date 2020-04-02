#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));

	int card[52];			  // �ϴ� ī�尡 52��
	int shape[3], number[3];  // �츮�� �Ź� 3���� ī�常 �����ֱ�
	int dest, sour, temp;
	int betting;
	int money = 100;
	int turn = 2;			  // ī�� 2���� ���� �̾Ƴ��� ����

	for (int i = 0; i < 52; i++)
	{
		card[i] = i;		  // �ϴ� ī�� 52���� �ʱ�ȭ�ؼ� ���ڰ��� �־���
	}

	for (int i = 0; i < 777; i++) // ī�� 52�� ��ü�� ����
	{
		dest = rand() % 52;
		sour = rand() % 52;
		
		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}

	while (true)
	{
		for (int i = 0; i < 3; i++)	// ī�� 3���� �� ����
		{
			shape[i] = card[i + turn - 2] / 13;
			//������ 4���̹Ƿ�, ���ڵ��� [0 ~ 12], [13 ~ 25], [26 ~ 38], [39 ~ 51]�� �з�
			//13���� ������ ���� ����  ��12/13=0,  ��25/13= 1 ��38/13 =2 ��51/13=3

			number[i] = card[i + turn - 2] % 13;
			// ī�忡 ���� ���ڴ� 13���� ������ ���� ���������� ���� �Ǵ��� ��
			//  -->  �������, 3���� ī�带 ��ǻ�Ͱ� �� ���� �ȴ�


			// �� ī�� 3�� �߿� 2�常 �����ְ� �Ѿ��. 0, 1�� �����شٴ� ��
			if (i == 2) break;	


			switch (shape[i])
			{
			case 0:
				cout << "��";	break;
			case 1:
				cout << "��";	break;
			case 2:
				cout << "��";	break;
			case 3:
				cout << "��";	break;
			}

			switch (number[i]) //� ī�� ������ �̾��� �� ���ڰ� 0�̸�~A ���ڰ� 10�̸�~J
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
				cout << number[i] + 1 << "\t"; // ���ڴ� A, J, Q, K�� ��츦 �����ϰ�� +1 �Ǿ� ���
				break;
			}

		}


		cout << endl;

		cout << endl << "�� ������ : " << money << endl << endl;
		cout << "�󸶸� �����ұ�? : ";
		cin >> betting;


		if (betting < 1)
		{
			cout << "�ּ� 1���� �̻� �Žÿ�." << endl;				continue;
		}

		if (betting > money)
		{
			cout << "�����ݺ��� ���� ������ �� �����ϴ�." << endl;		continue;
		}


		if ((number[0] < number[2] && number[2] < number[1]) ||
			(number[1] < number[2] && number[2] < number[0]))
		{
			money += betting;
			cout << endl << betting << " �� ���� ȹ���߽��ϴ�. Congratulations! :)" << endl << endl;
		}
		else
		{
			money -= betting;
			cout << endl << betting << " �� ���� �Ҿ����ϴ�. Try Again! :(" << endl << endl;
		}


		if (money < 1)
		{
			cout << endl << "���� ���� ��� �Ҿ����ϴ�. Game Over..." << endl << endl << endl;	break;
		}

		//����ó�� 
		if (turn + 3 <= 52)
		{
			turn += 3;	// �� ȸ���� 3���� ī�带 ��ŵ�ؼ� �ߺ��� ���� ��
		}

		else
		{
			turn = 2;
			for (int i = 0; i < 777; i++)
			{
				dest = rand() % 52;
				sour = rand() % 52;
				// ī�� 52�� ��ü�� �ٽ� ����
				temp = card[dest];
				card[dest] = card[sour];
				card[sour] = temp;
			}
		}
		cout << " ------------------------------- " << endl << endl;
	}

	return 0;
}