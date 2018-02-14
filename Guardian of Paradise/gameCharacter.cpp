#include "stdafx.h"
#include "gameCharacter.h"
#include "Player.h"
#include "EffectAndItemObject.h"
CEREAL_REGISTER_TYPE(gameCharacter);
gameCharacter::gameCharacter()
{
	
}


gameCharacter::~gameCharacter()
{
}
HRESULT gameCharacter::init(string tag, float startX, float startY, float width, float height, float speed, float zOrder, string imageKeyName, DIRECTION direction, STATE state)
{
	_gameAni = new gameAnimation;
	_gameAni->init(IMAGEMANAGER->findImage(imageKeyName), direction, state);

	_shadowImage = IMAGEMANAGER->findImage("multiply_InteractableObject");

	_invincible = false;
	_invincibleTime=0;
	_hitDelayTime=0;
	_initialHitPushbackTime=0;
	_hitSpeedX=0;
	_hitSpeedY=0;
	_turnUpDown = false;
	_downDistance=0;
	_downRange=0;
	_upDownSpeed=0;
	_AttackDelayTime = 0;
	_deadDelayTime = 0;
	_pushDelayTime = 0;
	gameObject::init(tag, startX, startY, width, height, speed, 0, true);

	setZ(zOrder);
	GOBJECTMANAGER->addGameObject(this);
	return S_OK;
}



void gameCharacter::render(float x, float y)
{
	if (_gameAni->getState() != FALL)
	{
		if (_turnUpDown)
			_shadowImage->frameRender(getMemDC(), x, y + (TILESIZE*MULTIPLY_Y) / 2 - 10, 7, 1);
		else
			_shadowImage->frameRender(getMemDC(), x, y + (TILESIZE*MULTIPLY_Y) / 2 - 10, 6, 1);
	}


	if (_gameAni->getState() == HIT || _gameAni->getState() == DIE)
	{
		//Rectangle(getMemDC(), x, y - _downDistance, x + getWidth(), y - _downDistance + getHeight());
		_gameAni->render(x, y - _downDistance);
	}

	else
	{

	//	Rectangle(getMemDC(), x, y , x + getWidth(), y + getHeight());
		_gameAni->render(x, y);
	}

}
void gameCharacter::release()
{
	SAFE_RELEASE(_gameAni);
}
void gameCharacter::onCollideEnter(gameObject* gObject, bool isPlayer, bool useReaction)
{
	bool checkHit = false;
	for (int i = 0; i < _hitReactionOpponents.size(); i++)
	{
		if (gObject->getTag() == _hitReactionOpponents[i])
		{
			checkHit = true; break;
		}
	}

	if (checkHit)
	{
		if (isPlayer)
		{
			gameCharacter* opponents = (gameCharacter*)gObject;
			if (opponents->getGameAnimation()->getState() == IDLE 
				|| opponents->getGameAnimation()->getState() == MOVE 
				|| opponents->getGameAnimation()->getState() == ATTACK
				|| opponents->getGameAnimation()->getState()==JUMP)
			{
				if (!_invincible)
				{
					if (_initialHitPushbackTime <= 0)
						_Hp--;
					gameObject* swordEffect = GOBJECTMANAGER->findGameObject("sword_effect");
					if (swordEffect != NULL)
						swordEffect->setDestroy(true);
					if (_Hp > 0)
					{
						_gameAni->setState(HIT);
						setHit(gObject, isPlayer);
						SOUNDMANAGER->play("hit01", 1.0f);
					}
					else if (_gameAni->getState() != DIE &&_Hp <= 0)
					{
						_gameAni->setState(DIE);
						setDie(gObject, useReaction);
						SOUNDMANAGER->play("over01", 1.0f);
					}
				}
			}
		} // end of if (isPlayer)
		else
		{
			if (!_invincible)
			{
				if (_initialHitPushbackTime <= 0 &&_gameAni->getState() != DIE)
				{
					Player* player = (Player*)GOBJECTMANAGER->findGameObject("player");
					player->setFight(true);
					player->setFightOpponent(this);
					SOUNDMANAGER->play("hit01", 1.0f);
					_Hp--;

					RECT temp;
					IntersectRect(&temp, &gObject->boundingBox(), &this->boundingBox());


					EffectAndItemObject* HitEffect = new EffectAndItemObject;
					HitEffect->init(EFFECT_HIT, temp.left, temp.top);

					if (_Hp > 0)
					{
						_gameAni->setState(HIT);
						setHit(gObject, isPlayer);
					}
					else if (_Hp <= 0 && _gameAni->getState() != DIE)
					{
						SOUNDMANAGER->play("hit06", 1.0f);
						_gameAni->setState(DIE);
						setDie(gObject, useReaction);
					}
				}
			}
		}//end else 
	}//end of if(checkHit)
}


