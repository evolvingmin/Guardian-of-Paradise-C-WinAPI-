#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

//셋업
HRESULT imageManager::init(void)
{
	return S_OK;
}

//해제
void imageManager::release(void)
{
	deleteAll();
}

//키 값으로 설정해서 초기화
image* imageManager::addImage(string strKey, int width, int height)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러온다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 맵 리스트에 추가해줌
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const DWORD resID,
	int width, int height, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러온다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면
	if (FAILED(img->init(resID, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 맵 리스트에 추가해줌
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName,
	float x, float y, int width, int height, bool trans,
	COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러온다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 맵 리스트에 추가해줌
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName,
	int width, int height, bool trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러온다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 맵 리스트에 추가해줌
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//키 값으로 설정해서 프레임 이미지 초기화
image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y,
	int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러온다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면
	if (FAILED(img->init(fileName, x, y, width, height, frameX,
		frameY, trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 맵 리스트에 추가해줌
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//동일한 이미지 있는지 찾는다
	image* img = findImage(strKey);

	//키 값과 같은 이미지가 있으면 추가 하지 않고 기존의 이미지를 불러온다
	if (img) return img;

	//이미지 생성
	img = new image;

	//이미지가 제대로 초기화 되지 않았으면
	if (FAILED(img->init(fileName, width, height, frameX, frameY,
		trans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지 맵 리스트에 추가해줌
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//이미지 찾는 함수
image* imageManager::findImage(string strKey)
{
	//해당키가 있는지 검사한다
	mapImageIter key = _mImageList.find(strKey);

	//키를 찾으면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

//이미지 지운다
BOOL imageManager::deleteImage(string strKey)
{
	//해당 키 검색해줌
	mapImageIter key = _mImageList.find(strKey);

	//키 찾으면
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();

		//메모리도 해제
		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return true;
	}

	return false;
}

//전체 이미지 지운다
BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();
	return TRUE;
}

//렌더 함수
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}
void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}