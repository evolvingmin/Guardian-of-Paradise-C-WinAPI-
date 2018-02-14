#pragma once
#include "gameNode.h"


class gameObject;
class gameCamera : public gameNode
{	
	bool _isMovableCamera;
	bool _isFocused;
	bool _isControlable;

	gameObject* _focusedObject;
	
	float _x, _y;
	RECT _cameraView;
	RECT _mapSize;



	float _speed;
	bool _instanceFocus;
	float _focusSpeed;

public:
	gameCamera();
	~gameCamera();

	void init( bool isControlable ,RECT mapSize = RectMake(0, 0, WINSIZEX, WINSIZEY));
	void onFocus(gameObject* object, bool instanceFocus);
	void onFocus(gameObject& object, bool instanceFocus);
	inline void onCamera(){ _isMovableCamera = true; }
	
	inline void offFocus() { _isFocused = false; }
	inline void setCameraSpeed(float speed){ _speed = speed; }
	inline float getCameraSpeed(){ return _speed; }
	inline void setFocusSpeed(float focusSpeed){ _focusSpeed = focusSpeed; }
	inline float getFocusSpeed(){ return _focusSpeed; }
	inline RECT getCameraView(){ return _cameraView; }
	inline POINT getRelativeAdress(float x, float y) { return PointMake(x - _cameraView.left ,  y -_cameraView.top ); }


	inline float getX(){ return _x; }
	inline float getY(){ return _y; }
	inline void setX(float x){ _x = x; }
	inline void setY(float y){ _y = y; }
	inline void setMapSize(RECT mapSIze) { _mapSize = mapSIze; }


	void update();
	void render();
	void cameraRender();
	void cameraUpdate();
	void cameraRender(gameObject& object);
	//spatial hasing °ü·Ã ·»´õµé
	void cameraRender(float x, float y);
	void cameraRender(int x, int y);
	void release();
};

