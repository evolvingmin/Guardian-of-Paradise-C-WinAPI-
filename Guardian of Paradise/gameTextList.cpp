#include "stdafx.h"
#include "gameTextList.h"


gameTextList::gameTextList()
{
}


gameTextList::~gameTextList()
{
}

HRESULT gameTextList::init(float x, float y, float width, float fontSize, ALIGNMENT alignment, int maxLength)
{
	_text = new gameFont;
	_text->init("", ORANGE, x, y, fontSize, alignment);
	_x = x;
	_y = y;
	_width = width;
	_height = fontSize;

	_isNumber = true;
	_isClicked = false;

	_selectionButton = new gameButton;
	_selectionCallBack = bind(&gameTextList::showSelectionList, this);
	_selectionButton->init("v", _x + _width, _y, fontSize, &_selectionCallBack, RED, ALIGNMENT_LEFT);


	_maxLength = maxLength;

	//gameTextList
	_isShowList = false;
	return S_OK;
}

void gameTextList::release(void)
{
	SAFE_RELEASE(_text);
	SAFE_RELEASE(_selectionButton);
}

void gameTextList::update(void)
{
	//if (_isShowList)
	//	_text->setText(_selectionMap[*_returnNumber]->returnFullText());
	_selectionButton->update();
}

//렌더
void gameTextList::render(void)
{
	Rectangle(getMemDC(), boundingBox().left, boundingBox().top, boundingBox().right, boundingBox().bottom);
	_text->render();
	_selectionButton->render();

	char result[120];
	
	if (_isShowList)
	{
		int i =1;
		for (map<int, gameFont*>::iterator iter = _selectionMap.begin(); iter != _selectionMap.end(); iter++)
		{
			Rectangle(getMemDC(), _x, _y + i*_height, _x + _width, _y + i*_height + _height);
			iter->second->render(_x, _y + i*_height);
			i++;
		}
	}

}
void gameTextList::render(float x, float y)
{
	
	
	_text->render(x, y);
	_selectionButton->render(x, y);
}
void gameTextList::onClickUp(int key)
{
	switch (key)
	{
	case MK_LBUTTON:
		if (_isShowList)
		{
			int i = 1;
			for (map<int, gameFont*>::iterator iter = _selectionMap.begin(); iter != _selectionMap.end(); iter++)
			{
				if (PtInRect(&RectMake(_x, _y + i*_height, _width, _height), _ptMouse))
				{
					//거기에 있는 값 넘겨주는거.
					int temp  = iter->first;
					*_returnNumber = temp;
					_text->setText(iter->second->returnFullText());
					_isShowList = false;
					break;
				}
				i++;
			}
			_isShowList = false;
		}

		break;
	}

	_selectionButton->onClickUp(key);

}
void gameTextList::onClickStay(int key)
{
	switch (key)
	{
	case MK_LBUTTON:

		break;
	}
	_selectionButton->onClickStay(key);
}
void gameTextList::onClickDown(int key)
{
	switch (key)
	{
	case MK_LBUTTON:

		break;
	}
	_selectionButton->onClickDown(key);
}
void gameTextList::setAffectedValue(int* affectedValue)
{

	char temp[120];
	_returnNumber = affectedValue;
	_text->setText(_selectionMap[*_returnNumber]->returnFullText());
}
void gameTextList::clearItems()
{

	for (map<int, gameFont*>::iterator iter = _selectionMap.begin(); iter != _selectionMap.end(); iter++)
		iter->second->release();

	_selectionMap.clear();
}
void gameTextList::addItem(int key, char* item)
{
	//map<int, gameFont*>::iterator _key = _selectionMap.find(key);

	////키를 찾으면
	//if (_key != _selectionMap.end())
	//	return;

	gameFont* tempFont = new gameFont();
	tempFont->init(item, ORANGE, _x, _y, _text->getFontSize(), ALIGNMENT_LEFT);
	_selectionMap.insert(make_pair(key, tempFont));
}
void gameTextList::showSelectionList(void)
{
	_isShowList = true;
}