//운동함수들
void gameCharacter::elasticity(float dampingRatio, float lostSpeed)
{
	if (!_turnUpDown)
		_downDistance += TIMEMANAGER->getElapsedTime() * _upDownSpeed;

	if (_downDistance >= _downRange && !_turnUpDown)
	{
		_downRange /= dampingRatio;
		if (_downRange < 1.0f)
			_downRange = 0;
		_downDistance = _downRange;
		_turnUpDown = true;

	}

	if (_turnUpDown)
		_downDistance -= TIMEMANAGER->getElapsedTime() * _upDownSpeed;

	if (_downDistance <= 0 && _turnUpDown)
	{
		_turnUpDown = false;
		_upDownSpeed -= lostSpeed;
		_downDistance = 0;
	}

	if (_upDownSpeed >0)
		_upDownSpeed -= TIMEMANAGER->getElapsedTime()* GRAVITY;
}
void gameCharacter::paravola()
{
	if (_initialHitPushbackTime > 0)
	{
		_initialHitPushbackTime -= TIMEMANAGER->getElapsedTime();

		if (_hitSpeedX > 0)
		{
			_hitSpeedX -= cosf(getObjectAngle()) * (GRAVITY/2) * TIMEMANAGER->getElapsedTime();
			setX(getX() + cosf(getObjectAngle()) *  _hitSpeedX);
		}
		if (_hitSpeedY > 0)
		{
			_hitSpeedY -= sinf(getObjectAngle()) * GRAVITY* TIMEMANAGER->getElapsedTime();
			setY(getY() - sinf(getObjectAngle()) *_hitSpeedY);
		}
	}
}

//Action Stuff
void gameCharacter::setHit(gameObject* gObject, bool isInvinsible)
{
	setObjectAngle(getAngle(gObject->getX(), gObject->getY(), getX(), getY()));

	_hitSpeedX = 4.0f;
	_hitSpeedY = 3.0f;
	_hitDelayTime = 1.5f;
	if (_initialHitPushbackTime<=0)
		_initialHitPushbackTime = 0.5f;
	_upDownSpeed = 600;
	_downRange = 150;


	_invincible = isInvinsible;
}
void gameCharacter::hitUpdate()
{


	paravola();
	elasticity(2, 35);


	if (_hitDelayTime>0)
		_hitDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		_gameAni->setState(IDLE);
		_invincibleTime = 2.0f;
		//무적으로 돌아다닐 수있는 시간을 2초정도 더 줘야한다.
	}

}
void gameCharacter::setDie(gameObject* gObject, bool useReaction)
{
	if (useReaction)
	{
		setObjectAngle(getAngle(gObject->getX(), gObject->getY(), getX(), getY()));


		_hitSpeedX = 8.0f;
		_hitSpeedY = 8.0f;
		_initialHitPushbackTime = 0.5f;
		_deadDelayTime = 2.0f;
		_upDownSpeed = 600;
		_downRange = 150;
	}

}
void gameCharacter::dieUpdate()
{
	paravola();
	elasticity(2, 35);

	if (_deadDelayTime > 0)
		_deadDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		EffectAndItemObject* deadEffect= new EffectAndItemObject;
		deadEffect->init(EFFECT_DIE, RND->getFromFloatTo(getX() - getWidth() / 2, getX() + getWidth() / 2), RND->getFromFloatTo(getY() - getHeight() / 2, getY() + getHeight() / 2));

		setDestroy(true);
		manaCoinDrop();
	}
}


void gameCharacter::setMove(){}
void gameCharacter::moveUpdate(){}
void gameCharacter::setAttack(){}
void gameCharacter::attackUpdate(){}
void gameCharacter::setIdle(){}
void gameCharacter::idleUpdate(){}

void gameCharacter::manaCoinDrop(){}
