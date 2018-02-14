#pragma once
#include "gameObject.h"
#include "gameAnimation.h"


class gameCharacter : public gameObject
{
private:
	//충돌 대상의 테그값들이 저장되는 벡터값.
	vector<string> _hitReactionOpponents;
protected :
	//Animation
	gameAnimation* _gameAni;
	image* _shadowImage;

	//statues
	int _maxHp;
	int _Hp;
	int _maxMp;
	int _Mp;

	//시간(_stateTime)과 조건(if(getState()==state)), 그리고 조건 만족시 초기화(setState(state)), 그 초기화를 바탕으로 한 업데이트(stateUpdate())가 한쌍인 것을 알 수 있다.
	//이를 바탕으로 좀더 개선작업을 할 수 있을 것 같다.
	//ex IDLE
	//setIdle, IdleUpdate ,_idleTime, 

	//무적 조건과 그 무적 시간.
	bool _invincible;
	float _invincibleTime;

	//Action Variable
	//타격상태 지속기간.
	float _hitDelayTime;
	//최초 피격시 다시 재피격에 제한 딜레이, 또한 기본 밀침 공격을 받을 시 최초 튀는 힘이 적용하는 시간.
	float _initialHitPushbackTime;
	float _hitSpeedX;
	float _hitSpeedY;

	//탄성운동 시 위로 왔다갔다 하는 조건체크
	bool _turnUpDown;
	//현재 어느정도 이동했는지에 대한 수량값
	float _downDistance;
	//탄성으로 튕길 시 어디까지 튕길 것인지에 대한 범위
	float _downRange;
	//탄성 운동 속도.
	float _upDownSpeed;

	//재 공격시 걸리는 시간.
	float _AttackDelayTime;

	//죽음이 확정되고 나서 죽기까지 걸리는 시간, DIE 상태값의 지속 시간.
	float _deadDelayTime;

	//IDLE상태의 지속시간
	float _idleDelayTime;
	//MOVE 상태의 지속시간
	float _moveDelayTime;

	float _jumpDelayTime;
	float _pushDelayTime;
public:
	gameCharacter();
	~gameCharacter();

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<gameObject>(this),
			CEREAL_NVP(_maxHp),
			CEREAL_NVP(_Hp),
			CEREAL_NVP(_maxMp),
			CEREAL_NVP(_Mp),
			CEREAL_NVP(_hitReactionOpponents)

			);
	}

	//gameNode methods

	HRESULT init(string tag, float startX, float startY,float width, float height, float speed, float zOrder , string imageKeyName, DIRECTION direction, STATE state);
	virtual void render(float x, float y);
	virtual void release();
	//gameObject Stuff, OnCollide
	void onCollideEnter(gameObject* gObject, bool isPlayer, bool useReaction);


	
	//state methods
	//항시 두개의 함수로 짝을 이룬다. set과 Action으로, 어떠한 최초의 상태 전환이 이루어 질 시, 
	//set으로 사용하는 변수들을 초기화 시켜준다. 
	//그리고 update에 상태값에 대한 케이스문을 통해 그 상태에 대한 연산을 수행 해줄 Update를 사용한다.
	virtual void setHit(gameObject* gObject, bool isInvinsible = false);
	virtual void hitUpdate();
	virtual void setDie(gameObject* gObject, bool useReaction = true);
	virtual void dieUpdate();
	virtual void setMove();
	virtual void moveUpdate();
	virtual void setAttack();
	virtual void attackUpdate();
	virtual void setIdle();
	virtual void idleUpdate();

	virtual void manaCoinDrop();

	virtual void setJump(gameObject* gObject){};

	//운동 함수들
	void elasticity(float dampingRatio, float lostSpeed);
	void paravola();

	//other methods
	//충돌 상대에가 하나가 아닌 여러개일때, 이 클래스를 상속하는 자식의 init부에서 이 함수로 그 대상을 등록 해 주도록 한다.
	void addOpponentsTag(string tag) { _hitReactionOpponents.push_back(tag); }
	void removeOppenetsTag(string tag)
	{
		for (vector<string>::iterator iter = _hitReactionOpponents.begin(); iter != _hitReactionOpponents.end(); iter++)
		{
			if (*iter == tag)
			{
				_hitReactionOpponents.erase(iter);
				break;
			}

		}
	}
	//inline methods
	inline gameAnimation* getGameAnimation(void){ return _gameAni; }
	inline int getHP(){ return _Hp; }
	inline void setHP(int HP)	{this->_Hp = HP;if (_Hp > _maxHp)_Hp = _maxHp;}
	inline int getMaxHp(){ return  _maxHp; }
	inline void setMaxHp(int mHp){ this->_maxHp = mHp; }
	inline int getMP(){ return _Mp; }
	inline void setMP(int MP){
		this->_Mp = MP;
		if (_Mp > _maxMp)
			_Mp = _maxMp;

		if (_Mp < 0)
			_Mp = 0;
	}
	inline int getMaxMP(){ return _maxMp; }
	inline void setMaxMP(int mMP){ this->_maxMp = mMP; }

	inline float getHitSpeedX(void){ return _hitSpeedX; }
	inline void setHitSpeedX(float hitSpeedX){ _hitSpeedX = hitSpeedX; }

	inline float getHitSpeedY(void){ return _hitSpeedY; }
	inline void setHitSpeedY(float hitSpeedY){ _hitSpeedY = hitSpeedY; }
};

