#include "stdafx.h"
#include "AbilityObject.h"
#include "Player.h"
#include "EffectAndItemObject.h"
#include "EnviromentObject.h"
AbilityObject::AbilityObject()
{
}


AbilityObject::~AbilityObject()
{
}

HRESULT AbilityObject::init(DIRECTION direction, float startX, float startY, ABILITYTYPE abilityType)
{
	_animation = new animation;
	_shadowImage = IMAGEMANAGER->findImage("multiply_InteractableObject");
	_direction = direction;
	_abilityType = abilityType;
	_onceShowed = false;
	_jumpTime = 0.5f;
	_jumpHeight = 0.0f;

	int sArr[] = { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 };
	int gsArr[] = { 28, 29, 30, 31, 32, 33, 34, 35 };
	int hsArr[] = { 28, 29, 30, 31, 32, 33, 34, 35, 53, 54,55 };
	switch (_abilityType)
	{
	case SWORD_EFFECT:
		switch (_direction)
		{
		case DIR_LEFT:
			_image = IMAGEMANAGER->findImage("hero_attack_left");
			gameObject::init("sword_effect", startX -115, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y - 8, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, PI, false);
			GOBJECTMANAGER->addGameObject(this);
			
			break;
		case DIR_RIGHT:
			_image = IMAGEMANAGER->findImage("hero_attack_right");
			gameObject::init("sword_effect", startX - 50 , startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y - 8, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, 0.0f, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_UP:
			_image = IMAGEMANAGER->findImage("hero_attack_up");
			gameObject::init("sword_effect", startX - 22, startY - 80 - ((TILESIZE / 4) * 3)*MULTIPLY_Y + 50, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, PI / 2, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_DOWN:
			_image = IMAGEMANAGER->findImage("hero_attack_down");
			gameObject::init("sword_effect", startX - 35, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y - 10, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		}
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_animation->setDefPlayFrame();
		_animation->setFPS(15);
		_animation->start();
		setZ(5);
		break;
	case SWORD:
		_image = IMAGEMANAGER->findImage("multiply_InteractableObject");
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		int arr[1];
		switch (_direction)
		{
		case DIR_LEFT:
			arr[0] = 14;
			gameObject::init("sword", startX - 115, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, PI);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_RIGHT:
			arr[0] = 12;
			gameObject::init("sword", startX +50, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, 0.0f);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_UP:
			arr[0] = 13;
			gameObject::init("sword", startX - 22, startY - 84 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_DOWN:
			arr[0] = 15;
			gameObject::init("sword", startX - 35, startY + 42 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3);
			GOBJECTMANAGER->addGameObject(this);
			break;
		}
		_animation->setPlayFrame(arr, 1, false);
		_animation->setFPS(10);
		_animation->start();
		SOUNDMANAGER->play("swing01", 1.0f);
		setZ(5);
		break;
	case EARTH_STAMP:

		_image = IMAGEMANAGER->findImage("multiply_InteractableObject");
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
	
		switch (_direction)
		{
		case DIR_LEFT:
			gameObject::init("stamp", startX - 142, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, PI, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_RIGHT:
			gameObject::init("stamp", startX + 90, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, 0.0f, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_UP:
			gameObject::init("stamp", startX - 32, startY - 80 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_DOWN:
			gameObject::init("stamp", startX - 32, startY + 62 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		}
		_animation->setPlayFrame(sArr, 11, false);
		_animation->setFPS(10);
		_animation->start();
		SOUNDMANAGER->play("shot01", 1.0f);
		setZ(11);
		break;
	case EARTH_GROW:
		_jumpTime = 0.3f;
		_image = IMAGEMANAGER->findImage("multiply_InteractableObject");
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		switch (_direction)
		{
		case DIR_LEFT:
			gameObject::init("grow", startX -142, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, PI, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_RIGHT:
			gameObject::init("grow", startX + 90, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, 0.0f, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_UP:
			gameObject::init("grow", startX - 32, startY - 80 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_DOWN:
			gameObject::init("grow", startX - 32, startY + 62 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		}
		_animation->setPlayFrame(gsArr, 8, false);
		_animation->setFPS(6);
		_animation->start();
		setZ(11);
		SOUNDMANAGER->play("shot01", 1.0f);
		break;
	case EARTH_HEAVYSTAMP:
		_jumpTime = 1.0f;
		_image = IMAGEMANAGER->findImage("multiply_InteractableObject");
		_animation->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		switch (_direction)
		{
		case DIR_LEFT:
			gameObject::init("heavy_stamp", startX - 142, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, PI, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_RIGHT:
			gameObject::init("heavy_stamp", startX +90, startY - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, 0.0f, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_UP:
			gameObject::init("heavy_stamp", startX - 32 , startY - 80 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		case DIR_DOWN:
			gameObject::init("heavy_stamp", startX - 32, startY + 62 - ((TILESIZE / 4) * 3)*MULTIPLY_Y, _image->getFrameWidth(), _image->getFrameHeight(), 0.0f, (PI / 2) * 3, false);
			GOBJECTMANAGER->addGameObject(this);
			break;
		}
		_animation->setPlayFrame(hsArr, 11, false);
		_animation->setFPS(8);
		_animation->start();
		setZ(11);
		SOUNDMANAGER->play("shot01", 1.0f);
		break;

	}


	return S_OK;
}
HRESULT AbilityObject::init(Player* target, ABILITYTYPE abilityType)
{
	_target = target;
	_abilityType = INTERACT;
	gameObject::init("interact", _target->getX(), _target->getY(), TILESIZE, TILESIZE, 0.0f, 0.0f);
			
	GOBJECTMANAGER->addGameObject(this);
	setZ(3);
	return S_OK;
}
void AbilityObject::update()
{

	switch (_abilityType)
	{
	case EARTH_STAMP:
		if (_jumpTime > 0)
		{
			_jumpTime -= TIMEMANAGER->getElapsedTime();
			_jumpHeight += 3.0f;
		}
		else
		{
			if (!this->_isColliderOn)
			{
				this->_isColliderOn = true;
				SOUNDMANAGER->play("hit02", 1.0f);
			}

			if (_jumpHeight > 0)
				_jumpHeight -= 18.0f;
			else
			{
				if (!_onceShowed)
				{
					EffectAndItemObject* leftCrashEffect = new EffectAndItemObject;
					leftCrashEffect->init(EFFECT_CRASH_LEFT, getX() - 65, getY() + 30);
					EffectAndItemObject* rightCrashEffect = new EffectAndItemObject;
					rightCrashEffect->init(EFFECT_CRASH_RIGHT, getX() - 65 + getWidth(), getY() + 30);
					_onceShowed = true;
				}

			}


		}
		break;
	case EARTH_HEAVYSTAMP:
		if (_jumpTime > 0.5f)
		{
			_jumpTime -= TIMEMANAGER->getElapsedTime();
			_jumpHeight += 5.0f;
		}
		else if (_jumpTime > 0)
		{
			_jumpTime -= TIMEMANAGER->getElapsedTime();
		}
		else
		{
			if (!this->_isColliderOn)
			{
				this->_isColliderOn = true;
				SOUNDMANAGER->play("power01", 1.0f);
			}
			if (_jumpHeight > 0)
				_jumpHeight -= 30.0f;
			else
			{
				if (!_onceShowed)
				{
					EffectAndItemObject* leftCrashEffect = new EffectAndItemObject;
					leftCrashEffect->init(EFFECT_CRASH_LEFT, getX() - 65, getY() + 30);
					EffectAndItemObject* rightCrashEffect = new EffectAndItemObject;
					rightCrashEffect->init(EFFECT_CRASH_RIGHT, getX() - 65 + getWidth(), getY() + 30);
					_onceShowed = true;
					SOUNDMANAGER->play("bom05", 1.0f);
				}

			}


		}
		break;
	case EARTH_GROW:
		if (_jumpTime > 0)
		{
			_jumpTime -= TIMEMANAGER->getElapsedTime();
			_jumpHeight += 7.0f;
		}
		else
		{
			if (!this->_isColliderOn)
			{
				this->_isColliderOn = true;
				SOUNDMANAGER->play("bom02", 1.0f);
			}
			if (_jumpHeight > 0)
				_jumpHeight -= 7.0f;
			else
			{
				if (!_onceShowed)
				{
					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							EffectAndItemObject* shinyEffect = new EffectAndItemObject;
							shinyEffect->init(EFFECT_SHINE_GREEN, getX() + 13 +j*40, getY() +10 + i* 30);
						}
					}

					_onceShowed = true;
				}

			}


		}
		break;
	} // end of switch (_abilityType)





	switch (_abilityType)
	{
	case INTERACT:
		switch (_target->getGameAnimation()->getDirection())
		{
		case DIR_LEFT:
			setX(_target->getX() - getWidth() -32);
			setY(_target->getY() - 30);
			break;
		case DIR_RIGHT:
			setX(_target->getX() + _target->getWidth() + 40 );
			setY(_target->getY() - 30);
			break;
		case DIR_UP:
			setX(_target->getCenterX() - 16);
			setY(_target->getY() - getHeight() - 80);
			break;
		case DIR_DOWN:
			setX(_target->getCenterX() - 16);
			setY(_target->getY() + 40);
			break;
		}
		break;
	default:
		_animation->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_animation->isPlay())
			setDestroy(true);
		break;
	}








}
void AbilityObject::render()
{

}
void AbilityObject::render(float x, float y)
{

	switch (_abilityType)
	{
	case EARTH_STAMP:
	case EARTH_GROW:
	case EARTH_HEAVYSTAMP:
		_shadowImage->frameRender(getMemDC(), x, y + (TILESIZE*MULTIPLY_Y) / 2 - 5, 7, 1);
		break;
	}


	switch (_abilityType)
	{
	case INTERACT:
	//	Rectangle(getMemDC(), x, y, x + getWidth(), y + getHeight());
		break;
	default:
		_image->aniRender(getMemDC(), x, y - _jumpHeight, _animation);
		break;
	}


}
void AbilityObject::release()
{
	SAFE_RELEASE(_animation);
}
void AbilityObject::onCollideEnter(gameObject* gObject)
{

	switch (_abilityType)
	{
		case INTERACT:
			if (gObject->getTag() == "door_key" )
			{
				_target->setAttackInteraction(false);
				if (KEYMANAGER->isStayKeyDown('Z'))
				{
					GQUESTMANAGER->checkQuestCondition((EnviromentObject*)gObject);
				}
			}
			else if (gObject->getTag() == "npc" || gObject->getTag() == "FRAMED_NPC" || gObject->getTag()=="hintmint")
			{
				EnviromentObject* object = (EnviromentObject*)gObject;

				_target->setAttackInteraction(false);

				if (KEYMANAGER->isStayKeyDown('Z'))
				{
					SOUNDMANAGER->play("pi", 1.0f);
					GQUESTMANAGER->showDialog(object);
					if (object->getObjectInfo().objectName == "luca" &&!object->getTrigger())
					{
						object->setTrigger(true);
						EffectAndItemObject* lucaItem = new EffectAndItemObject;
						lucaItem->init(tagObjectInfo(object->getObjectInfo().x, object->getObjectInfo().y, object->getObjectInfo().width, object->getObjectInfo().height, ITEM, OBJECT_ITEM_LUCA, "NPC", 0, 2), object);
					}

				}



			}
			else
				_target->setAttackInteraction(true);
	}


}