#include "stdafx.h"
#include "gameTile.h"
#include "EffectAndItemObject.h"
#include "EnviromentObject.h"
#include "enemy.h"
#include "MainGame.h"
CEREAL_REGISTER_TYPE(gameTile);
gameTile::gameTile()
{

}


gameTile::~gameTile()
{
}

HRESULT gameTile::init(int tileSelection, int x, int y, TERRAINTYPE terrainType)
{
	_tileSelection = tileSelection;

	char cResult[128];
	sprintf(cResult, "t_%d", _tileSelection);
	_tileSetImage = IMAGEMANAGER->findImage(cResult);
	gameObject::init("mapTile", x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE, 0, 0 , false);
	_tileIndexX = x;
	_tileIndexY = y;
	_imageIndexX = 1;
	_imageIndexY = 0;
	_terrain = terrainType;


	



	return S_OK;
}
void gameTile::release()
{
	SAFE_RELEASE(_animation);
}
//������Ʈ
void gameTile::update(bool inGame)
{
	if (!inGame)
	{
		
	}
	else
	{
		switch (_terrain)
		{
		case TR_GROUND:
			break;
			//�ٸ��������� ���� ��
		case TR_DOOR:
			break;
			//�÷��̾ �� �� �ִ� Ǯ
		case	TR_PLANTS:
			break;
			//���� ������ ���������� ������
		case	TR_WATER:
			_animation->frameUpdate(TIMEMANAGER->getElapsedTime()* 1.0f);
			break;
			//�Ϲ����� ���ع� ����, ����� ����
		case	TR_OBJECT:
			break;
			//����, ������ ��� ���ϸ��̼ǰ� �Բ� �ٸ� �������� or Ȥ�� �ٽ� �� �� ����
		case	TR_CLIFF:
			break;
			//Ƚ��, �� �Ѽ�Ʈ�� ��Ÿ�ϸ� ����.�Ƚ�
		case	TR_JUMP:
			break;
			//������ �Ǳ����� ���ٴ�
		case	TR_PRECLIFF:
			break;
			//���� ��, �ƹ��͵� �ƴ� ���
		case	TR_NONE:
			break;
		}
	}
	
	
}
//����
void gameTile::render(void)
{
	switch (_terrain)
	{
	case TR_GROUND:
	case  TR_DOOR:
	case TR_OBJECT:
	case TR_CLIFF:
	case TR_JUMP:
		_tileSetImage->frameRender(getMemDC(), boundingBox().left, boundingBox().top, _imageIndexX, _imageIndexY);
		break;
	case	TR_PLANTS:
		_tileSetImage->frameRender(getMemDC(), boundingBox().left, boundingBox().top, _imageIndexX, _imageIndexY);
		break;
	case	TR_WATER:
		_tileSetImage->aniRender(getMemDC(), getX(), getY(), _animation);
		break;
	case	TR_PRECLIFF:
		break;

	case	TR_NONE:
		break;
	}
	
}
//����, ���� ���̵� ����ؼ� ��ǥ�� �ܺο��� �������� �ʿ䰡 �ִ�.
void gameTile::render(bool inGame, float x, float y, bool showNumber)
{
	if (!inGame)
	{
		
		_tileSetImage->frameRender(getMemDC(), x   + getX(), y + getY(), _imageIndexX, _imageIndexY);
		if (showNumber)
		{
			char temp[120];
			sprintf(temp, "%d", _tileIndexX);
			TextOut(getMemDC(), x + getX(), y + getY(), temp, strlen(temp));
			sprintf(temp, "%d", _tileIndexY);
			TextOut(getMemDC(), x + getX(), y + getY() + 12, temp, strlen(temp));
		}

	}
	else
	{
		switch (_terrain)
		{
		case TR_GROUND:
		case  TR_DOOR:
		case TR_OBJECT:
		case TR_CLIFF:
		case TR_JUMP:
			_tileSetImage->frameRender(getMemDC(), x + getX(), y + getY(), _imageIndexX, _imageIndexY);
			break;
			//�ٲ�߉�
		case	TR_PLANTS:
			_tileSetImage->frameRender(getMemDC(), x + getX(), y + getY(), _imageIndexX, _imageIndexY);
			break;
		case	TR_WATER:
			_tileSetImage->aniRender(getMemDC(), x + getX(), y +getY(), _animation);

			break;



		case	TR_PRECLIFF:
			_tileSetImage->frameRender(getMemDC(), x + getX(), y + getY(), _imageIndexX, _imageIndexY);
			break;

		case	TR_NONE:
			break;
		}
	}
	
}
//�浹ó��
void gameTile::onCollideEnter(gameObject* gObject)
{

	if (gObject->getTag() == "sword" )
	{
		switch (_terrain)
		{
		case TR_PLANTS :
			if (!_isPassable)
			{
				_imageIndexY = 4;
				_isPassable = true;
				
				EffectAndItemObject* leafLeft1 = new EffectAndItemObject;
				leafLeft1->init(EFFECT_LEAF_LEFT,getCenterX() - 40 -30, getY()+20);
				EffectAndItemObject* leafLeft2 = new EffectAndItemObject;
				leafLeft2->init(EFFECT_LEAF_LEFT, getCenterX() - 20 - 30, getY());
				EffectAndItemObject* leafRight1 = new EffectAndItemObject;
				leafRight1->init(EFFECT_LEAF_RIGHT, getCenterX() + 20 - 30, getY());
				EffectAndItemObject* leafRight2 = new EffectAndItemObject;
				leafRight2->init(EFFECT_LEAF_RIGHT, getCenterX() + 40 - 30, getY() + 20);
				SOUNDMANAGER->play("cut01", 1.0f);
				int rnd = RND->getFromIntTo(0, 100);
				 if (rnd > 90)
				{
					EffectAndItemObject* item = new EffectAndItemObject;
					item->init(ITEM_HP_CHICKEN, getCenterX() - 60, getY());


				}
				else if (rnd > 80)
				{
					EffectAndItemObject* item = new EffectAndItemObject;
					item->init(ITEM_HP_CHEESE, getCenterX() - 60, getY() );
					
				}
				else if (rnd    > 70)
				{
					EffectAndItemObject* item = new EffectAndItemObject;
					item->init(ITEM_HP_APPLE, getCenterX() - 60, getY());


				}


			}
			break;
		}
	}
	else if (gObject->getTag() == "stamp" || gObject->getTag() == "heavy_stamp")
	{
		switch (_terrain)
		{
		case TR_PLANTS:
			if (!_isPassable)
			{
				_imageIndexY = 4;
				_isPassable = true;

				EffectAndItemObject* leafLeft1 = new EffectAndItemObject;
				leafLeft1->init(EFFECT_LEAF_LEFT, getCenterX() - 40 - 30, getY() + 20);
				EffectAndItemObject* leafLeft2 = new EffectAndItemObject;
				leafLeft2->init(EFFECT_LEAF_LEFT, getCenterX() - 20 - 30, getY());
				EffectAndItemObject* leafRight1 = new EffectAndItemObject;
				leafRight1->init(EFFECT_LEAF_RIGHT, getCenterX() + 20 - 30, getY());
				EffectAndItemObject* leafRight2 = new EffectAndItemObject;
				leafRight2->init(EFFECT_LEAF_RIGHT, getCenterX() + 40 - 30, getY() + 20);

				int rnd = RND->getFromIntTo(0, 100);
				if (rnd > 90)
				{
					EffectAndItemObject* item = new EffectAndItemObject;
					item->init(ITEM_HP_CHICKEN, getCenterX() - 60, getY());


				}
				else if (rnd > 80)
				{
					EffectAndItemObject* item = new EffectAndItemObject;
					item->init(ITEM_HP_CHEESE, getCenterX() - 60, getY());

				}
				else if (rnd > 70)
				{
					EffectAndItemObject* item = new EffectAndItemObject;
					item->init(ITEM_HP_APPLE, getCenterX() - 60, getY());


				}


			}
			break;
		case TR_PRECLIFF:
			_terrain = TR_CLIFF;
			_imageIndexX = 3;
			_imageIndexY = 3;
			EffectAndItemObject* effects[4];
			for (int i = 0; i < 4; i++)
			{
				effects[i] = new EffectAndItemObject;
				effects[i]->init(EFFECT_CRASH_ROCK, getX() + 30, getCenterY(), i * (PI / 3));
			}
			break;
		}

	}
	else if (gObject->getTag() == "player")
	{
		RECT temp;
		Player* player = (Player*)gObject;
		switch (_terrain)
		{
		case TR_JUMP:
			if (IntersectRect(&temp, &gObject->boundingBox(), &RectMake(getX(), getY() + getHeight() - 2, getWidth(), 2)))
			{
				player->setJump((PI / 2) * 3);
				
			}

			break;
		case TR_CLIFF:
			if (!player->getOnBoard() && player->getGameAnimation()->getState()!=JUMP)
			{
				RECT temp;
				if (IntersectRect(&temp, &RectMake(player->getCenterX(),player->getCenterY(), 5,5), &boundingBox()))
				{
					MainGame* _maingame = (MainGame*)SCENEMANAGER->FindScene("mainGameScene");
					_maingame->setMapPath(GQUESTMANAGER->getCurrentMap()->getMapLink()[4]);
					_maingame->setPlayerPath(4);
					_maingame->setPortalNext(PointMake(_tileIndexX, _tileIndexY));
					GQUESTMANAGER->getPlayer()->setFall();
	
				}
				
			}
	
		case TR_GROUND:

			break;
		}
	}


	if (!_isPassable)
	{
		if (gObject->getTag() == "player" || gObject->getTag() == "monster")
		{
			
			gameCharacter* character = (gameCharacter*)gObject;
			if (character->getGameAnimation()->getState() != JUMP)
				isCollisionReaction(this, gObject);
			if (character->getGameAnimation()->getState() == HIT || character->getGameAnimation()->getState() == DIE)
			{
				gObject->setObjectAngle(getAngle(getX(), getY(), gObject->getX(), gObject->getY()));
				character->setHitSpeedX(character->getHitSpeedX() - 2.0f);
				character->setHitSpeedY(character->getHitSpeedY() - 2.0f);

			}
			else
			{
				if (character->getName() == "grasshopper")
					character->setJump(this);
				else if (character->getName() == "slime")
					character->setMove();
				else if (character->getName() == "fly")
					character->setIdle();
				else if (character->getName() == "turtle")
					character->setIdle();
			}

		}
		else if (gObject->getTag() == "monster_projectile")
		{
			gameCharacter* character = (gameCharacter*)gObject;

			if (character->getGameAnimation()->getState() != DIE)
			{
				EffectAndItemObject* effect = new EffectAndItemObject;
				effect->init(EFFECT_BLINCK, gObject->getX(), gObject->getY());
				
				gObject->setDestroy(true);
			}
			else
			{
				isCollisionReaction(this, gObject);
				gObject->setObjectAngle(getAngle(getX(), getY(), gObject->getX(), gObject->getY()));
				character->setHitSpeedX(character->getHitSpeedX() - 2.0f);
				character->setHitSpeedY(character->getHitSpeedY() - 2.0f);
			}
		}
		else if (gObject->getTag() == "stone_movable" || gObject->getTag() == "stone_movable_once")
		{
			isCollisionReaction(this, gObject);
			EnviromentObject* enviroment = (EnviromentObject*)gObject;
			enviroment->setMove(false);
		}
		//�ٸ� ���ε� �߰��� �� �ְ���. �� ������ �̷��� ���´ٸ� ������. ��� ������ ���� ELEMENTAL_CHANGE�� ���� �� �� �����ϱ�.
		else if (gObject->getTag() == "coin_earth")
		{
			isCollisionReaction(this, gObject);
			gObject->setObjectAngle(getAngle(getX(), getY(), gObject->getX(), gObject->getY()));
		}
	}


}


