#pragma once
#include "gameTileMap.h"
#include "gameNode.h"
#include "gameCamera.h"
#include "Player.h"
#include "gameScreenEffect.h"
#include "gameUI.h"
#include "gameQuestManager.h"
#include "dialogWindow.h"


class MainGame : public gameNode
{
private :
	shared_ptr<gameTileMap> _map;

	

	string _mapPath;
	int _playerPath;
	POINT _portalNext;


	gameCamera* _gameCamera;
	gameUI* _gameUI;
	gameScreenEffect* _gameScreenEffect;
	METHOD_CALLBACK _destroyEventCallback;
public:
	//new GameÀÏ °æ¿ì.
	HRESULT init();
	void release();
	void update();
	void render();
	MainGame();
	~MainGame();


	void checkAndJumpToNextMap(POINT point);
	void jumpToNextMap();
	void destroyAllButPlayer(gameObject* object);
	//setter
	void setMapPath(string mapPath){ _mapPath = mapPath; }
	void setPlayerPath(int playerPath){_playerPath = playerPath;	}
	void setPortalNext(POINT portalNext) {_portalNext = portalNext;}
	//getter
	gameScreenEffect* getScreenEffectAddress(){return _gameScreenEffect;}
};

