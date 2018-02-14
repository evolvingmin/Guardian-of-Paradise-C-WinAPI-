#include "stdafx.h"
#include "ForestMiniBoss.h"
#include "Seed.h"
#include "gameTileMap.h"
ForestMiniBoss::ForestMiniBoss()
{
}


ForestMiniBoss::~ForestMiniBoss()
{
}
HRESULT ForestMiniBoss::init(float x, float y)
{
	setUp(x + 20 , y, 216, TILESIZE*2* MULTIPLY_Y, "monster", "Forest_MiniBoss", 4.0f, MOVE);
	setName("Forest_MiniBoss");

	//애니메이션 등록

	//MOVE
	int allMove[] = { 0, 1, 2 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, MOVE, allMove, 3, 6, true);

	//ATTACK
	int allAttack[] = { 5,6,7,8,9 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, ATTACK, allAttack, 5, 15, false);



	//BEING HIT
	int downHit[] = { 9,3 };
	_gameAni->SetArrayFrameAnimation(DIR_ALL, HIT, downHit, 2, 10, true);

	//BEING DEAD
	int downDead[] = { 9,4 };
	_gameAni->SetArrayFrameAnimation(DIR_ALL, DIE, downDead, 2, 15, true);




	_element = ELEMENTAL_MONSTER_EARTH;
	_isOnceAttack = false;
	//스텟
	_Hp = _maxHp = 18;
	_enemyDetectDistance = 600;
	_hitCount = 0;
	_gameAni->start();

	
	
	SOUNDMANAGER->stop(GQUESTMANAGER->getCurrentMap()->getBGMKey());

	SOUNDMANAGER->play("boss01.mid", 5.0f);
	_bombDelayTime = 0.2f;

	return S_OK;
}
void ForestMiniBoss::update()
{
	enemy::update();

	switch (_gameAni->getState())
	{
	case MOVE:
	case ATTACK:
		invincibleUpdate();
	case HIT:
		break;
	}
}

void ForestMiniBoss::render(float x, float y)
{
	if (_turnUpDown)
		_shadowImage->frameRender(getMemDC(),  x + (TILESIZE * MULTIPLY_X)/2, y + (TILESIZE * 2 * MULTIPLY_Y) / 2 + 10, 6, 1);
	else
		_shadowImage->frameRender(getMemDC(),  x + (TILESIZE * MULTIPLY_X) / 2 - 2.5f, y + (TILESIZE * 2 * MULTIPLY_Y) / 2 + 20, 9, 5);

	if (_gameAni->getState() == HIT || _gameAni->getState() == DIE)
	{
	//	Rectangle(getMemDC(), 20 + x, y - _downDistance, 20 + x + getWidth(), y + getHeight() - _downDistance);
		_gameAni->render( x, y - _downDistance);
	}

	else
	{
		//Rectangle(getMemDC(), 20 + x, y, 20 + x + getWidth(), y + getHeight());
		_gameAni->render(x, y);
	}

}
void ForestMiniBoss::onCollideEnter(gameObject* gObject)
{
	if (gObject->getTag() == "sword")
	{
		if (!_invincible)
		{
			if (_initialHitPushbackTime <= 0 )
			{
				RECT temp;
				IntersectRect(&temp, &gObject->boundingBox(), &this->boundingBox());
				EffectAndItemObject* HitEffect = new EffectAndItemObject;
				SOUNDMANAGER->play("kin01", 1.0f);
				HitEffect->init(EFFECT_HIT, temp.left, temp.top);
				if (_initialHitPushbackTime <= 0)
					_initialHitPushbackTime = 0.5f;

				if (_gameAni->getState() != MOVE)
				{

					Player* player = (Player*)GOBJECTMANAGER->findGameObject("player");
					player->setFight(true);
					player->setFightOpponent(this);
					_Hp--;
					_hitCount++;
					
					if (_Hp > 0 && _gameAni->getState() != DIE)
					{
						
						_gameAni->setState(HIT);
						if (_hitCount > 3)
						{
							SOUNDMANAGER->play("hit06", 1.0f);
							setHit(gObject, true);
							_hitCount = 0;
						}
						else
						{
							SOUNDMANAGER->play("hit01", 1.0f);
							setHit(gObject, false);
						}

					}
					else if (_gameAni->getState() != DIE &&_Hp <= 0)
					{
						SOUNDMANAGER->play("hit06", 1.0f);
						_gameAni->setState(DIE);
						setDie();
					}


				}


			}


			
		}

	}
}//end else 


	//힛 이펙트 위치에 대한 방안,IntersectRect에서 나오는 temp의 위치값을 기준으로 해보자.

