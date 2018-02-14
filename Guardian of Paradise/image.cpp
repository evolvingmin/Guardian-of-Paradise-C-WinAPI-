#include "stdafx.h"
#include "image.h"
//���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
#pragma comment (lib, "msimg32.lib") 

//��� �̴ϼȶ������ �ʱ�ȭ
image::image() : _imageInfo(NULL), _fileName(NULL), _trans(false), _transColor(RGB(0, 0, 0))
{
}
image::~image()
{
}
//==================================================================
//		## �����ڿ� �Ҹ��ڴ� ���̻� ������� �ʴ´� ## 
//==================================================================

//�� ��Ʈ�� �̹��� �����
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ����
	if (_imageInfo != NULL) release();

	//HDC ��´�
	HDC hdc = GetDC(_hWnd);
	//CreateCompatibleDC => ��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�
	//CreateCompatibleBitmap => ���� DC�� ȣȯ�Ǵ� ��Ʈ���� �����Ѵ�

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//���� �÷� �ʱ�ȭ
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹����� ���ҽ��κ��� �о�´�
HRESULT	image::init(const DWORD resID, int width, int height, BOOL trans, COLORREF transColor)
{
	//���ʱ�ȭ ����
	if (_imageInfo != NULL) release();

	//HDC ��´�
	HDC hdc = GetDC(_hWnd);
	//CreateCompatibleDC => ��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�
	//CreateCompatibleBitmap => ���� DC�� ȣȯ�Ǵ� ��Ʈ���� �����Ѵ�

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//���� �÷� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̳��� �� �߿���
//�̹����� ���Ϸκ��� �о�´�
HRESULT image::init(const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǹ�
	if (fileName == NULL) return E_FAIL;

	//���ʱ�ȭ ����
	if (_imageInfo != NULL) release();

	//HDC ��´�
	HDC hdc = GetDC(_hWnd);
	//CreateCompatibleDC => ��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�
	//CreateCompatibleBitmap => ���� DC�� ȣȯ�Ǵ� ��Ʈ���� �����Ѵ�

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = 0;
	_imageInfo->frameHeight = 0;

	//���� ��� �̸����� ����
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��⿡ ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ ó��
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ��� �̸� ����
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = isTrans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� + ������ ���� �ʱ�ȭ
HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ ó��
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� ��� �̸� ����
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ ó��
	if (_imageInfo != NULL) release();

	//DC ��´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���� ��� �̸� ����
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� �÷� ����
	_trans = trans;
	_transColor = transColor;

	//���� ���� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���� ���� ����� ���� �̹��� ����
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���� DC ����
	ReleaseDC(_hWnd, hdc);

	//���ҽ� ��� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//����
void image::release(void)
{
	//�̹����� �ִٸ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//���ĺ��� ��� �̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		//���� �÷� �ʱ�ȭ
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//���� Ű ����
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//����(hdc) 0, 0 ��ġ�� �̹����� �Ѹ���
void image::render(HDC hdc)
{
	//���� ����ȭ �Ǿ� �ֳ�?
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//������ ����� DC
			(int)_imageInfo->x,		//����� ��ǥ ������ X
			(int)_imageInfo->y,		//����� ��ǥ ������ Y
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,		//������ DC
			0, 0,					//���� ��������
			_imageInfo->width,		//����� ���� ����ũ��
			_imageInfo->height,		//����� ���� ����ũ��
			_transColor);			//���翡�� ������ ���� ����
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//����(hdc, x��ǥ, y��ǥ) ���� ���ϴ� ������ġ�� �̹����� �Ѹ���
void image::render(HDC hdc, int destX, int destY)
{
	//���� ����ȭ �Ǿ� �ֳ�?
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ����ũ��
			_imageInfo->height,	//����� ����ũ��
			_imageInfo->hMemDC,	//������ DC
			0, 0,				//���� ��������
			_imageInfo->width,	//����� ���� ����ũ��
			_imageInfo->height,	//����� ���� ����ũ��
			_transColor);		//���翡�� ������ ����
	}
	else
	{
		//BitBlt DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//����(hdc, x��ǥ, y��ǥ, �����̹��� x��ǥ, �����̹��� x��ǥ, �����̹��� ����ũ��, �����̹��� ����ũ��)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//���� ����ȭ �Ǿ� �ֳ�?
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			sourWidth,			//����� ����ũ��
			sourHeight,			//����� ����ũ��
			_imageInfo->hMemDC,	//������ DC
			sourX, sourY,		//���� ��������
			sourWidth,			//����� ���� ����ũ��
			sourHeight,			//����� ���� ����ũ��
			_transColor);		//���翡�� ������ ����
	}
	else
	{
		//BitBlt DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//�����ӷ���(hdc, x��ǥ, y��ǥ) ���� ���ϴ� ������ġ�� �������̹����� �Ѹ���
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//�����ӷ���(hdc, x��ǥ, y��ǥ, ������������ X��ġ, ������������ Y��ġ)
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

//���ķ���(hdc, ���İ�) 0, 0 ��ġ�� �̹����� �Ѹ���
void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//����ؾߵ�DC�� �׷����ִ� ������ Blend�� �׸���.
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �׸���.
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//BlendDC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//���ķ���(hdc, x��ǥ, y��ǥ) ���� ���ϴ� ������ġ�� �̹����� �Ѹ���
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	//���� ����ȭ �Ǿ� �ֳ�?
	if (_trans)
	{
		//����ؾ� �� DC�� �׷��� �ִ� ������ blend�� �׷��ش�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//����ؾ� �� �̹����� blend�� �׷��ش�

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//���ķ���(hdc, x��ǥ, y��ǥ, �����̹��� x��ǥ, �����̹��� x��ǥ, �����̹��� ����ũ��, �����̹��� ����ũ��)
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	//���� ����ȭ �Ǿ� �ֳ�?
	if (_trans)
	{
		//����ؾ� �� DC�� �׷��� �ִ� ������ blend�� �׷��ش�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//����ؾ� �� �̹����� blend�� �׷��ش�
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		//blendDC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}

}

//������ ���ķ���(hdc, x��ǥ, y��ǥ, ������������ X��ġ, ������������ Y��ġ, ���İ�)
void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	alphaRender(hdc, destX, destY,
		currentFrameX * _imageInfo->frameWidth,
		currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		alpha);
}

//��������(hdc, ������ų ��Ʈ����, x������, y������)
void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//offSet ���� ������ ��쿡 �������ش�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���)�� ������ ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷����� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ�(�̹���sour) ������ ���� ���
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �縸ŭ right ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

//�ִϷ���(hdc, x��ǥ, y��ǥ, �ִϸ��̼�)
void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
//�ִϷ�������(hdc, x��ǥ, y��ǥ, �ִϸ��̼�, ���İ�)
void image::aniRenderAlpha(HDC hdc, int destX, int destY, animation* ani, BYTE alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}
