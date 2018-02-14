#pragma once
#include "gameObject.h"
#include "gameAnimation.h"

//����, ����, �߻�ü

enum ABILITYTYPE
{
	///////////////////�÷��̾�///////////////////////
	//�⺻����
	SWORD,
	SWORD_EFFECT,
	//�������� �����Ƽ
	EARTH_STAMP,
	EARTH_GROW,
	EARTH_HEAVYSTAMP,
	INTERACT,
};
class Player;
class AbilityObject : public gameObject
{
private :
	DIRECTION _direction;
	ABILITYTYPE _abilityType;
	animation *_animation;
	image* _image;
	Player* _target;
	image* _shadowImage;

	float _jumpTime;
	float _jumpHeight;
	bool _onceShowed;



public:
	//�÷��̾�� init

	HRESULT init(DIRECTION direction, float startX, float startY, ABILITYTYPE abilityType);
	HRESULT init(Player* target, ABILITYTYPE abilityType);
	 void update();
	 void render();
	 void render(float x, float y);
	 void release();
	AbilityObject();
	~AbilityObject();
	 void onCollideEnter(gameObject* gObject);

	 DIRECTION getDirection(void){ return _direction; }
};

