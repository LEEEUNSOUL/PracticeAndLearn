#pragma once
#define PI 3.141592654f
#define PI2 PI * 2

namespace SEVENTEEN_UTIL
{
	//거리(빗변) 알아오는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//두 점의 사이각을 알아오는 함수
	float getAngle(float x1, float y1, float x2, float y2);
}