//MapEditer Initialize
void gameTile::setTileImage(int imageIndexX, int imageIndexY, int tileSelection)
{
	_imageIndexX = imageIndexX;
	_imageIndexY = imageIndexY;
	_tileSelection = tileSelection;
	char cResult[128];
	sprintf(cResult, "t_%d", _tileSelection);
	_tileSetImage = IMAGEMANAGER->findImage(cResult);
}
void gameTile::setTileImage()
{
	char cResult[128];
	sprintf(cResult, "t_%d", _tileSelection);
	_tileSetImage = IMAGEMANAGER->findImage(cResult);
}
//inGame Initialize
void gameTile::ScaleTo()
{

	char cResult[128];
	sprintf(cResult, "multiply_t_%d", _tileSelection);
	_tileSetImage = IMAGEMANAGER->findImage(cResult);
	setX(_tileIndexX * TILESIZE *MULTIPLY_X);
	setY(_tileIndexY * TILESIZE *MULTIPLY_Y);
	setWidth(TILESIZE *MULTIPLY_X);
	setHeight(TILESIZE *MULTIPLY_Y);
	setZ(1);

	int arr[3];

	switch (_terrain)
	{
	case TR_GROUND:
		_isPassable = true;
		break;
		//�ٸ��������� ���� ��
	case TR_DOOR:
		_isPassable = true;
		break;
		//�÷��̾ �� �� �ִ� Ǯ
	case	TR_PLANTS:
		//���̳� Ƚ�Ұ��� ������Ʈ�� ���� �߰� ���
		_isPassable = false;
		break;
		//���� ������ ���������� ������
	case	TR_WATER:
		//���̳� Ƚ�Ұ��� ������Ʈ�� ���� �߰� ���
		_animation = new animation;
		_animation->init(_tileSetImage->getWidth(), _tileSetImage->getHeight(), _tileSetImage->getFrameWidth(), _tileSetImage->getFrameHeight());
		arr[0] = SAMPLETILEX *_imageIndexY + _imageIndexX;
		arr[1] = SAMPLETILEX *_imageIndexY + _imageIndexX + 3;
		_animation->setFPS(1);
		_animation->setPlayFrame(arr, 2, true);
		_animation->start();
		_isPassable = false;
		break;
	case	TR_OBJECT:
		_isPassable = false;
		break;
		//����, ������ ��� ���ϸ��̼ǰ� �Բ� �ٸ� �������� or Ȥ�� �ٽ� �� �� ����
	case	TR_CLIFF:
		_isPassable = true;
		break;
	case	TR_JUMP:
		_isPassable = true;
		break;
		//������ �Ǳ����� ���ٴ�
	case	TR_PRECLIFF:
		_isPassable = true;
		break;
		//���� ��, �ƹ��͵� �ƴ� ���
	case	TR_NONE:
		_isPassable = false;
		break;
	}


}