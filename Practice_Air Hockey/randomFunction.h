#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{

	}

	//          0 ~ 매개변수에 넣은 숫자 - 1 만큼 범위 랜덤
	inline int getInt(int num) { return rand() % num; }

	//        정수와 정수 사이 범위에서 랜덤한 수를 뽑는 함수
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}

};

