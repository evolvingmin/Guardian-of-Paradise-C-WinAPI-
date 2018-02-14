#pragma once
#include "gameTile.h"
#include "gameCamera.h"
#include "addtionalMapInfo.h"


class gameTileMap : public gameObject
{
private:
	int _tileX;
	int _tileY;
	bool _Ingame;
	bool _showTile;
	gameCamera* _gameCamera;
	vector<tagMonsterInfo> _vMonster;
	vector<tagObjectInfo> _vObject;
	vector<tagPortalInfo> _vPortal;
	vector<gameQuest> _vQuest;
	//�ʸ��� �����ϴ� ������� Ű��.
	string _bgmKey;
	string _aMapLink[5];
public :
	gameTile _mapdata[MAXTILEY][MAXTILEX];
public:
	gameTileMap();
	~gameTileMap();
	//���� �ΰ��ӻ󿡼��� �� �����Ϳ��� ������ �ͺ��� Ŀ���Ѵ�. �ϴ��� �� ����� ���������� ���� ���̹Ƿ� ����� �޾� ��������
	HRESULT init();
	//�ʿ����� �ʱ�ȭ
	HRESULT init(int tileSelection , int tileX, int tileY);
	void release();
	void update();
	void render();
	void render(float x, float y);
	//����ȭ �ڵ�, �� ����Ÿ ����
	template<class Archive>
	void serialize(Archive & ar)
	{

		ar(cereal::base_class<gameObject>(this),
			CEREAL_NVP(_mapdata),
			CEREAL_NVP(_vMonster),
			CEREAL_NVP(_aMapLink),
			CEREAL_NVP(_vPortal),
			CEREAL_NVP(_vObject),
			CEREAL_NVP(_vQuest),
			CEREAL_NVP(_bgmKey),
			CEREAL_NVP(_tileX), CEREAL_NVP(_tileY), CEREAL_NVP(_Ingame) );
	}


	void onCollideEnter(gameObject* gObject);
	void linkAdressCameraObject(gameCamera* gameCamera) { _gameCamera = gameCamera;  }
	inline int getTileX(void){ return _tileX; }
	inline void setTileX(int _tileX){ this->_tileX = _tileX; }
	inline int getTileY(void){ return _tileY; }
	inline void setTileY(int _tileY){ this->_tileY = _tileY; }
	inline vector<tagMonsterInfo>* getMonsterSet(void){ return &_vMonster; }
	inline vector<tagPortalInfo>* getPortalSet(void){ return &_vPortal; }
	inline vector<tagObjectInfo>* getObjectSet(void){ return &_vObject; }
	inline vector<gameQuest>* getGameQuestSet(void){ return &_vQuest; }
	inline string* getMapLink() { return _aMapLink; }
	
	inline void setBGMKey(string bgmKey){ _bgmKey = bgmKey; }
	inline string getBGMKey(){ return _bgmKey; }
};
