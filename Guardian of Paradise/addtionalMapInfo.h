#pragma once
#include "gameTextBox.h"
#include "gameQuest.h"
//가로 타일 갯수
#define MAXTILEX 41
//세로 타일 갯수
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
	//몬스터들과는 다르게 타입별로 나눠 표시할 것이기 때문에 구분자가 필요하다.
	OBJECT_TYPE objectType;
	//거진 여기까지 왔으면 어떤 오브젝트들이 깔릴 것인지 특정이 된 것이다. 
	OBJECT_SELECT objectSelect;
	//다만 오브젝트의 경우 그 내부에서도 종류가 여러게 되므로  이미지 파일과 최종 인덱스를 잡아주는게 필요하다
	string objectImageFile;
	int objectImageIndexX;
	int objectImageIndexY;
	//특정 NPC나 대상을 지정해야 할 필요성이 있을 경우 이걸 사용해서 분류하도록 하자.
	string objectName;
	float x, y;
	float width;
	float height;

	//게임 오브젝트에 연결된 퀘스트가 어떤 것인지 알 필요가 있다.
	int questIndex;
	//NPC의 경우 Dialog FilePath가 존재한다.
	//퀘스트에 따라서 다이얼로그를 여러개 선택해야 할 경우, 이걸 벡터로 바꾸고 또한 텝에서 여러개의 다이얼로그를 선택할 수 있도록 만들것이다.
	string npcDialogFile;
	int goalNumber;
	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { int(x),
			int(y),
			int(x + width),
			int(y + height) };
		return rc;
	}
	// 오브젝트들은 몬스터와 다르게 맵 에디터 상에서 추가적인 설정이 필요 할 수 있다. 염두 해 둘 것.
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
	//바운딩 박스
	inline RECT boundingBox(void)
	{
		RECT rc = { int(x),
			int(y),
			int(x + width),
			int(y + height) };
		return rc;
	}

};