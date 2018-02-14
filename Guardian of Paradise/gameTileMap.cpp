#include "stdafx.h"
#include "gameTileMap.h"
#include "AbilityObject.h"

///////////////////////////////////////////////////monster//////////////////////////////////////////////////////////
#include "Slime.h"
#include "Flower.h"
#include "fly.h"
#include "Turtle.h"
#include "grasshopper.h"
#include "Shell.h"
#include "ForestBoss.h"
#include "ForestMiniBoss.h"
#include "tentacle.h"
////////////////////////////////////////////////////object//////////////////////////////////////////////////////////
#include "EnviromentObject.h"
#include "EffectAndItemObject.h"
CEREAL_REGISTER_TYPE(gameTileMap);
gameTileMap::gameTileMap()
{
}
gameTileMap::~gameTileMap()
{
}
HRESULT gameTileMap::init()
{

	for (int i = 0; i < _tileY; i++)
		for (int j = 0; j < _tileX; j++)
			_mapdata[i][j].ScaleTo();

	_isColliderOn = true;
	setWidth(_tileX * TILESIZE * MULTIPLY_X);
	setHeight(_tileY * TILESIZE * MULTIPLY_Y);
	GOBJECTMANAGER->addGameObject(this);
	_Ingame = true;

	setZ(1);

	for (int i = 0; i < _vObject.size(); i++)
	{
		if (_vObject[i].questIndex != 0)
			continue;
		EnviromentObject* object;

		switch (_vObject[i].objectSelect)
		{
			case WOOD_BLOCK: 
			case WOOD_ROOT: 
			case HINTMINT: 
			case MUSHIBOING: 
			case FRAMED_NPC: 
			case NPC:
			case STONE_MOVABLE: 
			case STONE_MOVABLE_ONCE:
			case STONE_BOARD: 
			case SPIKE_MOVABLE:
			case ENVIROMENT_HOME:
			case ENVIROMENT_GRASS:
			case PUZZLE_NUMBERBLOCK:
			case BUTTON_ONCE: 
			case BUTTON_KEEP:
			case BUTTON_ROBUST:
				object = new EnviromentObject;
				object->init(_vObject[i]);
				break;

		}
	}
	//이제 이렇게 몬스터 그냥 백터로 뿌리지 않아요.
	for (int i = 0; i < _vMonster.size(); i++)
	{
		enemy* baseEnemy;
		switch (_vMonster[i].monsterSelect)
		{
			case CRAP : break;
			case FLOWER:
				baseEnemy = new flower;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case FLY:
				baseEnemy = new fly;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case FOREST_BOSS: 
				baseEnemy = new ForestBoss;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case FOREST_BOSS_TENTACLE:
				baseEnemy = new tentacle;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case FOREST_MINIBOSS:
				baseEnemy = new ForestMiniBoss;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case FROG: break;
			case GRASSHOPPER: 
				baseEnemy = new grasshopper;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case SHELL_MONSTER: 
				baseEnemy = new Shell;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case SLIME: 
				baseEnemy = new Slime;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case TURTLE:		
				baseEnemy = new Turtle;
				baseEnemy->init(_vMonster[i].x * MULTIPLY_X, _vMonster[i].y * MULTIPLY_Y);
				break;
			case WATER_BOSS: break;
			case WATER_MINIBOSS: break;
			case WATER_SHELL_MONSTER: break;
			case WATER_FLOG: break;
		}
		
	}

	return S_OK;
}
HRESULT gameTileMap::init(int tileSelection, int tileX, int tileY)
{

	_tileY = tileY;
	_tileX = tileX;
	_showTile = false;
	char sResult[128];
	sprintf(sResult, "t_%d", tileSelection);


	//기본 타일 셋팅
	for (int i = 0; i < MAXTILEY; i++)
		for (int j = 0; j < MAXTILEX; j++)
			//gameObject
			_mapdata[i][j].init(tileSelection, j, i, TR_GROUND);
	
	for (int i = 0; i < 4; i++)
		_aMapLink[i] = "";



	gameObject::init("tileMap", 0, 0, _tileX * TILESIZE, _tileY * TILESIZE, 0, 0, true);
	_Ingame = false;
	return S_OK;
}

