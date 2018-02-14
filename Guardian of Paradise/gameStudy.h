#pragma once
#include "gameNode.h"
#include "MapEditer.h"
#include "MainGame.h"
#include "MainMenu.h"

class gameStudy : public gameNode
{
private:
	
	gameNode* _menuScene;
	gameNode* _mainGameScene;
	gameNode* _mapEditerScene;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	gameStudy();
	~gameStudy();
};
