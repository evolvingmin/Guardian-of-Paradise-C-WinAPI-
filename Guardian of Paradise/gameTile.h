#pragma once
#include "gameObject.h"
#include "player.h"
#include "gameAnimation.h"



//���� Ÿ���� Ŭ������ ������ ������, �浹ó���� ����ó���� ���ؼ� ���� �׻� ������ ����� ����ϱ� �����̴�. 
//�׷��� ���ؼ���, ������ Ŭ���� ��ü�� �����ϴ� ����� ã�ƾ� �ȴ�
//Ŭ������ ��ü�� �����ϴ°� ��� �̹� ����������, Ŭ�������� ������ ����� ��� �����ϴ� ����� ����ȭ�� �ִ�.

//Ÿ�ϼ� ũ�Ⱑ 200���̸� �̿� ���� ���� ���� �ۼ��ؾ� �ȴ�.(�������� ���ֵ���)
enum TERRAINTYPE
{
	//�⺻��
	TR_GROUND, 
	//�ٸ��������� ���� ��
	TR_DOOR,
	//�÷��̾ �� �� �ִ� Ǯ
	TR_PLANTS,
	//���� ������ ���������� ������
	TR_WATER, 
	//�Ϲ����� ���ع� ����, ����� ����
	TR_OBJECT,
	//����, ������ ��� ���ϸ��̼ǰ� �Բ� �ٸ� �������� or Ȥ�� �ٽ� �� �� ����
	TR_CLIFF,
	//������ �� �ִ� ����.
	TR_JUMP,
	//������ �Ǳ����� ���ٴ�
	TR_PRECLIFF,
	//���� ��, �ƹ��͵� �ƴ� ���
	TR_NONE
};

class gameTile : public gameObject
{
private :
	animation* _animation;
	image* _tileSetImage;


	int _tileSelection;
	int _tileIndexX;
	int _tileIndexY;

	TERRAINTYPE _terrain;
	int _imageIndexX;
	int _imageIndexY;
	bool _isPassable;

public:
	gameTile();
	~gameTile();
	//�̴�
	HRESULT init(int tileSelection, int x, int y, TERRAINTYPE terrainType);
	void release();
	//������Ʈ
	 void update(bool inGame);
	//����
	 void render(void);
	//����, ���� ���̵� ����ؼ� ��ǥ�� �ܺο��� �������� �ʿ䰡 �ִ�.
	 void render(bool inGame, float x, float y, bool showNumber=false );
	//�浹ó��
	void onCollideEnter(gameObject* gObject);


	//����ȭ �ڵ�, ��Ӱ��迡 ���� �θ� �Լ� ȣ�� �ָ�
	friend class cereal::access;
	template<class Archive>
	void serialize(Archive & ar)
	{
	//	gameObject::serialize(ar);
		ar(cereal::base_class<gameObject>(this),CEREAL_NVP(_tileSelection), CEREAL_NVP(_imageIndexX), CEREAL_NVP(_imageIndexY), CEREAL_NVP(_terrain), CEREAL_NVP(_tileIndexX), CEREAL_NVP(_tileIndexY));
		setTileImage();
	}

	void setTileImage(int imageIndexX, int imageIndexY, int tileSelection);
	void setTileImage();

	inline TERRAINTYPE getTerrainType(void) { return _terrain; }
	inline void setTerrainType(TERRAINTYPE terrainType){ this->_terrain = terrainType; }

	void ScaleTo();
};

