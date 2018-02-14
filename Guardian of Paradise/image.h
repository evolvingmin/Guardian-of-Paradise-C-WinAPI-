#pragma once
#include "animation.h"
//=====================================================
// 2015.03.11 ## image Class ## - Thursday Of Blood
//=====================================================
#include "animation.h"

class image
{
public:
	//이미지 로딩 스타일
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스로부터 생성
		LOAD_FILE,			//파일로부터 생성
		LOAD_EMPTY,			//그냥 생성
		LOAD_END			//아무것도 없음
	};

	//이미지 정보 구조체
	typedef struct tagImageInfo
	{
		DWORD	resID;			//리소스ID
		HDC		hMemDC;			//메모리DC
		HBITMAP	hBit;			//비트맵
		HBITMAP	hOBit;			//올드비트맵
		float	x;				//이미지 x좌표
		float	y;				//이미지 y좌표
		int		width;			//가로크기
		int		height;			//세로크기
		int		currentFrameX;	//현재 프레임 X
		int		currentFrameY;	//현재 프레임 Y
		int		maxFrameX;		//최대 프레임 X
		int		maxFrameY;		//최대 프레임 Y
		int		frameWidth;		//프레임 가로크기
		int		frameHeight;	//프레임 세로크기
		BYTE	loadType;		//이미지로딩타입
		RECT	boundingBox;	//이미지 바운딩박스

		//초기화
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}

	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	//생성자에서 멤버이니셜 라이즈로 바로 초기화 해줄것!!
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름

	BOOL			_trans;			//투명배경이냐? 
	COLORREF		_transColor;	//투명컬러 키

	BLENDFUNCTION	_blendFunc;		//알파블렌드를 위한 정보
	LPIMAGE_INFO	_blendImage;	//알파블렌드를 사용하기 위한 이미지 정보

public:
	image(void);
	~image(void);

	image(image&& other)
	{
		_imageInfo = other._imageInfo;
		_fileName = other._fileName;
		_trans = other._trans;
		_transColor = other._transColor;
		_blendFunc = other._blendFunc;
		_blendImage = other._blendImage;

		other._imageInfo = nullptr;
		other._fileName = nullptr;
		other._trans = false;
		other._transColor = 255;

		other._blendImage = nullptr;
	}
	image& operator=(image&& other)
	{
		if (this != &other)
		{
			this->_imageInfo = other._imageInfo;
			this->_fileName = other._fileName;
			this->_trans = other._trans;
			this->_transColor = other._transColor;
			this->_blendFunc = other._blendFunc;
			this->_blendImage = other._blendImage;

			other._imageInfo = nullptr;
			other._fileName = nullptr;
			other._trans = false;
			other._transColor = 255;
			other._blendImage = nullptr;
		}
		return *this;
	}

	//초기화 함수
	//빈 비트맵 이미지 만든다
	HRESULT init(int width, int height);

	//이미지를 리소스로부터 읽어온다
	HRESULT	init(const DWORD resID, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	//이놈이 젤 중요함
	//이미지 파일 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//이미지 + 프레임 파일 초기화
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//삭제
	void release(void);

	//투명 키 세팅
	void setTransColor(BOOL trans, COLORREF transColor);

	//==================================================================
	//		## 일반렌더 ##
	//==================================================================
	//렌더(hdc) 0, 0 위치에 이미지를 뿌린다
	void render(HDC hdc);
	//렌더(hdc, x좌표, y좌표) 내가 원하는 지정위치에 이미지를 뿌린다
	void render(HDC hdc, int destX, int destY);
	//렌더(hdc, x좌표, y좌표, 원본이미지 x좌표, 원본이미지 x좌표, 원본이미지 가로크기, 원본이미지 세로크기)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## 프레임렌더 ##
	//==================================================================

	//프레임렌더(hdc, x좌표, y좌표) 내가 원하는 지정위치에 프레임이미지를 뿌린다
	void frameRender(HDC hdc, int destX, int destY);
	//프레임렌더(hdc, x좌표, y좌표, 현재프레임의 X위치, 현재프레임의 Y위치)
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//==================================================================
	//		## 알파렌더 ##
	//==================================================================

	//알파렌더(hdc, 알파값) 0, 0 위치에 이미지를 뿌린다
	void alphaRender(HDC hdc, BYTE alpha);
	//알파렌더(hdc, x좌표, y좌표, 알파값) 내가 원하는 지정위치에 이미지를 뿌린다
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//알파렌더(hdc, x좌표, y좌표, 원본이미지 x좌표, 원본이미지 x좌표, 원본이미지 가로크기, 원본이미지 세로크기, 알파값)
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//==================================================================
	//		## 프레임 알파렌더 ##
	//==================================================================

	//프레임 알파렌더(hdc, x좌표, y좌표, 현재프레임의 X위치, 현재프레임의 Y위치, 알파값)
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//==================================================================
	//		## 루프렌더 ## (백그라운드 맵 스크롤링)
	//==================================================================

	//루프렌더(hdc, 루프시킬 렉트영역, x오프셋, y오프셋)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//==================================================================
	//		## 애니렌더 + 애니렌더알파 ##
	//==================================================================

	//애니렌더(hdc, x좌표, y좌표, 애니메이션)
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	//애니렌더알파(hdc, x좌표, y좌표, 애니메이션, 알파값)
	void aniRenderAlpha(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//==================================================================
	//		## 이미지 관련 inline(매크로함수) ##
	//==================================================================

	//DC 얻는다
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//이미지 x좌표 세팅
	inline void setX(float x) { _imageInfo->x = x; }

	//이미지 x좌표 얻기
	inline float getX(void) { return _imageInfo->x; }

	//이미지 y좌표 세팅
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 y좌표 세팅
	inline float getY(void) { return _imageInfo->y; }

	//이미지 센터좌표 세팅
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//가로크기 얻기
	inline int getWidth(void) { return _imageInfo->width; }

	//세로크기 얻기
	inline int getHeight(void) { return _imageInfo->height; }

	//바운딩박스(충돌체크)
	inline RECT boundingBox(void)
	{
		RECT rc = { int(_imageInfo->x - (_imageInfo->width / 2)),
			int(_imageInfo->y - (_imageInfo->height / 2)),
			int(_imageInfo->x + (_imageInfo->width / 2)),
			int(_imageInfo->y + (_imageInfo->height / 2)) };
		return rc;
	}

	//프레임바운드 박스(충돌체크)
	inline RECT frameBoundingBox(void)
	{
		RECT rc = { int(_imageInfo->x),
			int(_imageInfo->y),
			int(_imageInfo->x + _imageInfo->frameWidth),
			int(_imageInfo->y + _imageInfo->frameHeight) };
		return rc;
	}

	//프레임X 세팅
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	//프레임Y 세팅
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	//프레임X 얻기
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }

	//프레임Y 얻기
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	//프레임 가로길이 얻기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }

	//프레임 세로길이 얻기
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//맥스프레임 x 얻기
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }

	//맥스프레임 y 얻기
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }
};

