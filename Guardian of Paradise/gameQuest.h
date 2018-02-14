#pragma once


//����Ʈ�� ��ü�� ���̴�.
//����Ʈ�� ���� ����Ʈ�� �ȴ�.
//����Ʈ�� ����� �Ǵ� ������Ʈ��(��������, ����Ʈ������, ��)�� ��������Ʈ�� �����ͷ�, ���ͷ� ��ϵȴ�.
//���Ӹ���� ������, �� Start�� continue �� ������ �ִµ�
//Start�� ��� �� ��������Ʈ�� �� ����ŭ ������ ����Ʈ �޴����� �����ϰ�, �� ����Ʈ �Ŵ����� �� ����ŭ ����Ʈ�� ����ϴ� �۾��� �Ѵ�.
//( �ʿ��� ����Ʈ�� ���� ���� �ְ� ���� ���� �ִ�)
//���� �ε��ϸ�, ���� �̸��� �������� ���� ����Ʈ�� �ҷ��´�.
//�׸��� �� ����Ʈ�� ��ϴ���̴�, �� �ʵ����ʹ� ���Ⱑ �Ұ�����, �б⸸ �ϴ� ����������, ����Ʈ�޴����� ����ϴ� ����Ʈ�� 
//���� ����̴�. �׸��� continue�� �̷��� ����Ʈ �޴����� ����ȭ �ϰ� �ҷ����� ������ �ذ��Ѵ�.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����Ʈ�޴����� �����ϰ�
//���� �������� ����Ʈ"��"�� �����Ѵ�.
//���� �ʿ����Ϳ��� ���� ����� �߰� �޺� �ڽ��� �Ӽ��� �����ϸ� �׿� ���� ����Ʈ�� ���� ��� �ȴ�.
//�� ����Ʈ���� �� ����Ʈ�� �����ϴ� Ȥ�� ���ӵǴ� ������Ʈ���� ��� ������ 
//����Ʈ�� �Ϸ�Ǹ� �� ����Ʈ�� �θ��� �ʴ� ������� ���������� �׿� ���ӵ� ������Ʈ�� �ҷ����� �ʴ� �������� ����.
//�������� ���� �ִ� ����Ʈ�� ����Ʈ Ž��
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ϴ� ���ǿ� �´� ���� ���� �� ���� ��� �����ִ� ����Ʈ�� ���鵵�� ����.
//1. �� �� �ִ� ���͸� �� óġ ���� ��, ������ ��
//2. ���� �� ����Ʈ�� �� ������ �� ��� �� �� _isActive�� true�̸� ���� �� ������ �� ��ϵ� ���͵��� ���ڸ� ī���� �Ѵ�.
//3. ���� �� size�� 0�̶�� _isActive �� false�� �ϸ�, false��� ��� ���� ������Ʈ�� ��������, (Ư���� inGame���̶�� �ִ� ��� ���ű��� �ؾ��Ѵ�)

enum QUEST_TYPE
{
	QUEST_DOOR_MONSTER_DESTROY,
	QUEST_DOOR_BUTTON_SOLVED,
	QUEST_DOOR_NUMBER_MATCHED,
	QUEST_DOOR_KEY_REQUIRED,
	QUEST_BOSS_DESTROY,
	QUEST_NPC_TALK,
	//����Ʈ�� ���������� �Ҵ���� ���� ���� �ִ�.
	QUEST_ITEM_CONSUMED,
	QUEST_NONE
};


struct tagObjectInfo;

class gameQuest 
{
private:

	QUEST_TYPE _questType;
	
	bool _isActive;
	//���� üũ�� ���� �� �׽� üũ�Ǵ���, �ƴϸ� ������ �����ϴ� ����ڰ� �θ������� ������.
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
	//����Ʈ Ž�� (�������� ���鼭 ����Ʈ�� ��������� �ʉ������ üũ�ϴ� �޼ҵ�)
	//init�� ����Ʈ�� ������ �⺻ ������Ʈ�� �ҷ���
	QUEST_TYPE getQuestType(void) { return _questType; }
	QUEST_TYPE* getQuestTypeAdress(void){ return &_questType; }
	void setQuestType(QUEST_TYPE questType){ _questType = questType; }
	bool getIsCalledCheck(void){ return _isCalledCheck; }
	//�� �����ڸ� �ּҰ� �ƴ� ���� �ɹ��� ���� ������ �ƴ����� üũ�ϱ� ���� �������� �ɹ�, �� ����� _uniqueNum�� ���ǵȴ�.




	//���Ͳ��� �ϳ� ��.

	static int uniqueGenerateNum;
	int getUniqueNum(void){ return _uniqueNum; }
	bool operator==(const gameQuest& s);

	void setRelatedGameObject(vector<tagObjectInfo> objectSet);
	void checkQuestCondition();
	bool searchAndDestroy(string tag);

};

