#pragma once


//퀘스트의 주체는 맵이다.
//퀘스트는 지역 퀘스트가 된다.
//퀘스트의 대상이 되는 오브젝트들(보스몬스터, 퀘스트아이템, 문)은 지역퀘스트에 포인터로, 벡터로 등록된다.
//게임모드의 두종류, 즉 Start와 continue 두 종류가 있는데
//Start의 경우 이 지역퀘스트를 맵 수만큼 가지는 퀘스트 메니져가 존재하고, 이 퀘스트 매니져에 맵 수만큼 퀘스트를 등록하는 작업을 한다.
//( 맵에는 퀘스트가 있을 수도 있고 없을 수도 있다)
//맵을 로딩하면, 맵의 이름을 기준으로 맵의 퀘스트를 불러온다.
//그리고 이 퀘스트는 기록대상이다, 즉 맵데이터는 쓰기가 불가능한, 읽기만 하는 데이터지만, 퀘스트메니져에 등록하는 퀘스트는 
//변경 대상이다. 그리고 continue는 이러한 퀘스트 메니져를 직렬화 하고 불러오는 것으로 해결한다.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//퀘스트메니져가 존재하고
//맵을 기준으로 퀘스트"들"이 존재한다.
//가령 맵에디터에서 문을 만들고 추가 콤보 박스로 속성을 정의하면 그에 따른 퀘스트가 또한 등록 된다.
//그 퀘스트들은 그 퀘스트가 지배하는 혹은 종속되는 오브젝트들을 들고 있으며 
//퀘스트가 완료되면 그 퀘스트를 부르지 않는 방식으로 마찬가지로 그에 종속된 오브젝트도 불러오지 않는 방향으로 간다.
//포문으로 가져 있는 퀘스트로 퀘스트 탐색
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//일단 조건에 맞는 일을 했을 시 문이 계속 열려있는 퀘스트를 만들도록 하자.
//1. 맵 상에 있는 몬스터를 다 처치 했을 시, 열리는 문
//2. 먼저 이 퀘스트가 맵 에디터 상에 등록 될 시 _isActive가 true이면 현재 맵 에디터 상에 등록된 몬스터들의 숫자를 카운팅 한다.
//3. 만약 그 size가 0이라면 _isActive 를 false로 하며, false라면 도어를 게임 오브젝트에 넣지말고, (특히나 inGame중이라면 있는 도어를 제거까지 해야한다)

enum QUEST_TYPE
{
	QUEST_DOOR_MONSTER_DESTROY,
	QUEST_DOOR_BUTTON_SOLVED,
	QUEST_DOOR_NUMBER_MATCHED,
	QUEST_DOOR_KEY_REQUIRED,
	QUEST_BOSS_DESTROY,
	QUEST_NPC_TALK,
	//퀘스트를 생성했지만 할당되지 않을 수도 있다.
	QUEST_ITEM_CONSUMED,
	QUEST_NONE
};


struct tagObjectInfo;

class gameQuest 
{
private:

	QUEST_TYPE _questType;
	
	bool _isActive;
	//조건 체크가 게임 맵 항시 체크되는지, 아니면 조건이 만족하는 당사자가 부르는지를 결정함.
	bool _isCalledCheck;
	int _uniqueNum;
	friend cereal::access;
public:
	
	gameQuest();
	~gameQuest();
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(
			CEREAL_NVP(_questType),
			CEREAL_NVP(_isActive),
			CEREAL_NVP(_uniqueNum),
			CEREAL_NVP(uniqueGenerateNum)
			
			);
	}

//	void init(QUEST_TYPE QUEST_TYPE);
	//퀘스트 탐색 (포문으로 돌면서 퀘스트가 수행됬는지 않됬는지를 체크하는 메소드)
	//init부 퀘스트에 연동된 기본 오브젝트를 불러옴
	QUEST_TYPE getQuestType(void) { return _questType; }
	QUEST_TYPE* getQuestTypeAdress(void){ return &_questType; }
	void setQuestType(QUEST_TYPE questType){ _questType = questType; }
	bool getIsCalledCheck(void){ return _isCalledCheck; }
	//비교 연산자를 주소가 아닌 내부 맴버로 서로 같은지 아닌지를 체크하기 위한 변수생성 맴버, 그 결과는 _uniqueNum에 정의된다.




	//몬스터꺼도 하나 더.

	static int uniqueGenerateNum;
	int getUniqueNum(void){ return _uniqueNum; }
	bool operator==(const gameQuest& s);

	void setRelatedGameObject(vector<tagObjectInfo> objectSet);
	void checkQuestCondition();
	bool searchAndDestroy(string tag);

};

