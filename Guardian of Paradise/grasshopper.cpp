#include "stdafx.h"
#include "grasshopper.h"


grasshopper::grasshopper()
{
}


grasshopper::~grasshopper()
{
}
HRESULT grasshopper::init(float x, float y)
{
	setUp(x, y, TILESIZE*MULTIPLY_X, TILESIZE* MULTIPLY_Y, "monster", "grasshopper", 2.0f, IDLE);
	setName("grasshopper");

	//애니메이션 등록
	//IDLE
	int leftIdle[] = { 0, 1, 2 };
	_gameAni->SetArrayFrameAnimation(DIR_LEFT, IDLE, leftIdle, 3, 6, true);
	int rightIdle[] = { 6, 7, 8 };
	_gameAni->SetArrayFrameAnimation(DIR_RIGHT, IDLE, rightIdle, 3, 6, true);

	//JUMP
	int leftJump[] = { 3, 4, 5 };
	_gameAni->SetArrayFrameAnimation(DIR_LEFT, JUMP, leftJump, 3, 3, true);
	int rightJump[] = { 9, 10, 11 };
	_gameAni->SetArrayFrameAnimation(DIR_RIGHT, JUMP, rightJump, 3, 3, true);


	//BEING HIT
	int downHit[] = { 12, 13 };
	_gameAni->SetArrayFrameAnimation(DIR_ALL, HIT, downHit, 2, 10, true);

	//BEING DEAD
	int downDead[] = { 12, 14 };
	_gameAni->SetArrayFrameAnimation(DIR_ALL, DIE, downDead, 2, 15, true);


	_gameAni->setDirection(DIR_LEFT);
	_element = ELEMENTAL_MONSTER_EARTH;
	//스텟
	_Hp = _maxHp = 2;
	_enemyDetectDistance = 250;

	return S_OK;
}
void grasshopper::update()
{
	enemy::update();
	switch (_gameAni->getState())
	{
	case JUMP:
		JumpUpdate();
		break;
	}

}

void grasshopper::render(float x, float y)
{
	gameCharacter::render(x, y);
}
void grasshopper::onCollideEnter(gameObject* object)
{
	gameCharacter::onCollideEnter(object, false, true);
}
void grasshopper::idleUpdate()
{
	if (getDistance(_player->getX(), _player->getY(), getX(), getY()) < _enemyDetectDistance)
	{
		if (_idleDelayTime <= 0)
		{
			setJump((DIRECTION)RND->getInt(2));
		}
		else
		{
			_idleDelayTime -= TIMEMANAGER->getElapsedTime();
		}
	}
}
void grasshopper::setJump(gameObject* gObject)
{
	SOUNDMANAGER->play("jump01", 1.0f);
	setObjectAngle(getAngle(gObject->getX(), gObject->getY(), getX(), getY()));
	if (getObjectAngle() > PI / 2 && getObjectAngle() <= (PI / 2) * 3)
	{
		_gameAni->setDirection(DIR_LEFT);
	}
	else
		_gameAni->setDirection(DIR_RIGHT);



	_hitSpeedX = 15.0f;
	_hitSpeedY = 20.0f;
	_hitDelayTime = 1.5f;
	if (_initialHitPushbackTime <= 0)
		_initialHitPushbackTime = 0.5f;

	_gameAni->setState(JUMP);
}
void grasshopper::setJump(DIRECTION direction)
{
	SOUNDMANAGER->play("jump01", 1.0f);
	if (direction == DIR_LEFT)
	{
		setObjectAngle(RND->getFromFloatTo((PI / 4) * 3, (PI / 4) * 5));
		_gameAni->setDirection(DIR_LEFT);
	}
	else if (direction ==DIR_RIGHT)
	{
		setObjectAngle(RND->getFromFloatTo((PI / 4) * 7, (PI / 4) * 9));
		_gameAni->setDirection(DIR_RIGHT);
	}

	_hitSpeedX = 15.0f;
	_hitSpeedY = 20.0f;
	_hitDelayTime = 1.5f;
	if (_initialHitPushbackTime <= 0)
		_initialHitPushbackTime = 0.5f;

	_gameAni->setState(JUMP);
	_jumpDelayTime = 0.5f;
}
void grasshopper::JumpUpdate()
{
	paravola();
	if (_jumpDelayTime > 0)
		_jumpDelayTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		_gameAni->setState(IDLE);
		_idleDelayTime = 0.1f;
	}


}
