#pragma once
#include "gameNode.h"
#include <vector>

#define PIPEWIDTH 100
#define PIPEHEIGHT 450
#define NUMBERMAX 10
struct tagWall
{
	RECT top;
	RECT score; 
	RECT bottom; 
	float speed; 
	int x, y;
	bool isScore; 
	bool isCheck; 
	int rnd; 
}; 

struct tagBird
{
	RECT rc; 
	float gravity; 
	float jumpPower;
	bool isJump;
	int x, y; 
};

class playGround : public gameNode
{
private:
	tagWall _wall[3];
	tagBird _bird; 

	image* _background; 
	image* _background_night; 
	image* _birdImage; 
	image* _gameoverImage;
	image* _pipe_down; 
	image* _pipe_up; 
	image* _number[NUMBERMAX];


	int _score; 
	int _rand; 
	bool _gameOver; 
	
	int _middleX;
	int _middleY;


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render(HDC hdc);	//�׸��� ���� �Լ�
	
	void movingWall_collision();
};

