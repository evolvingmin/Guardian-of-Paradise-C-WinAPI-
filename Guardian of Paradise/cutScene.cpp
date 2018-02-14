#include "stdafx.h"
#include "cutScene.h"
#include "gameTileMap.h"
#include "MainGame.h"
cutScene::cutScene()
{
}


cutScene::~cutScene()
{
}
HRESULT cutScene::init()
{
	_cgDelay = 0;
	_isCGActive = false;
	_cgIndex;

	CG = IMAGEMANAGER->findImage("CGs");
	return S_OK;
}

void cutScene::showCutScene(cutSceneType type)
{
	_isCGActive = true;
	_cgDelay = 5.0f;
	_type = type;
	////////////////////////////////////////////////////////////////////////
	//select cutScenetype based on enum selection
	switch (_type)
	{
	case GAMEOVER:
		_cgIndex.x = 0;
		_cgIndex.y = 0;
		SOUNDMANAGER->stop("boss01.mid");
		SOUNDMANAGER->stop("boss02.mid");
		SOUNDMANAGER->stop(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("gameover.mid", 3.0f);
		_cgDelay = 6.0f;
		break;
	case MEET_FOREST_ELEMENTAL:
		_cgIndex.x = 3;
		_cgIndex.y = 3;
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("itemget01.mid", 3.0f);
		_cgDelay = 5.0f;
		break;
	case LEVELUP_FOREST_ELEMENTAL:
		_cgIndex.x = 0;
		_cgIndex.y = 5;
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("itemget01.mid", 3.0f);
		_cgDelay = 5.0f;
		break;
	case GET_FOREST_EMBLEM:
		_cgIndex.x = 1;
		_cgIndex.y = 6;
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("itemget01.mid", 3.0f);
		_cgDelay = 5.0f;
		break;
	case GET_HEALTH_POTION:
		_cgIndex.x = 2;
		_cgIndex.y = 7;
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("itemget02.mid", 3.0f);
		_cgDelay = 3.0f;
		break;
	case GET_SWORD:
		_cgIndex.x = 3;
		_cgIndex.y = 7;
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("itemget01.mid", 3.0f);
		_cgDelay = 5.0f;
		break;
	case GET_KEY:
		_cgIndex.x = 1;
		_cgIndex.y = 8;
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("itemget02.mid", 3.0f);
		_cgDelay = 3.0f;
		break;
	case INTRO_1:
		SOUNDMANAGER->pause(GQUESTMANAGER->getCurrentMap()->getBGMKey());
		SOUNDMANAGER->play("op01.mid", 3.0f);
		_cgIndex.x = 0;
		_cgIndex.y = 9;
		_cgDelay = 35.0f / 3.0f;
		break;
	case INTRO_2:
		_cgIndex.x = 1;
		_cgIndex.y = 9;
		_cgDelay = 35.0f / 3.0f;
		break;
	case INTRO_3:
		_cgIndex.x = 2;
		_cgIndex.y = 9;
		_cgDelay = 35.0f / 3.0f;
		break;
	default:
		_cgIndex.x = 0;
		_cgIndex.y = 0;
		break;
	}
}

void cutScene::release()
{

}

void cutScene::update()
{
	if (_isCGActive)
	{
		if (_cgDelay>0)
		{
			_cgDelay -= TIMEMANAGER->getElapsedTime();
		}
		else
		{
			if (_type == INTRO_1)
			{
				showCutScene(INTRO_2);
			}
			else if (_type == INTRO_2)
			{
				showCutScene(INTRO_3);
			}
			else if (_type == INTRO_3)
			{
				_isCGActive = false;
				SOUNDMANAGER->resume(GQUESTMANAGER->getCurrentMap()->getBGMKey());
				MainGame* _maingame = (MainGame*)SCENEMANAGER->FindScene("mainGameScene");
				_maingame->getScreenEffectAddress()->init(FADE_OUT);
			}
			else
			{
				_isCGActive = false;
				SOUNDMANAGER->resume(GQUESTMANAGER->getCurrentMap()->getBGMKey());
			}

		}
	}
	

}
void cutScene::render()
{
	if (_isCGActive)
	{
		CG->frameRender(getMemDC(), 0, 0, _cgIndex.x, _cgIndex.y);
	}
}