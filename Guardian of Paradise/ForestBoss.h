#pragma once
#include "enemy.h"

class ForestBoss :public enemy
{
	vector<enemy*> _tantacles;
	float _bombDelayTime;
public:
	ForestBoss();
	~ForestBoss();

	HRESULT init(float x, float y);
	void update();

	void render(float x, float y);

	void onCollideEnter(gameObject* object);
	void idleUpdate();
	void setHit();
	void hitUpdate();
	void setDie();
	void dieUpdate();
};

