#pragma once
#include "gameObject.h"
#include "gameAnimation.h"
#include "gameAttribute.h"
#include "Player.h"

#define HITDELAYTIME 2.0f
#define INITIALPUSHBACKTIME 0.5f;
#define HITPOWER 10.0f
#define RUNDISTANCE 400

enum ELEMENTAL_MONSTER
{
	ELEMENTAL_MONSTER_EARTH,
	ELEMENTAL_MONSTER_WATER,
	ELEMENTAL_MONSTER_WIND,
	ELEMENTAL_MONSTER_DARK,
	ELEMENTAL_MONSTER_FIRE
};



class enemy : public gameCharacter
{
protected:
	Player* _player;
	ELEMENTAL_MONSTER _element;
	//에너미와 적발견 기본 디스턴스
	float _enemyDetectDistance;




public:

public:
	enemy();
	~enemy();
	virtual HRESULT init(float x, float y) = 0;
	void setUp(float x, float y, float width, float height , string tag, string imageName, float speed, STATE state);
	virtual void update();
	virtual void render(float x, float y);

	void dieUpdate();

	virtual void manaCoinDrop(void);

	inline void getAddressLinkPlayer(){ _player = (Player*)GOBJECTMANAGER->findGameObject("player"); }
};

