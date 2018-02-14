#include "stdafx.h"
#include "EnviromentObject.h"
#include "EffectAndItemObject.h"
#include "Player.h"

EnviromentObject::EnviromentObject()
{
}


EnviromentObject::~EnviromentObject()
{
}

HRESULT EnviromentObject::init(tagObjectInfo objectInfo)
{
	string tag;
	_objectInfo = objectInfo;
	
	_mainImage = IMAGEMANAGER->findImage("multiply_"+_objectInfo.objectImageFile);
	_isDestroyDelay = false;
	_buttonClicked = false;
	_isAnimated = false;
	_isHit = false;
	_isMove = false;
	_oncePushed = false;
	_isTrigger = false;
	int arr[4];
	switch (_objectInfo.objectSelect)
	{
	case DOOR_CONDITION:
		tag = "door_condition";
		break;
	case DOOR_KEY_REQUIRED:
		tag = "door_key";
		break;
	case WOOD_BLOCK: 
		tag = "wood_block";
		break;
	case WOOD_ROOT: 
		break;
	case HINTMINT: 
		tag = "hintmint_amature";
		arr[0] = 51;	arr[1] = 52;	
		_animation = new animation;
		_isAnimated = true;
		_animation->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
		_animation->setPlayFrame(arr, 2, true);
		_animation->setFPS(5);
		_animation->start();
		break;
	case MUSHIBOING: 
		tag = "mushiboing_amature";
		arr[0] = 66;	arr[1] = 67;	
		_animation = new animation;
		_isAnimated = true;
		_animation->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
		_animation->setPlayFrame(arr, 2, true);
		_animation->setFPS(5);
		_animation->start();
		break;
	case NPC: 
		tag = "npc";
		break;
	case FRAMED_NPC: 
		tag = "FRAMED_NPC";
		arr[0] = (_mainImage->getMaxFrameX()+1) * objectInfo.objectImageIndexY + objectInfo.objectImageIndexX;
		arr[1] = arr[0] + 1;
		arr[2] = arr[1] + 1;
		_animation = new animation;
		_isAnimated = true;
		_animation->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
		_animation->setPlayFrame(arr, 3, true);
		_animation->setFPS(3);
		_animation->start();
		break;
	case STONE_MOVABLE: 
		tag = "stone_movable";
		break;
	case STONE_MOVABLE_ONCE:
		tag = "stone_movable_once";
		arr[0] = 85, arr[1] = 86, arr[2] = 87, arr[3] = 88;
		_animation = new animation;
		_isAnimated = true;
		_animation->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
		_animation->setPlayFrame(arr, 4, false);
		_animation->setFPS(5);
		break;
	case STONE_BOARD:

		break;
	case SPIKE_MOVABLE:
		break;
	case ENVIROMENT_HOME: 
		break;
	case ENVIROMENT_GRASS:
		break;
	case PUZZLE_NUMBERBLOCK: 
		tag = "numberLock";
		_HitCount = 0;
		break;
	case BUTTON_ONCE:
	case BUTTON_KEEP:
	case BUTTON_ROBUST: 
		tag = "button";
		_buttonClicked = false;
		_HitCount = 0;
		break;
	}


	switch (_objectInfo.objectSelect)
	{

	case HINTMINT:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, _objectInfo.y * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, _objectInfo.height * MULTIPLY_Y, 0.0f, 0.0f, true);
		setZ(4);
		break;
	case MUSHIBOING:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, _objectInfo.y * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, _objectInfo.height * MULTIPLY_Y, 0.0f, 0.0f, true);
		setZ(4);
		break;
	case NPC:
	case FRAMED_NPC:


	case SPIKE_MOVABLE:

	case PUZZLE_NUMBERBLOCK:
	case BUTTON_ROBUST:
	case DOOR_CONDITION:
	case DOOR_KEY_REQUIRED:
	case WOOD_BLOCK:
	case WOOD_ROOT:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, _objectInfo.y * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, _objectInfo.height * MULTIPLY_Y, 0.0f, 3.0f, true);
		setZ(4);
		break;
	case STONE_BOARD:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, _objectInfo.y * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, _objectInfo.height * MULTIPLY_Y, 3.0f, 0.0f, true);
		setZ(4);
		_isMove = true;
		_destX = getX() + cosf(getObjectAngle()) * _objectInfo.goalNumber* MULTIPLY_X;
		_destY = getY() - sinf(getObjectAngle())  * _objectInfo.goalNumber* MULTIPLY_Y;
		break;
	case BUTTON_ONCE:
	case BUTTON_KEEP:
		gameObject::init(tag,
			_objectInfo.x * MULTIPLY_X + (_objectInfo.width * MULTIPLY_X) /4, 
			_objectInfo.y * MULTIPLY_Y + (_objectInfo.height * MULTIPLY_Y)/4, 
			(_objectInfo.width * MULTIPLY_X)/2,
			(_objectInfo.height * MULTIPLY_Y)/2
			, 0.0f, 0.0f, true);
		setZ(4);
		break;
	case STONE_MOVABLE:
	case STONE_MOVABLE_ONCE:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, _objectInfo.y * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, _objectInfo.height * MULTIPLY_Y, 0.0f, 0.0f, true);
		setZ(6);
		break;
	case ENVIROMENT_GRASS:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, _objectInfo.y * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, _objectInfo.height * MULTIPLY_Y, 0.0f, 0.0f, false);
		setZ(11 + (int)(getY()/(TILESIZE*MULTIPLY_Y)));
		break;
	case ENVIROMENT_HOME:
		gameObject::init(tag, _objectInfo.x * MULTIPLY_X, (_objectInfo.y + TILESIZE * 2) * MULTIPLY_Y, _objectInfo.width * MULTIPLY_X, (_objectInfo.height - TILESIZE * 2) * MULTIPLY_Y, 0.0f, 0.0f, true);
		setZ(9);
		break;
	}

	GOBJECTMANAGER->addGameObject(this);
	return S_OK;
}
void EnviromentObject::update()
{
	if (_isDestroyDelay)
	{
		_destoryDelay -= TIMEMANAGER->getElapsedTime();
		if (_destoryDelay<0)
		{
			setDestroy(true);
		}
	}

	if (_isHit)
	{
		_HitDelay -= TIMEMANAGER->getElapsedTime();
		if (_HitDelay < 0)
		{
			_isHit = false;
		}
	}
	if (_isMove)
	{
		setX(getX() + cosf(getObjectAngle()) * 3.0f);
		setY(getY() - sinf(getObjectAngle()) * 3.0f);

		if (abs(getDistance(getX(), getY(), _destX, _destY)) <= 1.0f)
		{

			_isMove = false;
			if (_objectInfo.objectSelect == STONE_MOVABLE_ONCE)
			{
				_oncePushed = true;
				_animation->start();
			}
			if (_objectInfo.objectSelect == STONE_BOARD)
			{
				setObjectAngle(getObjectAngle() + PI);

				_destX = getX() + cosf(getObjectAngle()) * _objectInfo.goalNumber* MULTIPLY_X;
				_destY = getY() - sinf(getObjectAngle())  * _objectInfo.goalNumber* MULTIPLY_Y;
				_isMove = true;
			}
		} 
	}



	switch (_objectInfo.objectSelect)
	{
	case BUTTON_KEEP:

		_buttonClicked = false;
		break;
	case STONE_BOARD:
		RECT temp;
		if (!IntersectRect(&temp, &boundingBox(), &GQUESTMANAGER->getPlayer()->boundingBox()))
		{
			GQUESTMANAGER->getPlayer()->setOnBoard(false);
		}
		break;
	case ENVIROMENT_HOME:
		if (GQUESTMANAGER->getPlayer()->getY() < this->getY())
			setZ(11);
		else
			setZ(9);
		break;
	}





	if (_isAnimated)
		_animation->frameUpdate(TIMEMANAGER->getElapsedTime());


}
void EnviromentObject::render()
{
	switch (_objectInfo.objectSelect)
	{
		case DOOR_CONDITION:
		case DOOR_KEY_REQUIRED:
		case WOOD_BLOCK:
		case WOOD_ROOT:
		case HINTMINT:
		case MUSHIBOING:
		case NPC:
		case FRAMED_NPC:
		case STONE_MOVABLE:
		case STONE_MOVABLE_ONCE:
		case STONE_BOARD:
		case SPIKE_MOVABLE:
		case ENVIROMENT_GRASS:
		case PUZZLE_NUMBERBLOCK:
			_mainImage->frameRender(getMemDC(), getX(), getY(), _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
			break;
		case ENVIROMENT_HOME:
			_mainImage->frameRender(getMemDC(), getX(), getY() - TILESIZE*2*MULTIPLY_Y, _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
			break;
		case BUTTON_ONCE:
		case BUTTON_KEEP:
			if (_buttonClicked)
				_mainImage->frameRender(getMemDC(), getX() - (_objectInfo.width * MULTIPLY_X) / 4, getY() - (_objectInfo.height * MULTIPLY_Y) /4, _objectInfo.objectImageIndexX + 1, _objectInfo.objectImageIndexY);
			else
				_mainImage->frameRender(getMemDC(), getX() - (_objectInfo.width * MULTIPLY_X) / 4, getY() - (_objectInfo.height * MULTIPLY_Y) /4, _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
			break;
		case BUTTON_ROBUST:
			_mainImage->frameRender(getMemDC(), getX(), getY(), _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
			break;


	}

}
void EnviromentObject::render(float x, float y)
{
	switch (_objectInfo.objectSelect)
	{
	case HINTMINT:
	case MUSHIBOING:
	case STONE_MOVABLE_ONCE:
	case FRAMED_NPC:
		_mainImage->aniRender(getMemDC(), x, y, _animation);
		break;
	case NPC:

	case DOOR_CONDITION:
	case DOOR_KEY_REQUIRED:
	case WOOD_BLOCK:
	case WOOD_ROOT:
	
	case STONE_MOVABLE:
	case STONE_BOARD:
	case SPIKE_MOVABLE:
	case ENVIROMENT_GRASS:
		_mainImage->frameRender(getMemDC(), x, y, _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
		break;
	case ENVIROMENT_HOME:

		_mainImage->frameRender(getMemDC(), x, y   - TILESIZE * 2 * MULTIPLY_Y, _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
		break;
	case BUTTON_ONCE:
	case BUTTON_KEEP:
		if (_buttonClicked)
			_mainImage->frameRender(getMemDC(), x - (_objectInfo.width * MULTIPLY_X) / 4, y - (_objectInfo.height * MULTIPLY_Y) / 4, _objectInfo.objectImageIndexX + 1, _objectInfo.objectImageIndexY);
		else
			_mainImage->frameRender(getMemDC(), x - (_objectInfo.width * MULTIPLY_X) / 4, y- (_objectInfo.height * MULTIPLY_Y) / 4, _objectInfo.objectImageIndexX, _objectInfo.objectImageIndexY);
		break;
	case BUTTON_ROBUST:
	case PUZZLE_NUMBERBLOCK:
		_mainImage->frameRender(getMemDC(), x, y, _objectInfo.objectImageIndexX + _HitCount, _objectInfo.objectImageIndexY);
		break;
	}
}
void EnviromentObject::release()
{
	if (_isAnimated)
		SAFE_DELETE(_animation);

}
void EnviromentObject::onCollideEnter(gameObject* gObject)
{

	if (gObject->getTag()=="player")
	{
		Player* player = (Player*)gObject;
		RECT temp;
		switch (_objectInfo.objectSelect)
		{
		case STONE_BOARD:
		player->setOnBoard(true);
		if (player->getGameAnimation()->getState() != FALL)
		{

			player->setX(player->getX() + cosf(getObjectAngle()) * getSpeed());
			player->setY(player->getY() - sinf(getObjectAngle()) * getSpeed());
		}
		break;
		case FRAMED_NPC:
		case DOOR_CONDITION:
		case DOOR_KEY_REQUIRED:
		case WOOD_ROOT:
		case HINTMINT:
		case NPC:
		case SPIKE_MOVABLE:
		case PUZZLE_NUMBERBLOCK:
			isCollisionReaction(this, gObject);
			break;
		case ENVIROMENT_HOME:

			RECT temp;
			if (!IntersectRect(&temp, &gObject->boundingBox(), &RectMake(getX() + TILESIZE*MULTIPLY_X * 2 + (TILESIZE / 3)*MULTIPLY_X, getY() + TILESIZE*MULTIPLY_Y * 2, (TILESIZE / 3)*MULTIPLY_X, TILESIZE*MULTIPLY_Y)))
				isCollisionReaction(this, gObject);
			break;
		case BUTTON_ONCE:
		case BUTTON_KEEP:
			if (!_buttonClicked)
			{
			//	SOUNDMANAGER->play("kachi01", 1.0f);
				_buttonClicked = true;
			}

			break;
		case BUTTON_ROBUST:
			isCollisionReaction(this, gObject);
			break;
		case WOOD_BLOCK:
			isCollisionReaction(this, gObject);

			break;
		case MUSHIBOING:
			break;
		case STONE_MOVABLE:
			isCollisionReaction(this, gObject);
			if (!_isMove)
			{
				SOUNDMANAGER->play("drag01", 1.0f);
				_isMove = true;
				player->setPush();
				if (player->getGameAnimation()->getDirection() == DIR_LEFT)
				{
					_destX = getX() - TILESIZE*MULTIPLY_X;
					_destY = getY();
				}
				else if (player->getGameAnimation()->getDirection() == DIR_RIGHT)
				{
					_destX = getX() + TILESIZE*MULTIPLY_X;
					_destY = getY();
				}
				else if (player->getGameAnimation()->getDirection() == DIR_UP)
				{
					_destX = getX();
					_destY = getY() - TILESIZE*MULTIPLY_Y;
				}
				else if (player->getGameAnimation()->getDirection() == DIR_DOWN)
				{
					_destX = getX();
					_destY = getY() + TILESIZE*MULTIPLY_Y;
				}
				setObjectAngle(getAngle(getX(), getY(), _destX, _destY));
			}

			break;
		case STONE_MOVABLE_ONCE:
			isCollisionReaction(this, gObject);

			if (!_oncePushed)
			{
				if (!_isMove)
				{
					SOUNDMANAGER->play("drag01", 1.0f);
					_isMove = true;

					player->setPush();
					if (player->getGameAnimation()->getDirection() == DIR_LEFT)
					{
						_destX = getX() - TILESIZE*MULTIPLY_X;
						_destY = getY();
					}
					else if (player->getGameAnimation()->getDirection() == DIR_RIGHT)
					{
						_destX = getX() + TILESIZE*MULTIPLY_X;
						_destY = getY();
					}
					else if (player->getGameAnimation()->getDirection() == DIR_UP)
					{
						_destX = getX();
						_destY = getY() - TILESIZE*MULTIPLY_Y;
					}
					else if (player->getGameAnimation()->getDirection() == DIR_DOWN)
					{
						_destX = getX();
						_destY = getY() + TILESIZE*MULTIPLY_Y;
					}
					setObjectAngle(getAngle(getX(), getY(), _destX, _destY));
				}

			}
			break;

		}

	}
	else if (gObject->getTag() == "grow")
	{
		int arr[3];
		switch (_objectInfo.objectSelect)
		{
		case HINTMINT:
			arr[0] = 56; arr[1] = 57; arr[2] = 58;
			setTag("hintmint");
			_animation->setPlayFrame(arr, 3, true);
		//	_animation->start();
			break;
		case MUSHIBOING:
			setTag("mushiboing");
			arr[0] = 68; arr[1] =69; arr[2] = 70;
			_animation->setPlayFrame(arr, 3, true);
		//	_animation->start();
			break;
		}

	}
	else if (gObject->getTag() == "heavy_stamp")
	{
		switch (_objectInfo.objectSelect)
		{
		case BUTTON_ONCE:
		case BUTTON_KEEP:
			if (!_buttonClicked)
			{
				_buttonClicked = true;
			}

			break;
		case WOOD_BLOCK:
			_objectInfo.objectImageIndexX++;
			this->_isColliderOn = false;
			SOUNDMANAGER->play("hit07", 1.0f);
			break;
		case WOOD_ROOT:
			_objectInfo.objectImageIndexX = 0;
			_objectInfo.objectImageIndexY = 2;
			this->_isColliderOn = false;
			_isDestroyDelay = true;
			_destoryDelay = 0.3f;
			SOUNDMANAGER->play("bom03", 1.0f);
			EffectAndItemObject* effects[6];
			for (int i = 0; i < 6; i++)
			{
				effects[i] = new EffectAndItemObject;
				effects[i]->init(EFFECT_CRASH_ROOT, getCenterX(), getCenterY(), i * (PI / 3));
			}
			break;
		}

	}
	else if (gObject->getTag() == "stamp" )
	{
		switch (_objectInfo.objectSelect)
		{
		case WOOD_BLOCK:
			_objectInfo.objectImageIndexX++;
			this->_isColliderOn = false;
			SOUNDMANAGER->play("hit07", 1.0f);
			break;
		case ENVIROMENT_HOME:
			break;
		case PUZZLE_NUMBERBLOCK:
			break;
		case BUTTON_ONCE:
		case BUTTON_KEEP:
			if (!_buttonClicked)
				_buttonClicked = true;
			break;
		case BUTTON_ROBUST:
			if (!_isHit)
			{
				SOUNDMANAGER->play("bom04", 1.0f);
				_HitCount++;
				if (_HitCount == 3)
				{
					SOUNDMANAGER->play("kachi02", 1.0f);
					_buttonClicked = true;
					this->_isColliderOn = false;
				}
				_isHit = true;
				_HitDelay = 1.0f;
				EffectAndItemObject* effects[4];
				for (int i = 0; i < 4; i++)
				{
					effects[i] = new EffectAndItemObject;
					effects[i]->init(EFFECT_CRASH_ROCK, getX() + 30, getCenterY(), i * (PI / 3));
				}
			}
			break;

		default:
			break;
		}

	}
	else if (gObject->getTag() == "sword")
	{
		EffectAndItemObject* HitEffect = new EffectAndItemObject;
		switch (_objectInfo.objectSelect)
		{
		case WOOD_BLOCK:
		case STONE_MOVABLE:
		case STONE_MOVABLE_ONCE:
		case STONE_BOARD:
		case SPIKE_MOVABLE:
		case DOOR_CONDITION:
		case DOOR_KEY_REQUIRED:
		case BUTTON_ROBUST:
			if (!_isHit)
			{
				HitEffect->init(EFFECT_HIT, getX() - getWidth() / 2, getY() - getHeight() / 2);
				SOUNDMANAGER->play("kin01", 1.0f);
				_isHit = true;
				_HitDelay = 0.3f;
			}


			break;
		case WOOD_ROOT:
			if (!_isHit)
			{
				HitEffect->init(EFFECT_HIT, getCenterX() - getWidth() / 2 - 30, getCenterY() - getHeight() / 2 - 20);
				SOUNDMANAGER->play("kin01", 1.0f);
				_isHit = true;
				_HitDelay = 0.3f;
			}
			break;
		case ENVIROMENT_HOME:
			break;
		case PUZZLE_NUMBERBLOCK:

			if (!_isHit)
			{
				HitEffect->init(EFFECT_HIT, getX() - getWidth() / 2, getY() - getHeight() / 2);
				_HitCount++;
				SOUNDMANAGER->play("kachi03", 1.0f);
				if (_HitCount >= 4)
				{
					_HitCount = 0;
				}
				_isHit = true;
				_HitDelay = 0.3f;
			}
			break;

		}
	}
	else if (gObject->getTag() == "stone_movable" || gObject->getTag() == "stone_movable_once")
	{
		EnviromentObject* enviroment = (EnviromentObject*)gObject;
		switch (_objectInfo.objectSelect)
		{
		case DOOR_CONDITION:
		case DOOR_KEY_REQUIRED:
		case WOOD_BLOCK:
		case WOOD_ROOT:
		case HINTMINT:
		case MUSHIBOING:
		case NPC:
		case FRAMED_NPC:
		case STONE_MOVABLE_ONCE:
		case STONE_MOVABLE:
		case STONE_BOARD:
		case SPIKE_MOVABLE:
		case ENVIROMENT_HOME:
		case PUZZLE_NUMBERBLOCK:
		case BUTTON_ROBUST:
		case OBJECT_ITEM_SWORD:
		case OBJECT_ITEM_KEY:
		case OBJECT_ITEM_HEALTH:
			isCollisionReaction(this, gObject);
			enviroment->setMove(false);
		case BUTTON_ONCE:
		case BUTTON_KEEP:
			if (!_buttonClicked)
				_buttonClicked = true;
			break;



		}
	}

		





}

void EnviromentObject::setMove(bool move)
{
	_isMove = move;
}
