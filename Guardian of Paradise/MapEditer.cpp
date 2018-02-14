#include "stdafx.h"
#include "MapEditer.h"
#include "Slime.h"
#include "gameQuest.h"
MapEditer::MapEditer()
{

}
MapEditer::~MapEditer()
{
}
HRESULT MapEditer::init()
{
	_currentFilePath = "";
	_isPicking = false;
	_isDrag = false;
	_isMapRoamming = false;
	
	//일단 여기에서 필요한 맵타일 이미지를 모두 로드한다. 
	char sResult[128];
	char sResult_bmp[128];
	for (int i = 0; i < TILESETNUMBER; i++)
	{
		sprintf(sResult, "t_%d", i);
		_tileImageSet[i] = IMAGEMANAGER->findImage(sResult);
	}
	_backGround = IMAGEMANAGER->findImage("BasicBackGroundImage");
	_sampleTileBackGround = IMAGEMANAGER->addImage("sampleTileBackGroundImage", "Image/etc/SampleTileBackGround.bmp", SAMPLETILEX*32, SAMPLETILEY*32 + 30, false, RGB(255, 0, 255));
	_tileSetSelection =5;

	_gameTileMap = make_shared<gameTileMap>();
	setBasicMapInfo();
	
	_gameCamera = new gameCamera;
	_gameCamera->init(true,RectMake(0,0, 2500,2500));
	_gameCamera->onCamera();
	_gameCamera->setCameraSpeed(10.0f);

	_currentEndTileX = 1;
	_currentEndTileY = 0;

	_drowState = TILE;
	
	//오른쪽 샘플 타일에 렉트 설정
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i][j].terrainFrameX = j;
			_sampleTiles[i][j].terrainFrameY = i;
			SetRect(&_sampleTiles[i][j].rcTile, 
				SAMPLESTARTX + j * TILESIZE,
				SAMPLESTARTY + i * TILESIZE,
				SAMPLESTARTX + j * TILESIZE + TILESIZE,
				SAMPLESTARTY + i * TILESIZE + TILESIZE);

		}
	}

	sampleTerrainSet();
	sampleMonsterSet();


	////////////////////////////////////////////////////////////////////////////////////UI////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_menuBar = new menuBar;
	_menuBar->init(this, 0, WINSIZEY - 130, WINSIZEX, 130);
	// prev
	_prevButton = new gameButton;
	_prevCallback = std::bind(&MapEditer::prev, this);
	_prevButton->init("Prev", SAMPLESTARTX + 50, SAMPLESTARTY + SAMPLETILEY*TILESIZE + 10, 20, &_prevCallback,ORANGE);
	// next
	_nextButton = new gameButton;
	_nextCallback = std::bind(&MapEditer::next, this);
	_nextButton->init("Next", SAMPLESTARTX +50 + 130, SAMPLESTARTY + SAMPLETILEY*TILESIZE + 10, 20, &_nextCallback, ORANGE);

	//텝 버튼
	_tileTap = new gameButton;
	_tileTapCallback = std::bind(&MapEditer::setTileSelect, this);
	_tileTap->init("Tile", SAMPLESTARTX + 20, SAMPLESTARTY + SAMPLETILEY*TILESIZE + 40, 13, &_tileTapCallback, RED);
	_objectTap = new gameButton;
	_objectTapCallback = std::bind(&MapEditer::setObjectSelect, this);
	_objectTap->init("Object", SAMPLESTARTX + 20 + 80, SAMPLESTARTY + SAMPLETILEY*TILESIZE + 40, 13, &_objectTapCallback, RED);
	_monsterTap = new gameButton;
	_monsterCallback = std::bind(&MapEditer::setMonsterSelect, this);
	_monsterTap->init("Monster", SAMPLESTARTX + 20 + 180, SAMPLESTARTY + SAMPLETILEY*TILESIZE + 40, 13, &_monsterCallback, RED);
	_optionTap = new gameButton;
	_eventCallback = std::bind(&MapEditer::setEventSelect, this);
	_optionTap->init("Option", SAMPLESTARTX + 20, SAMPLESTARTY + SAMPLETILEY*TILESIZE + 55, 13, &_eventCallback, RED);
	//panel
	//option
	_optionPanel = new optionPanel;
	_optionPanel->init(this, SAMPLESTARTX, SAMPLESTARTY, SAMPLETILEX*TILESIZE, SAMPLETILEY*TILESIZE);
	//object
	_objectPanel = new objectPanel;
	_objectPanel->init(this, SAMPLESTARTX, SAMPLESTARTY, SAMPLETILEX*TILESIZE, SAMPLETILEY*TILESIZE);


	return S_OK;
}
void MapEditer::release()
{
	//////////////////////////UI////////////////////////////////////////
	SAFE_RELEASE(_menuBar);
	SAFE_RELEASE(_optionPanel);
	SAFE_RELEASE(_objectPanel);
	SAFE_RELEASE(_prevButton);
	SAFE_RELEASE(_nextButton);
	SAFE_RELEASE(_tileTap);
	SAFE_RELEASE(_objectTap);
	SAFE_RELEASE(_monsterTap);
	SAFE_RELEASE(_optionTap);
	/////////////////////////////////////////////////////////////////////
	SAFE_RELEASE(_gameCamera);
}
void MapEditer::update()
{
	if (PtInRect(&RectMake(-_gameCamera->getX(), -_gameCamera->getY(), TILESIZE * _gameTileMap->getTileX(), TILESIZE * _gameTileMap->getTileY()), _ptMouse))
	{
		_isMapRoamming = true;
		switch (_drowState)
		{
		case TILE:
		
			//맵 까는데 위에 시각적으로 도와주는 사각형 그려주는거
			for (int i = 0; i < _gameTileMap->getTileY(); i++)
			{
				for (int j = 0; j < _gameTileMap->getTileX(); j++)
				{
					if (PtInRect(&(RectMake(_gameTileMap->_mapdata[i][j].getX() - _gameCamera->getX(),
						_gameTileMap->_mapdata[i][j].getY() - _gameCamera->getY(),
						_gameTileMap->_mapdata[i][j].getWidth(),
						_gameTileMap->_mapdata[i][j].getHeight())
						), _ptMouse))
					{
						_MapRoammingArea.left = _gameTileMap->_mapdata[i][j].getX() - _gameCamera->getX();
						_MapRoammingArea.top =_gameTileMap->_mapdata[i][j].getY() - _gameCamera->getY();
						_MapRoammingArea.right = _gameTileMap->_mapdata[i][j].boundingBox().right - _gameCamera->getX();
						_MapRoammingArea.bottom = _gameTileMap->_mapdata[i][j].boundingBox().bottom - _gameCamera->getY();
					}
				}
			}
			break;
		case MONSTER:
			_MapRoammingArea.left = _ptMouse.x;
			_MapRoammingArea.top = _ptMouse.y;
			break;
		case OPTION:
			_optionPanel->setMapRoamingArea();
			break;
		case OBJECT:
			_objectPanel->setMapRoamingArea();
			break;

		}
	}
	else
		_isMapRoamming = false;


	_gameCamera->update();
	_gameTileMap->update();
	_optionPanel->update();
	_objectPanel->update();
	_menuBar->update();
	onClickDown();
	onClickStay();
	onClickUp();
}
void MapEditer::render()
{
	_backGround->render(getMemDC(), 0, 0);

	//게임 타일맵
	_gameCamera->cameraRender(*_gameTileMap);
	_sampleTileBackGround->alphaRender(getMemDC(), SAMPLESTARTX, SAMPLESTARTY, 100);


	if (_drowState == TILE)
	{
		//셈플 타일들
		char sResult[128];
		sprintf(sResult, "t_%d", _tileSetSelection);
		IMAGEMANAGER->render(sResult, getMemDC(), SAMPLESTARTX, SAMPLESTARTY);
	}
	else if (_drowState == MONSTER)
	{
		sampleMonsterRender();
	}

	//나머지 버튼이나 선택시 보이는 이미지 전부
	selectedShow();
}
void MapEditer::onClickDown()
{
	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	{
		switch (_drowState)
		{
		case TILE:
			//샘플타일 텝에서 샘플 선택하는  시작 구문, 키업과 콤보로 되어 있다.
			if (PtInRect(&RectMake(SAMPLESTARTX, SAMPLESTARTY, 320, 640), _ptMouse))
			{
				_isDrag = true;
				_DragArea.left = _ptMouse.x;
				_DragArea.top = _ptMouse.y;
				for (int i = 0; i < SAMPLETILEY; i++)
				{
					for (int j = 0; j < SAMPLETILEX; j++)
					{
						if (PtInRect(&_sampleTiles[i][j].rcTile, _ptMouse))
						{
							_currentStartTileX = _sampleTiles[i][j].terrainFrameX;
							_currentStartTileY = _sampleTiles[i][j].terrainFrameY;
							break;
						}
					}
				}
			}
			break;
		case MONSTER:
			//몬스터 샘플타일 텝에서 몬스터 선택하는 것.
			for (int i = 0; i < MONSTER_END; i++)
			{
				if (PtInRect(&_sampleMonster[i].rcMonster, _ptMouse))
				{
					_isPicking = true;
					_currentMonster = i;
					_pickingArea.left = _sampleMonster[i].rcMonster.left;
					_pickingArea.top = _sampleMonster[i].rcMonster.top;
					_pickingArea.right = _sampleMonster[i].rcMonster.right;
					_pickingArea.bottom = _sampleMonster[i].rcMonster.bottom;
					break;
				}
			}

			//맵 타일에 몬스터 깔기.
			if (_isPicking)
			{

				if (PtInRect(&RectMake(-_gameCamera->getX(), -_gameCamera->getY(), TILESIZE * _gameTileMap->getTileX(), TILESIZE * _gameTileMap->getTileY()), _ptMouse))
				{
					//맵에 까는데 그 위에 기존의 몬스터가 있으면 깔지 않는 구문.
					bool _isCollide = false;
					for (vector<tagMonsterInfo>::iterator iter = _gameTileMap->getMonsterSet()->begin(); iter != _gameTileMap->getMonsterSet()->end(); iter++)
					{
						if (PtInRect(&RectMake(
							-_gameCamera->getX() + iter->x,
							-_gameCamera->getY() + iter->y,
							iter->width,
							iter->height),
							_ptMouse))
						{
							_isCollide = true;
							break;
						}
					}

					if (!_isCollide)
					{
						float width = _sampleMonster[_currentMonster].rcMonster.right - _sampleMonster[_currentMonster].rcMonster.left;
						float height = _sampleMonster[_currentMonster].rcMonster.bottom - _sampleMonster[_currentMonster].rcMonster.top;

						_gameTileMap->getMonsterSet()->push_back(tagMonsterInfo((MONSTER_SELECT)_currentMonster,
							_gameCamera->getX() + _ptMouse.x - width / 2,
							_gameCamera->getY() + _ptMouse.y - height / 2,
							width,
							height));
					}
				}
			}
			break;
		case OPTION:
			_optionPanel->onClickDown(MK_LBUTTON);
			break;
		case OBJECT:
			_objectPanel->onClickDown(MK_LBUTTON);
			break;
		}// end of switch (_drowState)
	} // end of if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))


	if (KEYMANAGER->isOnceKeyDown(MK_RBUTTON))
	{
		switch (_drowState)
		{
		case OPTION:
			_optionPanel->onClickDown(MK_RBUTTON);
			break;
		case OBJECT:
			_objectPanel->onClickDown(MK_RBUTTON);
			break;
		}
	}

}
void MapEditer::onClickStay()
{
	//셈플타일에서 선택한걸 맵타일에 까는구문
	if (KEYMANAGER->isStayKeyDown(MK_LBUTTON))
	{
		switch (_drowState)
		{
		case TILE:
			if (_isDrag)
			{
				_DragArea.right = _ptMouse.x;
				_DragArea.bottom = _ptMouse.y;
			}
			if (_isPicking)
			{
					for (int i = 0; i < _gameTileMap->getTileY(); i++)
					{
						for (int j = 0; j < _gameTileMap->getTileX(); j++)
						{
							if (PtInRect(&(RectMake(_gameTileMap->_mapdata[i][j].getX() - _gameCamera->getX(),
								_gameTileMap->_mapdata[i][j].getY() - _gameCamera->getY(),
								_gameTileMap->_mapdata[i][j].getWidth(),
								_gameTileMap->_mapdata[i][j].getHeight())
								), _ptMouse))
							{
								//현재 내버튼이 지형에 체크되어있으면
								int tempX = 0;
								int tempY = 0;
								for (int k = _currentStartTileY; k <= _currentEndTileY; k++)
								{
									//선택한게 y축으로 더 삐져 나가지 않도록
									if (i + tempY >= _gameTileMap->getTileY())
										continue;
									for (int l = _currentStartTileX; l <= _currentEndTileX; l++)
									{
										//선택한게 x축으로 더 삐져 나가지 않도록
										if (j + tempX >= _gameTileMap->getTileX())
											continue;
										_gameTileMap->_mapdata[i + tempY][j + tempX].setTileImage(l, k, _tileSetSelection);
										_gameTileMap->_mapdata[i + tempY][j + tempX].setTerrainType(_sampleTiles[k][l].terrain);
										tempX++;
									}
									tempY++;
									tempX = 0;
								}
								break;
							}
						}
					}
			} //end of if (_isPicking)
			break;
		case MONSTER:
			break;
		case OPTION:
			_optionPanel->onClickStay(MK_LBUTTON);
			break;
		case OBJECT:
			_objectPanel->onClickStay(MK_LBUTTON);
			break;
		}
	}// end of if (KEYMANAGER->isStayKeyDown(MK_LBUTTON))


	//깔린 몬스터들 제거하는 구문
	if (KEYMANAGER->isStayKeyDown(MK_RBUTTON))
	{
		switch (_drowState)
		{
		case TILE:
			_isPicking = false;
			break;
		case MONSTER:
			_isPicking = false;
			for (vector<tagMonsterInfo>::iterator iter = _gameTileMap->getMonsterSet()->begin(); iter != _gameTileMap->getMonsterSet()->end(); iter++)
			{
				if (PtInRect(&RectMake(
					-_gameCamera->getX() + iter->x,
					-_gameCamera->getY() + iter->y,
					iter->width,
					iter->height),
					_ptMouse))
				{
					_gameTileMap->getMonsterSet()->erase(iter);
					break;
				}
			}
			break;
		case OPTION:
			_optionPanel->onClickStay(MK_RBUTTON);
			break;
		case OBJECT :
			_objectPanel->onClickStay(MK_RBUTTON);
			break;
		}
	}
}
void MapEditer::onClickUp()
{
	if (KEYMANAGER->isOnceKeyUp(MK_LBUTTON))
	{
		if (_drowState == TILE)
		{
			//밑의 선택 구문에 선행해서 먼저 블록범위 잡는 연산을 실행해주면 된다.
			if (_isDrag)
			{
				//셈플타일에서 선택완성 구문, 드레그 해서 범위 잡은 걸로 _pickingArea를 완성한다.
				for (int i = 0; i < SAMPLETILEY; i++)
				{
					for (int j = 0; j < SAMPLETILEX; j++)
					{
						if (PtInRect(&_sampleTiles[i][j].rcTile, _ptMouse))
						{
							_isPicking = true;
							_currentEndTileX = _sampleTiles[i][j].terrainFrameX;
							_currentEndTileY = _sampleTiles[i][j].terrainFrameY;

							if (_currentEndTileX == _currentStartTileX  && _currentEndTileY == _currentStartTileY)
								_pickingArea = _sampleTiles[i][j].rcTile;

							//드레그 해서 범위로 클릭 한 경우
							else
							{
								_pickingArea.left = _sampleTiles[_currentStartTileY][_currentStartTileX].rcTile.left;
								_pickingArea.top = _sampleTiles[_currentStartTileY][_currentStartTileX].rcTile.top;
								_pickingArea.right = _sampleTiles[_currentEndTileY][_currentEndTileX].rcTile.right;
								_pickingArea.bottom = _sampleTiles[_currentEndTileY][_currentEndTileX].rcTile.bottom;
							}

							break;
						}
					}
				}

			} //end of is Drag
			_isDrag = false;

		}// end of _drowState
	

		//tap
		_tileTap->onClickUp(MK_LBUTTON);
		_objectTap->onClickUp(MK_LBUTTON);
		_monsterTap->onClickUp(MK_LBUTTON);
		_optionTap->onClickUp(MK_LBUTTON);

		switch (_drowState)
		{
		case TILE :
			_nextButton->onClickUp(MK_LBUTTON);
			_prevButton->onClickUp(MK_LBUTTON);
		case OBJECT:
			_objectPanel->onClickUp(MK_LBUTTON);
			break;
		case MONSTER:
			break;
		case OPTION:
			_optionPanel->onClickUp(MK_LBUTTON);
			break;

		}
		//portal c
		for (vector<tagPortalInfo>::iterator iter = _gameTileMap->getPortalSet()->begin(); iter != _gameTileMap->getPortalSet()->end(); iter++)
		{
			iter->nextXBox->onClickUp(MK_LBUTTON, _gameCamera->getX(), _gameCamera->getY() );
			iter->nextYBox->onClickUp(MK_LBUTTON, _gameCamera->getX(), _gameCamera->getY());
		}
		//menu
		_menuBar->onClickUp(MK_LBUTTON);
	}//end of KEYMANAGER
}

