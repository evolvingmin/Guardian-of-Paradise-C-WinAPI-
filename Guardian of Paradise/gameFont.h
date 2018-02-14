#pragma once
#include "image.h"
#include "gameNode.h"
enum FONTCOLOR
{
	WHITE,
	RED,
	ORANGE
};
enum ALIGNMENT
{
	ALIGNMENT_LEFT,
	ALIGNMENT_RIGHT,
	ALIGNMENT_MIDDLE
};

struct tagFontInfo
{
	POINT imageIndex;
	char character;
	bool _isNext;
	int _pageNum;
	tagFontInfo(){}
	tagFontInfo(bool isNext, int pageNum)
	{
		_isNext = isNext;
		_pageNum = pageNum;
	}
	tagFontInfo(POINT imageIndex, char character, int pageNum)
	{
		this->imageIndex = imageIndex;
		this->character = character;
		_pageNum = pageNum;
		_isNext = false;
	}
	tagFontInfo(POINT imageIndex, char character, bool isNext, int pageNum)
	{
		this->imageIndex = imageIndex;
		this->character = character;
		_pageNum = pageNum;
		_isNext = isNext;
	}
	~tagFontInfo(){}
};



class gameFont : public gameNode
{
private:
	int x, y;
	image* fontImage;
	float fontSize;
	float _width;
	float _height;

	//줄넘김 guild
	bool _isEnableNext;
	int _currentPage;
	int _maxPage;
	POINT currentPosition;

	//폰트의 경우 인덱스별로 분류해야된다
	int imageIndexY;

	//정렬각, 일단 기본은 left
	ALIGNMENT alignment;

	vector<tagFontInfo> _fontImageIndex;
	char returnChar[120];
public:
	gameFont();
	~gameFont();
	HRESULT init(char* text, FONTCOLOR fontColor, float x, float y, int fontSize = 9, ALIGNMENT alignment = ALIGNMENT_LEFT);
	HRESULT init( FONTCOLOR fontColor, float x, float y, float width, float height, int fontSize = 9, ALIGNMENT alignment = ALIGNMENT_LEFT);
	void release(void);
	void update(void);
	void render(void);
	void render(bool isClicked);
	void render(float x , float y);
	void setText(char* text);
	void addText(char* text);
	void addText(const char text, int currentPage = 0);
	void removeLastElement();
	char* returnFullText();
	//getter, setter
	int getLength(){return _fontImageIndex.size();}
	ALIGNMENT getCurrentAlignment() {return alignment;}
	float getFontSize(){ return fontSize; }
	bool  isPageOver(void) 
	{
		if (_currentPage >= _maxPage)
		{
			_currentPage = 0;
			return true;
		}
		else
			return false;
	}
	void IncreaseCurrentPage(){ ++_currentPage; }
	void setCurrentPage(int pageNum){	_currentPage = pageNum;	}

};

