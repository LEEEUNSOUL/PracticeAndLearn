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


	//플레이어 렉트 설정
	_bird.x = WINSIZEX / 2 -200;
	_bird.y = WINSIZEY / 2;
	_bird.rc = RectMakeCenter(_bird.x, _bird.y, 30, 30);
	_bird.gravity = 0; 
	_bird.jumpPower = 0; 

	
	//그림 소환 
	_background = new image; 
	_background->init("_background.bmp", 1024, 768, false, RGB(0, 0, 0));

	_birdImage = new image;
	_birdImage->init("_birdImage.bmp", 60, 42, true, RGB(255, 0, 255)); // true는 특정 픽셀값 뺀다는 의미
	
	_pipe_down = new image; 
	_pipe_down->init("_pipe_down.bmp", 100, 450, true, RGB(255, 0, 255)); 

	_pipe_up= new image;
	_pipe_up->init("_pipe_up.bmp", 100, 450, true, RGB(255, 0, 255));

	_gameoverImage = new image; 
	_gameoverImage->init("_gameoverImage.bmp", 193, 42, true, RGB(255, 0, 255)); 
	

	//글자 이미지 가져오기 / 초기화 
	char str[256];
	for (int i = 0; i < NUMBERMAX; i++)
	{
		_number[i] = new image;
		sprintf_s(str, "number_%d.bmp", i); //파일 이름 넣기 
		_number[i]->init(str, 50, 75, true, RGB(255, 0, 255));
	}


	//movingWall 생성 
	for (int i = 0; i < 3; i++)
	{

		//높이 값에 랜덤을 줄 변수 선언 및 난수를 받아온다
		_wall[i].rnd = RND->getFromIntTo(-50, 150);


		//각 파이프들은 스코어박스를 기준으로 나오게 되는데 높이값은 350이 Default고 랜덤값으로 높이를 줌
		_wall[i].x = WINSIZEX / 2 + 500 * i+800; 
		_wall[i].y = 350 + _wall[i].rnd;
		

		//기준이 되는 스코어 박스를 먼저 그려주고
		_wall[i].score = RectMakeCenter(_wall[i].x, _wall[i].y, 50, 100);


		// 각 파이프들의 중점값 나열한다
		_middleX = (_wall[i].score.right + _wall[i].score.left) / 2;
		_middleY = (_wall[i].score.top + _wall[i].score.bottom) / 2;


		//위 아래 파이프는 스코어 박스의 중심값 기준으로 위치를 셋팅해준다
		_wall[i].top = RectMakeCenter(_middleX, _middleY - 300 , PIPEWIDTH, PIPEHEIGHT);
		_wall[i].bottom = RectMakeCenter(_middleX, _middleY + 300, PIPEWIDTH, PIPEHEIGHT + _wall[i].rnd);
		

		//처음에 박스 체크되는 상태 체크 
		_wall[i].isCheck = true;
	}


	//bool값 초기 설정 
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
		//키 누르면 점프하기 + 중력 적용 
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

		//점프한 위치에 플레이어 렉트 또 다시 생성
		_bird.rc = RectMakeCenter(_bird.x, _bird.y, 50, 50); 
	
		movingWall_collision(); //벽 움직이기 

		//충돌처리 
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
	//배경 그리기 
	_background->render(backDC, 0, 0);

	//플레이어 렉트 그리기 
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
	
	//점수 안내 
	//char str[100]; 
	//sprintf_s(str, "점수 : %d", _score);
	//TextOut(backDC, 50, 100, str, strlen(str));

	//게임 오버 안내 
	if (_gameOver)
	{
		_gameoverImage->render(backDC, WINSIZEX  / 2 - 96, WINSIZEY / 2 - 21);
		//SetTextColor(backDC, RGB(255, 100, 100));
		//TextOut(backDC, WINSIZEX*0.5f-10, WINSIZEY*0.5f, "[게임오버]", strlen("[게임오버]"));
	}

	//for (int i = 0; i < NUMBERMAX; i++)
	//{
	//	_number[i]->render(backDC, WINSIZEX / 2 - 200, WINSIZEY / 2-100);
	//}
	
	//자릿수를 나눠서 한자리씩 
	UINT num = _score; //0이 나오면 안되니까 UNIT(unsigned int)를 사용해서 양수만 나오게 한다. 
	UINT temp[4]; //빈공간 4개 만들어주기 0,1,2,3 

	ZeroMemory(&temp, sizeof(UINT)); //공간에 들어있는 값 초기화
	//스코어 자리 잡아놓기 예시) 8586
	
	temp[0] = (UINT) num / 1000; //1000으로 나눈 몫을 0번 자리에 넣어라 = 8
	temp[1] = num % 1000;        //1000으로 나눈 나머지를 1번 자리에 저장 = 586

	temp[2] = temp[1] % 100;     //1번 자리에 있는 586을 100으로 나눈 나머지를 2번 자리에 저장 = 86
	temp[1] = temp[1] / 100;     //1번 자리에 586을 100으로 나눠 몫을 저장 
	//------------------
	temp[3] = temp[2] % 10;      //2번 자리에 있는 86을 10으로 나눈 나머지를 3번 자리에 저장 = 6 
	temp[2] = temp[2] / 10;      //2번 자리에 있는 86을 10으로 나눈 몫을 2번 자리에 저장 = 8

						   //------------------
	vector<image*> board;
	//스코어의 변화에 따라 _number[i]값 변화 적용해야 함		
	for (int i = 0; i < 4; i++)
	{
		board.push_back(_number[temp[i]]); //
	}

	for (size_t t = 0; t < board.size(); t++) // board.size() = _number[temp[i]], 
	{
	//글자의 넓이가 50이니까 50씩 띄워주기 위해 t*50 

		board[t]->render(backDC, WINSIZEX / 2 - 450 +t * 50, WINSIZEY / 2 - 350);
	}

	board.clear(); //불러온 벡터 삭제


	//===================================================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::movingWall_collision() //벽 움직이기 & 충돌처리 
{
	if (!_gameOver)
	{
		for (int i = 0; i < 3; i++)
		{
			//파이프는 전부 5씩 앞으로 움직인다
			_wall[i].x -= 7;

			//만약 파이프의 오른쪽이 왼쪽 화면 밖으로 나가면
			if (_wall[i].top.right < 0)
			{
				//모든 렉트들은 중점 x,y 위주로 그려지고 + 움직이고 있으니
				//중점 X,Y만 여기서 값을 새로이 변화준다
				_wall[i].rnd = RND->getFromIntTo(-50, 100);
				_wall[i].x = WINSIZEX + 200; 
				_wall[i].y = 350 + _wall[i].rnd; //다시 높이 랜덤값을 받아준다
				_wall[i].isCheck = true;  //처음에 박스 체크되는 상태 체크 
			}

			//이 변수들은 매번 선언해줘야 함. 
			_middleX = (_wall[i].score.right + _wall[i].score.left) / 2;
			_middleY = (_wall[i].score.top + _wall[i].score.bottom) / 2;


			//_wall[i].x 의 값이 계속 변하고 있으니 렉트를 그에 맡게 계속 그려준다
			_wall[i].score = RectMakeCenter(_wall[i].x, _wall[i].y, 50, 100);
			_wall[i].top = RectMakeCenter(_middleX, _middleY - 300, PIPEWIDTH, PIPEHEIGHT);
			_wall[i].bottom = RectMakeCenter(_middleX, _middleY + 300, PIPEWIDTH, PIPEHEIGHT);
		}
	}
}

