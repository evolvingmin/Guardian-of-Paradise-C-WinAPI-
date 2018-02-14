#pragma once
#include "gameTextBox.h"
#include "gameQuest.h"
//���� Ÿ�� ����
#define MAXTILEX 41
//���� Ÿ�� ����
#define MAXTILEY 41


enum OBJECT_TYPE
{
	DOOR,
	//DOOR_CONDITION,DOOR_KEY_REQUIRED
	OBJECT_NPC,
	//FRAMED_NPC,NPC
	SKILL_INTERACT,
	//WOOD_BLOCK,WOOD_ROOT,HINTMINT, MUSHIBOING
	ENVIROMENT,
	//STONE_MOVABLE,STONE_BOARD,SPIKE_MOVABLE, ENVIROMENT_HOME
	PUZZLE,
	//PUZZLE_NUMBERBLOCK,	BUTTON_ONCE,BUTTON_KEEP
	ITEM,
	OBJECT_END
};


enum OBJECT_SELECT
{
	DOOR_CONDITION,
	DOOR_KEY_REQUIRED,
	WOOD_BLOCK,
	WOOD_ROOT,
	HINTMINT,
	MUSHIBOING,
	NPC,
	FRAMED_NPC,
	STONE_MOVABLE_ONCE,
	STONE_MOVABLE,
	STONE_BOARD,
	SPIKE_MOVABLE,
	ENVIROMENT_HOME,
	ENVIROMENT_GRASS,
	PUZZLE_NUMBERBLOCK,
	BUTTON_ONCE,
	BUTTON_KEEP,
	BUTTON_ROBUST,
	OBJECT_ITEM_SWORD,
	OBJECT_ITEM_KEY,
	OBJECT_ITEM_HEALTH,
	OBJECT_ITEM_LUCA,
	OBJECT_ITEM_LUCA_UP,
	OBJECT_ITEM_FOREST_EMBLEM,
	OBJECT_SELECT_END
};


enum MONSTER_SELECT
{
	CRAP,
	FLOWER,
	FLY,
	FOREST_BOSS,
	FOREST_BOSS_TENTACLE,
	FOREST_MINIBOSS,
	FROG,
	GRASSHOPPER,
	SHELL_MONSTER,
	SLIME,
	TURTLE,
	WATER_BOSS,
	WATER_MINIBOSS,
	WATER_SHELL_MONSTER,
	WATER_FLOG,
	MONSTER_END
};

struct tagObjectInfo
{
	//���͵���� �ٸ��� Ÿ�Ժ��� ���� ǥ���� ���̱� ������ �����ڰ� �ʿ��ϴ�.
	OBJECT_TYPE objectType;
	//���� ������� ������ � ������Ʈ���� �� ������ Ư���� �� ���̴�. 
	OBJECT_SELECT objectSelect;
	//�ٸ� ������Ʈ�� ��� �� ���ο����� ������ ������ �ǹǷ�  �̹��� ���ϰ� ���� �ε����� ����ִ°� �ʿ��ϴ�
	string objectImageFile;
	int objectImageIndexX;
	int objectImageIndexY;
	//Ư�� NPC�� ����� �����ؾ� �� �ʿ伺�� ���� ��� �̰� ����ؼ� �з��ϵ��� ����.
	string objectName;
	float x, y;
	float width;
	float height;

