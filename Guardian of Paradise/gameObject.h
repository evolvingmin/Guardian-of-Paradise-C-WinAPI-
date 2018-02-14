#pragma once
#include "stdafx.h"
#include "gameNode.h"
//충돌하는 객체의 타입을 정의
//현재는 사각형, 원, 점 이 세개로 이루어졌다.


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

		//클레스 별로 이것이 어떤 개체인지를 구분하기 위한 테그.
		string tag;
		//테그로도 부족하다면, name으로 좀더 정확히 상대를 지목할 수 있다. (유니크 몬스터라던지)
		string name;
		//이속
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
	//직렬화 코드
public:
	//직렬화 코드, 게임 오브젝트 저장 대상.
	bool _isColliderOn;
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(_COLLIDERTYPE) ,CEREAL_NVP(_gameObjectInfo));
	}

	gameObject();
	~gameObject();
	//기본 초기화, 콜라이더 정보 역시 지정되지 않음.
	HRESULT init();
	//점 초기화
	HRESULT init(string tag, float x, float y, float speed, float angle, bool isColliderOn = true);
	//사각형 초기화
	HRESULT init(string tag, float x, float y, float width, float height, float speed, float angle, bool isColliderOn = true);
	//사각형 초기화
	HRESULT init(string tag, RECT rect, float speed, float angle, bool isColliderOn = true);
	//원초기화
	HRESULT init(string tag, float x, float y, float radius, float speed, float angle, bool isColliderOn = true);


	//업데이트
	virtual void update(void){}
	//렌더
	virtual void render(void){}
	//렌더, 이제 맵이동 고려해서 좌표를 외부에서 재조정할 필요가 있다.
	virtual void render(float x, float y){}
	//충돌처리
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

	//좌표 X
	inline void setX(float x) { _gameObjectInfo->x = x;   }
	inline float getX(void) { return _gameObjectInfo->x; }

	//좌표 Y
	inline void setY(float y) { _gameObjectInfo->y = y; }
	inline float getY(void) { return _gameObjectInfo->y; }

	//좌표 Z, 여기서는 렌더 오더에 쓰일 것.
	inline void setZ(float z) { _gameObjectInfo->z = z; }
	inline float getZ(void) { return _gameObjectInfo->z; }

	//반지름
	inline void setRadius(float radius) { _gameObjectInfo->radius = radius; }
	inline float getRadius(void) { return _gameObjectInfo->radius; }

	//각도
	inline void setObjectAngle(float angle) 
	{ 
		while (angle > PI2)
			angle -= PI2;
		
		while (angle < 0)
			angle += PI2;

		_gameObjectInfo->angle = angle; 
	}
	inline float getObjectAngle(void) { return _gameObjectInfo->angle; }

	//이속
	inline float getSpeed(){ return _gameObjectInfo->speed; }
	inline void setSpeed(float speed){ _gameObjectInfo->speed = speed; }

	//좌표 센터
	inline void setCenter(float x, float y){	_gameObjectInfo->x = x - (_gameObjectInfo->width / 2);_gameObjectInfo->y = y - (_gameObjectInfo->height / 2);}
	//중점 x
	inline float getCenterX(void){return  _gameObjectInfo->x + (_gameObjectInfo->width / 2.0f);}
	//중점 y
	inline float getCenterY(void){ return _gameObjectInfo->y + (_gameObjectInfo->height / 2.0f); }
	
	//가로 해상도
	inline float getWidth(void) { return _gameObjectInfo->width; }
	inline void setWidth(float  widhth) { _gameObjectInfo->width = widhth;; }

	//세로 해상도
	inline float getHeight(void) { return _gameObjectInfo->height; }
	inline void setHeight(float  height) { _gameObjectInfo->height = height; }

	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_gameObjectInfo->x),
			int(_gameObjectInfo->y),
			int(_gameObjectInfo->x + _gameObjectInfo->width),
			int(_gameObjectInfo->y + _gameObjectInfo->height) };
		return rc;
	}

	//is Deleted?, 제거 대상이 되면 이 Destroy를 set하여 true로 설정하면, 게임 메니져의 업데이트의 구문이 끝나고 이 값이 true인 오브젝트를 릴리즈 하는 작업을 하게 된다.
	inline void setDestroy(bool destroy) { _gameObjectInfo->isDeleted = destroy; }
	inline bool IsDeleted(void) { return _gameObjectInfo->isDeleted; }
};

