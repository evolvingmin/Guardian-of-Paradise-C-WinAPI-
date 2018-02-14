#pragma once
#include "enemy.h"
class flower :public enemy
{
private:

public:
	flower();
	~flower();
	HRESULT init(float x, float y);
	void update();

	void render(float x, float y);
	void onCollideEnter(gameObject* object);
	 void setHit(gameObject* gObject, bool isInvinsible = false);
	 void hitUpdate();
	 void setDie(gameObject* gObject, bool useReaction = true);
	 void dieUpdate();
	 void idleUpdate();
	 void setAttack();
	 void attackUpdate();

	 


};

