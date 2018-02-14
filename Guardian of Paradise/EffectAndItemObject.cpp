#include "stdafx.h"
#include "EffectAndItemObject.h"
#include "EnviromentObject.h"
#include "addtionalMapInfo.h"
#include "cutScene.h"
#include "Player.h"

EffectAndItemObject::EffectAndItemObject()
{
}


EffectAndItemObject::~EffectAndItemObject()
{
}
HRESULT EffectAndItemObject::init(tagObjectInfo objectinfo)
{
	string tag;

	switch (objectinfo.objectSelect)
	{
		case OBJECT_ITEM_SWORD : 
			_objectType = ITEM_SWORD;
			tag = "item_sword";
			break;
		case OBJECT_ITEM_KEY:
			_objectType = ITEM_KEY;
			tag = "item_key";
			break;
		case OBJECT_ITEM_HEALTH:
			_objectType = ITEM_HEALTH;
			tag = "item_health";
			break;
		case 	OBJECT_ITEM_LUCA:
			_objectType = ITEM_LUCA;
			tag = "item_Luca";
			break;
		case	OBJECT_ITEM_LUCA_UP:
			_objectType = ITEM_LUCA_UP;
			tag = "item_Luca_up";
			break;
		case OBJECT_ITEM_FOREST_EMBLEM:
			_objectType = ITEM_FOREST_EMBLEM;
			tag = "item_Forest_Emblem";
			break;
	}
	_isAnimated = false;
	_image = IMAGEMANAGER->findImage("multiply_" + objectinfo.objectImageFile);
	_imageIndexX = objectinfo.objectImageIndexX;
	_imageIndexY = objectinfo.objectImageIndexY;
	_relatedQuestNum = objectinfo.questIndex;

	gameObject::init(tag, objectinfo.x * MULTIPLY_X, 
		objectinfo.y * MULTIPLY_Y, 
		objectinfo.width  * MULTIPLY_X, 
		objectinfo.height * MULTIPLY_Y
		,0,0, true);
	setZ(2);
	_alphaValue = 255;
	GOBJECTMANAGER->addGameObject(this);
	return S_OK;

}
HRESULT EffectAndItemObject::init(tagObjectInfo objectType, EnviromentObject* linkedObject)
{
	init(objectType);
	_linkedObject = linkedObject;
	return S_OK;
}
HRESULT EffectAndItemObject::init(INTERACTABLE_OBJECT_TYPE objectType, float x, float y, float angle)
{
	

	_objectType = objectType;
	_alphaValue = 255;
	int arr[10];
	switch (_objectType)
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////EFFECT/////////////////////////////////////////////////////////////////////////////////////////////
	case EFFECT_CRASH_SHELL_BIG :
		_image = IMAGEMANAGER->findImage("shell_effect");
		arr[0] = 0;	arr[1] = 1;	arr[2] = 2;	arr[3] = 3;
		arr[4] = 4;	arr[5] = 5;	arr[6] = 6;	arr[7] = 7;
		_isAnimated = true;
		_animation = new animation;
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setPlayFrame(arr, 8, false);
		_animation->setFPS(5);
		_animation->start();
		gameObject::init("crashEffectSellBIg", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 3.0f, angle, false);
		setZ(11);
		break;
	case	EFFECT_CRASH_SHELL_SMALL :
		_image = IMAGEMANAGER->findImage("shell_effect");
		arr[0] = 8;	arr[1] = 9;	arr[2] = 10;	arr[3] = 11;
		arr[4] = 12;	arr[5] = 13;	arr[6] = 14;	arr[7] = 15;
		_isAnimated = true;
		_animation = new animation;
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setPlayFrame(arr, 8, false);
		_animation->setFPS(5);
		_animation->start();
		gameObject::init("crashEffectSellSmall", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 3.0f, angle ,false);
		setZ(11);
		break;
	case EFFECT_CRASH_LEFT:
		_image = IMAGEMANAGER->findImage("multiply_InteractableObject_2");
		arr[0] = 65;
		arr[1] = 66;
		arr[2] = 67;
		_isAnimated = true;
		_animation = new animation;
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setPlayFrame(arr, 3, false);
		_animation->setFPS(5);
		_animation->start();
		gameObject::init("crashEffectLeft", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 3.0f, 0.0f, false);
		setZ(11);
		break;
	case EFFECT_CRASH_RIGHT:
		_image = IMAGEMANAGER->findImage("multiply_InteractableObject_2");
		arr[0] = 62;
		arr[1] = 63;
		arr[2] = 64;
		_isAnimated = true;
		_animation = new animation;
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setPlayFrame(arr, 3, false);
		_animation->setFPS(5);
		_animation->start();
		gameObject::init("crashEffectLeft", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 3.0f, PI, false);
		setZ(11);
		break;
	case EFFECT_CRASH_ROOT:
		_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
		arr[0] = 84;	arr[1] = 85;	arr[2] = 86;	arr[3] = 87;
		arr[4] = 88;	arr[5] = 89;	arr[6] = 90;	arr[7] = 91;
		_isAnimated = true;
		_animation = new animation;
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setPlayFrame(arr, 8, false);
		_animation->setFPS(8);
		_animation->start();
		gameObject::init("crashEffectRoot", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 4.0f, angle, false);
		setZ(11);
		break;
	case EFFECT_CRASH_ROCK:
		_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
		arr[0] = 100;	arr[1] = 101;	arr[2] = 102;	arr[3] = 103;
		_isAnimated = true;
		_animation = new animation;
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setPlayFrame(arr, 4, false);
		_animation->setFPS(8);
		_animation->start();
		gameObject::init("crashEffectRoot", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 4.0f, angle, false);
		setZ(11);
		break;
		case 	EFFECT_LEAF_LEFT :
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			arr[0] = 13;
			arr[1] = 14;
			arr[2] = 15;
			arr[3] = 16;
			_isAnimated = true;
			_animation = new animation;
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setPlayFrame(arr, 4, false);
			_animation->setFPS(5);
			_animation->start();
			gameObject::init("leftEffectLeft", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 3.0f, (PI / 4) * 3, false);
			setZ(11);
			break;
		case EFFECT_LEAF_RIGHT:
			arr[0] = 17;
			arr[1] = 18;
			arr[2] = 19;
			arr[3] = 20;
			_isAnimated = true;
			_animation = new animation;
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setPlayFrame(arr, 4, false);
			_animation->setFPS(8);
			_animation->start();
			
			gameObject::init("leftEffectRight", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 3.0f, PI / 4 ,false);
			setZ(11);
			break;
		case 	EFFECT_HPUP_10:
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			_liveTime = 1.0f;
			_imageIndexX = 1;
			_imageIndexY = 4;
			_isAnimated = false;

			gameObject::init("hpUp10%", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 0, 0, false);
			setZ(11);
			break;
		case EFFECT_HPUP_30:
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			gameObject::init("hpUp30%", x, y, _image->getFrameWidth() , _image->getFrameHeight() , 0, 0, false);
			_liveTime = 1.0f;
			_imageIndexX = 2;
			_imageIndexY = 4;
			_isAnimated = false;
			setZ(11);
			break;
		case EFFECT_HPUP_50:
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			gameObject::init("hpUp50%", x, y, _image->getFrameWidth() , _image->getFrameHeight() , 0, 0, false);
			_liveTime = 1.0f;
			_imageIndexX = 3;
			_imageIndexY = 4;
			_isAnimated = false;
			setZ(11);
			break;
		case EFFECT_MPUP:
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			gameObject::init("mpUp", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 0, 0, false);
			_liveTime = 1.0f;
			_imageIndexX = 0;
			_imageIndexY = 4;
			_isAnimated = false;
			setZ(11);
			break;
		case	EFFECT_HIT:

			_image = IMAGEMANAGER->findImage("hit_Effect");
			_animation = new animation;
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setDefPlayFrame();
			_animation->setFPS(10);
			_animation->start();
			_isAnimated = true;
			gameObject::init("hitEffect", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 0, 0, false);
			setZ(11);
			break;
		case EFFECT_DIE:
			arr[0] = 3;	arr[1] = 4;	arr[2] = 5;	arr[3] = 6;			
			arr[4] = 7;	arr[5] = 8;	arr[6] = 9;	arr[7] = 10;
			_isAnimated = true;
			_animation = new animation;
			_image = IMAGEMANAGER->findImage("multiply_InteractableObject_3");
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setPlayFrame(arr, 8, false);
			_animation->setFPS(14);
			_animation->start();
			gameObject::init("deadEffect", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 0, 0, false);
			SOUNDMANAGER->play("bom01", 1.0f);
			setZ(11);
			break;
		case EFFECT_BLINCK:
			arr[0] = 21;	arr[1] = 22;	arr[2] = 23;	arr[3] = 24; arr[4] = 25;	
			_isAnimated = true;
			_animation = new animation;
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setPlayFrame(arr, 5, false);
			_animation->setFPS(10);
			_animation->start();
			gameObject::init("blinckEffect", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 0, 0, false);
			SOUNDMANAGER->play("hit05", 1.0f);
			setZ(11);
			break;
		case EFFECT_SHINE_GREEN:
			arr[0] = 26;	arr[1] = 27;	arr[2] = 28;	arr[3] = 29; arr[4] = 30;  arr[5] = 31; arr[6] = 32;  arr[7] = 33;
			_isAnimated = true;
			_animation = new animation;
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setPlayFrame(arr, 8, false);
			_animation->setFPS(10);
			_animation->start();
			gameObject::init("shinyGreen", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 0, 0, false);
			setZ(11);
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////ITEM////////////////////////////////////////////////////////////////////////////////////////////////////
		case ITEM_HP_APPLE:
			_image = IMAGEMANAGER->findImage("multiply_itemObject");
			_startX = x;
			_startY = y;
			_JumpTime = 0.25f;
			_imageIndexX = 2;
			_imageIndexY = 0;
			_liveTime = 7.0f;
			_isAnimated = false;
			gameObject::init("item_apple", x, y, _image->getFrameWidth() - 48, _image->getFrameHeight() - 24, 0, 0, true);
			setZ(9);
			break;
		case ITEM_HP_CHEESE:
			_image = IMAGEMANAGER->findImage("multiply_itemObject");
			_startX = x;
			_startY = y;
			_JumpTime = 0.25f;
			_imageIndexX = 4;
			_imageIndexY = 0;
			_liveTime = 7.0f;
			_isAnimated = false;
			gameObject::init("item_cheese", x, y, _image->getFrameWidth() - 48, _image->getFrameHeight() - 24, 0, 0, true);
			setZ(9);
			break;
		case ITEM_HP_CHICKEN:
			_image = IMAGEMANAGER->findImage("multiply_itemObject");
			_startX = x;
			_startY = y;
			_JumpTime = 0.25f;
			_imageIndexX = 6;
			_imageIndexY = 0;
			_liveTime = 7.0f;
			_isAnimated = false;
			gameObject::init("item_chicken", x, y, _image->getFrameWidth() - 48, _image->getFrameHeight() - 24, 0, 0, true);
			setZ(9);
			break;
		case ITEM_MP_EARTH:
			arr[0] = 50;	arr[1] = 51;	arr[2] =52;	arr[3] = 53; arr[4] = 54;  arr[5] = 55; 
			_isAnimated = true;
			_animation = new animation;
			_image = IMAGEMANAGER->findImage("multiply_smalleffectObject");
			_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
			_animation->setPlayFrame(arr, 6, true);
			_animation->setFPS(10);
			_animation->start();
			_JumpTime = 1.0f;
			_liveTime = 7.0f;
			gameObject::init("coin_earth", x, y, _image->getFrameWidth(), _image->getFrameHeight(), 4.0f, angle, true);
			EffectAndItemObject* _shinyGreen = new EffectAndItemObject;
			_shinyGreen->init(EFFECT_SHINE_GREEN, x, y);
			setZ(11);
			break;
	}

	
	GOBJECTMANAGER->addGameObject(this);
	return S_OK;
}

