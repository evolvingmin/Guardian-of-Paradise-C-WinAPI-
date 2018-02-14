#pragma once
#include "gameTileMap.h"
#include "gameButton.h"
#include "gameFont.h"
#include "gameCamera.h"
#include "optionPanel.h"
#include "objectPanel.h"
#include "menuBar.h"
#define TILESETNUMBER 10

//Ÿ�ϻ��� �̹������� ������ Ÿ��
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

//Ÿ���� �׷��� Ÿ���̹��� ����
//���� ���� �� Ŭ���ߴ��� �˰� ó���ҷ��� �̰� �ִ°� ����.
struct tagSampleTile
{
	RECT rcTile;
	TERRAINTYPE terrain;
	int terrainFrameX;
	int terrainFrameY;
};


//������ ������ UIŬ������� �� �� �ְ�.
//���� ���� ȭ�� ������ �̻� Ŀ�� ���, UI �� �ش�Ǵ� �̱�ɵ��� ���⿡ �����ϴ°� �´�.
//UI ǥ�� ���� Ŭ���� ���� Ŭ���ι� ��� ���� ���� Ŭ���� ������ �ϴ°� ��� �Ѵ�.
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

	//Ÿ�ϼ��� ����� �̹�����
	image* _tileImageSet[TILESETNUMBER];
	//Ŭ���ؼ� ������ Ÿ�ϵ�
	tagSampleTile _sampleTiles[SAMPLETILEY][SAMPLETILEX];
	tagSampleMonster _sampleMonster[MONSTER_END];
	//�� �����Ϳ��� ������ Ÿ�� ��
	int _tileSetSelection;

	//�� �����Ϳ��� ������ ����
	int _currentStartTileX;
	int _currentStartTileY;
	int _currentEndTileX;
	int _currentEndTileY;
	//�� �����Ϳ��� ������ �����ε���
	int _currentMonster;
	


	//////////////////////////////////////////UI////////////////////////////////////////////////////////////////
	menuBar* _menuBar;

	gameButton* _prevButton;
	BUTTON_CALLBACK _prevCallback;
	gameButton* _nextButton;
	BUTTON_CALLBACK _nextCallback;

	//Ÿ�� ������Ʈ ���� �ٸ� �͵� �����ϰ� �������ϱ� ����
	DROW_SELECT _drowState;
	gameButton* _tileTap;
	BUTTON_CALLBACK _tileTapCallback;
	gameButton* _objectTap;
	BUTTON_CALLBACK _objectTapCallback;
	gameButton* _monsterTap;
	BUTTON_CALLBACK _monsterCallback;
	gameButton* _optionTap;
	BUTTON_CALLBACK _eventCallback;
	//������ ���ʷ� Ŭ������ ������.. (T.T)
	optionPanel* _optionPanel;
	objectPanel* _objectPanel;


	//���� �����ǥ�� �������� ���� ī�޶�.
	gameCamera* _gameCamera;



	/////////////////////////////////////////////////////////�����ͷ� ������ ����//////////////////////////////////////////////////////////////////////
	//�ʿ����ͷ� ������ �ʵ���Ÿ
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

	//��ư �ݹ� �Լ�.
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

