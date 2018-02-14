#include "stdafx.h"
#include "menu.h"


menu::menu()
{
}


menu::~menu()
{
}

HRESULT menu::init()
{
	scene::init();

	//메뉴 배경 및 메뉴버튼 이미지 && 오프닝영상이미지
	IMAGEMANAGER->addImage("menuBg", "image/menuBackground.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("newGameButton", "image/newGameButton.bmp", 273 * 2, 89 * 2, 1, 2, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("loadGameButton", "image/loadGameButton.bmp", 282 * 2, 88 * 2, 1, 2, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("exitButton", "image/exitButton.bmp", 293 * 2, 96 * 2, 1, 2, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("opening1", "image/opening1.bmp", WINSIZEX * 25, WINSIZEY, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("opening2", "image/opening2.bmp", WINSIZEX * 11, WINSIZEY, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("opening3", "image/opening3.bmp", WINSIZEX * 25, WINSIZEY, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("opening4", "image/opening4.bmp", WINSIZEX * 12, WINSIZEY, 12, 1, true, RGB(255, 0, 255));

	//아이템 이미지
	IMAGEMANAGER->addImage("disk", "image/itemDisk.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("carrot", "image/itemCarrot.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bigBullet", "image/itemBigBullet.bmp", 50, 58, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("smallBullet", "image/itemSmallBullet.bmp", 22, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("unbeatable", "image/itemUnbeatable.bmp", 30, 30, true, RGB(255, 0, 255));

	_menuBackground = IMAGEMANAGER->findImage("menuBg");
	_newGameButton = IMAGEMANAGER->findImage("newGameButton");
	_loadGameButton = IMAGEMANAGER->findImage("loadGameButton");
	_exitButton = IMAGEMANAGER->findImage("exitButton");
	

	_opening1 = IMAGEMANAGER->findImage("opening1");
	_opening2 = IMAGEMANAGER->findImage("opening2");
	_opening3 = IMAGEMANAGER->findImage("opening3");
	_opening4 = IMAGEMANAGER->findImage("opening4");

	_stage = new Stage1of1;
	SCENEMANAGER->addScene("stage", _stage);

	_end = new ending;
	SCENEMANAGER->addScene("end", _end);

	_ani1 = new animation;
	_ani1->init(_opening1->getWidth(), _opening1->getHeight(), _opening1->getFrameWidth(), _opening1->getFrameHeight());
	_ani1->setDefPlayFrame(false, false);
	_ani1->setFPS(1);
	//_ani1->start();

	_ani2 = new animation;
	_ani2->init(_opening2->getWidth(), _opening2->getHeight(), _opening2->getFrameWidth(), _opening2->getFrameHeight());
	_ani2->setDefPlayFrame(false, false);
	_ani2->setFPS(1);

	_ani3 = new animation;
	_ani3->init(_opening3->getWidth(), _opening3->getHeight(), _opening3->getFrameWidth(), _opening3->getFrameHeight());
	_ani3->setDefPlayFrame(false, false);
	_ani3->setFPS(1);

	_ani4 = new animation;
	_ani4->init(_opening4->getWidth(), _opening4->getHeight(), _opening4->getFrameWidth(), _opening4->getFrameHeight());
	_ani4->setDefPlayFrame(false, false);
	_ani4->setFPS(1);

	//게임 완성시 false로 초기화
	_isPlaying = true;

	_playTimer = new timer;
	
	_menuNum = 0;
	_isAni1Played = false;
	_isAni2Played = false;
	_isAni3Played = false;
	_isAni4Played = false;

	//메인사운드
	SOUNDMANAGER->addSound("01_mainSound", "music/mainSound.mp3", true, true);
	SOUNDMANAGER->addSound("02_stageSound", "music/stageSound.mp3", true, true);

	SOUNDMANAGER->play("01_mainSound", 1.0f);

	return S_OK;
}

void menu::release(void)
{
	scene::release();
}

void menu::update(void)
{
	scene::update();

	//openingPlay();


	if (_isPlaying)
	{
		switch (_menuNum)
		{
		case 0:
			_newGameButton->setFrameY(1);
			_loadGameButton->setFrameY(0);
			_exitButton->setFrameY(0);
			break;

		case 1:
			_newGameButton->setFrameY(0);
			_loadGameButton->setFrameY(1);
			_exitButton->setFrameY(0);
			break;

		case 2:
			_newGameButton->setFrameY(0);
			_loadGameButton->setFrameY(0);
			_exitButton->setFrameY(1);
			break;
		}


		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuNum++;

			if (_menuNum > 2)
			{
				_menuNum = 0;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuNum--;

			if (_menuNum < 0)
			{
				_menuNum = 2;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_menuNum == 0)
			{
				SCENEMANAGER->changeScene("stage");
			}

			else if (_menuNum == 1)
			{

			}

			else if (_menuNum == 2)
			{
				SCENEMANAGER->changeScene("end");
			}
		}
	}

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);
	if (_isAni1Played)
	{
		_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);
	}
	if (_isAni2Played)
	{
		_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);
	}
	if (_isAni3Played)
	{
		_ani4->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);
	}
}

void menu::render(void)
{
	//일단 주석 , 현재 카메라가 구현이 안되있음
	scene::render();

	_opening1->aniRender(getMemDC(), 0, 0, _ani1);
	if (_isAni1Played)
	{
		_opening2->aniRender(getMemDC(), 0, 0, _ani2);
	}
	if (_isAni2Played)
	{
		_opening3->aniRender(getMemDC(), 0, 0, _ani3);
	}
	if (_isAni3Played)
	{
		_opening4->aniRender(getMemDC(), 0, 0, _ani4);
	}


	if (_isPlaying)
	{
		_menuBackground->render(getMemDC());
		_newGameButton->frameRender(getMemDC(), 230, 320);
		_loadGameButton->frameRender(getMemDC(), 220, 420);
		_exitButton->frameRender(getMemDC(), 205, 520);
	}
}

void menu::openingPlay()
{

	//에니메이션 2 실행시점
	if (!_ani1->isPlay() && !_ani2->isPlay() && !_ani3->isPlay() && !_ani4->isPlay() && !_isAni1Played && !_isAni2Played && !_isAni3Played && !_isAni4Played)
	{
		_isAni1Played = true;
		_ani2->start();
	}
	//에니메이션 3 실행시점
	if (!_ani1->isPlay() && !_ani2->isPlay() && !_ani3->isPlay() && !_ani4->isPlay() && _isAni1Played && !_isAni2Played && !_isAni3Played && !_isAni4Played)
	{
		_isAni2Played = true;
		_ani3->start();

	}
	//에니메이션 4 실행시점
	if (!_ani1->isPlay() && !_ani2->isPlay() && !_ani3->isPlay() && !_ani4->isPlay() && _isAni1Played && _isAni2Played && !_isAni3Played && !_isAni4Played)
	{
		_isAni3Played = true;
		_ani4->start();


	}
	//에니메이션 4 끝난시점
	if (!_ani1->isPlay() && !_ani2->isPlay() && !_ani3->isPlay() && !_ani4->isPlay() && _isAni1Played && _isAni2Played && _isAni3Played && !_isAni4Played)
	{
		_playTimer->init();
		_isAni4Played = true;
	}

	if (!_ani1->isPlay() && !_ani2->isPlay() && !_ani3->isPlay() && !_ani4->isPlay() && _isAni1Played && _isAni2Played && _isAni3Played && _isAni4Played)
	{
		_playTimer->tick(60.0f);

		if (_playTimer->getWorldTime() > 2.0f)
		{
			_isPlaying = true;
		}

	}
}