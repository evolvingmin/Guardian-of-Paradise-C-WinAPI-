#include "stdafx.h"
#include "gameTextBox.h"


gameTextBox::gameTextBox()
{
}


gameTextBox::~gameTextBox()
{
}

HRESULT gameTextBox::init(float x, float y, float width, float fontSize, FONTCOLOR fontColor, ALIGNMENT alignment, int maxLength)
{
	_text = new gameFont;
	_text->init("", fontColor, x, y, fontSize, alignment);
	_x = x;
	_y = y;
	_width = width;
	_height = fontSize;

	_isNumber = true;
	_isClicked = false;


	_maxLength = maxLength;
	return S_OK;
}
HRESULT gameTextBox::init(int* value, float x, float y, float width, float fontSize, FONTCOLOR fontColor, ALIGNMENT alignment, int maxLength)
{
	init(x, y, width, fontSize, fontColor, alignment, maxLength);
	_isNumber = true;
	char result[120];
	_text->setText(_itoa(*value, result, 10));
	_returnNumber = value;
	return S_OK;
}
HRESULT gameTextBox::init(char** value, float x, float y, float width, float fontSize, FONTCOLOR fontColor, ALIGNMENT alignment, int maxLength)
{
	init(x, y, width, fontSize, fontColor, alignment, maxLength);
	_isNumber = false;
	_text->setText(*value);
	_returnString = value;
	return S_OK;
}
void gameTextBox:: release(void)
{
	SAFE_RELEASE(_text);
}

void gameTextBox::update(void)
{

	if (_isClicked)
	{
		_text->update();

		for (int i = 0; i < 256; i++)
		{
			 if (KEYMANAGER->isOnceKeyDown(i))
			{
				if (i == 8)
				{
					_text->removeLastElement();
					break;
				}
				else if (i == VK_RETURN)
				{

					_isClicked = false;
					strcpy(_bindedMember, _text->returnFullText());
					if (_isNumber)
						*_returnNumber = atoi(_bindedMember);
					else
						*_returnString = _bindedMember;

					break;
				}
				else
				{
					if (_text->getLength() < _maxLength)
					{
						_text->addText(i);
						break;
					}
				}
				
			}
		}
	}



}

//·»´õ
void gameTextBox::render(void)
{
	Rectangle(getMemDC(), boundingBox().left, boundingBox().top, boundingBox().right, boundingBox().bottom);
	_text->render();




}
void gameTextBox::render(float x, float y)
{
	_text->render(x, y);
}
void gameTextBox::onClickUp(int key, float x, float y)
{
	switch (key)
	{
	case MK_LBUTTON:
		if (PtInRect(&boundingBox(), PointMake(_ptMouse.x + x, _ptMouse.y + y)))
		{
			_isClicked = true;
		}
		else
		{
			if (_isClicked)
			{

				strcpy(_bindedMember, _text->returnFullText());

				if (_isNumber)
					*_returnNumber = atoi(_bindedMember);
				else
					*_returnString = _bindedMember;
			}
			_isClicked = false;


		}

		break;
	}
}
void gameTextBox::onClickUp(int key)
{
	switch (key)
	{
	case MK_LBUTTON:
		if (PtInRect(&boundingBox(), _ptMouse))
		{
			_isClicked = true;
		}
		else
		{
			if (_isClicked)
			{

				strcpy(_bindedMember, _text->returnFullText());

				if (_isNumber)
					*_returnNumber = atoi(_bindedMember);
				else
					*_returnString = _bindedMember;
			}
			_isClicked = false;


		}

		break;
	}



}
void gameTextBox::onClickStay(int key)
{
	switch (key)
	{
	case MK_LBUTTON:

		break;
	}
}
void gameTextBox::onClickDown(int key)
{
	switch (key)
	{
	case MK_LBUTTON:

		break;
	}
}
