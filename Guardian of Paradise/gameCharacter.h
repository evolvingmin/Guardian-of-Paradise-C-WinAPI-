#pragma once
#include "gameObject.h"
#include "gameAnimation.h"


class gameCharacter : public gameObject
{
private:
	//�浹 ����� �ױװ����� ����Ǵ� ���Ͱ�.
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

	//�ð�(_stateTime)�� ����(if(getState()==state)), �׸��� ���� ������ �ʱ�ȭ(setState(state)), �� �ʱ�ȭ�� �������� �� ������Ʈ(stateUpdate())�� �ѽ��� ���� �� �� �ִ�.
	//�̸� �������� ���� �����۾��� �� �� ���� �� ����.
	//ex IDLE
	//setIdle, IdleUpdate ,_idleTime, 

	//���� ���ǰ� �� ���� �ð�.
	bool _invincible;
	float _invincibleTime;

	//Action Variable
	//Ÿ�ݻ��� ���ӱⰣ.
	float _hitDelayTime;
	//���� �ǰݽ� �ٽ� ���ǰݿ� ���� ������, ���� �⺻ ��ħ ������ ���� �� ���� Ƣ�� ���� �����ϴ� �ð�.
	float _initialHitPushbackTime;
	float _hitSpeedX;
	float _hitSpeedY;

	//ź��� �� ���� �Դٰ��� �ϴ� ����üũ
	bool _turnUpDown;
	//���� ������� �̵��ߴ����� ���� ������
	float _downDistance;
	//ź������ ƨ�� �� ������ ƨ�� �������� ���� ����
	float _downRange;
	//ź�� � �ӵ�.
	float _upDownSpeed;

	//�� ���ݽ� �ɸ��� �ð�.
	float _AttackDelayTime;

	//������ Ȯ���ǰ� ���� �ױ���� �ɸ��� �ð�, DIE ���°��� ���� �ð�.
	float _deadDelayTime;

	//IDLE������ ���ӽð�
	float _idleDelayTime;
	//MOVE ������ ���ӽð�
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
	//�׽� �ΰ��� �Լ��� ¦�� �̷��. set�� Action����, ��� ������ ���� ��ȯ�� �̷�� �� ��, 
	//set���� ����ϴ� �������� �ʱ�ȭ �����ش�. 
	//�׸��� update�� ���°��� ���� ���̽����� ���� �� ���¿� ���� ������ ���� ���� Update�� ����Ѵ�.
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

	//� �Լ���
	void elasticity(float dampingRatio, float lostSpeed);
	void paravola();

	//other methods
	//�浹 ��뿡�� �ϳ��� �ƴ� �������϶�, �� Ŭ������ ����ϴ� �ڽ��� init�ο��� �� �Լ��� �� ����� ��� �� �ֵ��� �Ѵ�.
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

