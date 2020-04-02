#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//백버퍼가 존재하면 메모리 해제
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// 빈 DC영역 하나를 만든다
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//위에 셋팅이 실패해서 백버퍼가 생성되지 않았다면
	if (_imageInfo == NULL)
	{
		//메모리 해제
		release();

		//그리고 실패했단 메세지를 호출해라
		return E_FAIL;
	}


	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//찾고자하는 이미지 파일 이름이 없으면 실패를 출력해라
	if (fileName == NULL) return E_FAIL;

	//호옥시이 이미지 정보가 초기화 되어있지 않다면 해제를 시켜라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성한다
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름의 길이를 알아온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);


		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = NULL;
		_transColor = RGB(0, 0, 0);
	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	trans = trans;
	transColor = transColor;
}

void image::render(HDC hdc, int destX, int destY)
{
	//트랜스 컬러 처리를 해야하냐
	if (_trans)
	{
		//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC 
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기
			_imageInfo->height,		//복사될 크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사해올 좌표
			_imageInfo->width,		//복사해올 크기
			_imageInfo->height,
			_transColor);			//복사해올때 제외할 칼라

	}
	//아니냐
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}
