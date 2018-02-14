#pragma once
#include "enemy.h"
class ForestMiniBoss :public enemy
{
private:
	bool _isOnceAttack;
	int _hitCount;
	float _bombDelayTime;
public:
	ForestMiniBoss();
	~ForestMiniBoss();

	HRESULT init(float x, float y);
	void update();

	void render(float x, float y);
	void onCollideEnter(gameObject* object);

	void moveUpdate();
	void hitUpdate();
	void setHit(gameObject* gObject, bool isInvinsible = false);
	void setAttack();
	void attackUpdate();
	void invincibleUpdate();
	void setDie();
	void dieUpdate();
};

