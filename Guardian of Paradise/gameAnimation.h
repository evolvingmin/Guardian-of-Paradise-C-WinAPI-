#pragma once
#include "animation.h"
#include "gameNode.h"
//�⺻ ����� KeyAnimationManager�� ����
//�ٸ� �װͰ� �ٸ����� ����� ���°��� Ű������ �� �� ������ ����Ÿ�� �������μ� �ڵ�󿡼� ���� ���������� ������ �����ϴٴ� ���̴�.


enum DIRECTION
{
	//���伥���� �̹����� �����Ҷ��� ������ �ǽðڴ�
	DIR_RIGHT, //������ �ʿ���� ���� ������Ʈ�� ��쿡�� �⺻ ������ DIR_RIGHT�� �Ѵ�.
	DIR_LEFT,
	DIR_UP,
	DIR_DOWN,
	DIR_ALL
};
//Game Character states
enum STATE
{
	IDLE,
	MOVE,
	RUN,
	JUMP,
	DOWN,
	HANG,
	PUSH,
	FIRE,
	ATTACK,
	HIT,
	DIE,
	FALL,
	STUN,
	STATE_END
};

class gameAnimation : public gameNode
{
private:

	DIRECTION _direction;
	STATE _state;

	map<pair<DIRECTION, STATE>, animation* > _mGameAnimation;
	image* _mainImage;
	int _alphaValue;

public:
	gameAnimation();
	~gameAnimation();
	HRESULT init(image* image, DIRECTION direction, STATE state);

	//�⺻ ������ ���ϸ��̼�
	void SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop);
	void SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop, void* cbFunction);
	void SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop, void* cbFunction, void* obj);
	//�迭 ���ϸ��̼�
	void SetArrayFrameAnimation(DIRECTION direction, STATE state, int*arr, int arrLen, int fps, bool loop);
	void SetArrayFrameAnimation(DIRECTION direction, STATE state, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void SetArrayFrameAnimation(DIRECTION direction, STATE state, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);
	//���� ���ϸ��̼�
	void SetCoordinateFrameAnimation(DIRECTION direction, STATE state, int start, int end, int fps, bool reverse, bool loop);
	void SetCoordinateFrameAnimation(DIRECTION direction, STATE state, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void SetCoordinateFrameAnimation(DIRECTION direction, STATE state, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);


	void render(float x, float y);
	void frameUpdate();
	void release(void);
	void deleteStateAnimation(STATE state);

	/////////////////////////////////inline//////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline DIRECTION getDirection(void){ return _direction; }
	inline void setDirection(DIRECTION direction)
	{
		if (_direction != direction)
		{
			_direction = direction;
			if (!_mGameAnimation[make_pair(_direction, _state)]->isPlay())
				_mGameAnimation[make_pair(_direction, _state)]->start();

		}

	}

	inline STATE getState(void){ return _state; }
	inline void setState(STATE state)
	{
		if (_state != state)
		{
			_state = state;
			if (!_mGameAnimation[make_pair(_direction, _state)]->isPlay())
				_mGameAnimation[make_pair(_direction, _state)]->start();
		}

	}

	inline void setAlpha(int alpha){ _alphaValue = alpha; }
	inline int getAlpha(void){ return _alphaValue; }
	inline void start() { _mGameAnimation[make_pair(_direction, _state)]->start(); }
	inline void stop(){ _mGameAnimation[make_pair(_direction, _state)]->stop(); }
	inline void pause(){ _mGameAnimation[make_pair(_direction, _state)]->pause(); }
	inline void resume(){ _mGameAnimation[make_pair(_direction, _state)]->resume(); }
	inline bool isPlay(){return _mGameAnimation[make_pair(_direction, _state)]->isPlay();}
};