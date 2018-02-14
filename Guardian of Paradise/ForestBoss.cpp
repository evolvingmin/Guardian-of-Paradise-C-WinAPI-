#include "stdafx.h"
#include "ForestBoss.h"
#include "tentacle.h"
#include "gameTileMap.h"
ForestBoss::ForestBoss()
{
}


ForestBoss::~ForestBoss()
{
}
HRESULT ForestBoss::init(float x, float y)
{
	setUp(x, y, (TILESIZE * 2 - 10) *MULTIPLY_X, (TILESIZE * 2 - 10) * MULTIPLY_Y, "monster", "Forest_boss", 2.0f, IDLE);


	//애니메이션 등록
	//IDLE
	int downIdle[] = { 0, 1, 2 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, IDLE, downIdle, 3, 6, true);

	//BEING HIT
	int downHit[] = { 3 , 4 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, HIT, downHit, 2, 10, true);
	//BEING DEAD
	int downDead[] = { 3,5 };
	_gameAni->SetArrayFrameAnimation(DIR_DOWN, DIE, downDead, 2, 15, true);

	//스텟
	_Hp = _maxHp = 4;
	_gameAni->start();

	_element = ELEMENTAL_MONSTER_EARTH;


	tentacle* _tentacle = new tentacle;
	tentacle* _tentacle1 = new tentacle;
	tentacle* _tentacle2 = new tentacle;
	tentacle* _tentacle3 = new tentacle;


	_tentacle->init(getX()  -250, getY() - 100);
	_tentacle1->init(getX() + 300, getY() - 100);
	_tentacle2->init(getX() - 200, getY() + 100);
	_tentacle3->init(getX() + 250 , getY() + 100);

	_tantacles.push_back(_tentacle);
	_tantacles.push_back(_tentacle1);
	_tantacles.push_back(_tentacle2);
	_tantacles.push_back(_tentacle3);


	SOUNDMANAGER->stop(GQUESTMANAGER->getCurrentMap()->getBGMKey());

	SOUNDMANAGER->play("boss02.mid", 5.0f);
	//setDie();
	return S_OK;
}
void ForestBoss::update()
{
	enemy::update();
}


void ForestBoss::render(float x, float y)
{
	_gameAni->render(x, y);
}

void ForestBoss::onCollideEnter(gameObject* gObject)
{
	if (gObject->getTag() == "sword")
	{
		if (_initialHitPushbackTime <= 0)
		{
			RECT temp;
			IntersectRect(&temp, &gObject->boundingBox(), &this->boundingBox());
			EffectAndItemObject* HitEffect = new EffectAndItemObject;
			SOUNDMANAGER->play("kin01", 1.0f);
			HitEffect->init(EFFECT_HIT, temp.left, temp.top);
			if (_initialHitPushbackTime <= 0)
				_initialHitPushbackTime = 0.5f;

		}
	}
}
void ForestBoss::idleUpdate()
{
	if (_initialHitPushbackTime > 0)
	{
		_initialHitPushbackTime -= TIMEMANAGER->getElapsedTime();
	}


	for (vector<enemy*>::iterator iter = _tantacles.begin(); iter != _tantacles.end(); )
	{
		if ((*iter)->IsDeleted())
		{
			_tantacles.erase(iter);
		}
		else
		{
			if ((*iter)->getGameAnimation()->getState() == HIT || (*iter)->getGameAnimation()->getState() == DIE)
			{
				if (_tantacles.size() == 1 && (*iter)->getGameAnimation()->getState() == DIE)
				{
					setDie();
					break;
				}

				else
				{
					_gameAni->setState(HIT);
					_hitDelayTime = 2.0f;
					break;
				}

			}
			iter++;
		}
	}



}
void ForestBoss::setHit()
{

}

void ForestBoss::hitUpdate()
{
	if (_hitDelayTime > 0)
	{
		_hitDelayTime -= TIMEMANAGER->getElapsedTime();
	}
	else
	{
		_gameAni->setState(IDLE);
	}
}

void ForestBoss::setDie()
{
	_gameAni->setState(DIE);
	_deadDelayTime = 4.0f;
}
void ForestBoss::dieUpdate()
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
		SOUNDMANAGER->stop("boss02.mid");
		SOUNDMANAGER->play(GQUESTMANAGER->getCurrentMap()->getBGMKey(),5.0f);
		EffectAndItemObject* forest = new EffectAndItemObject;
		forest->init(tagObjectInfo((getCenterX()-35) / (MULTIPLY_X), getCenterY() / (MULTIPLY_Y), TILESIZE, TILESIZE,
			ITEM, OBJECT_ITEM_FOREST_EMBLEM, "itemObject", 0, 2));
	}

}