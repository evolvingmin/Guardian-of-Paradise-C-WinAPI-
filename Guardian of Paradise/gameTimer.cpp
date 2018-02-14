#include "stdafx.h"
#include "gameTimer.h"


gameTimer::gameTimer()
{
	_timer = new timer;
	_isSaveActive = false;
}


gameTimer::~gameTimer()
{
	SAFE_DELETE(_timer);
}

void gameTimer::ActiveTimer()
{

	if (!_isSaveActive)
	{
		_isSaveActive = true;
		_timer->init();
	}


}
void gameTimer::DeActiveTimer()
{
	_isSaveActive = false;
}
void gameTimer::update()
{
	if (_isSaveActive)
	{
		_timer->tick(60.0f);
	}
}
bool gameTimer::IsElapsedAt(float time, bool isContinue)
{
	if (_isSaveActive)
	{
		if (_timer->getWorldTime() > time)
		{
			if (!isContinue)
				DeActiveTimer();
			return true;
		}

		else
			return false;
	}
	else
		return false;
}
bool gameTimer::ActiveWhile(float time)
{
	if (_isSaveActive)
	{
		update();
		if (_timer->getWorldTime() > time)
		{
			DeActiveTimer();
			return false;
		}
		else
			return true;
	}
	else
		return false;
}
