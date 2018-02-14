#pragma once
#include "addtionalMapInfo.h"
#include "gameObject.h"
class gameQuest;
//맵 에디터에서 까는, 아이템을 제외한 오브젝트들.
class EnviromentObject : public gameObject
{
private:


	tagObjectInfo _objectInfo;
	image* _mainImage;
	animation* _animation;
	bool _isAnimated;
	//button
	bool _buttonClicked;
	//robust
	bool _isHit;
	float _HitDelay;
	int _HitCount;
	//Destroy Delay Counter
	float _destoryDelay;
	bool _isDestroyDelay;
	//target location
	bool _isMove;
	float _destX, _destY;
	bool _oncePushed;
	//script about
	bool _isTrigger;
public:
	EnviromentObject();
	~EnviromentObject();
	HRESULT init(tagObjectInfo objectInfo);
	void update();
	void render();
	void render(float x, float y);
	void release();
	void onCollideEnter(gameObject* gObject);
	//getter ,setter
	tagObjectInfo getObjectInfo(void){ return _objectInfo; }
	bool getButtonClicked(void){ return _buttonClicked; }
	int getHitCount(void) { return _HitCount + 1; }
	void setMove(bool move);
	void setTrigger(bool trigger){ _isTrigger = trigger; }
	bool getTrigger(){ return _isTrigger; }

};

