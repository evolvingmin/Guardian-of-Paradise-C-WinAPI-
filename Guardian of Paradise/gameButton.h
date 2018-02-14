#pragma once
#include "gameFont.h"
//메소드 콜벡 정의 사용하기 위해서
#include <functional>

typedef std::function<void(void)> BUTTON_CALLBACK;




class gameButton  : public gameNode
{

private : 
	BUTTON_CALLBACK* _buttonCallBack;
	RECT _Collide;
	gameFont* _text;
	float _x;
	float _y;
	float _width;
	float _height;

public:
	gameButton();
	~gameButton();
	//기본 버튼 이닛
	HRESULT init(char* text, float x, float y, float fontSize, BUTTON_CALLBACK* buttonCallBack =nullptr, FONTCOLOR fontColor = WHITE , ALIGNMENT alignment =ALIGNMENT_LEFT);
	//기본 버틋 이닛2, 폰트 사이즈에 맞춰서 랙트가 설정되는게 아닌, 폰트 따로 렉트 따로 설정해준다.
	HRESULT init(char* text, float x, float y, float fontSize, float width, float height, BUTTON_CALLBACK* buttonCallBack = nullptr, FONTCOLOR fontColor = WHITE, ALIGNMENT alignment = ALIGNMENT_LEFT);
	//업데이트
	void release(void);
	void update(void);
	void onClickUp(int key);
	void onClickStay(int key);
	void onClickDown(int key);
	//렌더
	void render(void);
	void render(float x, float y);
	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_x),
			int(_y),
			int(_x + _width),
			int(_y + _height) };
		return rc;
	}
};

