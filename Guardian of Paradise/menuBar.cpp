#include "stdafx.h"
#include "menuBar.h"
#include "MapEditer.h"

menuBar::menuBar()
{
}


menuBar::~menuBar()
{
}
HRESULT menuBar::init(MapEditer* mapEditer, float startX, float startY, float widht, float height)
{
	_startX = startX;
	_startY = startY;
	_barRect = RectMake(startX, startY, widht, height);
	_mapEditer = mapEditer;
	_mapEditerMenuBackGround = IMAGEMANAGER->addImage("mapEditerMenuBackGround", "Image/etc/mapEditerMenuBackGround.bmp", widht, height, false, RGB(255, 0, 255));
	
	// Menu


	_currentFile = new gameFont;
	_currentFile->init(stringToWriteableChar(_mapEditer->_currentFilePath), WHITE, startX + 30, startY + 30, 12, ALIGNMENT_LEFT);
	_newButton = new gameButton;
	_newCallback = std::bind(&MapEditer::setBasicMapInfo, _mapEditer);
	_newButton->init("New", startX + 30, startY + 70, 25, &_newCallback);

	_saveButton = new gameButton;
	_saveCallback = std::bind(&MapEditer::save, _mapEditer);
	_saveButton->init("Save", startX + 30 + 150, startY+ 70, 25, &_saveCallback);

	_loadButton = new gameButton;
	_loadCallback = std::bind(&MapEditer::load, _mapEditer);
	_loadButton->init("Load", startX + 30 + 150  * 2, startY + 70, 25, &_loadCallback);

	_exitButton = new gameButton;
	_exitCallback = std::bind(&MapEditer::exit, _mapEditer);
	_exitButton->init("Exit", startX + 30 + 150 * 3, startY + 70, 25, &_exitCallback, WHITE);




	return S_OK;
}
void menuBar::release()
{
	SAFE_RELEASE(_exitButton);
	SAFE_RELEASE(_saveButton);
	SAFE_RELEASE(_loadButton);
}
void menuBar::update()
{
	//���� ������Ʈ �� ������ �ؽ�Ʈ�� �ٲ��ְ� �ִµ� �̴� ���곶���. �����ؼ� ���� ���� ����� ã���� ����.
	//int temp = _mapEditer->_currentFilePath.find_last_of('//');

	//char* writeable = new char[_mapEditer->_currentFilePath.size() + 1];
	//_mapEditer->
	//std::copy(_mapEditer->_currentFilePath.at(temp), _mapEditer->_currentFilePath.end(), writeable);
	//writeable[_mapEditer->_currentFilePath.size()] = '\0';


	_currentFile->setText(stringToWriteableChar(_mapEditer->_currentFilePath));
}
void menuBar::render()
{
	//Rectangle(getMemDC(), _barRect.left, _barRect.top, _barRect.right, _barRect.bottom);



	_mapEditerMenuBackGround->alphaRender(getMemDC(), _barRect.left, _barRect.top, 100);



	_currentFile->render();
	_newButton->render();
	_saveButton->render();
	_loadButton->render();
	_exitButton->render();

}
void menuBar::onClickDown(int key)
{

}
void menuBar::onClickUp(int key)
{
	_newButton->onClickUp(key);
	//serialize
	_saveButton->onClickUp(key);
	_loadButton->onClickUp(key);
	//exit���� �Ǵ°� ���� ���߿� �ؾߵȴ�. 
	_exitButton->onClickUp(key);
}
void menuBar::onClickStay(int key)
{

}

