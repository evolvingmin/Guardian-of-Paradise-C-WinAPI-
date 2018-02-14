#pragma once
#include "gameObject.h"
#include "player.h"
#include "gameAnimation.h"



//개별 타일을 클래스로 정의한 이유는, 충돌처리나 연산처리에 대해서 내가 항상 접근한 방식을 고수하기 위함이다. 
//그러기 위해서도, 더더욱 클레스 자체를 저장하는 방식을 찾아야 된다
//클래스를 통체로 저장하는건 사실 이미 존재하지만, 클래스에서 저장할 대상만을 골라서 저장하는 방식이 직렬화에 있다.

//타일셋 크기가 200개이며 이에 따른 엑셀 맵을 작성해야 된다.(참고가능할 수있도록)
enum TERRAINTYPE
{
	//기본땅
	TR_GROUND, 
	//다른지형으로 들어가는 문
	TR_DOOR,
	//플레이어가 벨 수 있는 풀
	TR_PLANTS,
	//물의 힘으로 수영가능한 물지형
	TR_WATER, 
	//일반적인 방해물 지형, 언덕도 포함
	TR_OBJECT,
	//절벽, 떨어질 경우 에니메이션과 함께 다른 지형으로 or 혹은 다시 그 맵 시작
	TR_CLIFF,
	//점프할 수 있는 지점.
	TR_JUMP,
	//절벽이 되기전의 땅바닥
	TR_PRECLIFF,
	//상태 끝, 아무것도 아닌 경우
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
	//이닛
	HRESULT init(int tileSelection, int x, int y, TERRAINTYPE terrainType);
	void release();
	//업데이트
	 void update(bool inGame);
	//렌더
	 void render(void);
	//렌더, 이제 맵이동 고려해서 좌표를 외부에서 재조정할 필요가 있다.
	 void render(bool inGame, float x, float y, bool showNumber=false );
	//충돌처리
	void onCollideEnter(gameObject* gObject);


	//직렬화 코드, 상속관계에 따른 부모 함수 호출 주목
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

