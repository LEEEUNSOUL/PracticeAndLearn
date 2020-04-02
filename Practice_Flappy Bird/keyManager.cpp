#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
	}

	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{
	//어떠한 키를 눌렀을때
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//만약에 그 키가 눌려져있지 않다면
		if (!this->getKeyDown()[key])
		{
			//눌러졌다고 신호를 보내라
			this->setKeyDown(key, true);

			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);

			return true;
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
