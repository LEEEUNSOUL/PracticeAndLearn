#include "stdafx.h"
#include "AirHockeyPractice.h"


AirHockeyPractice::AirHockeyPractice()
{
}


AirHockeyPractice::~AirHockeyPractice()
{
}


HRESULT AirHockeyPractice::init()
{
	gameNode::init();
	srand(GetTickCount());
	temp = rand() % 2; //0~1���� ���ڸ� �������� ���� 

	//playball�� ������
	_playBall.x = WINSIZEX / 2;
	_playBall.y = WINSIZEY / 2;
	_playBall.radius = 20;
	_playBall.angle = PI * temp;
	_playBall.speed = 3;


	//�׸� ��ȯ
	_ball    = new image; 
	_ball-> init("ball.bmp", 40, 40, true, RGB(255, 0, 255)); 
	_ground  = new image;
	_ground	 ->init("ground.bmp", 1024, 768, false, RGB(0, 0, 0));
	
	_player1 = new image;
	_player1 ->init("player1.bmp", 80, 80, true, RGB(255, 0, 255));
	
	_player2 = new image;
	_player2 ->init("player2.bmp", 80, 80, true, RGB(255, 0, 255));


	//���� �ڸ� ���� �� �ʱ�ȭ 
	char str[256];
	for(int i = 0; i < NUMBERMAX; i++)
	{
		_number[i] = new image; 
		sprintf_s(str, "%d.bmp", i);
		_number[i]->init(str, 50, 75, true, RGB(255, 0, 255)); 
	}

	//1P ������ 
	_1pBall.x = WINSIZEX / 2 - 350; _1pBall.y = WINSIZEY / 2;
	_1pBall.radius = 40;
	_1pBall.moving = false;

	//2P ������
	_2pBall.x = WINSIZEX / 2 + 350; _2pBall.y = WINSIZEY / 2;
	_2pBall.radius = 40;
	_2pBall.moving = false;

	//��� 1 ��Ʈ ���� 
	_goal1 = RectMakeCenter(0, WINSIZEY / 2, 50, 300); 

	//��� 2 ��Ʈ ���� 
	_goal2 = RectMakeCenter(WINSIZEX, WINSIZEY / 2, 50, 300);
	_1pBall.point = 0;
	_2pBall.point = 0;

	_count = 0;
	_playBall.goalIn = false;
	return S_OK;
}

void AirHockeyPractice::release()
{
	gameNode::release();
}


void AirHockeyPractice::update()
{
	gameNode::update();
	keyControl();
	playBallCollision();
	playBallMove();
	goalIn();
}


void AirHockeyPractice::render(HDC hdc)
{
	
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	_ground->render(backDC, 0, 0);
	//RectangleMakeCenter(backDC, WINSIZEX / 2, WINSIZEY / 2, 1024, 768);

	//���� ��� �׸��� 
	//Rectangle(backDC, _goal1);

	//������ ��� �׸��� 
	//Rectangle(backDC, _goal2);

	//��� �߽����� �� �߱� 
	//LineMake(backDC, WINSIZEX / 2, 0, WINSIZEX / 2, WINSIZEY);
	
	//playBall
	//EllipseMakeCenter(backDC, _playBall.x, _playBall.y, _playBall.radius * 2, _playBall.radius * 2);
	_ball->render(backDC, _playBall.x - _playBall.radius, _playBall.y - _playBall.radius);
	//1P��

	/*HBRUSH brush4 = CreateSolidBrush(RGB(188, 143, 143));
	HBRUSH oldBrush4 = (HBRUSH)SelectObject(backDC, brush4);
	EllipseMakeCenter(backDC, _1pBall.x, _1pBall.y, _1pBall.radius * 2, _1pBall.radius * 2);
	SelectObject(backDC, oldBrush4);
	DeleteObject(brush4);*/
	_player1->render(backDC, _1pBall.x - _1pBall.radius, _1pBall.y - _1pBall.radius);

	//2P�� 
	/*HBRUSH brush5 = CreateSolidBrush(RGB(70, 130, 180));
	HBRUSH oldBrush5 = (HBRUSH)SelectObject(backDC, brush5);
	EllipseMakeCenter(backDC, _2pBall.x, _2pBall.y, _2pBall.radius * 2, _2pBall.radius * 2);
	SelectObject(backDC, oldBrush5);
	DeleteObject(brush5);*/
	_player2->render(backDC, _2pBall.x - _2pBall.radius, _2pBall.y - _2pBall.radius);
	
	//���ھ� �ȳ� 

	//char p1Score[20];
//	char p2Score[20];

	//sprintf_s(p1Score, "%d", _1pBall.point);
//	sprintf_s(p2Score, "%d", _2pBall.point);

	//TextOut(backDC, WINSIZEX / 2 - 300, WINSIZEY / 2 - 300, p1Score, strlen(p1Score));
	//TextOut(backDC, WINSIZEX / 2 + 300, WINSIZEY / 2 + 300, p2Score, strlen(p2Score));
	
	//���� 1 = player 1 ���ھ� 
	UINT num = _1pBall.point; 
	UINT temp[2];
	ZeroMemory(&temp, sizeof(UINT));
	//23
	temp[0] = num / 10; 
	temp[1] = num % 10; 

	vector<image*> board; 

	//���ھ��� ��ȭ�� ���� _number[i]�� ��ȭ ����
	for (int i = 0; i < 2; i++)
	{
		board.push_back(_number[temp[i]]); 
	}
	for (size_t t = 0; t < board.size(); t++)
	{
		board[t]->render(backDC, WINSIZEX / 2 - 450 + t * 50, WINSIZEY / 2 - 350); 
	}


	//���� 2 = player 2 ���ھ� 
	UINT num2 = _2pBall.point;
	UINT temp2[2];
	ZeroMemory(&temp2, sizeof(UINT));
	
	//23
	temp2[0] = num2 / 10;
	temp2[1] = num2 % 10;

	vector<image*> board2;

	//���ھ��� ��ȭ�� ���� _number[i]�� ��ȭ ����
	for (int i = 0; i < 2; i++)
	{
		board2.push_back(_number[temp2[i]]);
	}

	for (size_t t = 0; t < board2.size(); t++)
	{
		board2[t]->render(backDC, WINSIZEX / 2 + 350 + t * 50, WINSIZEY / 2 - 350);
	}

	//===================================================

	this->getBackBuffer()->render(hdc, 0, 0);
}

