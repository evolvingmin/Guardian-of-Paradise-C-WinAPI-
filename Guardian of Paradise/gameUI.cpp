#include "stdafx.h"
#include "gameUI.h"
#include "Player.h"
#include "enemy.h"

gameUI::gameUI()
{
}


gameUI::~gameUI()
{
}
HRESULT gameUI::init(Player* player)
{


	//IMAGEMANAGER->addFrameImage("ElementChange", "Image/UI/ElementChange.bmp", 43 * MULTIPLY_X, 32 * MULTIPLY_Y, 1, 2, true, RGB(0, 0, 0));
	//IMAGEMANAGER->addFrameImage("ElementSelect", "Image/UI/elementSelect.bmp", 192 * MULTIPLY_X, 32 * MULTIPLY_Y, 6, 1, true, RGB(0, 0, 0));
	//IMAGEMANAGER->addFrameImage("ElementSkill", "Image/UI/ElementSkill.bmp", 144 * MULTIPLY_X, 48 * MULTIPLY_Y, 6, 3, true, RGB(0, 0, 0));
	//IMAGEMANAGER->addFrameImage("QuestItem", "Image/UI/QuestItem.bmp", 128 * MULTIPLY_X, 16 * MULTIPLY_Y, 8, 1, true, RGB(0, 0, 0));

	_statueBar = IMAGEMANAGER->findImage("StatusBar");
	_elementBackGround = IMAGEMANAGER->findImage("elementBackGround");
	_label_Player = IMAGEMANAGER->findImage("StateLable");
	_label_enemy = IMAGEMANAGER->findImage("StateLable_enemy");
	_elementSelect = IMAGEMANAGER->findImage("ElementSelect");
	_elementalSkill = IMAGEMANAGER->findImage("ElementSkill");
	_questItems = IMAGEMANAGER->findImage("QuestItem");
	_player = player;
	return S_OK;
}
void gameUI::release(void)
{

}
void gameUI::update(void)
{

}
void gameUI::render(void)
{
	_label_Player->render(getMemDC(), BASIC_UI_INTERVAL, BASIC_UI_INTERVAL);
	for (int i = 0; i < _player->getMaxHp(); i++)
		_statueBar->frameRender(getMemDC(), i*_statueBar->getFrameWidth() - 4 + BASIC_UI_INTERVAL + _label_Player->getWidth() + 10, BASIC_UI_INTERVAL+1, 0, 1);
	for (int i = 0; i < _player->getHP(); i++)
		_statueBar->frameRender(getMemDC(), i*_statueBar->getFrameWidth() - 4 + BASIC_UI_INTERVAL + _label_Player->getWidth() + 10, BASIC_UI_INTERVAL + 1, 1, 1);
	for (int i = 0; i < _player->getMaxMP(); i++)
		_statueBar->frameRender(getMemDC(), i*_statueBar->getFrameWidth() - 4 + BASIC_UI_INTERVAL + _label_Player->getWidth() + 10, _label_Player->getHeight() / 2 + BASIC_UI_INTERVAL +1, 0, 2);
	for (int i = 0; i < _player->getMP(); i++)
		_statueBar->frameRender(getMemDC(), i*_statueBar->getFrameWidth() - 4 + BASIC_UI_INTERVAL + _label_Player->getWidth() + 10, _label_Player->getHeight() / 2 + BASIC_UI_INTERVAL +1, 1, 2);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////수정요망(가라)//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_elementBackGround->render(getMemDC(), WINSIZEX - _elementBackGround->getWidth() - BASIC_UI_INTERVAL, BASIC_UI_INTERVAL);
	_elementSelect->frameRender(getMemDC(), WINSIZEX - _elementBackGround->getWidth() + 5, BASIC_UI_INTERVAL + 21, _player->getCurrentElemental(), 0);
	_elementalSkill->frameRender(getMemDC(), WINSIZEX - _elementBackGround->getWidth() + 110, BASIC_UI_INTERVAL + 41, _player->getCurrentSkill(), _player->getCurrentElemental() - 1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ITEMS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < ITEMMAX; i++)
	{
		_questItems->frameRender(getMemDC(), WINSIZEX - 340 + i * 56, WINSIZEY - 75, _player->getItems()[i], 0);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	if (_player->IsFight())
	{
		_label_enemy->render(getMemDC(), BASIC_UI_INTERVAL, WINSIZEY - _label_enemy->getHeight() - BASIC_UI_INTERVAL);

		for (int i = 0; i < _player->getFightOpponent()->getMaxHp(); i++)
			_statueBar->frameRender(getMemDC(), i*_statueBar->getFrameWidth() - 4 + BASIC_UI_INTERVAL + _label_enemy->getWidth() + 10, WINSIZEY - _label_enemy->getHeight() - BASIC_UI_INTERVAL, 0, 0);
		for (int i = 0; i < _player->getFightOpponent()->getHP(); i++)
			_statueBar->frameRender(getMemDC(), i*_statueBar->getFrameWidth() - 4 + BASIC_UI_INTERVAL + _label_enemy->getWidth()+10, WINSIZEY - _label_enemy->getHeight() - BASIC_UI_INTERVAL, 1, 0);
	}
	
}