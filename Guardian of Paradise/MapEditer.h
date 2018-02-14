#pragma once
#include "gameTileMap.h"
#include "gameButton.h"
#include "gameFont.h"
#include "gameCamera.h"
#include "optionPanel.h"
#include "objectPanel.h"
#include "menuBar.h"
#define TILESETNUMBER 10

//타일샘플 이미지에서 가져올 타임
#define SAMPLESTARTX WINSIZEX - (SAMPLETILEX * TILESIZE)
#define SAMPLESTARTY 0




enum DROW_SELECT
{
	TILE,
	OBJECT,
	MONSTER,
	OPTION,
	DROW_END
};

struct tagSampleMonster
{
	RECT rcMonster;
	MONSTER_SELECT monsterSelect;

};

//타일을 그려올 타일이미지 모음
//내가 지금 뭐 클릭했는지 알고 처리할려면 이거 있는게 좋다.
struct tagSampleTile
{
	RECT rcTile;
	TERRAINTYPE terrain;
	int terrainFrameX;
	int terrainFrameY;
};


//일종의 에디터 UI클레스라고도 볼 수 있고.
//가령 맵이 화면 사이즈 이상 커질 경우, UI 에 해당되는 이기능들은 여기에 존재하는게 맞다.
//UI 표시 관련 클레스 따로 클리핑및 기능 구현 따로 클래스 구현을 하는게 어떨까 한다.
class MapEditer : public gameNode
{

	bool _isDrag;
	RECT _DragArea;
	bool _isPicking;
	RECT _pickingArea;
	bool _isMapRoamming;
	RECT _MapRoammingArea;


	image* _backGround;
	image* _sampleTileBackGround;

	//타일셋이 저장된 이미지들
	image* _tileImageSet[TILESETNUMBER];
	//클릭해서 지정할 타일들
	tagSampleTile _sampleTiles[SAMPLETILEY][SAMPLETILEX];
	tagSampleMonster _sampleMonster[MONSTER_END];
	//맵 에디터에서 선택한 타일 셋
	int _tileSetSelection;

	//맵 에디터에서 선택한 영역
	int _currentStartTileX;
	int _currentStartTileY;
	int _currentEndTileX;
	int _currentEndTileY;
	//멥 에디터에서 선택한 몬스터인덱스
	int _currentMonster;
	


	//////////////////////////////////////////UI////////////////////////////////////////////////////////////////
	menuBar* _menuBar;

	gameButton* _prevButton;
	BUTTON_CALLBACK _prevCallback;
	gameButton* _nextButton;
	BUTTON_CALLBACK _nextCallback;

	//타일 오브젝트 말고 다른 것도 선택하게 만들어야하기 때문
	DROW_SELECT _drowState;
	gameButton* _tileTap;
	BUTTON_CALLBACK _tileTapCallback;
	gameButton* _objectTap;
	BUTTON_CALLBACK _objectTapCallback;
	gameButton* _monsterTap;
	BUTTON_CALLBACK _monsterCallback;
	gameButton* _optionTap;
	BUTTON_CALLBACK _eventCallback;
	//에디터 최초로 클래스로 나눈것.. (T.T)
	optionPanel* _optionPanel;
	objectPanel* _objectPanel;


	//맵을 상대좌표로 렌더해줄 게임 카메라.
	gameCamera* _gameCamera;



	/////////////////////////////////////////////////////////데이터로 저장할 정보//////////////////////////////////////////////////////////////////////
	//맵에디터로 저장할 맵데이타
	shared_ptr<gameTileMap> _gameTileMap;
public:
	string _currentFilePath;

public:
	MapEditer();
	~MapEditer();

	HRESULT init();


	void release();
	void update();
	void render();

	

	void selectedShow(void);
	void sampleTerrainSet(void);
	void sampleMonsterSet(void);
	void sampleMonsterRender(void);

	//버튼 콜백 함수.
	void setBasicMapInfo(void);
	void save(void);
	void load(void);
	void exit(void)
	{
		SCENEMANAGER->changeScene("menuScene");
	}
	void prev(void)
	{
		if (_drowState == TILE)
		{
			if (_tileSetSelection < TILESETNUMBER - 1)
			{
				_tileSetSelection++;
				sampleTerrainSet();
			}
		}

	}
	void next(void)
	{
		if (_drowState == TILE)
		{
			if (_tileSetSelection > 0)
			{
				_tileSetSelection--;
				sampleTerrainSet();
			}
		}
	}
	
	//////////////////////////////////////_drowState CHANGE///////////////////////////////////////////////////////////////////
	inline void setTileSelect(void)
	{
		_drowState = TILE;
		_isDrag= false;
		_isPicking = false;
	}
	inline void setObjectSelect(void)
	{
		_drowState = OBJECT;
		_isDrag = false;
		_isPicking = false;
	}
	inline void setMonsterSelect(void)
	{
		_drowState = MONSTER;
		_isDrag = false;
		_isPicking = false;
	}
	inline void setEventSelect(void)
	{
		_drowState = OPTION;
		_isDrag = false;
		_isPicking = false;
	}
	///////////////////////////////////////OPTION FUNCTIONS///////////////////////////////////////////////////////////////////////////
	void onClickDown();
	void onClickUp();
	void onClickStay();
	////////////////////////////////////////////////////GETTER, SETTER/////////////////////////////////////////////////////////////

	inline gameTileMap& getGameTileMap(void){ return* _gameTileMap; }
	inline bool getIsPicking(void){ return _isPicking; }
	inline void setIsPicking(bool isPicking){ _isPicking = isPicking; }
	inline bool getIsMapRoamming(void){ return _isMapRoamming; }
	inline void setIsMapRoamming(bool isMapRoamming){ _isMapRoamming = isMapRoamming; }
	inline void setPickingArea(RECT rect){ _pickingArea = rect; }
	inline RECT* getMapRoamingArea(void) { return & _MapRoammingArea; }
	inline gameCamera* getGameCameraLocation(void) { return _gameCamera; }
};

