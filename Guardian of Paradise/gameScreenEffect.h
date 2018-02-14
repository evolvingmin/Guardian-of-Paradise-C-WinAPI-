#pragma once
#include "gameNode.h"

enum EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};

class gameScreenEffect : public gameNode
{
	EFFECT _currentEffect;
	float _effectTime;

	float _addFactor;
	RECT _fadeRect[4];
	image* _fadeImage[4];
public:
	gameScreenEffect();
	~gameScreenEffect();
	HRESULT init(EFFECT effect);
	void update();
	void release();
	void render();
	
	//getter
	inline float getEffectTime(void){ return _effectTime; }
	inline EFFECT getCurrentEFFECT(void) { return _currentEffect; }
};

