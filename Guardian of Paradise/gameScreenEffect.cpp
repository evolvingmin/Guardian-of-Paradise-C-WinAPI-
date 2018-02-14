#include "stdafx.h"
#include "gameScreenEffect.h"


gameScreenEffect::gameScreenEffect()
{
}


gameScreenEffect::~gameScreenEffect()
{
}
HRESULT gameScreenEffect::init(EFFECT effect)
{
	_currentEffect = effect;
	
	//_fadeRect[0] = left
	//_fadeRect[1] = top
	//_fadeRect[2] = right
	//_fadeRect[3] = bottom
	switch (_currentEffect)
	{
	case 	FADE_IN:
		_fadeRect[0] = RectMake(0, 0, 0, WINSIZEY);
		_fadeRect[1] = RectMake(0, 0, WINSIZEX, 0);
		_fadeRect[2] = RectMake(WINSIZEX, 0, WINSIZEX, WINSIZEY);
		_fadeRect[3] = RectMake(0, WINSIZEY, WINSIZEX, WINSIZEY);

		for (int i = 0; i < 4; i++)
		{
			_fadeImage[i] = new image;
			_fadeImage[i]->init("Image/etc/FADE.bmp", (float)_fadeRect[i].left, (float)_fadeRect[i].top, _fadeRect[i].right - _fadeRect[i].left, _fadeRect[i].bottom - _fadeRect[i].top, false, 0UL);
		}
		_addFactor = 4.5f;
		_effectTime = 0.8f;
		break;
	case	FADE_OUT:
		_fadeRect[0] = RectMake(0, 0, WINSIZEX/2, WINSIZEY);
		_fadeRect[1] = RectMake(0, 0, WINSIZEX, WINSIZEY/2);
		_fadeRect[2] = RectMake(WINSIZEX / 2, 0, WINSIZEX, WINSIZEY);
		_fadeRect[3] = RectMake(0, WINSIZEY / 2, WINSIZEX, WINSIZEY);
		for (int i = 0; i < 4; i++)
		{
			_fadeImage[i] = new image;
			_fadeImage[i]->init("Image/etc/FADE.bmp", (float)_fadeRect[i].left, (float)_fadeRect[i].top, _fadeRect[i].right - _fadeRect[i].left, _fadeRect[i].bottom - _fadeRect[i].top, false, 0UL);
		}
		_addFactor = 4.5f;
		_effectTime = 0.8f;
		break;
	case NONE:
		_addFactor = 0;
		_effectTime = 0;
		break;

	}


	return S_OK; 
	

}
void gameScreenEffect ::update()
{
	
	//if (_effectTime <= 0)
	//	release();

	if (_effectTime > 0)
	{
		_effectTime -= TIMEMANAGER->getElapsedTime();
		switch (_currentEffect)
		{
		case FADE_IN:
			_fadeRect[0].right += _addFactor * 4;
			_fadeRect[1].bottom += _addFactor *2.5f;
			_fadeRect[2].left -= _addFactor * 4;
			_fadeRect[3].top -= _addFactor*2.5f;
			break;
		case FADE_OUT:
			_fadeRect[0].right -= _addFactor * 4;
			_fadeRect[1].bottom -= _addFactor *2.5f;
			_fadeRect[2].left += _addFactor * 4;
			_fadeRect[3].top += _addFactor*2.5f;
			break;
		}

	}

}
void gameScreenEffect::release()
{
	for (int i = 0; i < 4; i++)
		SAFE_RELEASE(_fadeImage[i]);

}
void gameScreenEffect::render()
{
	if (_effectTime > 0)
	{
		for (int i = 0; i < 4; i++)
			_fadeImage[i]->render(getMemDC(), _fadeRect[i].left, _fadeRect[i].top, 0, 0, _fadeRect[i].right - _fadeRect[i].left, _fadeRect[i].bottom - _fadeRect[i].top);
	}
}