#pragma once
#include "enemy.h"
class grasshopper : public enemy
{
private:
	
public:
	grasshopper();
	~grasshopper();
	HRESULT init(float x, float y);
	void update();

	void render(float x, float y);
	void onCollideEnter(gameObject* object);

	void idleUpdate();
	void setJump(gameObject* gObject);
	void setJump(DIRECTION direction);
	void JumpUpdate();
};

