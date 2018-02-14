#include "stdafx.h"
#include "gameAnimation.h"

gameAnimation::gameAnimation()
{
	_direction = DIR_LEFT;
	_state = STATE_END;
	_alphaValue = 255;
}
gameAnimation::~gameAnimation()
{

}
HRESULT gameAnimation::init(image* image, DIRECTION direction, STATE state)
{
	_direction = direction;
	_state = state;
	_mainImage = image;


	return S_OK;
}

//기본 프레임 에니메이션
void gameAnimation::SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop)
{
	animation* ani = new animation;

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);


	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
void gameAnimation::SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop, void* cbFunction)
{
	animation* ani = new animation;

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
void gameAnimation::SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	animation* ani = new animation;

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
//배열 에니메이션
void gameAnimation::SetArrayFrameAnimation(DIRECTION direction, STATE state, int*arr, int arrLen, int fps, bool loop)
{
	animation* ani = new animation;


	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));

}
void gameAnimation::SetArrayFrameAnimation(DIRECTION direction, STATE state, int* arr, int arrLen, int fps, bool loop, void* cbFunction)
{
	animation* ani = new animation;


	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
void gameAnimation::SetArrayFrameAnimation(DIRECTION direction, STATE state, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj)
{
	animation* ani = new animation;
	

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
//구간 에니메이션
void gameAnimation::SetCoordinateFrameAnimation(DIRECTION direction, STATE state, int start, int end, int fps, bool reverse, bool loop)
{
	animation* ani = new animation;

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
void gameAnimation::SetCoordinateFrameAnimation(DIRECTION direction, STATE state, int start, int end, int fps, bool reverse, bool loop, void* cbFunction)
{
	animation* ani = new animation;

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}
void gameAnimation::SetCoordinateFrameAnimation(DIRECTION direction, STATE state, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	animation* ani = new animation;

	ani->init(_mainImage->getWidth(), _mainImage->getHeight(), _mainImage->getFrameWidth(), _mainImage->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	if (direction == DIR_ALL)
	{
		for (int i = 0; i < 4; i++)
			_mGameAnimation.insert(make_pair(make_pair((DIRECTION)i, state), ani));
	}
	else
		_mGameAnimation.insert(make_pair(make_pair(direction, state), ani));
}

void gameAnimation::render(float x, float y)
{
	_mainImage->aniRenderAlpha(getMemDC(), x, y, _mGameAnimation[make_pair(_direction, _state)], _alphaValue);
}
void gameAnimation::frameUpdate()
{
	_mGameAnimation[make_pair(_direction, _state)]->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}
void gameAnimation::release(void)
{
	map<pair<DIRECTION, STATE>, animation* >::iterator iter = _mGameAnimation.begin();

	for (; iter != _mGameAnimation.end();)
	{
		if (iter->second != NULL)
		{

			SAFE_RELEASE(iter->second);
			iter = _mGameAnimation.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mGameAnimation.clear();
}
void gameAnimation::deleteStateAnimation(STATE state)
{
	map<pair<DIRECTION, STATE>, animation* >::iterator iter = _mGameAnimation.begin();
	for (; iter != _mGameAnimation.end();)
	{
		if (iter->first.second == state)
		{

			SAFE_RELEASE(iter->second);
			iter = _mGameAnimation.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}