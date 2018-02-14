#include "stdafx.h"
#include "gameObjectManager.h"
#include "gameObject.h"
gameObjectManager::gameObjectManager()
{
}


gameObjectManager::~gameObjectManager()
{
}

//�¾�
HRESULT gameObjectManager::init()
{

	return S_OK;
}

HRESULT gameObjectManager::init(DATA_STRUCTURE_TYPE dataStuructureType, float width, float height)
{
	_dataStructureType = dataStuructureType;

	if (_dataStructureType == SPATIALHASING)
		_sHgameObjectList = new SpatialHasing(width, height);
	return S_OK;
}
//����
void gameObjectManager::release(void)
{
 if (_dataStructureType == SPATIALHASING)
	{

	}
	else
		deleteAll();
	
}
void gameObjectManager::update(void)
{
	vectorGameObjectIter vGameObjectIter;

	if (_vGameObjectList.size() >= 1)
	{
		gameObject* temp;
		for (int i = 0; i < _vGameObjectList.size() - 1; i++)
		{
			for (int j = 0; j < _vGameObjectList.size() - 1; j++)
			{
				if (_vGameObjectList[i]->getZ() > _vGameObjectList[i + 1]->getZ())
				{
					temp = _vGameObjectList[i];
					_vGameObjectList[i] = _vGameObjectList[i + 1];
					_vGameObjectList[i + 1] = temp;
				}
			}

		}
	}

	for (vGameObjectIter = _vGameObjectList.begin(); vGameObjectIter != _vGameObjectList.end(); vGameObjectIter++)
	{
		if ((*vGameObjectIter) != NULL)
		{
			(*vGameObjectIter)->update();
		}

	}

	//���� �߰��� ���ӿ�����Ʈ�� ���Ϳ� �ְ�
	addGameObjectListToVecter();
	//���� ������ ������Ʈ���� �����
	removeGameObject();
}
void gameObjectManager::update(float x, float y)
{
	vectorGameObjectIter vGameObjectIter;

 if (_dataStructureType == SPATIALHASING)
	{
		vectorGameObjectList vGameObjectList = _sHgameObjectList->GetObjectsAt(x, y);
		for (int i = 0; i < vGameObjectList.size(); i++)
		{
			if (vGameObjectList[i] != NULL)
			{
				vGameObjectList[i]->update();
				_sHgameObjectList->AddObject(x, y ,vGameObjectList[i] );
				if (vGameObjectList[i]->IsDeleted())
					_sHgameObjectList->RemoveObject(x, y, vGameObjectList[i]);

			}
		}
	}
}
int compvar(gameObject* first, gameObject* second)
{
	return first->getZ() < second->getZ();
}

void gameObjectManager::setRenderOrder(void)
{
	std::sort(_vGameObjectList.begin(), _vGameObjectList.end(), compvar);
}

void gameObjectManager::render(void)
{
	
	for (int i = 0; i < _vGameObjectList.size(); i++)
	{
			_vGameObjectList[i]->render();
	}
}
void gameObjectManager::render(float x, float y)
{



 if (_dataStructureType == SPATIALHASING)
	{
		vectorGameObjectList vGameObjectList = _sHgameObjectList->GetObjectsAt(x, y);

		for (int i = 0; i < vGameObjectList.size(); i++)
		{
			if (vGameObjectList[i] != NULL)
				vGameObjectList[i]->render();
		}

	}
}

gameObject* gameObjectManager::findGameObject(string tag)
{
	if (_dataStructureType == SPATIALHASING)
	{
		//����� ���������� �׷��� ��ɻ� �߰��� �ؾ� �Ѵ�.


	}
	else
	{
		for (int i = 0; i < _vGameObjectList.size(); i++)
		{
			if (_vGameObjectList[i]->getTag() == tag)
				return _vGameObjectList[i];
		}
	}

	return  NULL;
}
gameObject* gameObjectManager::findGameObject(string tag, float x,float y)
{

	if (_dataStructureType == SPATIALHASING)
	{
		vectorGameObjectList vGameObjectList = _sHgameObjectList->GetObjectsAt(x, y);

		for (int i = 0; i < vGameObjectList.size(); i++)
		{
			if (vGameObjectList[i]->getTag() == tag)
				return vGameObjectList[i];
		}
	}
	return  NULL;
}

