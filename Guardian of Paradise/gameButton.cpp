#include "stdafx.h"
#include "gameButton.h"


gameButton::gameButton()
{
}


gameButton::~gameButton()
{
}
HRESULT gameButton::init(char* text, float x, float y, float fontSize, BUTTON_CALLBACK* buttonCallBack, FONTCOLOR fontColor, ALIGNMENT alignment)
{
	_buttonCallBack = buttonCallBack;
	_text = new gameFont;
	_text->init(text, fontColor, x, y, fontSize, alignment);
	_x = x;
	_y = y;
	
	_height = fontSize;

	int index = 0;
	while (text[index] != NULL)
	{
		index++;
	}

	_width = index*fontSize;

	switch (alignment)
	{
	case ALIGNMENT_LEFT :
		_Collide = RectMake(_x, _y, _width, _height);
		break;
	case ALIGNMENT_MIDDLE :
		_Collide = RectMake(_x - _width/2, _y, _width, _height);
		break;
	}
	return S_OK;
}
HRESULT gameButton::init(char* text, float x, float y, float fontSize, float width, float height, BUTTON_CALLBACK* buttonCallBack, FONTCOLOR fontColor, ALIGNMENT alignment)
{
	_buttonCallBack = buttonCallBack;
	_text = new gameFont;
	_text->init(text, fontColor, x, y, fontSize, alignment);
	_x = x;
	_y = y;

	_width = width;
	_height = height;
	


	switch (alignment)
	{
	case ALIGNMENT_LEFT:
		_Collide = RectMake(_x, _y, _width, _height);
		break;
	case ALIGNMENT_MIDDLE:
		_Collide = RectMake(_x - _width / 2, _y, _width, _height);
		break;
	}

	return S_OK;
}
void gameButton::release(void)
{
	SAFE_RELEASE(_text);
//	SAFE_DELETE(_buttonCallBack);
}
//업데이트
void gameButton::update(void)
{
	_text->update();


	
}
//렌더
void gameButton::render(void)
{
	//Rectangle(getMemDC(), _Collide.left, _Collide.top, _Collide.right, _Collide.bottom);
	_text->render();
}
void gameButton::render(float x, float y)
{
	//Rectangle(getMemDC(), x, y, x+_width, y+_height);
	_text->render(x, y);
}
void gameButton::onClickUp(int key)
{
	switch (key)
	{
	case MK_LBUTTON:
		if (PtInRect(&_Collide, _ptMouse))
		{
			(*_buttonCallBack)();

		}
		break;
	}
}
void gameButton::onClickStay(int key)
{
	switch (key)
	{
	case MK_LBUTTON:

		break;
	}
}
void gameButton::onClickDown(int key)
{
	switch (key)
	{
	case MK_LBUTTON:

		break;
	}
}