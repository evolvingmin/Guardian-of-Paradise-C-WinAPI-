#pragma once
#include "Stage1of1.h"
#include "ending.h"
#include "timer.h"
#include "animation.h"


class menu : public scene
{
private:
	image* _menuBackground;
	image* _newGameButton;
	image* _loadGameButton;
	image* _exitButton;
	image* _opening1;
	image* _opening2;
	image* _opening3;
	image* _opening4;

	animation* _ani1;
	animation* _ani2;
	animation* _ani3;
	animation* _ani4;

	Stage1of1* _stage;
	ending* _end;

	timer* _playTimer;

	int _x, _y;

	int _menuNum;
	bool _isPlaying;
	bool _isAni1Played;
	bool _isAni2Played;
	bool _isAni3Played;
	bool _isAni4Played;

public:
	virtual HRESULT init();
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	void openingPlay();

	menu();
	~menu();
};

