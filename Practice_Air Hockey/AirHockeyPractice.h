#pragma once
#include "gameNode.h"
#include <vector>
#define SLOW 0.09
#define PI 3.141592654f 
#define NUMBERMAX 9
struct tagBall
{
	float x, y;		//�Ѿ��� ����
	int speed;	//�Ѿ��� ���ǵ�
	float angle;	//�Ѿ��� ����
	float radius;	//�Ѿ��� ��~
	bool isCollision;
	bool moving;
	bool goalIn;
	int point;
};


class AirHockeyPractice : public gameNode
{
private:
	tagBall _playBall;
	tagBall _1pBall;
	tagBall _2pBall;

	RECT _goal1, _goal2;
	int temp;
	int _count;

	image* _ball;
	image* _ground; 
	image* _player1; 
	image* _player2; 
	image* _number[NUMBERMAX]; 

public:
	AirHockeyPractice();
	~AirHockeyPractice();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render(HDC hdc);	//�׸��� ���� �Լ�

	void keyControl();
	void playBallMove();
	void playBallCollision();
	void goalIn();

};

