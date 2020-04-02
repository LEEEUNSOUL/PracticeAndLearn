#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"

using namespace SEVENTEEN_UTIL;

//=========================================
// ## 19.10.30 ## - 디파인문 -
//=========================================

#define WINNAME (LPCTSTR)(TEXT("SevenTeen Class"))
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 1024
#define WINSIZEY 768
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()


#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}

//==========================================
// ## 19.10.31 ## Extern
//==========================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;