void EffectAndItemObject::update()
{
	switch (_objectType)
	{
	case EFFECT_SHINE_GREEN:
	case EFFECT_CRASH_LEFT:
	case EFFECT_CRASH_RIGHT:
		if (!_animation->isPlay())
			setDestroy(true);
		break;
	case EFFECT_CRASH_SHELL_BIG:
	case EFFECT_CRASH_SHELL_SMALL:
	case EFFECT_CRASH_ROOT:
	case EFFECT_CRASH_ROCK:
		if (!_animation->isPlay())
			setDestroy(true);
		setX(getX() + cosf(getObjectAngle()) * getSpeed());
		setY(getY() - sinf(getObjectAngle()) * getSpeed());
		if (_alphaValue>0)
			_alphaValue -= 5;
		break;
	case EFFECT_LEAF_LEFT :
		if (!_animation->isPlay())
			setDestroy(true);
		setX(getX() + cosf(getObjectAngle()) * getSpeed());
		setY(getY() - sinf(getObjectAngle()) * getSpeed());
		if (getObjectAngle() <= (PI / 2) * 3)
			setObjectAngle(getObjectAngle() + 0.25f);
		setSpeed(getSpeed() -0.01f);
		_alphaValue -= 5;
		break;
	case EFFECT_LEAF_RIGHT:
		if (!_animation->isPlay())
			setDestroy(true);
		setX(getX() + cosf(getObjectAngle()) * getSpeed());
		setY(getY() - sinf(getObjectAngle()) * getSpeed());
		if (getObjectAngle() >= -PI / 2  )
			setObjectAngle(getObjectAngle() - 0.25f);
		setSpeed(getSpeed() -0.01f);
		_alphaValue -= 5;
		break;
	case EFFECT_HPUP_10:
	case EFFECT_HPUP_30:
	case EFFECT_HPUP_50:
	case EFFECT_MPUP:
		setY(getY() - 1.0f);
		_liveTime -= TIMEMANAGER->getElapsedTime();
		if (_liveTime < 0)
		{
			setDestroy(true);
		}
		else if (_liveTime <0.5f)
		{
			if (_alphaValue > 50)
				_alphaValue -= 50;
			else
				_alphaValue = 255;
		}
		break;
	case EFFECT_HIT:
	case EFFECT_DIE:
	case EFFECT_BLINCK:
		if (!_animation->isPlay())
			setDestroy(true);
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////Item..///////////////////////////////////////////////////////////////
	case ITEM_MP_EARTH:
		if (_JumpTime > 0)
		{
			setX(getX() + cosf(getObjectAngle()) * getSpeed());
			setY(getY() - sinf(getObjectAngle()) * getSpeed());
			_JumpTime -= TIMEMANAGER->getElapsedTime();
		}
		_liveTime -= TIMEMANAGER->getElapsedTime();

		if (_liveTime < 0)
		{
			setDestroy(true);
		}
		else if (_liveTime <1.0f)
		{
			if (_alphaValue > 100)
				_alphaValue -= 100;
			else
				_alphaValue = 255;
		}
		else if (_liveTime <2.0f)
		{
			if (_alphaValue > 50)
				_alphaValue -= 50;
			else
				_alphaValue = 255;
		}
		break;
	case ITEM_HP_APPLE:
	case ITEM_HP_CHEESE:
	case ITEM_HP_CHICKEN:
		if (_JumpTime > 0 && _JumpTime <50.0f)
		{
			_JumpTime -= TIMEMANAGER->getElapsedTime();
			setY(getY() - 5.0f);
		}
		else if (_JumpTime <0)
		{
			if (getY() <= _startY)
				setY(getY() + 7.0f);
			else if (getY() > _startY)
			{
				_imageIndexX++;
				_JumpTime = 100.0f;
			}
		}

		_liveTime -= TIMEMANAGER->getElapsedTime();

		if (_liveTime < 0)
		{
			setDestroy(true);
		}
		else if (_liveTime <1.0f)
		{
			if (_alphaValue > 100)
				_alphaValue -= 100;
			else
				_alphaValue = 255;
		}
		else if (_liveTime <2.0f)
		{
			if (_alphaValue > 50)
				_alphaValue -= 50;
			else
				_alphaValue = 255;
		}

		break;


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	if (_isAnimated)
		_animation->frameUpdate(TIMEMANAGER->getElapsedTime());
}
void EffectAndItemObject::render()
{

}
void EffectAndItemObject::render(float x, float y)
{
	if (_isAnimated)
		_image->aniRender(getMemDC(), x, y, _animation);
	else
		_image->frameAlphaRender(getMemDC(), x, y, _imageIndexX, _imageIndexY, _alphaValue);
}
void EffectAndItemObject::release()
{

}
void EffectAndItemObject::onCollideEnter(gameObject* gObject)
{
	if (gObject->getTag() == "player")
	{

			EffectAndItemObject* effectHP = new EffectAndItemObject;
			Player*  p = (Player*)gObject;
			switch (_objectType)
			{

				/////////////////////////////////////////ITEM/////////////////////////////////
				if (_JumpTime > 50.0f)
				{
				case ITEM_HP_CHEESE:
					setDestroy(true);
					effectHP->init(EFFECT_HPUP_30, _startX + 30, _startY);
					p->setHP(static_cast<int>(p->getHP() + p->getMaxHp() / 3.33 + 1));
					SOUNDMANAGER->play("get02", 1.0f);
					break;
				case ITEM_HP_CHICKEN:
					setDestroy(true);
					effectHP->init(EFFECT_HPUP_50, _startX + 30, _startY);
					p->setHP(static_cast<int>(p->getHP() + p->getMaxHp() / 2));
					SOUNDMANAGER->play("get02", 1.0f);
					break;
				case ITEM_HP_APPLE:
					setDestroy(true);
					effectHP->init(EFFECT_HPUP_10, _startX + 30, _startY);
					p->setHP(static_cast<int>(p->getHP() + 1));
					SOUNDMANAGER->play("get02", 1.0f);
					break;
				case ITEM_MP_EARTH:
					setDestroy(true);
					effectHP->init(EFFECT_MPUP, getX(), getY());
					p->setMP(static_cast<int>(p->getMP() + 1));
					//¾ÆÁ÷ ¿¤·¹¸àÅ» Ã¼ÀÎÁö°¡ ±¸Çö¾È‰ç±â¿¡ ÀÌ°Ç ³ÀµÎÀÚ.
					//p->setCurrentElemental(ELEMENTAL_EARTH);
					SOUNDMANAGER->play("get01", 1.0f);
					break;
				}

			case ITEM_SWORD :
				p->setSword();
				setDestroy(true);
				GQUESTMANAGER->checkQuestCondition(this);
				GQUESTMANAGER->getCutScene()->showCutScene(GET_SWORD);
				break;
			case ITEM_KEY :
				setDestroy(true);
				for (int i = 0; i < ITEMMAX; i++)
				{
					if (p->getItems()[i] == 0)
					{
						p->getItems()[i] = 1;
						break;
					}
				}
				GQUESTMANAGER->checkQuestCondition(this);
				GQUESTMANAGER->getCutScene()->showCutScene(GET_KEY);
				break;
			case ITEM_HEALTH:
				setDestroy(true);
				p->setMaxHp(p->getMaxHp() + 1);
				GQUESTMANAGER->checkQuestCondition(this);
				GQUESTMANAGER->getCutScene()->showCutScene(GET_HEALTH_POTION);
				break;
			case ITEM_LUCA:
				p->setCurrentElemental(ELEMENTAL_EARTH);
				setDestroy(true);
				GQUESTMANAGER->checkQuestCondition(this);
				GQUESTMANAGER->getCutScene()->showCutScene(MEET_FOREST_ELEMENTAL);
				_linkedObject->setDestroy(true);
				break;
			case	ITEM_LUCA_UP:
				p->increaseSkill();
				setDestroy(true);
				GQUESTMANAGER->checkQuestCondition(this);
				GQUESTMANAGER->getCutScene()->showCutScene(LEVELUP_FOREST_ELEMENTAL);
				break;
			case ITEM_FOREST_EMBLEM:
				setDestroy(true);
				GQUESTMANAGER->checkQuestCondition(this);
				GQUESTMANAGER->getCutScene()->showCutScene(GET_FOREST_EMBLEM);
				EnviromentObject* luca = new EnviromentObject;
				luca->init(tagObjectInfo(getX() / MULTIPLY_X, getY() / MULTIPLY_Y, TILESIZE, TILESIZE,
					OBJECT_NPC, FRAMED_NPC, "NPC", 0, 2, "", "end.txt"));
				break;
			}
		



	}

}