void AirHockeyPractice::keyControl()
{

	//1P 
	if (KEYMANAGER->isStayKeyDown('A') & _1pBall.x > 0)
	{
		_1pBall.x -= 6;
		_1pBall.moving = true;

	}// LEFT
	if (KEYMANAGER->isStayKeyDown('D') & _1pBall.x < WINSIZEX / 2)
	{
		_1pBall.x += 6; //RIGHT 
		_1pBall.moving = true;
	}
	if (KEYMANAGER->isStayKeyDown('W') & _1pBall.y > 0)
	{
		_1pBall.y -= 6; // UP
		_1pBall.moving = true;
	}
	if (KEYMANAGER->isStayKeyDown('S') & _1pBall.y < WINSIZEY)
	{
		_1pBall.y += 6; // DOWN
		_1pBall.moving = true;
	}
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D') ||
		KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S'))
		_1pBall.moving = false;

	//2P
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) & _2pBall.x > WINSIZEX / 2)
	{
		_2pBall.x -= 6; //LEFT 
		_2pBall.moving = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) & _2pBall.x < WINSIZEX)
	{
		_2pBall.x += 6; //RIGHT
		_2pBall.moving = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) & _2pBall.y > 0)
	{
		_2pBall.y -= 6; // UP
		_2pBall.moving = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) & _2pBall.y < WINSIZEY)
	{
		_2pBall.y += 6; // DOWN
		_2pBall.moving = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT)
		|| KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
		_2pBall.moving = false;
}

void AirHockeyPractice::playBallMove()
{
	_count++;
	if (_count > 30)
	{
		_playBall.speed -= SLOW;
		_count = 0;
	}
	_playBall.x += cosf(_playBall.angle) * _playBall.speed;
	_playBall.y += -sinf(_playBall.angle) * _playBall.speed;
}


void AirHockeyPractice::playBallCollision()
{
	//_playBall : 1P�� �ε����� ��
	if (_playBall.radius + _1pBall.radius >= getDistance(_1pBall.x, _1pBall.y, _playBall.x, _playBall.y))
	{
		_playBall.angle = getAngle(_1pBall.x, _1pBall.y, _playBall.x, _playBall.y);
		if (_1pBall.moving == true) _playBall.speed = 10;
	}

	//_playBall : 2P�� �ε����� ��
	if (_playBall.radius + _2pBall.radius >= getDistance(_2pBall.x, _2pBall.y, _playBall.x, _playBall.y))
	{
		_playBall.angle = getAngle(_2pBall.x, _2pBall.y, _playBall.x, _playBall.y);
		if (_2pBall.moving == true) _playBall.speed = 10;
	}
}


void AirHockeyPractice::goalIn()
{
	//goal�� �浹���� �� ī��Ʈ +1 �ǰ� �� ������� 
	//��輱�� �浹���� �� �ݻ簢 ������Ѽ� ƨ��� �ϱ� 

	//Y�� 0 �̻� �ö� �� ƨ�� ó�� 
	if (_playBall.y - _playBall.radius <= 0)
	{
		_playBall.y = _playBall.radius;
		_playBall.angle = PI2 - _playBall.angle;
	}


	//Y�� MAX �̻� ������ �� 
	if (_playBall.y + _playBall.radius >= WINSIZEY)
	{
		_playBall.y = WINSIZEY - _playBall.radius; //WINSIZEY���� �������� ����ŭ�� ���� _playBall�� ����
		_playBall.angle = PI2 - _playBall.angle;
	}


	//X�� 0�� �Ѿ �� ƨ�� ó�� 
	if (_playBall.x - _playBall.radius <= 0)
	{
		if (_playBall.y - _playBall.radius < _goal1.top || _playBall.y + _playBall.radius > _goal1.bottom)
		{
			_playBall.x = _playBall.radius;
			_playBall.angle = PI - _playBall.angle;
		}
		else
		{
			_2pBall.point++;
			_playBall.x = WINSIZEX / 2; _playBall.y = WINSIZEY / 2;
			_playBall.speed = 5; _playBall.angle = PI;
		}
	}


	//X�� MAX �Ѿ �� ƨ�� ó��
	if (_playBall.x + _playBall.radius >= WINSIZEX)
	{
		if (_playBall.y < _goal2.top || _goal2.bottom < _playBall.y)
		{
			_playBall.x = WINSIZEX - _playBall.radius;
			_playBall.angle = PI - _playBall.angle;
		}

		else
		{
			_1pBall.point++;
			_playBall.x = WINSIZEX / 2; _playBall.y = WINSIZEY / 2;
			//���� ���ǵ带 �ٽ� �����������. 
			_playBall.speed = 5; _playBall.angle = 0;
		}
	}
}
