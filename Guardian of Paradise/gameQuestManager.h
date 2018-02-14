#pragma once
#include "singletonBase.h"
#include "image.h"

#include <vector>
#include <map>

//프로그램 흐름을 먼저 계획한다면
//게임 맵이 로딩됨, 그럼 그 로딩되는 filepath를 키값으로 하여 string값을 생성하고 맵에 있는 퀘스트 목록을 담아 
//_mQuests에 넣을 거임. 이렇게 담는다면 스트링값이 똑같을 때 퀘스트값을 갱신하여 넣지 않을 것임
//이것으로 같은 맵을 재이동 한다 하더라도 원래 퀘스트 매니져에 있는 값을 덧쒸우진 않을 것이고, 이 퀘스트 메니져를 저장한다면 그게 바로 세이브 파일.
//맵의 _vObjectSet은 몬스터 처럼 아무 생각없이 뿌리는게 아님, 아니 몬스터 그 자체도 이제 아무생각없이 뿌리지 않을 거임
//정정, map의 init부에서 퀘스트 오브젝트 인지 아닌지를 판별한뒤 아닌건 그냥 뿌릴 거임. 만약 그게 퀘스트 와 연결된 것이라면,
//gameQuest가 영향력을 행사할 것

//뿌리기 이전에 이 퀘스트 매니져에서 받은 퀘스트 목록을 기반으로 뿌릴 것인지 안 뿌릴 것인지 결정할 것임.

class Player;
class gameQuest;
class cutScene;
class dialogWindow;
class saveWindow;
class pauseMenu;
class gameTileMap;
class EnviromentObject;
class EffectAndItemObject;

typedef vector<gameQuest> arrQuests;
typedef vector<gameQuest> :: iterator arrQuestsIter;

typedef map<string, arrQuests> arrQuest;
typedef map<string, arrQuests> ::iterator arrQuestIter;

class gameQuestManager : public singletonBase<gameQuestManager>
{
private:

	dialogWindow* _dialogWindow;
	saveWindow* _saveWindow;
	pauseMenu* _pauseMenu;
	cutScene* _cutScene;

	arrQuest _mQuests;
	string _currentFilePath;
	shared_ptr<gameTileMap> _currentMap;
	shared_ptr<Player> _player;

	
	bool _isMainGame;
	bool _isContinue;
	float _playerStartLocationX;
	float _playerStartLocationY;



public:

	gameQuestManager();
	~gameQuestManager();



	HRESULT init(void);
	
	void release(void);
	void update(void);
	void render(void);

	void clearGameQuests();
	void addGameQuests(string filePath, arrQuests localQuest, shared_ptr<gameTileMap> currentMap);
	void setUpGameObject();
	void checkQuestsCondition();
	void checkQuestCondition(EnviromentObject* questObject);
	void checkQuestCondition(EffectAndItemObject* questObject);
	void showDialog(EnviromentObject* TalkableObject);


	/////////////////////////////////////////////////////show load///////////////////////////////////////////////////////////////////////////////////////////
	void saveSetup();
	void loadSetup();
	void saveData(string filePath);
	void loadData(string filePath);
	/////////////////////////////////////////////////////////setter, getter////////////////////////////////////////////////////////////////////////////////////////////
	saveWindow* getSaveWindow(void){ return _saveWindow; }
	bool IsSaveWindowActive(void);
	dialogWindow* getDialogWindow(void){ return _dialogWindow; }
	cutScene* getCutScene(){ return _cutScene; }
	gameTileMap* getCurrentMap(){return _currentMap.get();}
	void setPlayerMapLocation(float x, float y){ _playerStartLocationX = x; _playerStartLocationY = y; }
	void setPlayerMapLocation(void);
	float getPlayerMapLocationX(void){ return _playerStartLocationX;}
	float getPlayerMapLocationY(void){ return _playerStartLocationY; }

	void setIsContinue(bool isContinue){ _isContinue = isContinue; }
	bool getIsContinue(void){ return _isContinue; }

	void setIsInGame(bool isInGame){ _isMainGame = isInGame; }
	bool getIsInGame(void){ return _isMainGame; }

	string getCurrentMapPath(void){return _currentFilePath;}
	bool isOkayToUpdate();
	void backToGame(void);

	///////////////////////////////////////////////////////////init for dynamic memebers///////////////////////////////////////////////////////
	void setWindowsInit(void);
	void setPlayerInit(void);
	Player* getPlayer(void);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};

