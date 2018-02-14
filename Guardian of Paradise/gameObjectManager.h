#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>
#include <functional>
#include "SpatialHasing.h"


class gameObject;

//여기 한번 정리좀 해야겠다. 
enum DATA_STRUCTURE_TYPE
{
	VECTOR,
	SPATIALHASING,
};


typedef std::function<void(gameObject*)> METHOD_CALLBACK;
//Type of GameObject vector
typedef vector<gameObject*> vectorGameObjectList;
typedef vector<gameObject*>::iterator vectorGameObjectIter;
//Type of gameEvent(funtion Pointer) Iter;
typedef map<string, METHOD_CALLBACK*> mapGameEventList;
typedef map<string, METHOD_CALLBACK*> ::iterator mapGameEventIter;

//다시 유니크한 메니져로 변모했다. 
class gameObjectManager :public singletonBase<gameObjectManager>
{

protected:
	DATA_STRUCTURE_TYPE _dataStructureType;
	vectorGameObjectList _vGameObjectList;	//벡터로 구현된 gameObject 리스트, 윈도우 사이즈를 넘어가는 타일형 게임에서는 사용하지 않는다
	vectorGameObjectList _vGameObjectAddList; //게임 오브젝트가 다른 오브젝트를 생성할 시, 여기에 담아뒀다가 업데이트 구문이 끝난 뒤 채워 넣는다.
	//new version of dataStore, 
	//지금 고민하는게 하나의 기본 데이터 구조를 설정한뒤 사용할 것이냐, 아니면 따로 함수로 정의해서 계속 새로운 데이터구조를 추가할 수있게하느냐임.
	
	SpatialHasing* _sHgameObjectList;// 스파시열해싱으로 구현된 gameObject 리스트

	mapGameEventList _mGameEventList; //맵으로 구현된 델리게이터 리스트
public:	

	HRESULT init();
	HRESULT init(DATA_STRUCTURE_TYPE dataStuructureType, float width, float height);

	void release(void);

	void update(void);

	void update(float x, float y);

	void render(void);

	void render(float x, float y);

	//렌더 순서를 정함
	void setRenderOrder();



	//Method for gameObject
	gameObject* findGameObject(string tag);

	gameObject* findGameObject(string tag, float x, float y);
	HRESULT addGameObject(gameObject* gObject);
	HRESULT addGameObject(gameObject& gObject);
	void addGameObjectListToVecter();
	void removeGameObject();
	HRESULT removeGameObject(gameObject* gObject);
	
	//전체 게임 오브젝트를 메모리 해제한다. 이때 각각의 게임 오브젝트에 동적할당이 있을 경우 그에 상응하는 제대로된 릴리즈 함수가 있어야 됨은 물론이다.
	BOOL deleteAll(void);

	//등록된 콜라이더들을 체크하는 작업을 하게 된다. 그리고 충돌된 대상 콜라이드를 넘겨주는 작업도 하게되고.
	bool colliderCheck();
	bool colliderCheck(vectorGameObjectList vgameObjectList);

	bool colliderCheck(float x, float y);
	


	//Method for gameEvent
	METHOD_CALLBACK* addGameEvent(string strKey, METHOD_CALLBACK*);
	METHOD_CALLBACK* findGameEvent(string strKey);
	void activateEvent(string strKey);

	void activateEvent(string strKey, float x, float y);

	//원래는 이걸 지양하고 싶었지만, 연산효율을 늘리기 위해서는 구조변경이 불가피하다.
	//카메라와 같이 반복연산이 잦은 밀접한 녀석들만 받게하자.
	SpatialHasing* getSpatialHasingData(){ return _sHgameObjectList; };
	vectorGameObjectList getVectorData(){ return _vGameObjectList; }
	
	gameObjectManager();
	~gameObjectManager();

};
