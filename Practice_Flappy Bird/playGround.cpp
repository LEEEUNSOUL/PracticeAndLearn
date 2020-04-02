#include "stdafx.h"
#include "playGround.h"
#include  <string>


playGround::playGround()
{
	
}

playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init();


	//�÷��̾� ��Ʈ ����
	_bird.x = WINSIZEX / 2 -200;
	_bird.y = WINSIZEY / 2;
	_bird.rc = RectMakeCenter(_bird.x, _bird.y, 30, 30);
	_bird.gravity = 0; 
	_bird.jumpPower = 0; 

	
	//�׸� ��ȯ 
	_background = new image; 
	_background->init("_background.bmp", 1024, 768, false, RGB(0, 0, 0));

	_birdImage = new image;
	_birdImage->init("_birdImage.bmp", 60, 42, true, RGB(255, 0, 255)); // true�� Ư�� �ȼ��� ���ٴ� �ǹ�
	
	_pipe_down = new image; 
	_pipe_down->init("_pipe_down.bmp", 100, 450, true, RGB(255, 0, 255)); 

	_pipe_up= new image;
	_pipe_up->init("_pipe_up.bmp", 100, 450, true, RGB(255, 0, 255));

	_gameoverImage = new image; 
	_gameoverImage->init("_gameoverImage.bmp", 193, 42, true, RGB(255, 0, 255)); 
	

	//���� �̹��� �������� / �ʱ�ȭ 
	char str[256];
	for (int i = 0; i < NUMBERMAX; i++)
	{
		_number[i] = new image;
		sprintf_s(str, "number_%d.bmp", i); //���� �̸� �ֱ� 
		_number[i]->init(str, 50, 75, true, RGB(255, 0, 255));
	}


	//movingWall ���� 
	for (int i = 0; i < 3; i++)
	{

		//���� ���� ������ �� ���� ���� �� ������ �޾ƿ´�
		_wall[i].rnd = RND->getFromIntTo(-50, 150);


		//�� ���������� ���ھ�ڽ��� �������� ������ �Ǵµ� ���̰��� 350�� Default�� ���������� ���̸� ��
		_wall[i].x = WINSIZEX / 2 + 500 * i+800; 
		_wall[i].y = 350 + _wall[i].rnd;
		

		//������ �Ǵ� ���ھ� �ڽ��� ���� �׷��ְ�
		_wall[i].score = RectMakeCenter(_wall[i].x, _wall[i].y, 50, 100);


		// �� ���������� ������ �����Ѵ�
		_middleX = (_wall[i].score.right + _wall[i].score.left) / 2;
		_middleY = (_wall[i].score.top + _wall[i].score.bottom) / 2;


		//�� �Ʒ� �������� ���ھ� �ڽ��� �߽ɰ� �������� ��ġ�� �������ش�
		_wall[i].top = RectMakeCenter(_middleX, _middleY - 300 , PIPEWIDTH, PIPEHEIGHT);
		_wall[i].bottom = RectMakeCenter(_middleX, _middleY + 300, PIPEWIDTH, PIPEHEIGHT + _wall[i].rnd);
		

		//ó���� �ڽ� üũ�Ǵ� ���� üũ 
		_wall[i].isCheck = true;
	}


	//bool�� �ʱ� ���� 
	_score = 0; 
	_bird.isJump = false;
	_gameOver = false; 
	return S_OK;
}


void playGround::release()
{
	gameNode::release();
}


void playGround::update()
{
	gameNode::update();

	if (_gameOver && KEYMANAGER->isOnceKeyDown(VK_SPACE)) init();

	if (!_gameOver)
	{
		//Ű ������ �����ϱ� + �߷� ���� 
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_bird.jumpPower = 5; 
			_bird.gravity = 0.15f; 
			_bird.isJump = true; 
		}

		if (_bird.isJump)
		{
			_bird.y -= _bird.jumpPower; 
			_bird.jumpPower -= _bird.gravity; 
		} 

		//������ ��ġ�� �÷��̾� ��Ʈ �� �ٽ� ����
		_bird.rc = RectMakeCenter(_bird.x, _bird.y, 50, 50); 
	
		movingWall_collision(); //�� �����̱� 

		//�浹ó�� 
		for (int i = 0; i < 3; i++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_wall[i].score, &_bird.rc) && _wall[i].isCheck)
			{
				_wall[i].isCheck = false;
				_score++;
			}

			if (IntersectRect(&temp, &_wall[i].top, &_bird.rc) ||
				IntersectRect(&temp, &_wall[i].bottom, &_bird.rc)) _gameOver = true;
		}
	}
}


