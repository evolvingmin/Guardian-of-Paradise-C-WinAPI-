#pragma once
#include "gameNode.h"
#include "gameButton.h"
class MainMenu :public gameNode
{
private:
	image* _mainImage;
	image* _background;
	float _roopSpeed;


	BUTTON_CALLBACK _newGameCallback;
	gameButton* _newGame;
	BUTTON_CALLBACK _continueCallback;
	gameButton* _continue;


	BUTTON_CALLBACK _mapEditerCallback;
	gameButton* _mapEditer;
	BUTTON_CALLBACK _exitCallback;
	gameButton* _exit;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void newGame();
	void continueGame();
	void loadMapEditer();
	void exitGame();
	
	MainMenu();
	~MainMenu();
};

