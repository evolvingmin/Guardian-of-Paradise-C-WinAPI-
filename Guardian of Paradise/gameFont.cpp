#include "stdafx.h"
#include "gameFont.h"


gameFont::gameFont()
{
}


gameFont::~gameFont()
{
}

HRESULT gameFont::init(char* text, FONTCOLOR fontColor, float x, float y, int fontSize, ALIGNMENT alignment)
{
	imageIndexY = fontColor * 2;
	this->x = x;
	this->y = y;
	fontImage = new image;
	fontImage->init("Image/etc/font.bmp", (288 / 9)*fontSize, (54 / 9)*fontSize, 32, 6, true, RGB(255, 0, 255));
	this->fontSize = fontSize;
	_width = 0;
	_height = 0;
	_currentPage = 0;
	_isEnableNext = false;
	setText(text);

	this->alignment = alignment;
	return S_OK;
}
HRESULT gameFont::init( FONTCOLOR fontColor, float x, float y,float width, float height,  int fontSize, ALIGNMENT alignment)
{
	imageIndexY = fontColor * 2;
	this->x = x;
	this->y = y;
	fontImage = new image;
	fontImage->init("Image/etc/font.bmp", (288 / 9)*fontSize, (54 / 9)*fontSize, 32, 6, true, RGB(255, 0, 255));
	this->fontSize = fontSize;
	_width = width;
	_height = height;
	_isEnableNext = true;
	_currentPage = 0;
	currentPosition.x = 0;
	currentPosition.y = 0;

	this->alignment = alignment;
	return S_OK;
}
void gameFont::release(void)
{
	SAFE_RELEASE(fontImage);
}
void gameFont::update(void)
{

}
void gameFont::render(void)
{
	
	int j = 0;
	int k = 0;
	switch (alignment)
	{

	case ALIGNMENT_LEFT:

		for (int i = 0; i < _fontImageIndex.size(); i++)
		{
			if (_fontImageIndex[i]._pageNum == _currentPage)
			{
				if (_fontImageIndex[i]._isNext)
				{
					j = -1;
					k++;
				}
				else
					fontImage->frameRender(getMemDC(), x + fontSize*j, y + fontSize*k, _fontImageIndex[i].imageIndex.x, _fontImageIndex[i].imageIndex.y);
				j++;
			}
		}
		
		break;
	case ALIGNMENT_MIDDLE:
		for (int i = 0; i < _fontImageIndex.size(); i++)
			fontImage->frameRender(getMemDC(), x + fontSize*i - (_fontImageIndex.size() * fontSize) / 2, y, _fontImageIndex[i].imageIndex.x, _fontImageIndex[i].imageIndex.y);
		break;

	}

}

