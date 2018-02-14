#pragma once
#include "gameObject.h"

//����Ʈ �����۵� �پ��� ������Ʈ���� ���⿡ ���Ѵ�.
//�÷��̾�� ��ȣ �ۿ��� �������� �ִ�. (����Ʈ)

//����Ʈ�� ������ �� �η��� Ŭ������ �ɰ���.
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
	/// �÷��̾ ���� �� �ִ� ������
	ITEM_HP_APPLE,
	ITEM_HP_CHEESE,
	ITEM_HP_CHICKEN,
	ITEM_MP_EARTH,
	ITEM_MP_WATER,
	ITEM_MP_WIND,
	ITEM_MP_DARKNESS,
	ITEM_MP_FIRE,
	////////////////////////////////////////////////////////////
	///�׳� ����Ʈ
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
	//���ϸ��̼��� �ƴ� ���, ������ ������ ���ϴ°� ����ߵ�
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