void ForestMiniBoss::moveUpdate()
{

	if (_initialHitPushbackTime > 0)
		_initialHitPushbackTime -= TIMEMANAGER->getElapsedTime();


	_moveDelayTime -= TIMEMANAGER->getElapsedTime();
	if (_moveDelayTime <= 0)
	{
			_AttackDelayTime = 2.5f;
		_gameAni->setState(ATTACK);
		_isOnceAttack = false;
	}

	setObjectAngle(getAngle(getX(), getY(), _player->getX(), _player->getY()));
	setX(getX() + cosf(getObjectAngle())* getSpeed());
	setY(getY() - sinf(getObjectAngle()) * getSpeed());

}
void ForestMiniBoss::hitUpdate()
{
	paravola();
	elasticity(2, 35);


	if (_hitDelayTime>0)
		_hitDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		_hitCount = 0;
		_moveDelayTime = 4.0f;
		_gameAni->setState(MOVE);
		_invincibleTime = 2.0f;
		//무적으로 돌아다닐 수있는 시간을 2초정도 더 줘야한다.
	}

}
void ForestMiniBoss::setHit(gameObject* gObject, bool isInvinsible)
{
	setObjectAngle(getAngle(gObject->getX(), gObject->getY(), getX(), getY()));

	_hitSpeedX = 4.0f;
	_hitSpeedY = 3.0f;
	_hitDelayTime = 1.5f;
	if (_initialHitPushbackTime <= 0)
		_initialHitPushbackTime = 0.5f;
	_upDownSpeed = 600;
	_downRange = 150;


	_invincible = isInvinsible;


}
void ForestMiniBoss::setAttack()
{

	SOUNDMANAGER->play("shot02", 1.0f);
	Seed* seed[5];
	for (int i = 0; i < 5; i++)
	{
		seed[i] = new Seed;
		seed[i]->init(getX() + 50, getY());
		seed[i]->setObjectAngle(getAngle(getX(), getY(), _player->getX(), _player->getY()) +(i - 2)* (PI / 8));
		seed[i]->setSpeed(7.0f);
	}


	//seed[0] = new Seed;
	//seed[0]->init(getX() +  50, getY());
	//seed[0]->setObjectAngle(getAngle(getX(), getY(), _player->getX(), _player->getY()));


}
void ForestMiniBoss::attackUpdate()
{
	_AttackDelayTime -= TIMEMANAGER->getElapsedTime();

	if (!_gameAni->isPlay() && !_isOnceAttack)
	{
		setAttack();
		_isOnceAttack = true;
	}


	if (_AttackDelayTime < 0.0f)
	{
		_moveDelayTime = 4.0f;
		_gameAni->setState(MOVE);
	}

}

void ForestMiniBoss::invincibleUpdate()
{
	if (_invincible)
	{
		_invincibleTime -= TIMEMANAGER->getElapsedTime();

		if (_gameAni->getAlpha() > 50)
			_gameAni->setAlpha(_gameAni->getAlpha() - 50);
		else
			_gameAni->setAlpha(255);

		if (_invincibleTime <= 0)
		{
			_gameAni->setAlpha(255);
			_invincible = false;
		}
	}
}
void ForestMiniBoss::setDie()
{
	_gameAni->setState(DIE);
	_deadDelayTime = 4.0f;
}
void ForestMiniBoss::dieUpdate()
{
	if (_deadDelayTime > 0)
	{
		_deadDelayTime -= TIMEMANAGER->getElapsedTime();


		if (_bombDelayTime > 0)
		{
			_bombDelayTime -= TIMEMANAGER->getElapsedTime();
		}
		else
		{
			EffectAndItemObject* deadEffect = new EffectAndItemObject;
			deadEffect->init(EFFECT_DIE, RND->getFromFloatTo(getX() - getWidth(), getX() + getWidth()), RND->getFromFloatTo(getY() - getHeight(), getY() + getHeight()));
			_bombDelayTime = 0.2f;
		}

	}
	else
	{

		setDestroy(true);
		_player->setFight(false);
		SOUNDMANAGER->stop("boss01.mid");
		SOUNDMANAGER->play(GQUESTMANAGER->getCurrentMap()->getBGMKey(), 5.0f);

	}

}