HRESULT gameObjectManager::addGameObject(gameObject* gObject)
{
 if (_dataStructureType == SPATIALHASING)
		_sHgameObjectList->AddObject(gObject);
	else
	{
		for (int i = 0; i < _vGameObjectList.size(); i++)
		{
			if (_vGameObjectList[i] == gObject)
				return E_FAIL;
		}
		_vGameObjectAddList.push_back(gObject);
	}


	return  S_OK;
}
HRESULT gameObjectManager::addGameObject(gameObject& gObject)
{
	if (_dataStructureType == SPATIALHASING)
		_sHgameObjectList->AddObject(&gObject);
	else
	{
		for (int i = 0; i < _vGameObjectList.size(); i++)
		{
			if (_vGameObjectList[i] == &gObject)
				return E_FAIL;
		}
		_vGameObjectAddList.push_back(&gObject);
	}


	return  S_OK;
}

void gameObjectManager::addGameObjectListToVecter()
{
	////�־�� ���� ���ӿ�����Ʈ�� �ִ´�
	vectorGameObjectIter vGameObjectIter;

	for (vGameObjectIter = _vGameObjectAddList.begin(); vGameObjectIter != _vGameObjectAddList.end();)
	{
		_vGameObjectList.push_back(*vGameObjectIter);
		vGameObjectIter = _vGameObjectAddList.erase(vGameObjectIter);
	}
}
void gameObjectManager::removeGameObject()
{
	vectorGameObjectIter vGameObjectIter;
	for (vGameObjectIter = _vGameObjectList.begin(); vGameObjectIter != _vGameObjectList.end(); )
	{
		if ((*vGameObjectIter)->IsDeleted())
		{
			(*vGameObjectIter)->release();
			vGameObjectIter = _vGameObjectList.erase(vGameObjectIter);
		}
		else
			vGameObjectIter++;
	}
}
HRESULT gameObjectManager::removeGameObject(gameObject* gObject)
{
	vectorGameObjectIter vGameObjectIter;
	for (vGameObjectIter = _vGameObjectList.begin(); vGameObjectIter != _vGameObjectList.end(); vGameObjectIter++)
	{
		if ((*vGameObjectIter) == gObject)
		{
			_vGameObjectList.erase(vGameObjectIter);
			return  S_OK;
		}
	}
	return E_FAIL;

}
BOOL gameObjectManager::deleteAll(void)
{
	vectorGameObjectIter vGameObjectIter = _vGameObjectList.begin();

	for (; vGameObjectIter != _vGameObjectList.end();)
	{
		if ((*vGameObjectIter) != NULL)
		{
			vGameObjectIter = _vGameObjectList.erase(vGameObjectIter);
		}
		else
		{
			++vGameObjectIter;
		}
	}
	_vGameObjectList.clear();
	return TRUE;
}
METHOD_CALLBACK* gameObjectManager::addGameEvent(string strKey, METHOD_CALLBACK* _gameEvent)
{

	//������ �����̺�Ʈ�� �ִ��� ã�´�
	METHOD_CALLBACK* gEvent = findGameEvent(strKey);

	

	//Ű ���� ���� �����̺�Ʈ�� ������ �߰� ���� �ʰ� ������ �����̺�Ʈ�� �ҷ��´�
	if (gEvent) return gEvent;


	//������ �����̺�Ʈ�� �� ����Ʈ�� �߰�����
	_mGameEventList.insert(make_pair(strKey, _gameEvent));

	return _gameEvent;
}
METHOD_CALLBACK* gameObjectManager::findGameEvent(string strKey)
{
	//�ش�Ű�� �ִ��� �˻��Ѵ�
	mapGameEventIter key = _mGameEventList.find(strKey);

	//Ű�� ã����
	if (key != _mGameEventList.end())
	{
		return (key->second);
	}

	return nullptr;
}
void gameObjectManager::activateEvent(string strKey)
{
	METHOD_CALLBACK* tEvent = nullptr;

	for (int i = 0; i < _vGameObjectList.size(); i++)
	{
		tEvent = findGameEvent(strKey);
		if (tEvent != nullptr)
			(*tEvent)(_vGameObjectList[i]);
	}
}
void gameObjectManager::activateEvent(string strKey, float x, float y)
{
	METHOD_CALLBACK* tEvent = nullptr;

	 if (_dataStructureType == SPATIALHASING)
	{
		vectorGameObjectList vGameObjectList = _sHgameObjectList->GetObjectsAt(x, y);

			for (int i = 0; i < vGameObjectList.size(); i++)
			{
				tEvent = findGameEvent(strKey);
				if (tEvent != nullptr)
					(*tEvent)(vGameObjectList[i]);
			}

	}
}
bool gameObjectManager::colliderCheck(vectorGameObjectList vgameObjectList)
{
	//�ֶܼ� ��� ���̽������� ��������������Ŷ� ������ ����.
	COLLIDERTYPE prevType;
	COLLIDERTYPE nextType;
	for (int prev = 0; prev < vgameObjectList.size(); prev++)
	{
		if (!(vgameObjectList[prev]->_isColliderOn) || vgameObjectList[prev]->IsDeleted())
			continue;

		for (int next = 0; next < vgameObjectList.size(); next++)
		{
			if (!(vgameObjectList[next]->_isColliderOn) || vgameObjectList[next]->IsDeleted())
				continue;
			if (prev != next)
			{
				prevType = vgameObjectList[prev]->getCOLLIDERTYPE();
				nextType = vgameObjectList[next]->getCOLLIDERTYPE();
				switch (prevType)
				{
				case COLLIDERTYPE::COLL_POINT:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (vgameObjectList[prev]->getX() == vgameObjectList[next]->getX() && vgameObjectList[prev]->getY() == vgameObjectList[next]->getY())
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						if (PtInRect(&vgameObjectList[next]->boundingBox(), PointMake(vgameObjectList[prev]->getX(), vgameObjectList[prev]->getY())))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndPoint(vgameObjectList[next]->getX(), vgameObjectList[next]->getY(), vgameObjectList[next]->getRadius(), vgameObjectList[prev]->getX(), vgameObjectList[next]->getY()))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					}
					break;
				case COLLIDERTYPE::COLL_RECTANGLE:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (PtInRect(&vgameObjectList[prev]->boundingBox(), PointMake(vgameObjectList[next]->getX(), vgameObjectList[next]->getY())))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						RECT temp;
						if (IntersectRect(&temp, &vgameObjectList[prev]->boundingBox(), &vgameObjectList[next]->boundingBox()))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndRectangle(vgameObjectList[next]->getX(), vgameObjectList[next]->getY(), vgameObjectList[next]->getRadius(), vgameObjectList[prev]->boundingBox()))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					}
					break;
				case COLLIDERTYPE::COLL_ELLIPSE:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (isCollisionCircleAndPoint(vgameObjectList[prev]->getX(), vgameObjectList[prev]->getY(), vgameObjectList[prev]->getRadius(), vgameObjectList[next]->getX(), vgameObjectList[prev]->getY()))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						if (isCollisionCircleAndRectangle(vgameObjectList[prev]->getX(), vgameObjectList[prev]->getY(), vgameObjectList[prev]->getRadius(), vgameObjectList[next]->boundingBox()))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndCircle(vgameObjectList[prev]->getX(), vgameObjectList[prev]->getY(), vgameObjectList[prev]->getRadius(), vgameObjectList[next]->getX(), vgameObjectList[next]->getY(), vgameObjectList[next]->getRadius()))
							vgameObjectList[prev]->onCollideEnter(vgameObjectList[next]);
						break;
					}
					break;
				}
			}
		}
	}
	return true;
}
bool gameObjectManager::colliderCheck()
{
	
	//�ֶܼ� ��� ���̽������� ��������������Ŷ� ������ ����.
	COLLIDERTYPE prevType;
	COLLIDERTYPE nextType;
	for (int prev = 0; prev < _vGameObjectList.size(); prev++)
	{
		if (!(_vGameObjectList[prev]->_isColliderOn))
			continue;

		for (int next = 0; next < _vGameObjectList.size(); next++)
		{
			if (!(_vGameObjectList[next]->_isColliderOn))
				continue;
			if (prev != next)
			{
				prevType = _vGameObjectList[prev]->getCOLLIDERTYPE();
				nextType = _vGameObjectList[next]->getCOLLIDERTYPE();
				switch (prevType)
				{
				case COLLIDERTYPE::COLL_POINT:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (_vGameObjectList[prev]->getX() == _vGameObjectList[next]->getX() && _vGameObjectList[prev]->getY() == _vGameObjectList[next]->getY())
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						if (PtInRect(&_vGameObjectList[next]->boundingBox(), PointMake(_vGameObjectList[prev]->getX(), _vGameObjectList[prev]->getY())))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndPoint(_vGameObjectList[next]->getX(), _vGameObjectList[next]->getY(), _vGameObjectList[next]->getRadius(), _vGameObjectList[prev]->getX(), _vGameObjectList[next]->getY()))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					}
					break;
				case COLLIDERTYPE::COLL_RECTANGLE:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (PtInRect(&_vGameObjectList[prev]->boundingBox(), PointMake(_vGameObjectList[next]->getX(), _vGameObjectList[next]->getY())))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						RECT temp;
						if (IntersectRect(&temp, &_vGameObjectList[prev]->boundingBox(), &_vGameObjectList[next]->boundingBox()))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndRectangle(_vGameObjectList[next]->getX(), _vGameObjectList[next]->getY(), _vGameObjectList[next]->getRadius(), _vGameObjectList[prev]->boundingBox()))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					}
					break;
				case COLLIDERTYPE::COLL_ELLIPSE:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (isCollisionCircleAndPoint(_vGameObjectList[prev]->getX(), _vGameObjectList[prev]->getY(), _vGameObjectList[prev]->getRadius(), _vGameObjectList[next]->getX(), _vGameObjectList[prev]->getY()))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						if (isCollisionCircleAndRectangle(_vGameObjectList[prev]->getX(), _vGameObjectList[prev]->getY(), _vGameObjectList[prev]->getRadius(), _vGameObjectList[next]->boundingBox()))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndCircle(_vGameObjectList[prev]->getX(), _vGameObjectList[prev]->getY(), _vGameObjectList[prev]->getRadius(), _vGameObjectList[next]->getX(), _vGameObjectList[next]->getY(), _vGameObjectList[next]->getRadius()))
							_vGameObjectList[prev]->onCollideEnter(_vGameObjectList[next]);
						break;
					}
					break;
				}
			}
		}
	}
	return true;
}
bool gameObjectManager::colliderCheck(float x, float y)
{
	vectorGameObjectList vGameObjectList;

	if (_dataStructureType == SPATIALHASING)
		vGameObjectList = _sHgameObjectList->GetObjectsAt(x, y);



	COLLIDERTYPE prevType;
	COLLIDERTYPE nextType;
	for (int prev = 0; prev < vGameObjectList.size(); prev++)
	{
		for (int next = 0; next < vGameObjectList.size(); next++)
		{
			if (prev != next)
			{
				prevType = vGameObjectList[prev]->getCOLLIDERTYPE();
				nextType = vGameObjectList[next]->getCOLLIDERTYPE();
				switch (prevType)
				{
				case COLLIDERTYPE::COLL_POINT:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (vGameObjectList[prev]->getX() == vGameObjectList[next]->getX() && vGameObjectList[prev]->getY() == vGameObjectList[next]->getY())
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						if (PtInRect(&vGameObjectList[next]->boundingBox(), PointMake(vGameObjectList[prev]->getX(), vGameObjectList[prev]->getY())))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndPoint(vGameObjectList[next]->getX(), vGameObjectList[next]->getY(), vGameObjectList[next]->getRadius(), vGameObjectList[prev]->getX(), vGameObjectList[next]->getY()))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					}
					break;
				case COLLIDERTYPE::COLL_RECTANGLE:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (PtInRect(&vGameObjectList[prev]->boundingBox(), PointMake(vGameObjectList[next]->getX(), vGameObjectList[next]->getY())))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						RECT temp;
						if (IntersectRect(&temp, &vGameObjectList[prev]->boundingBox(), &vGameObjectList[next]->boundingBox()))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndRectangle(vGameObjectList[next]->getX(), vGameObjectList[next]->getY(), vGameObjectList[next]->getRadius(), vGameObjectList[prev]->boundingBox()))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					}
					break;
				case COLLIDERTYPE::COLL_ELLIPSE:
					switch (nextType)
					{
					case COLLIDERTYPE::COLL_POINT:
						if (isCollisionCircleAndPoint(vGameObjectList[prev]->getX(), vGameObjectList[prev]->getY(), vGameObjectList[prev]->getRadius(), vGameObjectList[next]->getX(), vGameObjectList[prev]->getY()))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_RECTANGLE:
						if (isCollisionCircleAndRectangle(vGameObjectList[prev]->getX(), vGameObjectList[prev]->getY(), vGameObjectList[prev]->getRadius(), vGameObjectList[next]->boundingBox()))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					case COLLIDERTYPE::COLL_ELLIPSE:
						if (isCollisionCircleAndCircle(vGameObjectList[prev]->getX(), vGameObjectList[prev]->getY(), vGameObjectList[prev]->getRadius(), vGameObjectList[next]->getX(), vGameObjectList[next]->getY(), vGameObjectList[next]->getRadius()))
							vGameObjectList[prev]->onCollideEnter(vGameObjectList[next]);
						break;
					}
					break;
				}
			}
		}
	}
	return true;
}