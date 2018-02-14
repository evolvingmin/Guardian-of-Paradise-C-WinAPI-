#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>
#include <functional>
#include "SpatialHasing.h"


class gameObject;

//���� �ѹ� ������ �ؾ߰ڴ�. 
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

//�ٽ� ����ũ�� �޴����� �����ߴ�. 
class gameObjectManager :public singletonBase<gameObjectManager>
{

protected:
	DATA_STRUCTURE_TYPE _dataStructureType;
	vectorGameObjectList _vGameObjectList;	//���ͷ� ������ gameObject ����Ʈ, ������ ����� �Ѿ�� Ÿ���� ���ӿ����� ������� �ʴ´�
	vectorGameObjectList _vGameObjectAddList; //���� ������Ʈ�� �ٸ� ������Ʈ�� ������ ��, ���⿡ ��Ƶ״ٰ� ������Ʈ ������ ���� �� ä�� �ִ´�.
	//new version of dataStore, 
	//���� ����ϴ°� �ϳ��� �⺻ ������ ������ �����ѵ� ����� ���̳�, �ƴϸ� ���� �Լ��� �����ؼ� ��� ���ο� �����ͱ����� �߰��� ���ְ��ϴ�����.
	
	SpatialHasing* _sHgameObjectList;// ���Ľÿ��ؽ����� ������ gameObject ����Ʈ

	mapGameEventList _mGameEventList; //������ ������ ���������� ����Ʈ
public:	

	HRESULT init();
	HRESULT init(DATA_STRUCTURE_TYPE dataStuructureType, float width, float height);

	void release(void);

	void update(void);

	void update(float x, float y);

	void render(void);

	void render(float x, float y);

	//���� ������ ����
	void setRenderOrder();



	//Method for gameObject
	gameObject* findGameObject(string tag);

	gameObject* findGameObject(string tag, float x, float y);
	HRESULT addGameObject(gameObject* gObject);
	HRESULT addGameObject(gameObject& gObject);
	void addGameObjectListToVecter();
	void removeGameObject();
	HRESULT removeGameObject(gameObject* gObject);
	
	//��ü ���� ������Ʈ�� �޸� �����Ѵ�. �̶� ������ ���� ������Ʈ�� �����Ҵ��� ���� ��� �׿� �����ϴ� ����ε� ������ �Լ��� �־�� ���� �����̴�.
	BOOL deleteAll(void);

	//��ϵ� �ݶ��̴����� üũ�ϴ� �۾��� �ϰ� �ȴ�. �׸��� �浹�� ��� �ݶ��̵带 �Ѱ��ִ� �۾��� �ϰԵǰ�.
	bool colliderCheck();
	bool colliderCheck(vectorGameObjectList vgameObjectList);

	bool colliderCheck(float x, float y);
	


	//Method for gameEvent
	METHOD_CALLBACK* addGameEvent(string strKey, METHOD_CALLBACK*);
	METHOD_CALLBACK* findGameEvent(string strKey);
	void activateEvent(string strKey);

	void activateEvent(string strKey, float x, float y);

	//������ �̰� �����ϰ� �;�����, ����ȿ���� �ø��� ���ؼ��� ���������� �Ұ����ϴ�.
	//ī�޶�� ���� �ݺ������� ���� ������ �༮�鸸 �ް�����.
	SpatialHasing* getSpatialHasingData(){ return _sHgameObjectList; };
	vectorGameObjectList getVectorData(){ return _vGameObjectList; }
	
	gameObjectManager();
	~gameObjectManager();

};
