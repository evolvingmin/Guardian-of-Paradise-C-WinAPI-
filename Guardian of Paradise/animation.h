#pragma once
#include <vector>

//===========================================
// ## animation ##
//===========================================

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

class animation
{
public:
	//프레임 접근은 임의 접근이 가능해야해서 public으로 선언
	typedef vector<POINT> _vFrameList;
	//프레임 플레이리스트
	typedef vector<int> _vPlayList;

private:
	int _frameNum;

	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameWidth;
	int _frameHeight;

	BOOL _loop;

	float _frameUpdateSec;
	float _elapsedSec;

	DWORD _nowPlayIdx;
	BOOL _play;

	void* _obj;
	CALLBACK_FUNCTION _callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//그냥 일반 프레임 재생
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열에 담아서 프레임 재생
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//구간의 시작과 끝을 가지고 프레임 재생
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);


	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	//플레이 여부 확인
	inline BOOL isPlay(void) { return _play; }

	//프레임 위치 가져오기
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	//프레임 가로크기 얻어오기
	inline int getFrameWidth(void) { return _frameWidth; }

	//프레임 세로크기 얻어오기
	inline int getFrameHeight(void) { return _frameHeight; }
	//현재 재생중인 에니메이션 인덱스값 가져오기.
	inline DWORD getCurrentPlayIndex(void) { return _nowPlayIdx; }
	inline void setCurrentPlayIndex(DWORD playIndex) { _nowPlayIdx = playIndex; }
};