void gameTileMap::update()
{
	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{

			_mapdata[i][j].update(_Ingame);
		}
	}

	if (!_Ingame)
	{
		for (int i = 0; i < _vPortal.size(); i++)
		{
			_vPortal[i].nextXBox->update();
			_vPortal[i].nextYBox->update();

		}

		if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
			_showTile = true;
		else if (KEYMANAGER->isOnceKeyUp(VK_CONTROL))
			_showTile = false;

	}
}
void gameTileMap::release()
{
	_vMonster.clear();
	_vPortal.clear();
	for (int i = 0; i < MAXTILEY; i++)
	{
		for (int j = 0; j < MAXTILEX; j++)
		{
			_mapdata[i][j].release();
		}
	}
}
void gameTileMap::render()
{
	//지형뿌림
	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{

			_mapdata[i][j].render();
		}
	}
}
void gameTileMap::render(float x, float y)
{

	if (_Ingame)
	{
		//지형뿌림
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				RECT rcTemp;
				if (!(IntersectRect(&rcTemp, &_mapdata[i][j].boundingBox(), &_gameCamera->getCameraView())))
					continue;
				_mapdata[i][j].render(_Ingame, x, y);
			}
		}
	}
	else
	{
		char temp[80];
		for (int i = 0; i < _tileY; i++)
		{
			for (int j = 0; j < _tileX; j++)
			{
				_mapdata[i][j].render(_Ingame, x, y, _showTile);

			}
		}
		//Monster
		char sResult[120];
		for (int i = 0; i < _vMonster.size(); i++)
		{
			sprintf(sResult, "monster_%d", _vMonster[i].monsterSelect);
			IMAGEMANAGER->findImage(sResult)->frameRender(getMemDC(), _vMonster[i].x  + x, _vMonster[i].y + y, 0, 0);
		}


		//Object, better then Monster(XD)
		for (int i = 0; i < _vObject.size(); i++)
			IMAGEMANAGER->findImage(_vObject[i].objectImageFile)->frameRender(getMemDC(), _vObject[i].x + x, _vObject[i].y + y, _vObject[i].objectImageIndexX, _vObject[i].objectImageIndexY);

		//Portal
		for (int i = 0; i < _vPortal.size(); i++)
		{
			IMAGEMANAGER->findImage("PortalAlpha")->alphaRender(getMemDC(),
				_mapdata[_vPortal[i].currentIndexY][_vPortal[i].currentIndexX].getX() + x,
				_mapdata[_vPortal[i].currentIndexY][_vPortal[i].currentIndexX].getY() + y, 100);

			_vPortal[i].nextXBox->render(x + _vPortal[i].nextXBox->boundingBox().left, y + _vPortal[i].nextXBox->boundingBox().top);
			_vPortal[i].nextYBox->render(x + _vPortal[i].nextYBox->boundingBox().left, y + _vPortal[i].nextYBox->boundingBox().top);
		}
	}
}

void gameTileMap::onCollideEnter(gameObject* gObject)
{
	RECT temp;
	POINT collideTile1;
	POINT collideTile2;
	float angle;
	DIRECTION direction;
	if (gObject->getTag() == "player" )
	{

		Player* player = (Player*)gObject;
		direction = player->getGameAnimation()->getDirection();

		switch (direction)
		{
		case  DIR_LEFT:
			collideTile1.y =static_cast<LONG> (gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG> (gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG> (gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));
			break;
		case DIR_RIGHT:
			collideTile1.y = static_cast<LONG> (gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG>(gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG>(gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		case DIR_UP:
			collideTile1.y = static_cast<LONG>(gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG>(gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG> (gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG> (gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		case DIR_DOWN:
			collideTile1.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG> (gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG> (gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		default:
			collideTile1.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG> (gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG> (gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		}

		//일단 기본적으로 전부 사각형일테니깐...
		if (IntersectRect(&temp,
			&RectMake(gObject->getX() ,gObject->getY() , gObject->getWidth()-8 , gObject->getHeight() ),
			&_mapdata[collideTile1.y][collideTile1.x].boundingBox()))
			_mapdata[collideTile1.y][collideTile1.x].onCollideEnter(gObject);
		if (IntersectRect(&temp, 
			&RectMake(gObject->getX(), gObject->getY(), gObject->getWidth() - 8, gObject->getHeight()),
			&_mapdata[collideTile2.y][collideTile2.x].boundingBox()))
			_mapdata[collideTile2.y][collideTile2.x].onCollideEnter(gObject);
	}
	else
	{

		angle = gObject->getObjectAngle();

		if (angle< PI / 4 || angle >(PI / 4) * 7)
				direction =DIR_RIGHT;
		else if (angle >= PI / 4 && angle< (PI / 4) * 3)
				direction =DIR_UP;
		else if (angle >= (PI / 4) * 3 && angle< (PI / 4) * 5)
				direction =DIR_LEFT;
		else if (angle >= (PI / 4) * 5 && angle < (PI / 4) * 7)
				direction =DIR_DOWN;

		switch (direction)
		{
		case  DIR_LEFT:
			collideTile1.y = static_cast<LONG>(gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG>(gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG>(gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG>(gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));
			break;
		case DIR_RIGHT:
			collideTile1.y = static_cast<LONG>(gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG>(gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG>(gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG> (gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		case DIR_UP:
			collideTile1.y = static_cast<LONG>(gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG>(gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG> (gObject->boundingBox().top / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG>(gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		case DIR_DOWN:
			collideTile1.y = static_cast<LONG> (gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile1.x = static_cast<LONG> (gObject->boundingBox().left / (TILESIZE * MULTIPLY_X));

			collideTile2.y = static_cast<LONG>(gObject->boundingBox().bottom / (TILESIZE * MULTIPLY_Y));
			collideTile2.x = static_cast<LONG>(gObject->boundingBox().right / (TILESIZE * MULTIPLY_X));
			break;
		}

		//일단 기본적으로 전부 사각형일테니깐...
		if (IntersectRect(&temp,
			&gObject->boundingBox(),
			&_mapdata[collideTile1.y][collideTile1.x].boundingBox()))
			_mapdata[collideTile1.y][collideTile1.x].onCollideEnter(gObject);
		if (gObject != NULL)
		{
			if (IntersectRect(&temp,
				&gObject->boundingBox(),
				&_mapdata[collideTile2.y][collideTile2.x].boundingBox()))
				_mapdata[collideTile2.y][collideTile2.x].onCollideEnter(gObject);
		}
	}

}
