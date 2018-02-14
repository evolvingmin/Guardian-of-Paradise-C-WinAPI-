#include "stdafx.h"
#include "enemy.h"
#include "EffectAndItemObject.h"
#include "Player.h"
enemy::enemy()
{
}


enemy::~enemy()
{
}

void  enemy::setUp(float x, float y, float width, float height, string tag, string imageName, float speed, STATE state)
{
	_enemyDetectDistance = 400.0f;
	_player =  (Player*)GOBJECTMANAGER->findGameObject("player");

	gameCharacter::init(tag, x, y, width, height, speed, 9, imageName, DIR_DOWN, state);
	addOpponentsTag("sword");
	addOpponentsTag("stamp");
	addOpponentsTag("heavy_stamp");
}
void enemy::update()
{
	if (_player == NULL)
		_player = GQUESTMANAGER->getPlayer();
	
	switch (_gameAni->getState())
	{
		case IDLE:
			idleUpdate();
			break;
		case HIT:
			hitUpdate();
			break;
		case DIE:
			dieUpdate();
			break;
		case ATTACK:
			attackUpdate();
			break;
		case MOVE:
			moveUpdate();
			break;
	}

	_gameAni->frameUpdate();
}

void enemy::render(  float x, float y)
{
	gameCharacter::render(x, y);
}
 void enemy::dieUpdate()
 {
	 gameCharacter::dieUpdate();
	 if (_deadDelayTime <=0)
		 _player->setFight(false);
 }

 void enemy::manaCoinDrop(void)
 {
	 EffectAndItemObject* manas[3];

	 for (int i = 0; i < 3; i++)
	 {
		 manas[i] = new EffectAndItemObject;
		 manas[i]->init(ITEM_MP_EARTH, getX() + RND->getFromFloatTo(-20.0f, 20.0f), getY() + RND->getFromFloatTo(-20.0f, 20.0f), RND->getFromFloatTo(0,2*PI));
	 }
 }