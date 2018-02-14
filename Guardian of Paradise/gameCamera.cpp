#include "stdafx.h"
#include "gameCamera.h"
#include "gameObject.h"
#include "gameObjectManager.h"


gameCamera::gameCamera()
{
}


gameCamera::~gameCamera()
{
}


void gameCamera::init(bool isControlable , RECT mapSize)
{

	_isControlable = isControlable;
	_isMovableCamera = _isFocused = false;
	_mapSize = mapSize;
	_x = 0;
	_y = 0;
	_cameraView = RectMake(_x, _y, WINSIZEX, WINSIZEY);
	_speed = 50.0f;
	_focusSpeed = 70.0f;
}
void gameCamera::onFocus(gameObject* object, bool instanceFocus)
{

	_isMovableCamera = _isFocused = true;
	_instanceFocus = instanceFocus;
	_focusedObject = object;

	_x = _focusedObject->boundingBox().left - (WINSIZEX / 2 - _focusedObject->getWidth() / 2);
	_y = _focusedObject->boundingBox().top - (WINSIZEY / 2 - _focusedObject->getHeight() / 2);

	//맵사이즈에 대한 보정
	if (_x < (float)_mapSize.left)
		_x = (float)_mapSize.left;
	if (_y < (float)_mapSize.top)
		_y = (float)_mapSize.top;
	if (_x + WINSIZEX>(float)_mapSize.right)
		_x = (float)_mapSize.right - WINSIZEX;
	if (_y + WINSIZEY>(float)_mapSize.bottom)
		_y = (float)_mapSize.bottom - WINSIZEY;

	_cameraView = RectMake(_x, _y, WINSIZEX, WINSIZEY);
}
void gameCamera::onFocus(gameObject& object, bool instanceFocus)
{

	_isMovableCamera = _isFocused = true;
	_instanceFocus = instanceFocus;
	_focusedObject = &object;

	_x = _focusedObject->boundingBox().left - (WINSIZEX / 2 - _focusedObject->getWidth() / 2);
	_y = _focusedObject->boundingBox().top - (WINSIZEY / 2 - _focusedObject->getHeight() / 2);

	//맵사이즈에 대한 보정
	if (_x < (float)_mapSize.left)
		_x = (float)_mapSize.left;
	if (_y < (float)_mapSize.top)
		_y = (float)_mapSize.top;
	if (_x + WINSIZEX>(float)_mapSize.right)
		_x = (float)_mapSize.right - WINSIZEX;
	if (_y + WINSIZEY>(float)_mapSize.bottom)
		_y = (float)_mapSize.bottom - WINSIZEY;

	_cameraView = RectMake(_x, _y, WINSIZEX, WINSIZEY);
}
void gameCamera::render()
{

	if (_isMovableCamera)
	{
		cameraRender();
	}
	else
		GOBJECTMANAGER->render();

}
void gameCamera::update()
{
	if (_isMovableCamera)
	{
		if (_isFocused)
		{
			
			float fX = _focusedObject->boundingBox().left - (WINSIZEX / 2 - _focusedObject->getWidth()/2);
			float fY = _focusedObject->boundingBox().top - (WINSIZEY / 2 - _focusedObject->getHeight()/2);

			//맵사이즈에 대한 보정
			if (fX < (float)_mapSize.left)
				fX = (float)_mapSize.left;
			if (fY < (float)_mapSize.top)
				fY = (float)_mapSize.top;
			if (fX + WINSIZEX>(float)_mapSize.right)
				fX = (float)_mapSize.right - WINSIZEX;
			if (fY + WINSIZEY> _mapSize.bottom)
				fY = (float)_mapSize.bottom - WINSIZEY;

			if (_instanceFocus)
			{
				_x = fX;
				_y = fY;
			}
			else
			{
				float angle;
				angle = getAngle(_x, _y, fX, fY);

				if (abs(_x - fX) < _focusSpeed  && abs(_y - fY) < _focusSpeed)
				{
					_x = fX;
					_y = fY;

				}

				else
				{
					_x += cosf(angle) * _focusSpeed;
					_y += -sinf(angle) *_focusSpeed;
				}

			}

		}

		if (_isControlable)
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_y -= _speed;
				_isFocused = false;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_y += _speed;
				_isFocused = false;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_x -= _speed;
				_isFocused = false;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_x += _speed;
				_isFocused = false;
			}
		}


		//맵사이즈에 대한 보정
		if (_x < (float)_mapSize.left)
			_x = (float)_mapSize.left;
		if (_y < (float)_mapSize.top)
			_y = (float)_mapSize.top;
		if (_x + WINSIZEX>(float)_mapSize.right)
			_x = (float)_mapSize.right - WINSIZEX;
		if (_y + WINSIZEY>(float)_mapSize.bottom)
			_y = (float)_mapSize.bottom - WINSIZEY;


		_cameraView = RectMake(_x, _y, WINSIZEX, WINSIZEY);
		
	}

	if (_isMovableCamera)
		cameraUpdate();
	else
		GOBJECTMANAGER->update();
}

