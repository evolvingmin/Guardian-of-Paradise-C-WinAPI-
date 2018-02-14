#pragma once
#include "timer.h"
class gameTimer 
{
	timer* _timer;
	bool _isSaveActive;

public:
	gameTimer();
	~gameTimer();
	inline bool IsActive(void){ return _isSaveActive; };
	void ActiveTimer();
	void DeActiveTimer();
	bool IsElapsedAt(float time, bool isContinue);
	void update();
	//��Ÿ� ����
	bool ActiveWhile(float time);
	
};

