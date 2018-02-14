#pragma once
#include "stdafx.h"
#include "gameNode.h"
//�浹�ϴ� ��ü�� Ÿ���� ����
//����� �簢��, ��, �� �� ������ �̷������.


enum COLLIDERTYPE
{
	COLL_RECTANGLE,
	COLL_ELLIPSE,
	COLL_POINT,
	COLL_NONE
};

class gameObject :public gameNode
{
public:
	typedef struct tagGameObjectInfo
	{

		//Ŭ���� ���� �̰��� � ��ü������ �����ϱ� ���� �ױ�.
		string tag;
		//�ױ׷ε� �����ϴٸ�, name���� ���� ��Ȯ�� ��븦 ������ �� �ִ�. (����ũ ���Ͷ����)
		string name;
		//�̼�
		float speed;
		float angle;
		float x, y, z;
		float radius;
		float width;
		float height;
		bool isDeleted;

		tagGameObjectInfo()
		{
			x = y = z = 0;
			width = 0;
			height = 0;
			radius = 0;
			angle = 0;
			speed = 0;
			isDeleted = false;
		}
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(tag), CEREAL_NVP(name), CEREAL_NVP(speed), CEREAL_NVP(angle),
				CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z), CEREAL_NVP(radius),
				CEREAL_NVP(width),CEREAL_NVP(height), CEREAL_NVP(isDeleted));
		}
	}gameObject_INFO, *LPGameObject_INFO;
private:
	COLLIDERTYPE _COLLIDERTYPE;
	shared_ptr<gameObject_INFO> _gameObjectInfo;
	
	friend class cereal::access;
	//����ȭ �ڵ�
public:
	//����ȭ �ڵ�, ���� ������Ʈ ���� ���.
	bool _isColliderOn;
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(_COLLIDERTYPE) ,CEREAL_NVP(_gameObjectInfo));
	}

	gameObject();
	~gameObject();
	//�⺻ �ʱ�ȭ, �ݶ��̴� ���� ���� �������� ����.
	HRESULT init();
	//�� �ʱ�ȭ
	HRESULT init(string tag, float x, float y, float speed, float angle, bool isColliderOn = true);
	//�簢�� �ʱ�ȭ
	HRESULT init(string tag, float x, float y, float width, float height, float speed, float angle, bool isColliderOn = true);
	//�簢�� �ʱ�ȭ
	HRESULT init(string tag, RECT rect, float speed, float angle, bool isColliderOn = true);
	//���ʱ�ȭ
	HRESULT init(string tag, float x, float y, float radius, float speed, float angle, bool isColliderOn = true);


	//������Ʈ
	virtual void update(void){}
	//����
	virtual void render(void){}
	//����, ���� ���̵� ����ؼ� ��ǥ�� �ܺο��� �������� �ʿ䰡 �ִ�.
	virtual void render(float x, float y){}
	//�浹ó��
	virtual void onCollideEnter(gameObject* gObject) {}



	//COLLIDERTYPE
	inline COLLIDERTYPE getCOLLIDERTYPE(void) { return _COLLIDERTYPE; }
	inline void setCOLLIDERTYPE(COLLIDERTYPE collideType) { _COLLIDERTYPE = collideType; }
	//name
	inline void setName(string name) { _gameObjectInfo->name = name; }
	inline string getName(void) { return _gameObjectInfo->name; }
	//tag
	inline void setTag(string tag) { _gameObjectInfo->tag = tag; }
	inline string getTag(void) { return _gameObjectInfo->tag; }

	//��ǥ X
	inline void setX(float x) { _gameObjectInfo->x = x;   }
	inline float getX(void) { return _gameObjectInfo->x; }

	//��ǥ Y
	inline void setY(float y) { _gameObjectInfo->y = y; }
	inline float getY(void) { return _gameObjectInfo->y; }

	//��ǥ Z, ���⼭�� ���� ������ ���� ��.
	inline void setZ(float z) { _gameObjectInfo->z = z; }
	inline float getZ(void) { return _gameObjectInfo->z; }

	//������
	inline void setRadius(float radius) { _gameObjectInfo->radius = radius; }
	inline float getRadius(void) { return _gameObjectInfo->radius; }

	//����
	inline void setObjectAngle(float angle) 
	{ 
		while (angle > PI2)
			angle -= PI2;
		
		while (angle < 0)
			angle += PI2;

		_gameObjectInfo->angle = angle; 
	}
	inline float getObjectAngle(void) { return _gameObjectInfo->angle; }

	//�̼�
	inline float getSpeed(){ return _gameObjectInfo->speed; }
	inline void setSpeed(float speed){ _gameObjectInfo->speed = speed; }

	//��ǥ ����
	inline void setCenter(float x, float y){	_gameObjectInfo->x = x - (_gameObjectInfo->width / 2);_gameObjectInfo->y = y - (_gameObjectInfo->height / 2);}
	//���� x
	inline float getCenterX(void){return  _gameObjectInfo->x + (_gameObjectInfo->width / 2.0f);}
	//���� y
	inline float getCenterY(void){ return _gameObjectInfo->y + (_gameObjectInfo->height / 2.0f); }
	
	//���� �ػ�
	inline float getWidth(void) { return _gameObjectInfo->width; }
	inline void setWidth(float  widhth) { _gameObjectInfo->width = widhth;; }

	//���� �ػ�
	inline float getHeight(void) { return _gameObjectInfo->height; }
	inline void setHeight(float  height) { _gameObjectInfo->height = height; }

	//�ٿ�� �ڽ�
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_gameObjectInfo->x),
			int(_gameObjectInfo->y),
			int(_gameObjectInfo->x + _gameObjectInfo->width),
			int(_gameObjectInfo->y + _gameObjectInfo->height) };
		return rc;
	}

	//is Deleted?, ���� ����� �Ǹ� �� Destroy�� set�Ͽ� true�� �����ϸ�, ���� �޴����� ������Ʈ�� ������ ������ �� ���� true�� ������Ʈ�� ������ �ϴ� �۾��� �ϰ� �ȴ�.
	inline void setDestroy(bool destroy) { _gameObjectInfo->isDeleted = destroy; }
	inline bool IsDeleted(void) { return _gameObjectInfo->isDeleted; }
};

