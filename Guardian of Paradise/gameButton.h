#pragma once
#include "gameFont.h"
//�޼ҵ� �ݺ� ���� ����ϱ� ���ؼ�
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
	//�⺻ ��ư �̴�
	HRESULT init(char* text, float x, float y, float fontSize, BUTTON_CALLBACK* buttonCallBack =nullptr, FONTCOLOR fontColor = WHITE , ALIGNMENT alignment =ALIGNMENT_LEFT);
	//�⺻ ��ƶ �̴�2, ��Ʈ ����� ���缭 ��Ʈ�� �����Ǵ°� �ƴ�, ��Ʈ ���� ��Ʈ ���� �������ش�.
	HRESULT init(char* text, float x, float y, float fontSize, float width, float height, BUTTON_CALLBACK* buttonCallBack = nullptr, FONTCOLOR fontColor = WHITE, ALIGNMENT alignment = ALIGNMENT_LEFT);
	//������Ʈ
	void release(void);
	void update(void);
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
};