void gameCamera::cameraUpdate()
{
	vectorGameObjectList  vGameObjectList = GOBJECTMANAGER->getVectorData();
	vectorGameObjectList vGameCollideList;
	for (int i = 0; i <(signed) vGameObjectList.size(); i++)
	{
		RECT rcTemp;
		vGameObjectList[i]->update();
		if (!(IntersectRect(&rcTemp, &(vGameObjectList[i]->boundingBox()), &_cameraView)))
			continue;
		vGameCollideList.push_back(vGameObjectList[i]);
	}
	



	GOBJECTMANAGER->addGameObjectListToVecter();
	GOBJECTMANAGER->removeGameObject();
	GOBJECTMANAGER->setRenderOrder();
	GOBJECTMANAGER->colliderCheck(vGameCollideList);
}

void gameCamera::cameraRender()
{

	vectorGameObjectList  vGameObjectList = GOBJECTMANAGER->getVectorData();
	for (int i = 0; i <(signed)vGameObjectList.size(); i++)
	{
		RECT rcTemp;

		if (vGameObjectList[i] == _focusedObject && _isFocused && _instanceFocus)
			vGameObjectList[i]->render(WINSIZEX / 2 - (vGameObjectList[i]->getWidth() / 2), WINSIZEY / 2 - (vGameObjectList[i]->getHeight() / 2));
		else 
		{
			if (!(IntersectRect(&rcTemp, &(vGameObjectList[i]->boundingBox()), &_cameraView)))
				continue;

			float x = (vGameObjectList[i]->boundingBox().left - _cameraView.left);
			float y = (vGameObjectList[i]->boundingBox().top - _cameraView.top);
			if (!vGameObjectList[i]->IsDeleted())
				vGameObjectList[i]->render(x, y);
		}
	}
}
//for shared_ptr
void gameCamera::cameraRender(gameObject& object)
{
	RECT rcTemp;
	float x, y;

	if (!(IntersectRect(&rcTemp, &(object.boundingBox()), &_cameraView))) return;
	x = static_cast<float>(object.boundingBox().left - _cameraView.left);
	y = static_cast<float>(object.boundingBox().top - _cameraView.top);
	object.render(x, y);

}
void gameCamera::cameraRender(float _x, float _y)
{

	vector<gameObject*> temp = GOBJECTMANAGER->getSpatialHasingData()->GetObjectsAt(_x, _y);

	
	for (int i = 0; i <temp.size(); i++)
	{
		float x, y;

		if (_isMovableCamera)
		{
			if (temp[i] == _focusedObject && _isFocused && _instanceFocus)
			{
				temp[i]->render(WINSIZEX / 2 - (temp[i]->getWidth() / 2), WINSIZEY / 2 - (temp[i]->getHeight() / 2));
			}
			else
			{
				x = static_cast<float>(temp[i]->boundingBox().left - _cameraView.left);
				y = static_cast<float>(temp[i]->boundingBox().top - _cameraView.top);
				temp[i]->render(x, y);
			}
		}

	}
}
void gameCamera::release()
{

}

