#pragma once
#include "animation.h"
#include "gameNode.h"
//기본 방식은 KeyAnimationManager와 같다
//다만 그것과 다른것은 방향과 상태값을 키값으로 한 맵 형식의 데이타를 만듬으로서 코드상에서 보다 직관적으로 접근이 가능하다는 것이다.


enum DIRECTION
{
	//포토샵에서 이미지를 저장할때의 순서가 되시겠다
	DIR_RIGHT, //방향이 필요없는 게임 오브젝트의 경우에도 기본 방향은 DIR_RIGHT로 한다.
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

	//기본 프레임 에니메이션
	void SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop);
	void SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop, void* cbFunction);
	void SetDefaultFrameAnimation(DIRECTION direction, STATE state, int fps, bool reverse, bool loop, void* cbFunction, void* obj);
	//배열 에니메이션
	void SetArrayFrameAnimation(DIRECTION direction, STATE state, int*arr, int arrLen, int fps, bool loop);
	void SetArrayFrameAnimation(DIRECTION direction, STATE state, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void SetArrayFrameAnimation(DIRECTION direction, STATE state, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);
	//구간 에니메이션
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