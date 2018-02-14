#pragma once
#include "scene.h"
class ending : public scene
{
private:
	image* _bg;
	image* _credit;

	RECT _rc;
	float _x;
	float _y;

public:
	virtual HRESULT init();
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	ending();
	~ending();
};	