void playGround::render(HDC hdc)
{
	HDC  backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	//��� �׸��� 
	_background->render(backDC, 0, 0);

	//�÷��̾� ��Ʈ �׸��� 
	HBRUSH brush1 = CreateSolidBrush(RGB(255, 255, 2));
	HBRUSH oldBrush1 = (HBRUSH)SelectObject(backDC, brush1);
	
	_birdImage->render(backDC, _bird.rc.left, _bird.rc.top);

	//Rectangle(backDC, _bird.rc); 

	SelectObject(backDC, oldBrush1);
	DeleteObject(brush1); 

	HBRUSH brush2 = CreateSolidBrush(RGB(26, 148, 49));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(backDC, brush2);

	for (int i = 0; i < 3; i++)
	{
		//Rectangle(backDC, _wall[i].top);
		_pipe_down->render(backDC, _wall[i].top.left, _wall[i].top.top);
		//Rectangle(backDC, _wall[i].score);
		//Rectangle(backDC, _wall[i].bottom);
		_pipe_up->render(backDC, _wall[i].bottom.left, _wall[i].bottom.top);
	}

	SelectObject(backDC, oldBrush2);
	DeleteObject(brush2); 
	
	//���� �ȳ� 
	//char str[100]; 
	//sprintf_s(str, "���� : %d", _score);
	//TextOut(backDC, 50, 100, str, strlen(str));

	//���� ���� �ȳ� 
	if (_gameOver)
	{
		_gameoverImage->render(backDC, WINSIZEX  / 2 - 96, WINSIZEY / 2 - 21);
		//SetTextColor(backDC, RGB(255, 100, 100));
		//TextOut(backDC, WINSIZEX*0.5f-10, WINSIZEY*0.5f, "[���ӿ���]", strlen("[���ӿ���]"));
	}

	//for (int i = 0; i < NUMBERMAX; i++)
	//{
	//	_number[i]->render(backDC, WINSIZEX / 2 - 200, WINSIZEY / 2-100);
	//}
	
	//�ڸ����� ������ ���ڸ��� 
	UINT num = _score; //0�� ������ �ȵǴϱ� UNIT(unsigned int)�� ����ؼ� ����� ������ �Ѵ�. 
	UINT temp[4]; //����� 4�� ������ֱ� 0,1,2,3 

	ZeroMemory(&temp, sizeof(UINT)); //������ ����ִ� �� �ʱ�ȭ
	//���ھ� �ڸ� ��Ƴ��� ����) 8586
	
	temp[0] = (UINT) num / 1000; //1000���� ���� ���� 0�� �ڸ��� �־�� = 8
	temp[1] = num % 1000;        //1000���� ���� �������� 1�� �ڸ��� ���� = 586

	temp[2] = temp[1] % 100;     //1�� �ڸ��� �ִ� 586�� 100���� ���� �������� 2�� �ڸ��� ���� = 86
	temp[1] = temp[1] / 100;     //1�� �ڸ��� 586�� 100���� ���� ���� ���� 
	//------------------
	temp[3] = temp[2] % 10;      //2�� �ڸ��� �ִ� 86�� 10���� ���� �������� 3�� �ڸ��� ���� = 6 
	temp[2] = temp[2] / 10;      //2�� �ڸ��� �ִ� 86�� 10���� ���� ���� 2�� �ڸ��� ���� = 8

						   //------------------
	vector<image*> board;
	//���ھ��� ��ȭ�� ���� _number[i]�� ��ȭ �����ؾ� ��		
	for (int i = 0; i < 4; i++)
	{
		board.push_back(_number[temp[i]]); //
	}

	for (size_t t = 0; t < board.size(); t++) // board.size() = _number[temp[i]], 
	{
	//������ ���̰� 50�̴ϱ� 50�� ����ֱ� ���� t*50 

		board[t]->render(backDC, WINSIZEX / 2 - 450 +t * 50, WINSIZEY / 2 - 350);
	}

	board.clear(); //�ҷ��� ���� ����


	//===================================================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::movingWall_collision() //�� �����̱� & �浹ó�� 
{
	if (!_gameOver)
	{
		for (int i = 0; i < 3; i++)
		{
			//�������� ���� 5�� ������ �����δ�
			_wall[i].x -= 7;

			//���� �������� �������� ���� ȭ�� ������ ������
			if (_wall[i].top.right < 0)
			{
				//��� ��Ʈ���� ���� x,y ���ַ� �׷����� + �����̰� ������
				//���� X,Y�� ���⼭ ���� ������ ��ȭ�ش�
				_wall[i].rnd = RND->getFromIntTo(-50, 100);
				_wall[i].x = WINSIZEX + 200; 
				_wall[i].y = 350 + _wall[i].rnd; //�ٽ� ���� �������� �޾��ش�
				_wall[i].isCheck = true;  //ó���� �ڽ� üũ�Ǵ� ���� üũ 
			}

			//�� �������� �Ź� ��������� ��. 
			_middleX = (_wall[i].score.right + _wall[i].score.left) / 2;
			_middleY = (_wall[i].score.top + _wall[i].score.bottom) / 2;


			//_wall[i].x �� ���� ��� ���ϰ� ������ ��Ʈ�� �׿� �ð� ��� �׷��ش�
			_wall[i].score = RectMakeCenter(_wall[i].x, _wall[i].y, 50, 100);
			_wall[i].top = RectMakeCenter(_middleX, _middleY - 300, PIPEWIDTH, PIPEHEIGHT);
			_wall[i].bottom = RectMakeCenter(_middleX, _middleY + 300, PIPEWIDTH, PIPEHEIGHT);
		}
	}
}

