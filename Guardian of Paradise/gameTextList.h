#pragma once
#include "gameFont.h"
#include "gameButton.h"
#include <map>

class gameTextList : public gameNode
{
private:

	map<int, gameFont*> _selectionMap;
	bool _isNumber;
	gameFont* _text;
	bool _isClicked;
	float _x;
	float _y;
	float _width;
	float _height;

	char  _bindedMember[120];
	int _maxLength;


	bool _isShowList;
	BUTTON_CALLBACK _selectionCallBack;
	gameButton* _selectionButton;
	/////////////////////////////////리턴 타입 저장할 주소///////////////////////////////
	int* _returnNumber;
	char** _returnString;
public:

	HRESULT init(float x, float y, float width, float fontSize,  ALIGNMENT alignment = ALIGNMENT_LEFT, int maxLength = 2);
	
	gameTextList();
	~gameTextList();
	//업데이트
	void release(void);
	void update(void);


	void onClickUp(int key);
	void onClickStay(int key);
	void onClickDown(int key);
	//렌더
	void render(void);
	void render(float x, float y);


	/////////////////////Set a list Items/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	void clearItems();
	void addItem(int key, char* item);
	void setAffectedValue(int* affectedValue);
	//////////////////////////////////////////////////////////////////////////////////
	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_x),
			int(_y),
			int(_x + _width),
			int(_y + _height) };
		return rc;
	}
	//gettter
	gameFont* returnText(void){ return _text; }

	//callback
	void showSelectionList(void);
};

