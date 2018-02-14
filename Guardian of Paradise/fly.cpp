#include "stdafx.h"
#include "fly.h"


fly::fly()
{
}


fly::~fly()
{
}
HRESULT fly::init(float x, float y)
{
	setUp(x, y, TILESIZE*MULTIPLY_X, TILESIZE* MULTIPLY_Y, "monster", "fly", 2.0f, ATTACK);
	setName("fly");

	//애니메이션 등록
	
	//MOVE
	int downIdle[] = {0,1,2 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, MOVE, downIdle, 3, 6, true);
	//MOVE
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, IDLE, downIdle, 3, 6, true);
//ATTACK
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, ATTACK, downIdle, 3, 12, true);

	//BEING DEAD
	int downDead[] = { 3,4,5 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, DIE, downDead, 3, 15, true);


	_element = ELEMENTAL_MONSTER_EARTH;
	//스텟
	_Hp = _maxHp = 1;
	_gameAni->start();
	_enemyDetectDistance = 300;
	_moveDelayTime = 3.0f;

	return S_OK;
}
void fly::update()
{
	enemy::update();
}
	
void fly::render(float x, float y)
{
	gameCharacter::render(x, y);
}
void fly::onCollideEnter(gameObject* object)
{
	gameCharacter::onCollideEnter(object, false, true);
}
void fly::setAttack()
{
	if (_gameAni->getState() != ATTACK)
	{
		if (getDistance(_player->getX(), _player->getY(), getX(), getY()) < _enemyDetectDistance)
		{
			_AttackDelayTime = 2.0f;
			setSpeed(8.0f);
			setObjectAngle(getAngle(getX(), getY(), _player->getX(), _player->getY()));
			_gameAni->setState(ATTACK);
			SOUNDMANAGER->play("bee01", 1.0f);
		}
		else
			setMove();
	}

}
void fly::attackUpdate()
{

	if (_AttackDelayTime > 0)
		_AttackDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		setMove();
	}

	setX(getX() + cosf(getObjectAngle())* getSpeed());
	setY(getY() - sinf(getObjectAngle()) * getSpeed() );

}
void fly::setMove()
{

	if (_gameAni->getState() != MOVE)
	{
		_gameAni->setState(MOVE);
		_moveDelayTime = 4.0f;
		setSpeed(5.0f);
		setObjectAngle(getAngle(getX(), getY(), _player->getX() + RND->getFromFloatTo(-150, +150), _player->getY() + RND->getFromFloatTo(-150, +150)));
	}


}
void fly::moveUpdate()
{

	if (_moveDelayTime > 0)
		_moveDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		setAttack();
	}

	if (getDistance(_player->getX(), _player->getY(), getX(), getY()) < _enemyDetectDistance)
		setAttack();

	setX(getX() + cosf(getObjectAngle())* getSpeed());
	setY(getY() - sinf(getObjectAngle()) * getSpeed());


}
void fly::setIdle()
{
	if (_gameAni->getState() != IDLE)
	{
		_gameAni->setState(IDLE);
		_idleDelayTime = 0.5f;
		setSpeed(4.0f);
	}

}
void fly::idleUpdate()
{
	if (_idleDelayTime > 0)
		_idleDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		setMove();
	}

}
void fly::manaCoinDrop(void)
{
	EffectAndItemObject* manas[1];

	for (int i = 0; i < 1; i++)
	{
		manas[i] = new EffectAndItemObject;
		manas[i]->init(ITEM_MP_EARTH, getX() + RND->getFromFloatTo(-20.0f, 20.0f), getY() + RND->getFromFloatTo(-20.0f, 20.0f), RND->getFromFloatTo(0, 2 * PI));
	}
}