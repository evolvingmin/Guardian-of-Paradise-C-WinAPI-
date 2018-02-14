#pragma once
#include "gameObject.h"

//이펙트 아이템등 다양한 오브젝트들이 여기에 속한다.
//플레이어와 상호 작용이 없을수도 있다. (이펙트)

//이펙트와 아이템 두 부류로 클레스를 쪼개자.
enum INTERACTABLE_OBJECT_TYPE
{
	ITEM_NONE,
	ITEM_KEY,
	ITEM_BITTLE, 
	ITEM_SWORD,
	ITEM_HEALTH,
	ITEM_LUCA,
	ITEM_LUCA_UP,
	ITEM_FOREST_EMBLEM,
	///////////////////////////////////////////////////////
	/// 플레이어가 먹을 수 있는 아이템
	ITEM_HP_APPLE,
	ITEM_HP_CHEESE,
	ITEM_HP_CHICKEN,
	ITEM_MP_EARTH,
	ITEM_MP_WATER,
	ITEM_MP_WIND,
	ITEM_MP_DARKNESS,
	ITEM_MP_FIRE,
	////////////////////////////////////////////////////////////
	///그냥 이펙트
	EFFECT_LEAF_LEFT,
	EFFECT_LEAF_RIGHT,
	EFFECT_HPUP_10,
	EFFECT_HPUP_30,
	EFFECT_HPUP_50,
	EFFECT_MPUP,
	EFFECT_HIT,
	EFFECT_DIE,
	EFFECT_BLINCK,
	EFFECT_CRASH_LEFT,
	EFFECT_CRASH_RIGHT,
	EFFECT_CRASH_ROOT,
	EFFECT_CRASH_SHELL_BIG,
	EFFECT_CRASH_SHELL_SMALL,
	EFFECT_CRASH_ROCK,
	EFFECT_SHINE_GREEN,
	///////////////////////////////////////////////////////////////////

};
class EnviromentObject;
struct tagObjectInfo;
class EffectAndItemObject : public gameObject
{
private:
	INTERACTABLE_OBJECT_TYPE _objectType;
	animation* _animation;
	image* _image;
	bool _isAnimated;
	int _alphaValue;

	float _liveTime;
	float _JumpTime;
	float _startX;
	float _startY;
	//에니메이션이 아닐 경우, 프레임 렌더로 원하는걸 집어내야됨
	int _imageIndexX;
	int _imageIndexY;

	int _relatedQuestNum;
	EnviromentObject* _linkedObject;
public:
	HRESULT init(INTERACTABLE_OBJECT_TYPE objectType, float x, float y, float angle =PI);
	HRESULT init(tagObjectInfo objectType);
	HRESULT init(tagObjectInfo objectType, EnviromentObject* linkedObject);
	 void update();
	 void render();
	 void render(float x, float y);
	 void release();
	EffectAndItemObject();
	~EffectAndItemObject();
	void onCollideEnter(gameObject* gObject);


	inline int getQuestNum(){ return _relatedQuestNum; }
};

