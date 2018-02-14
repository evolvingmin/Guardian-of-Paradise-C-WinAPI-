#pragma once
#include "gameNode.h"
#include "gameFont.h"
#define DIALOG_WINDOW_INTERVAL_X 58
#define DIALOG_WINDOW_INTERVAL_Y 36
class dialogWindow : public gameNode
{
private :
	bool _isActive;
	
	image* _windowImage;
	_TCHAR buffer[1024];
	gameFont* _dialogText;
	int _fontSize;
	int _x;
	int _y;
	float _width;
	float _height;
public:
	dialogWindow();
	~dialogWindow();

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
	void setTextToWindow(string filepath);

	///////////////////////////getter, setter/////////////////////////////////////
	inline void setIsActive(bool isActive){ _isActive = isActive; }
	inline bool getIsActive(void){ return _isActive; }
	inline gameFont* getText(){return _dialogText;}
};

