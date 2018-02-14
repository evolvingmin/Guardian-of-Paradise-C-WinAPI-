#pragma once
#include "gameFont.h"

class gameTextBox : public gameNode
{
private:
	bool _isNumber;
	gameFont* _text;
	bool _isClicked;
	float _x;
	float _y;
	float _width;
	float _height;

	char  _bindedMember[120];
	int _maxLength;

/////////////////////////////////���� Ÿ�� ������ �ּ�///////////////////////////////
	int* _returnNumber;
	char** _returnString;
public:

	HRESULT init(float x, float y, float width, float fontSize,FONTCOLOR fontColor = WHITE, ALIGNMENT alignment = ALIGNMENT_LEFT, int maxLength = 2);
	HRESULT init(int* value, float x, float y, float width, float fontSize, FONTCOLOR fontColor = WHITE, ALIGNMENT alignment = ALIGNMENT_LEFT, int maxLength = 2);
	HRESULT init(char** value, float x, float y, float width, float fontSize, FONTCOLOR fontColor = WHITE, ALIGNMENT alignment = ALIGNMENT_LEFT, int maxLength = 2);


	gameTextBox();
	~gameTextBox();
	//������Ʈ
	void release(void);
	void update(void);

	void onClickUp(int key, float x, float y);
	void onClickUp(int key);
	void onClickStay(int key);
	void onClickDown(int key);
	//����
	void render(void);
	void render(float x, float y);



	//�ٿ�� �ڽ�
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
	//setter
	void setLinkNumber(int* value){ 
		char temp[10];
		_returnNumber = value; 
		_text->setText(_itoa(*value, temp, 10));
	}
};