void gameFont::render(float x, float y)
{
	switch (alignment)
	{
	case ALIGNMENT_LEFT:
		for (int i = 0; i < _fontImageIndex.size(); i++)
			fontImage->frameRender(getMemDC(), x + fontSize*i, y, _fontImageIndex[i].imageIndex.x, _fontImageIndex[i].imageIndex.y);
		break;
	case ALIGNMENT_MIDDLE:
		for (int i = 0; i < _fontImageIndex.size(); i++)
			fontImage->frameRender(getMemDC(), x + fontSize*i - (_fontImageIndex.size() * fontSize) / 2, y, _fontImageIndex[i].imageIndex.x, _fontImageIndex[i].imageIndex.y);
		break;

	}
}
void gameFont::addText(char* text)
{
	int currentPage = 0;
	int index = 0;
	currentPosition.x = 0;
	currentPosition.y = 0;
	while (text[index] != NULL)
	{
		char check = text[index];
		addText(text[index], currentPage);
		if (_isEnableNext)
		{
			if (text[index] == '\n' )
			{
				_fontImageIndex.push_back(tagFontInfo(true, currentPage));
				currentPosition.x = 0;
				currentPosition.y += fontSize;
			}
			
			if (currentPosition.x + fontSize >= _width )
			{
				currentPosition.x = 0;
				currentPosition.y += fontSize;
				_fontImageIndex.push_back(tagFontInfo(true, currentPage));
			}
			if (currentPosition.y + fontSize >= _height)
			{
				currentPage++;
				currentPosition.x = 0;
				currentPosition.y = 0;
			}
			currentPosition.x += fontSize;
		}


	
		index++;
	}

	_maxPage = currentPage;
	//현재 키 바인딩에 따른 대화 시스템을 위한 예외적 구문처리
	if (_maxPage > 0)
		_currentPage = -1;

}
void gameFont::addText(char text, int currentPage)
{
	if (text!= NULL)
	{
		//알파벳
		if (text == 'A' || text == 'a')
			_fontImageIndex.push_back(tagFontInfo(PointMake(1, 1 + imageIndexY), text,currentPage));
		if (text == 'B' || text == 'b')
			_fontImageIndex.push_back(tagFontInfo(PointMake(2, 1 + imageIndexY), text,currentPage));
		if (text == 'C' || text == 'c')
			_fontImageIndex.push_back(tagFontInfo(PointMake(3, 1 + imageIndexY), text,currentPage));
		if (text == 'D' || text == 'd')
			_fontImageIndex.push_back(tagFontInfo(PointMake(4, 1 + imageIndexY), text,currentPage));
		if (text == 'E' || text == 'e')
			_fontImageIndex.push_back(tagFontInfo(PointMake(5, 1 + imageIndexY), text,currentPage));
		if (text == 'F' || text == 'f')
			_fontImageIndex.push_back(tagFontInfo(PointMake(6, 1 + imageIndexY), text,currentPage));
		if (text == 'G' || text == 'g')
			_fontImageIndex.push_back(tagFontInfo(PointMake(7, 1 + imageIndexY), text,currentPage));
		if (text == 'H' || text == 'h')
			_fontImageIndex.push_back(tagFontInfo(PointMake(8, 1 + imageIndexY),text,currentPage));
		if (text == 'I' || text == 'i')
			_fontImageIndex.push_back(tagFontInfo(PointMake(9, 1 + imageIndexY), text,currentPage));
		if (text == 'J' || text == 'j')
			_fontImageIndex.push_back(tagFontInfo(PointMake(10, 1 + imageIndexY), text,currentPage));
		if (text == 'K' || text == 'k')
			_fontImageIndex.push_back(tagFontInfo(PointMake(11, 1 + imageIndexY), text,currentPage));
		if (text == 'L' || text == 'l')
			_fontImageIndex.push_back(tagFontInfo(PointMake(12, 1 + imageIndexY), text,currentPage));
		if (text == 'M' || text == 'm')
			_fontImageIndex.push_back(tagFontInfo(PointMake(13, 1 + imageIndexY), text,currentPage));
		if (text == 'N' || text == 'n')
			_fontImageIndex.push_back(tagFontInfo(PointMake(14, 1 + imageIndexY), text,currentPage));
		if (text == 'O' || text == 'o')
			_fontImageIndex.push_back(tagFontInfo(PointMake(15, 1 + imageIndexY), text,currentPage));
		if (text == 'P' || text == 'p')
			_fontImageIndex.push_back(tagFontInfo(PointMake(16, 1 + imageIndexY), text,currentPage));
		if (text == 'Q' || text == 'q')
			_fontImageIndex.push_back(tagFontInfo(PointMake(17, 1 + imageIndexY), text,currentPage));
		if (text == 'R' || text == 'r')
			_fontImageIndex.push_back(tagFontInfo(PointMake(18, 1 + imageIndexY), text,currentPage));
		if (text == 'S' || text == 's')
			_fontImageIndex.push_back(tagFontInfo(PointMake(19, 1 + imageIndexY), text,currentPage));
		if (text == 'T' || text == 't')
			_fontImageIndex.push_back(tagFontInfo(PointMake(20, 1 + imageIndexY), text,currentPage));
		if (text == 'U' || text == 'u')
			_fontImageIndex.push_back(tagFontInfo(PointMake(21, 1 + imageIndexY), text,currentPage));
		if (text == 'V' || text == 'v')
			_fontImageIndex.push_back(tagFontInfo(PointMake(22, 1 + imageIndexY), text,currentPage));
		if (text == 'W' || text == 'w')
			_fontImageIndex.push_back(tagFontInfo(PointMake(23, 1 + imageIndexY), text,currentPage));
		if (text == 'X' || text == 'x')
			_fontImageIndex.push_back(tagFontInfo(PointMake(24, 1 + imageIndexY), text,currentPage));
		if (text == 'Y' || text == 'y')
			_fontImageIndex.push_back(tagFontInfo(PointMake(25, 1 + imageIndexY), text,currentPage));
		if (text == 'Z' || text == 'z')
			_fontImageIndex.push_back(tagFontInfo(PointMake(26, 1 + imageIndexY), text,currentPage));
		if (text == ' ')
			_fontImageIndex.push_back(tagFontInfo(PointMake(0, 0 + imageIndexY), text,currentPage));
		//숫자
		if (text == '0')
			_fontImageIndex.push_back(tagFontInfo(PointMake(16, 0 + imageIndexY), text,currentPage));
		if (text == '1')
			_fontImageIndex.push_back(tagFontInfo(PointMake(17, 0 + imageIndexY), text,currentPage));
		if (text == '2')
			_fontImageIndex.push_back(tagFontInfo(PointMake(18, 0 + imageIndexY), text,currentPage));
		if (text == '3')
			_fontImageIndex.push_back(tagFontInfo(PointMake(19, 0 + imageIndexY), text,currentPage));
		if (text == '4')
			_fontImageIndex.push_back(tagFontInfo(PointMake(20, 0 + imageIndexY), text,currentPage));
		if (text == '5')
			_fontImageIndex.push_back(tagFontInfo(PointMake(21, 0 + imageIndexY), text,currentPage));
		if (text == '6')
			_fontImageIndex.push_back(tagFontInfo(PointMake(22, 0 + imageIndexY), text,currentPage));
		if (text == '7')
			_fontImageIndex.push_back(tagFontInfo(PointMake(23, 0 + imageIndexY), text,currentPage));
		if (text == '8')
			_fontImageIndex.push_back(tagFontInfo(PointMake(24, 0 + imageIndexY), text,currentPage));
		if (text == '9')
			_fontImageIndex.push_back(tagFontInfo(PointMake(25, 0 + imageIndexY), text,currentPage));
		//그외
		if (text == '_')
			_fontImageIndex.push_back(tagFontInfo(PointMake(31, 1 + imageIndexY), text,currentPage));
		if (text == '-')
			_fontImageIndex.push_back(tagFontInfo(PointMake(13, 0 + imageIndexY), text,currentPage));
		if (text == '<')
			_fontImageIndex.push_back(tagFontInfo(PointMake(28, 0 + imageIndexY), text,currentPage));
		if (text == '>')
			_fontImageIndex.push_back(tagFontInfo(PointMake(30, 0 + imageIndexY), text,currentPage));
		if (text == ':')
			_fontImageIndex.push_back(tagFontInfo(PointMake(26, 0 + imageIndexY), text,currentPage));
		if (text == '.')
			_fontImageIndex.push_back(tagFontInfo(PointMake(14, 0 + imageIndexY), text,currentPage));
		if (text == '//')
			_fontImageIndex.push_back(tagFontInfo(PointMake(15, 0 + imageIndexY), text,currentPage));
		if (text == '!')
			_fontImageIndex.push_back(tagFontInfo(PointMake(1, 0 + imageIndexY), text,currentPage));
		if (text == '?')
			_fontImageIndex.push_back(tagFontInfo(PointMake(31, 0 + imageIndexY), text, currentPage));
		if (text == '\'')
			_fontImageIndex.push_back(tagFontInfo(PointMake(7, 0 + imageIndexY), text, currentPage));
		if (text == '[')
			_fontImageIndex.push_back(tagFontInfo(PointMake(27, 1 + imageIndexY), text, currentPage));
		if (text == ']')
			_fontImageIndex.push_back(tagFontInfo(PointMake(29, 1 + imageIndexY), text, currentPage));

	}
}
void gameFont::setText(char* text)
{
	_fontImageIndex.clear();
	addText(text);
}

void gameFont::removeLastElement()
{
	if (_fontImageIndex.size() >0 )
		_fontImageIndex.pop_back();
}
char* gameFont::returnFullText()
{
	
	int i;
	for ( i = 0; i < _fontImageIndex.size(); i++)
		returnChar[i] = _fontImageIndex[i].character;

	returnChar[i] = NULL;
	return returnChar;

}