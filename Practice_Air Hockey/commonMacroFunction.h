#pragma once

//==============================
// ## 19.10.30 ## 매크로 ##
//==============================

//          선긋기  뿌려줄DC, 시작좌표X, 시작좌표Y, 끝좌표X, 끝좌표Y
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//================= 렉트 관련 함쑤 ===================
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int centerX, int centerY, int width, int height)
{
	RECT rc = { centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2) };

	return rc;
}


//============== 사 각 형 =====================
//       Left, Top을 기준(그려줄DC, Left, Top, 가로크기, 세로크기)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
//          중점좌표 기준 (그려줄DC, 중점X, 중점Y, 가로크기, 세로크기)
inline void RectangleMakeCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//============== 원 ===================
//			Left, Top을 기준(그려줄DC, Left, Top, 가로크기, 세로크기)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//          중점좌표 기준 (그려줄DC, 중점X, 중점Y, 가로크기, 세로크기)
inline void EllipseMakeCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2), centerX + (width / 2), centerY + (height / 2));
}

inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
