#include "stdafx.h"
#include "utils.h"



namespace SEVENTEEN_UTIL
{
	//거리(빗변) 알아오는 함수
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//두 점의 사이각을 알아오는 함수
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		//저는 아크코싸인을 원해요 하면 이 주석을 풀고 쓰세요
		/*
		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;

			if (angle >= PI2) angle -= PI2;
		}
		*/


		//아크탄젠트를 원하는 그대여 이걸 쓰세여
		float angle = -atan2f(y, x);


		return angle;

	}
}