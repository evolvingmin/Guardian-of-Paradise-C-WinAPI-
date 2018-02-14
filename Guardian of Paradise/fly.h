#pragma once
#include "enemy.h"
class fly :public enemy
{
private :

public:
	fly();
	~fly();
	HRESULT init(float x, float y);
	void update();

	void render(float x, float y);
	void onCollideEnter(gameObject* object);
	
	void setAttack();
	void attackUpdate();
	void setMove();
	void moveUpdate();
	void setIdle();
	void idleUpdate();


	virtual void manaCoinDrop();
};

