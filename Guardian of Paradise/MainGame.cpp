#include "stdafx.h"
#include "MainGame.h"
#include "cutScene.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::init()
{
	_gameScreenEffect = new gameScreenEffect;
	//��Ƽ���� �θ� ��
	if (GQUESTMANAGER->getIsContinue())
	{
		_mapPath = GQUESTMANAGER->getCurrentMapPath();
		std::ifstream fs("map\\" + _mapPath);
		cereal::XMLInputArchive iArchive(fs);


		iArchive(_map);

		GQUESTMANAGER->addGameQuests(_mapPath, *_map->getGameQuestSet(), _map);
		SOUNDMANAGER->play(_map->getBGMKey(), 5.0f);
		_map->init();
		GQUESTMANAGER->setUpGameObject();
		GQUESTMANAGER->setPlayerInit();
		_gameScreenEffect->init(FADE_OUT);
	}
	//���� ���� ��
	else
	{
		_mapPath = "";
		std::ifstream fs("map\\01.xml");
		cereal::XMLInputArchive iArchive(fs);

		iArchive(_map);

		GQUESTMANAGER->clearGameQuests();
		GQUESTMANAGER->addGameQuests("01.xml", *_map->getGameQuestSet(), _map);
		SOUNDMANAGER->play(_map->getBGMKey(), 5.0f);
		_map->init();

		GQUESTMANAGER->setUpGameObject();
		GQUESTMANAGER->setPlayerInit();

		GQUESTMANAGER->getCutScene()->showCutScene(INTRO_1);

	}

	_gameCamera = new gameCamera;
	_gameCamera->init(false, _map->boundingBox());
	_gameCamera->onCamera();
	_map->linkAdressCameraObject(_gameCamera);

	_gameUI = new gameUI;
	_gameUI->init(GQUESTMANAGER->getPlayer());


	_gameCamera->onFocus(GQUESTMANAGER->getPlayer(), false);

	_destroyEventCallback = std::bind(&MainGame::destroyAllButPlayer, this, std::placeholders::_1);
	GOBJECTMANAGER->addGameEvent("NextMap", &_destroyEventCallback);





	GOBJECTMANAGER->addGameObjectListToVecter();
	GOBJECTMANAGER->setRenderOrder();
	return S_OK;
}


void MainGame::release()
{
	SAFE_RELEASE(_gameCamera);
	SAFE_RELEASE(_gameUI);
	SAFE_RELEASE(_gameScreenEffect);
}
void MainGame::update()
{





	if (GQUESTMANAGER->isOkayToUpdate())
	{
		_gameUI->update();
		_gameScreenEffect->update();

		if (_gameScreenEffect->getCurrentEFFECT() != FADE_IN)
		{
			_gameCamera->update();

			checkAndJumpToNextMap(
				PointMake(GQUESTMANAGER->getPlayer()->getX() / (TILESIZE * MULTIPLY_X),
				GQUESTMANAGER->getPlayer()->getY() / (TILESIZE*MULTIPLY_Y)));




		
		}
		else if (_gameScreenEffect->getCurrentEFFECT() == FADE_IN
			&&  _gameScreenEffect->getEffectTime() < 0)
		{
			jumpToNextMap();
		}
		


	}

	GQUESTMANAGER->update();

}
void MainGame::render()
{

	_gameCamera->render();
	_gameUI->render();
	

	GQUESTMANAGER->render();
	_gameScreenEffect->render();
}


//�׽� üũ�� �ϴ±� ��ü�� ��� ������. ��Ȯ�� �Ͼ�� �������� ������Ʈ�� �ؼ� Ȯ���� �� ��� �ϴµ� �̷������� �ﰢ�ϴ°� ���� �ٶ��� ���� ������ ����.
//������ �ܺο��� �ϴ� �Ŷ�� �� �����͸� ���⿡ ������ �̷��� ����üũ�� �ѱ�°� �̱��濡�� ���ִ°� ���? 
//�� üũ�� �� ���ο��� �ϰ� üũ�ؼ� �ѱ�� �Ϸ��� ���μ����� �̱��� ����Ʈ �޴����� �� �ִ°ɷ�.
//����Ʈ �޴��� ������ ��ɺ��� ��� Ȯ��Ǵ� �����̴�.
//��ǻ� �̳༮�� ���� ���Ͷ�� �θ� ���� �ְڴ�.
//�׷����� ���̵��� // ���̵� �ƿ� ���õ� ����Ʈ �޴����� �ٷ�� ��� �Ѵ�.
//�׳� �����ϰ� �����ϴ� �ɷ� �ص� ������ �ȵɰŶ� ����������....