	//���� ������Ʈ�� ����� ����Ʈ�� � ������ �� �ʿ䰡 �ִ�.
	int questIndex;
	//NPC�� ��� Dialog FilePath�� �����Ѵ�.
	//����Ʈ�� ���� ���̾�α׸� ������ �����ؾ� �� ���, �̰� ���ͷ� �ٲٰ� ���� �ܿ��� �������� ���̾�α׸� ������ �� �ֵ��� ������̴�.
	string npcDialogFile;
	int goalNumber;
	//�ٿ�� �ڽ�
	inline RECT boundingBox(void)
	{
		RECT rc = { int(x),
			int(y),
			int(x + width),
			int(y + height) };
		return rc;
	}
	// ������Ʈ���� ���Ϳ� �ٸ��� �� ������ �󿡼� �߰����� ������ �ʿ� �� �� �ִ�. ���� �� �� ��.
	tagObjectInfo(float x, float y, float widht, float height, OBJECT_TYPE objectType, OBJECT_SELECT objectSelect, string objectImageFIle,
		int objectImageIndexX, int objectImageIndexY, string ObjName = "", string npcDialogFile ="")
	{
		this->objectType = objectType;
		this->objectSelect = objectSelect;
		this->objectImageFile = objectImageFIle;
		this->objectImageIndexX = objectImageIndexX;
		this->objectImageIndexY = objectImageIndexY;
		this->x = x;
		this->y = y;
		this->width = widht;
		this->height = height;
		this->questIndex = 0;
		this->goalNumber = 0;
		this->npcDialogFile = npcDialogFile;
		this->objectName = ObjName;
	}
	tagObjectInfo(){};
	~tagObjectInfo(){};
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(
			CEREAL_NVP(x),
			CEREAL_NVP(y),
			CEREAL_NVP(width),
			CEREAL_NVP(height),
			CEREAL_NVP(objectType),
			CEREAL_NVP(objectSelect),
			CEREAL_NVP(objectImageFile),
			CEREAL_NVP(objectImageIndexX),
			CEREAL_NVP(objectImageIndexY),
			CEREAL_NVP(questIndex),
			CEREAL_NVP(npcDialogFile),
			CEREAL_NVP(goalNumber),
			CEREAL_NVP(objectName)
			);
	}
};

struct tagPortalInfo
{
	gameTextBox* nextXBox;
	gameTextBox* nextYBox;
	string portalMapLink;

	int  currentIndexX, currentIndexY;
	int _nextIndexX, _nextIndexY;


	template<class Archive>
	void save(Archive & archive) const
	{

		archive(CEREAL_NVP(portalMapLink),
			CEREAL_NVP(currentIndexX), CEREAL_NVP(currentIndexY),
			CEREAL_NVP(_nextIndexX), CEREAL_NVP(_nextIndexY));
	}

	template<class Archive>
	void load(Archive & archive)
	{
		char temp[120];
		archive(CEREAL_NVP(portalMapLink),
			CEREAL_NVP(currentIndexX), CEREAL_NVP(currentIndexY),
			CEREAL_NVP(_nextIndexX), CEREAL_NVP(_nextIndexY));
		nextXBox = new gameTextBox;
		nextXBox->init(&_nextIndexX, 5 + currentIndexX*TILESIZE, currentIndexY*TILESIZE, TILESIZE, 10);
		nextXBox->returnText()->setText(_itoa(_nextIndexX, temp, 10));

		nextYBox = new gameTextBox;
		nextYBox->init(&_nextIndexY, 5 + currentIndexX*TILESIZE, currentIndexY*TILESIZE + TILESIZE / 2, TILESIZE, 10);
		nextYBox->returnText()->setText(_itoa(_nextIndexY, temp, 10));
	}

	tagPortalInfo(){};
	tagPortalInfo(string portalMapLink, int  currentIndexX, int  currentIndexY, int nextIndexX, int nextIndexY)
	{

		this->portalMapLink = portalMapLink;
		_nextIndexX = nextIndexY;
		_nextIndexY = nextIndexY;
		this->currentIndexX = currentIndexX;
		this->currentIndexY = currentIndexY;

	}
	~tagPortalInfo(){};
	void setUptextBox()
	{
		nextXBox = new gameTextBox;
		nextXBox->init(&_nextIndexX, 5 + currentIndexX*TILESIZE, currentIndexY*TILESIZE, TILESIZE, 10);
		nextYBox = new gameTextBox;
		nextYBox->init(&_nextIndexY, 5 + currentIndexX*TILESIZE, currentIndexY*TILESIZE + TILESIZE / 2, TILESIZE, 10);
	}
};

struct tagMonsterInfo
{
	MONSTER_SELECT monsterSelect;
	float x, y;
	float width;
	float height;
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(monsterSelect), CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(width), CEREAL_NVP(height));
	}
	tagMonsterInfo(){};
	tagMonsterInfo(MONSTER_SELECT monsterSelect, float x, float y, float width, float height)
	{
		this->monsterSelect = monsterSelect;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	~tagMonsterInfo(){};
	//�ٿ�� �ڽ�
	inline RECT boundingBox(void)
	{
		RECT rc = { int(x),
			int(y),
			int(x + width),
			int(y + height) };
		return rc;
	}

};