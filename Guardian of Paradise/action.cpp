#include "stdafx.h"
#include "action.h"


action::action()
{
}


action::~action()
{
}

HRESULT action::init(void)
{
	_callbackFunction = NULL;
	_worldTimeCount = 0.0f;
	_isMoving = false;

	return S_OK;
}

void action::release(void)
{

}

void action::update(void)
{
	moving();
}

void action::render(void)
{

}

void action::moveTo(image* image, float endX, float endY, float time)
{
	if (!_isMoving)
	{
		_callbackFunction = NULL;

		//이미지 주소
		_image = image;

		//이동 시작점
		_startX = image->getX();
		_startY = image->getY();

		//도착점
		_endX = endX;
		_endY = endY;

		//여행거리 구함
		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		_angle = getAngle(_startX, _startY, _endX, _endY);

		//월드 타임 저장
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		//이동시간
		_time = time;

		_isMoving = true;
	}
}

void action::moveTo(image* image, float endX, float endY, float time, CALLBACK_FUNCTION cbFunction)
{
	if (!_isMoving)
	{
		_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

		//이미지 주소
		_image = image;

		//이동 시작점
		_startX = image->getX();
		_startY = image->getY();

		//도착점
		_endX = endX;
		_endY = endY;

		//여행거리 구함
		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		_angle = getAngle(_startX, _startY, _endX, _endY);

		//월드 타임 저장
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		//이동시간
		_time = time;

		_isMoving = true;
	}
}

void action::moving(void)
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = (elapsedTime / _time) * _travelRange;

	//이동
	_image->setX(_image->getX() + cosf(_angle) * moveSpeed);
	_image->setY(_image->getY() + (-sinf(_angle) * moveSpeed));

	//타임 매니져를 이용한 이미지 무빙
	float time = TIMEMANAGER->getElapsedTime();

	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_image->setX(_endX);
		_image->setY(_endY);
		_isMoving = false;

		if (_callbackFunction != NULL)
		{
			//콜백 호출
			_callbackFunction();
		}

	}
}