void MainGame::checkAndJumpToNextMap(POINT point)
{
	if (GQUESTMANAGER->getPlayer()->getGameAnimation()->getState() == FALL &&
		!GQUESTMANAGER->getPlayer()->getGameAnimation()->isPlay())
	{
		_gameScreenEffect->init(FADE_IN);
		return;
	}



	if (GQUESTMANAGER->getPlayer()->getGameAnimation()->getState() != FALL)
	{
		_mapPath = "";

		//left == 0
		if (point.x < 0)
		{
			_mapPath = _map->getMapLink()[0];
			_playerPath = 0;
		}
		//right ==1
		if (point.x >= _map->getTileX())
		{
			_mapPath = _map->getMapLink()[1];
			_playerPath = 1;
		}
		//top ==2
		if (point.y < 0)
		{
			_mapPath = _map->getMapLink()[2];
			_playerPath = 2;
		}
		//bottom ==3
		if (point.y >= _map->getTileY())
		{
			_mapPath = _map->getMapLink()[3];
			_playerPath = 3;
		}





		for (vector<tagPortalInfo>::iterator iter = _map->getPortalSet()->begin(); iter != _map->getPortalSet()->end(); iter++)
		{

			RECT temp;
			if (IntersectRect(&temp, &_map->_mapdata[iter->currentIndexY][iter->currentIndexX].boundingBox(), &GQUESTMANAGER->getPlayer()->boundingBox()))
			{
				_mapPath = iter->portalMapLink;
				_playerPath = 4;
				_portalNext.x = iter->_nextIndexX;
				_portalNext.y = iter->_nextIndexY;
				break;
			}

		}




		if (_mapPath == "")
			return;
		else
			_gameScreenEffect->init(FADE_IN);

	}
	

}
void MainGame::jumpToNextMap()
{
	string compareBGM = _map->getBGMKey();

	GOBJECTMANAGER->activateEvent("NextMap");
	GOBJECTMANAGER->removeGameObject();

	{
		std::ifstream fs("map\\" + _mapPath);
		cereal::XMLInputArchive iArchive(fs);
		iArchive(_map);
	}
	GQUESTMANAGER->addGameQuests(_mapPath, *_map->getGameQuestSet(), _map);
	if (compareBGM != _map->getBGMKey())
	{
		SOUNDMANAGER->stop("boss01.mid");
		SOUNDMANAGER->stop("boss02.mid");
		SOUNDMANAGER->stop(compareBGM);
		SOUNDMANAGER->play(_map->getBGMKey(), 5.0f);
	}
	_map->init();

	GQUESTMANAGER->setUpGameObject();

	switch (_playerPath)
	{
		//left -> right
	case 0:
		GQUESTMANAGER->getPlayer()->setX(_map->getWidth() - TILESIZE*MULTIPLY_X);
		break;
		//right - >left
	case 1:
		GQUESTMANAGER->getPlayer()->setX(0);
		break;
		//top->bottom
	case 2:
		GQUESTMANAGER->getPlayer()->setY(_map->getHeight() - TILESIZE*MULTIPLY_Y);
		break;
		//bottom ->top
	case 3:
		GQUESTMANAGER->getPlayer()->setY(0);
		break;
	case 4:
		GQUESTMANAGER->getPlayer()->setX(_portalNext.x * TILESIZE*MULTIPLY_X);
		GQUESTMANAGER->getPlayer()->setY(_portalNext.y *  TILESIZE*MULTIPLY_Y);
		break;
	}

	GQUESTMANAGER->setPlayerMapLocation();
	_gameCamera->setMapSize(_map->boundingBox());
	_gameCamera->onFocus(GQUESTMANAGER->getPlayer(), false);
	_map->linkAdressCameraObject(_gameCamera);
	_gameScreenEffect->init(FADE_OUT);




	GOBJECTMANAGER->addGameObjectListToVecter();
	GOBJECTMANAGER->setRenderOrder();
}
void MainGame::destroyAllButPlayer(gameObject* object)
{
	if (object->getTag() != "player" && object->getTag() != "interact")
		object->setDestroy(true);
}