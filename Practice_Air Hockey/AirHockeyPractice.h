#pragma once
#include "gameNode.h"
#include <vector>
#define SLOW 0.09
#define PI 3.141592654f 
#define NUMBERMAX 9
struct tagBall
{
	float x, y;		//총알의 중점
	int speed;	//총알의 스피드
	float angle;	//총알의 각도
	float radius;	//총알의 얼~
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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render(HDC hdc);	//그리기 전용 함수

	void keyControl();
	void playBallMove();
	void playBallCollision();
	void goalIn();

};

