#include "stdafx.h"
#include "gameObject.h"


gameObject::gameObject() 
{
}
gameObject::~gameObject()
{
}
//기본 초기화, 
HRESULT gameObject::init()
{
	_gameObjectInfo = make_shared < gameObject_INFO >() ;
	_COLLIDERTYPE = COLL_NONE;


	return S_OK;
}
//점초기화
HRESULT gameObject::init(string tag, float x, float y, float speed, float angle, bool isColliderOn)
{

	//콜라이더 정보설정
	_gameObjectInfo = make_shared < gameObject_INFO >();
	_COLLIDERTYPE = COLL_POINT;
	_isColliderOn = isColliderOn;
	_gameObjectInfo->x = x;
	_gameObjectInfo->y = y;
	_gameObjectInfo->speed = speed;
	_gameObjectInfo->angle = angle;
	_gameObjectInfo->width = 0.0f;
	_gameObjectInfo->height = 0.0f;
	_gameObjectInfo->tag = tag;

	return S_OK;
}

//사각형 초기화
HRESULT gameObject::init(string tag, float x, float y, float width, float height, float speed, float angle, bool isColliderOn)
{

	//콜라이더 정보설정
	_gameObjectInfo = make_shared<gameObject_INFO>();
	_COLLIDERTYPE = COLL_RECTANGLE;
	_isColliderOn = isColliderOn;
	_gameObjectInfo->x = x;
	_gameObjectInfo->y = y;
	_gameObjectInfo->speed = speed;
	_gameObjectInfo->angle = angle;
	_gameObjectInfo->width = width;
	_gameObjectInfo->height = height;
	_gameObjectInfo->radius = _gameObjectInfo->width / 2;
	_gameObjectInfo->tag = tag;

	return S_OK;
}

HRESULT gameObject::init(string tag, RECT rect, float speed, float angle, bool isColliderOn)
{


	//콜라이더 정보설정
	_gameObjectInfo = make_shared < gameObject_INFO >();
	_COLLIDERTYPE = COLL_RECTANGLE;
	_isColliderOn = isColliderOn;
	_gameObjectInfo->x = rect.left;
	_gameObjectInfo->y = rect.top;
	_gameObjectInfo->speed = speed;
	_gameObjectInfo->angle = angle;
	_gameObjectInfo->width = rect.right - rect.left;
	_gameObjectInfo->height = rect.bottom - rect.top;
	_gameObjectInfo->radius = _gameObjectInfo->width / 2;
	_gameObjectInfo->tag = tag;

	return S_OK;
}

//원초기화
HRESULT gameObject::init(string tag, float x, float y, float radius, float speed, float angle, bool isColliderOn)
{
	//초기화가 다시 되는것을 방지
	if (_gameObjectInfo != NULL) release();

	//콜라이더 정보설정
	_gameObjectInfo = make_shared < gameObject_INFO >();
	_COLLIDERTYPE = COLL_ELLIPSE;
	_isColliderOn = isColliderOn;
	_gameObjectInfo->x = x;
	_gameObjectInfo->y = y;
	_gameObjectInfo->speed = speed;
	_gameObjectInfo->angle = angle;
	_gameObjectInfo->radius = radius;
	_gameObjectInfo->tag = tag;
	_gameObjectInfo->height = radius * 2;
	_gameObjectInfo->width = radius * 2;

	return S_OK;
}