void MapEditer::setBasicMapInfo(void)
{
	_gameTileMap->init(_tileSetSelection, 20, 20);
	_gameTileMap->getMonsterSet()->clear();
	_gameTileMap->getPortalSet()->clear();
	_gameTileMap->getObjectSet()->clear();
	_gameTileMap->getGameQuestSet()->clear();

	_currentFilePath = "";

}
void MapEditer::save(void)
{
	if (_currentFilePath == "")
	{
		TCHAR szFile[MAX_PATH] = { 0, };
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = _T("XML Files(*.xml)\0*.xml\0All Files (*.*)\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrTitle = _T("Save XML map FILE");
		ofn.lpstrInitialDir = "map";
		ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
		if (GetSaveFileName(&ofn) == false)
			return;
		
		_currentFilePath = getFileNameFromPath(ofn.lpstrFile);

	}
	

	///시리얼라이즈
	///////////////////////output(data->file)////////////////////////////////////////////////


	std::ofstream fs("map//"+_currentFilePath);
	cereal::XMLOutputArchive oArchive(fs);

	oArchive(CEREAL_NVP(_gameTileMap));


}
void MapEditer::load(void)
{
	_TCHAR szFilePath[MAX_PATH] = { 0, };
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = sizeof(szFilePath);
	ofn.lpstrFilter = _T("XML Files(*.xml)\0*.xml\0All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "map";
	ofn.lpstrTitle = _T("Load XML map FILE");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == false)
		return;
	_currentFilePath = getFileNameFromPath(ofn.lpstrFile);

	///시리얼라이즈
	///////////////////////output(file->data)////////////////////////////////////////////////


	std::ifstream fs("map//" + _currentFilePath);
	cereal::XMLInputArchive iArchive(fs);

	iArchive(CEREAL_NVP(_gameTileMap));


	//불러온 맵 사이즈에 맞게 정보 재수정.
	_optionPanel->tileInfoSetUp();

}
void MapEditer::selectedShow(void)
{
	_menuBar->render();

	switch (_drowState)
	{
	case TILE:
		_nextButton->render();
		_prevButton->render();
		break;
	case OBJECT:
		_objectPanel->render();
		break;
	case MONSTER:
		break;
	case OPTION:
		_optionPanel->render();
		break;

	}

	_tileTap->render();
	_objectTap->render();
	_monsterTap->render();
	_optionTap->render();

	if (_isDrag)
	{
		HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hMyPen);


		LineMake(getMemDC(), _DragArea.left, _DragArea.top, _DragArea.right, _DragArea.top);
		LineMake(getMemDC(), _DragArea.right, _DragArea.top, _DragArea.right, _DragArea.bottom);
		LineMake(getMemDC(), _DragArea.right, _DragArea.bottom, _DragArea.left, _DragArea.bottom);
		LineMake(getMemDC(), _DragArea.left, _DragArea.bottom, _DragArea.left, _DragArea.top);
		DeleteObject(SelectObject(getMemDC(), hOldPen));
	}


	switch (_drowState)
	{
	case TILE:
	case OBJECT:
	case MONSTER:
		if (_isPicking)
		{
			HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
			HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hMyPen);
			LineMake(getMemDC(), _pickingArea.left, _pickingArea.top, _pickingArea.right, _pickingArea.top);
			LineMake(getMemDC(), _pickingArea.right, _pickingArea.top, _pickingArea.right, _pickingArea.bottom);
			LineMake(getMemDC(), _pickingArea.right, _pickingArea.bottom, _pickingArea.left, _pickingArea.bottom);
			LineMake(getMemDC(), _pickingArea.left, _pickingArea.bottom, _pickingArea.left, _pickingArea.top);
			DeleteObject(SelectObject(getMemDC(), hOldPen));
		}
		break;
	}



	if (_isMapRoamming && _isPicking)
	{
		HPEN hMyPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hMyPen);
		LONG RoammingAreaWidth;
		LONG RoammingAreaHeight;

		switch (_drowState)
		{
		case TILE:
		case OBJECT:
			RoammingAreaWidth = _pickingArea.right - _pickingArea.left;
			RoammingAreaHeight = _pickingArea.bottom - _pickingArea.top;
			LineMake(getMemDC(), _MapRoammingArea.left, _MapRoammingArea.top, _MapRoammingArea.left + RoammingAreaWidth, _MapRoammingArea.top);
			LineMake(getMemDC(), _MapRoammingArea.left + RoammingAreaWidth, _MapRoammingArea.top, _MapRoammingArea.left + RoammingAreaWidth, _MapRoammingArea.top + RoammingAreaHeight);
			LineMake(getMemDC(), _MapRoammingArea.left + RoammingAreaWidth, _MapRoammingArea.top + RoammingAreaHeight, _MapRoammingArea.left, _MapRoammingArea.top + RoammingAreaHeight);
			LineMake(getMemDC(), _MapRoammingArea.left, _MapRoammingArea.top + RoammingAreaHeight, _MapRoammingArea.left, _MapRoammingArea.top);
			DeleteObject(SelectObject(getMemDC(), hOldPen));


			break;
		case MONSTER:
			char sResult[120];
			sprintf(sResult, "monster_%d", _currentMonster);
			IMAGEMANAGER->findImage(sResult)->frameAlphaRender(getMemDC(), _ptMouse.x - IMAGEMANAGER->findImage(sResult)->getFrameWidth() / 2, _ptMouse.y - IMAGEMANAGER->findImage(sResult)->getFrameHeight() / 2, 0, 0, 100);
			break;
		case OPTION:
			IMAGEMANAGER->findImage("PortalAlpha")->alphaRender(getMemDC(), _MapRoammingArea.left, _MapRoammingArea.top, 100);
			break;
		}

	}
}
void MapEditer::sampleTerrainSet(void)
{
	HANDLE file;

	//10*20 의 숫자 데이터, 추가로 8개의 공백문자와 2개의 줄넘김 문자.  총 420개
	_TCHAR buffer[420];

	DWORD read;

	_TCHAR sResult[128];
	sprintf(sResult, "terrainData//t_%d.txt", _tileSetSelection);
	file = CreateFile(sResult, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, buffer, sizeof(buffer), &read, NULL);
	
	//읽어 왔으면 파싱해야징
	int index = 0;
	int actualIndex = 0;
	while (index < 420)
	{
		//버퍼에서 받아처먹는게 줄넘김이나 여백이 아니라면
		if (buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\r')
		{
			_sampleTiles[actualIndex / 10][actualIndex % 10].terrain = ((TERRAINTYPE)(buffer[index] - '0'));
			actualIndex++;
		}
		index++;
	}

	CloseHandle(file);
	

}
void MapEditer::sampleMonsterRender(void)
{
	char sResult[128];
	for (int i = 0; i < MONSTER_END; i++)
	{
		sprintf(sResult, "monster_%d", i);
		IMAGEMANAGER->findImage(sResult)->frameRender(getMemDC(), _sampleMonster[i].rcMonster.left, _sampleMonster[i].rcMonster.top, 0, 0);
		
	}

}
void MapEditer::sampleMonsterSet(void)
{

	char sResult[128];
	//셈플몬스터를 까는데 섬네일을 쓰고 싶지 않다.
	//크기를 고려한 X size, 누적 X사이즈가 320넘어가면 (배열로 돌아가면서 계속 누적시킴)
	//까는중에 가장 큰 Y 사이즈를 maxSizeY라 하고(물론 배열로 돌아가면서 계속 그걸 저장해야지)
	//그 maxSizeY만큼 넘겨 렉트를 그려준다.
	int accumulatedX = 0;
	int maxSizeY = 0;
	int accumulatedY = 0;

	for (int i = 0; i < MONSTER_END; i++)
	{
		sprintf(sResult, "monster_%d", i);
		_sampleMonster[i].monsterSelect = (MONSTER_SELECT)i;
	
		maxSizeY = max(IMAGEMANAGER->findImage(sResult)->getFrameHeight(), maxSizeY);

	
		_sampleMonster[i].rcMonster = RectMake(SAMPLESTARTX + accumulatedX
			, SAMPLESTARTY + accumulatedY
			, IMAGEMANAGER->findImage(sResult)->getFrameWidth()
			, IMAGEMANAGER->findImage(sResult)->getFrameHeight());


		accumulatedX += IMAGEMANAGER->findImage(sResult)->getFrameWidth();
		if (accumulatedX >= (SAMPLETILEX-1) * TILESIZE)
		{
			accumulatedY += maxSizeY;
			//줄단을 넘어갈 때에는 누적X 포지션을 초기화 해 준다.
			accumulatedX = 0;
		}

	}
}
