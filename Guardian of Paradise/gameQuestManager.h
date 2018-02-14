#pragma once
#include "singletonBase.h"
#include "image.h"

#include <vector>
#include <map>

//���α׷� �帧�� ���� ��ȹ�Ѵٸ�
//���� ���� �ε���, �׷� �� �ε��Ǵ� filepath�� Ű������ �Ͽ� string���� �����ϰ� �ʿ� �ִ� ����Ʈ ����� ��� 
//_mQuests�� ���� ����. �̷��� ��´ٸ� ��Ʈ������ �Ȱ��� �� ����Ʈ���� �����Ͽ� ���� ���� ����
//�̰����� ���� ���� ���̵� �Ѵ� �ϴ��� ���� ����Ʈ �Ŵ����� �ִ� ���� �������� ���� ���̰�, �� ����Ʈ �޴����� �����Ѵٸ� �װ� �ٷ� ���̺� ����.
//���� _vObjectSet�� ���� ó�� �ƹ� �������� �Ѹ��°� �ƴ�, �ƴ� ���� �� ��ü�� ���� �ƹ��������� �Ѹ��� ���� ����
//����, map�� init�ο��� ����Ʈ ������Ʈ ���� �ƴ����� �Ǻ��ѵ� �ƴѰ� �׳� �Ѹ� ����. ���� �װ� ����Ʈ �� ����� ���̶��,
//gameQuest�� ������� ����� ��

//�Ѹ��� ������ �� ����Ʈ �Ŵ������� ���� ����Ʈ ����� ������� �Ѹ� ������ �� �Ѹ� ������ ������ ����.

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

