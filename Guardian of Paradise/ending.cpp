#include "stdafx.h"
#include "ending.h"


ending::ending()
{
}


ending::~ending()
{
}

HRESULT ending::init()
{
	scene::init();

	IMAGEMANAGER->addImage("bg", "image/blackBg.bmp", WINSIZEX, WINSIZEY, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("credit", "image/ending.bmp", 1024, 1500, true, RGB(255, 0, 255));

	_bg = IMAGEMANAGER->findImage("bg");
	_credit = IMAGEMANAGER->findImage("credit");

	_x = 0;
	_y = WINSIZEY;
	_rc = RectMakeCenter(_x, _y, _credit->getWidth(), _credit->getHeight());


	return S_OK;
}

void ending::release(void)
{
	scene::release();
}

void ending::update(void)
{
	scene::update();

	_y -= 5;

	if (_y + _credit->getHeight() < 0)
	{
		PostQuitMessage(0);
	}

	_rc = RectMakeCenter(_x, _y, _credit->getWidth(), _credit->getHeight());
}

void ending::render(void)
{
	scene::render();

	_bg->render(getMemDC());
	_credit->render(getMemDC(), _x, _y);
}