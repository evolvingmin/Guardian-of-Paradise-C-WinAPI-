#pragma once
#include "gameNode.h"
#define BASIC_UI_INTERVAL 25
class Player;
class gameUI :public gameNode
{
private:



	image* _elementSelect;
	image* _elementalSkill;
	image* _elementBackGround;
	image* _label_Player;
	image* _label_enemy;

	image* _statueBar;
	image* _questItems;

	
	Player* _player;
public:
	gameUI();
	~gameUI();
	HRESULT init(Player* player);
	void release(void);
	void update(void);
	void render(void);
};

