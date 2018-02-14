#pragma once
#include "gameNode.h"
#include "gameScreenEffect.h"
enum cutSceneType
{
	GAMEOVER,
	MEET_FOREST_ELEMENTAL,
	LEVELUP_FOREST_ELEMENTAL,
	GET_FOREST_EMBLEM,
	GET_HEALTH_POTION,
	GET_SWORD,
	GET_KEY,
	INTRO_1,
	INTRO_2,
	INTRO_3,
};
class cutScene : public gameNode
{
	cutSceneType _type;
	float _cgDelay;
	bool _isCGActive;
	POINT _cgIndex;
	image* CG;
public:
	cutScene();
	~cutScene();
	HRESULT init();
	void showCutScene(cutSceneType type);
	void release();;
	void update();
	void render();
	bool getIsActive(void){ return _isCGActive; }
};

