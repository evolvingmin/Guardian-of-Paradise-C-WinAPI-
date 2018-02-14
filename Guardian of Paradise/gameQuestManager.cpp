#include "stdafx.h"
#include "gameQuestManager.h"
#include "gameQuest.h"
#include "gameTileMap.h"
#include "EnviromentObject.h"
#include "EffectAndItemObject.h"
#include "dialogWindow.h"
#include "saveWindow.h"
#include "pauseMenu.h"
#include "cutScene.h"
gameQuestManager::gameQuestManager()
{
}


gameQuestManager::~gameQuestManager()
{
}
HRESULT gameQuestManager::init(void)
{
	_isMainGame = false;
	_isContinue = false;
	return S_OK;
}
void gameQuestManager::setPlayerInit(void)
{
	if (_isContinue)
	{
		_player->init(_playerStartLocationX, _playerStartLocationY);
	}
	else
	{
		_player = make_shared <Player >();
		_playerStartLocationX = WINSIZEX / 2;
		_playerStartLocationY = WINSIZEY / 2;
		_player->init();
	}
	_isMainGame = true;
}
Player* gameQuestManager::getPlayer(void)
{
	return _player.get();
}

void gameQuestManager::setWindowsInit(void)
{
	_saveWindow = new saveWindow;
	_saveWindow->init();
	_dialogWindow = new dialogWindow;
	_dialogWindow->init();
	_pauseMenu = new pauseMenu;
	_pauseMenu->init();
	_cutScene = new cutScene;
	_cutScene->init();
}
bool gameQuestManager::IsSaveWindowActive(void)
{
	return _saveWindow->getIsActive();
}
void gameQuestManager::release(void)
{

}
void gameQuestManager::update(void)
{
	if (_isMainGame)
	{
		//MainGame
		if (_saveWindow->getIsActive() && KEYMANAGER->isOnceKeyDown('Q'))
		{
			backToGame();
		}

	}
	else
	{
		//mainMenu;
		if (_saveWindow->getIsActive() && KEYMANAGER->isOnceKeyDown('Q'))
		{
			backToGame();
		}

	}


	if (isOkayToUpdate())
	{
		if (_isMainGame)
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				saveSetup();
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				loadSetup();
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			_pauseMenu->setIsActive(true);
		}
	}


	
	checkQuestsCondition();
	_cutScene->update();
	_dialogWindow->update();
	_saveWindow->update();
	_pauseMenu->update();

}
void gameQuestManager::render(void)
{
	_saveWindow->render();
	_dialogWindow->render();
	_pauseMenu->render();
	_cutScene->render();
}
void gameQuestManager::clearGameQuests()
{
	_mQuests.clear();
}
//키 값으로 설정해서 초기화
void gameQuestManager::addGameQuests(string filePath, arrQuests localQuest, shared_ptr<gameTileMap> currentMap)
{
	if (_mQuests[filePath].empty())
	{
		arrQuests quests = localQuest;
		_mQuests[filePath] = quests;
	}
	_currentFilePath = filePath;
	_currentMap = currentMap;
}
void gameQuestManager::setUpGameObject()
{
	//맵의 init에 있는 몬스터 까는 연산이 여기에 올 것이다. 
	//마찬가지로 오브젝트 역시 여기 함수의 통제를 받게 된다.
	//일단 오브젝트만 여기서 깔아본다.

	for (int i = 0; i < _mQuests[_currentFilePath].size(); i++)
	{
		_mQuests[_currentFilePath][i].setRelatedGameObject(*_currentMap->getObjectSet());
	}
}
void gameQuestManager::checkQuestsCondition()
{
	for (int i = 0; i < _mQuests[_currentFilePath].size(); i++)
	{
		if (!_mQuests[_currentFilePath][i].getIsCalledCheck())
			_mQuests[_currentFilePath][i].checkQuestCondition();
	}
}
void gameQuestManager::checkQuestCondition(EnviromentObject* questObject)
{
	for (int i = 0; i < _mQuests[_currentFilePath].size(); i++)
	{
		if (questObject->getObjectInfo().questIndex == _mQuests[_currentFilePath][i].getUniqueNum())
		{
			_mQuests[_currentFilePath][i].checkQuestCondition();
			break;
		}
	}

	
}
void gameQuestManager::checkQuestCondition(EffectAndItemObject* questObject)
{
	for (int i = 0; i < _mQuests[_currentFilePath].size(); i++)
	{
		if (questObject->getQuestNum() == _mQuests[_currentFilePath][i].getUniqueNum())
		{
			_mQuests[_currentFilePath][i].checkQuestCondition();
			break;
		}
	}


}
void gameQuestManager::showDialog(EnviromentObject* TalkableObject)
{

	if (!_dialogWindow->getIsActive())
	{
		_dialogWindow->setIsActive(true);
		_dialogWindow->setTextToWindow(TalkableObject->getObjectInfo().npcDialogFile);
	}

}

bool gameQuestManager::isOkayToUpdate()
{
	if (!_saveWindow->getIsActive() && !_pauseMenu->getIsActive() && !_cutScene->getIsActive())
		return true;
	else
		return false;
}
void gameQuestManager::saveSetup()
{

	//윈도우 뛰우는거.
	_saveWindow->setIsActive(true);
	_dialogWindow->setIsActive(true);

	_saveWindow->setIsSave(true);
	_dialogWindow->setTextToWindow("info.txt");
	_dialogWindow->getText()->setCurrentPage(0);
		SOUNDMANAGER->play("kakunin", 1.0f);

}
void gameQuestManager::saveData(string filePath)
{
	std::ofstream fs("save//" + filePath);
	cereal::XMLOutputArchive oArchive(fs);

	oArchive(CEREAL_NVP(_mQuests));
	oArchive(CEREAL_NVP(_currentFilePath));
	oArchive(CEREAL_NVP(_playerStartLocationX));
	oArchive(CEREAL_NVP(_playerStartLocationY));
	oArchive(CEREAL_NVP(_player));

}
void gameQuestManager::loadSetup()
{
	_isContinue = true;
	_saveWindow->setIsActive(true);
	_dialogWindow->setIsActive(true);

	_saveWindow->setIsSave(false);
	_dialogWindow->setTextToWindow("info.txt");
	_dialogWindow->getText()->setCurrentPage(0);
}
void gameQuestManager::loadData(string filePath)
{
	std::ifstream fs("save//" + filePath);
	cereal::XMLInputArchive iArchive(fs);

	iArchive(_mQuests);
	iArchive(_currentFilePath);
	iArchive(_playerStartLocationX);
	iArchive(_playerStartLocationY);
	iArchive(_player);

	SCENEMANAGER->changeScene("mainGameScene");



}
void gameQuestManager::backToGame(void)
{
	_saveWindow->setIsActive(false);
	_dialogWindow->setIsActive(false);
	_isContinue = false;
}
void gameQuestManager::setPlayerMapLocation(void)
{
	_playerStartLocationX = _player->getX();
	_playerStartLocationY = _player->getY();

	_player->setFight(false);
	_player->getGameAnimation()->setState(IDLE);
}