#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}
HRESULT MainMenu::init()
{
	//Image SetUp
	_mainImage = new image;
	_mainImage->init("Image/CG/mainMenu.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_background = new image;
	_background->init("Image/CG/mainMenu_BackGround.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_roopSpeed = 0;







	//button SetUp
	_newGameCallback = std::bind(&MainMenu::newGame, this);
	_newGame = new gameButton;
	_newGame->init("new game", WINSIZEX / 2, WINSIZEY / 2 + 160 - 100, 25, &_newGameCallback, ORANGE, ALIGNMENT_MIDDLE);


	_continueCallback = bind(&MainMenu::continueGame, this);
	_continue = new gameButton;
	_continue->init("continue", WINSIZEX / 2, WINSIZEY / 2 + 160 - 50, 25, &_continueCallback, ORANGE, ALIGNMENT_MIDDLE);


	_mapEditerCallback = std::bind(&MainMenu::loadMapEditer, this);
	_mapEditer = new gameButton;
	_mapEditer->init("Map Editer", WINSIZEX / 2, WINSIZEY / 2 + 160, 25, &_mapEditerCallback, ORANGE, ALIGNMENT_MIDDLE);

	_exitCallback = std::bind(&MainMenu::exitGame, this);
	_exit = new gameButton;
	_exit->init("Exit", WINSIZEX / 2, WINSIZEY / 2 + 160 + 50, 25, &_exitCallback, ORANGE, ALIGNMENT_MIDDLE);



	GQUESTMANAGER->setWindowsInit();
	return S_OK;
}
void MainMenu::release()
{
	SAFE_RELEASE(_newGame);
	SAFE_RELEASE(_continue);
	SAFE_RELEASE(_exit);
	SAFE_RELEASE(_mapEditer);


	SAFE_RELEASE(_mainImage);
	SAFE_RELEASE(_background);
}
void MainMenu::update()
{





	if (GQUESTMANAGER->isOkayToUpdate())
	{
		if (KEYMANAGER->isOnceKeyUp(MK_LBUTTON))
		{
			if (_newGame != NULL)
				_newGame->onClickUp(MK_LBUTTON);
			if (_continue != NULL)
				_continue->onClickUp(MK_LBUTTON);
			if (_mapEditer != NULL)
				_mapEditer->onClickUp(MK_LBUTTON);
			if (_exit != NULL)
				_exit->onClickUp(MK_LBUTTON);

		}
		_roopSpeed += 0.9f;
	}


	GQUESTMANAGER->update();

	

}
void MainMenu::render()
{

	_background->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _roopSpeed, 0);
	_mainImage->render(getMemDC(), 0, 0);


	_newGame->render();
	_continue->render();
	_mapEditer->render();
	_exit->render();


	GQUESTMANAGER->render();

}
void MainMenu::newGame()
{
	SCENEMANAGER->changeScene("mainGameScene");
}
void MainMenu::loadMapEditer()
{
	SCENEMANAGER->changeScene("mapEditerScene");
}
void MainMenu::continueGame()
{
	GQUESTMANAGER->loadSetup();
}
void MainMenu::exitGame()
{
	PostQuitMessage(0);
}