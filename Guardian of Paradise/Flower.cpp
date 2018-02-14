#include "stdafx.h"
#include "Flower.h"
#include "EffectAndItemObject.h"
#include "Seed.h"
flower::flower()
{
}


flower::~flower()
{
}
HRESULT flower::init(float x, float y)
{
	setUp(x, y, TILESIZE*MULTIPLY_X, TILESIZE* MULTIPLY_Y, "monster", "flower", 2.0f, IDLE);


	//애니메이션 등록
	//IDLE
	int downIdle[] = { 0, 1, 2 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, IDLE, downIdle, 3, 4, true);

	//ATTACK
	int downAttack[] = { 3, 4 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, ATTACK, downAttack, 2, 5, false);

	//BEING HIT
	int downHit[] = { 5, 6 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, HIT, downHit, 2, 10, true);

	//BEING DEAD
	int downDead[] = { 5, 7 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, DIE, downDead, 2, 15, true);


	_element = ELEMENTAL_MONSTER_EARTH;
	//스텟
	_Hp = _maxHp = 3;


	return S_OK;
}
void flower::update()
{
	enemy::update();

}

void flower::render(float x, float y)
{
	enemy::render(x, y);
}

void flower::onCollideEnter(gameObject* object)
{
	gameCharacter::onCollideEnter(object, false, true);
}

//Action Stuff
void flower::setHit(gameObject* gObject, bool isInvinsible)
{
	_hitDelayTime = 2.0f;
	if (_initialHitPushbackTime <= 0)
		_initialHitPushbackTime = 0.5f;
	_upDownSpeed = 800;
	_downRange = 150;
	_invincible = isInvinsible;
}
void flower::hitUpdate()
{
	if (_initialHitPushbackTime > 0)
		_initialHitPushbackTime -= TIMEMANAGER->getElapsedTime();

	elasticity(2, 35);

	_hitDelayTime -= TIMEMANAGER->getElapsedTime();
	if (_hitDelayTime < 0 && _gameAni->getState() == HIT)
	{
		_gameAni->setState(IDLE);
	}

}
void flower::setDie(gameObject* gObject, bool useReaction)
{
	if (useReaction)
	{
		_hitDelayTime = 2.0f;
		_initialHitPushbackTime = 0.5f;
		_upDownSpeed = 1000;
		_downRange = 200;
		_deadDelayTime = 2.0f;
	}

}
void flower::dieUpdate()
{

	elasticity(2, 35);

	if (_deadDelayTime > 0)
	{
		_deadDelayTime -= TIMEMANAGER->getElapsedTime();
	}
	else
	{
		EffectAndItemObject* deadEffect= new EffectAndItemObject;
		deadEffect->init(EFFECT_DIE, RND->getFromFloatTo(getX() - getWidth() / 2, getX() + getWidth() / 2), RND->getFromFloatTo(getY() - getHeight() / 2, getY() + getHeight() / 2));
		_player->setFight(false);
		setDestroy(true);
		manaCoinDrop();
	}

}
void flower::idleUpdate()
{

	_AttackDelayTime -= TIMEMANAGER->getElapsedTime();

	if (_AttackDelayTime <= 0)
	{
		if (getDistance(_player->getX(), _player->getY(), getX(), getY()) < _enemyDetectDistance)
		{
			_gameAni->setState(ATTACK);
			setAttack();
		}
	}
}
void flower::setAttack()
{
	_AttackDelayTime = 4.0f;
	Seed* seed = new Seed;
	seed->init(getX(), getY());
	SOUNDMANAGER->play("shot02", 1.0f);
}
void flower::attackUpdate()
{
	_AttackDelayTime -= TIMEMANAGER->getElapsedTime();


	if (_AttackDelayTime < 2.5f)
		_gameAni->setState(IDLE);
}

