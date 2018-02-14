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

		//�̹��� �ּ�
		_image = image;

		//�̵� ������
		_startX = image->getX();
		_startY = image->getY();

		//������
		_endX = endX;
		_endY = endY;

		//����Ÿ� ����
		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		_angle = getAngle(_startX, _startY, _endX, _endY);

		//���� Ÿ�� ����
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		//�̵��ð�
		_time = time;

		_isMoving = true;
	}
}

void action::moveTo(image* image, float endX, float endY, float time, CALLBACK_FUNCTION cbFunction)
{
	if (!_isMoving)
	{
		_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

		//�̹��� �ּ�
		_image = image;

		//�̵� ������
		_startX = image->getX();
		_startY = image->getY();

		//������
		_endX = endX;
		_endY = endY;

		//����Ÿ� ����
		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		_angle = getAngle(_startX, _startY, _endX, _endY);

		//���� Ÿ�� ����
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		//�̵��ð�
		_time = time;

		_isMoving = true;
	}
}

void action::moving(void)
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = (elapsedTime / _time) * _travelRange;

	//�̵�
	_image->setX(_image->getX() + cosf(_angle) * moveSpeed);
	_image->setY(_image->getY() + (-sinf(_angle) * moveSpeed));

	//Ÿ�� �Ŵ����� �̿��� �̹��� ����
	float time = TIMEMANAGER->getElapsedTime();

	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_image->setX(_endX);
		_image->setY(_endY);
		_isMoving = false;

		if (_callbackFunction != NULL)
		{
			//�ݹ� ȣ��
			_callbackFunction();
		}

	}
}