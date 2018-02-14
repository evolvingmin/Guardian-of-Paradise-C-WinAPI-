#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;


	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		TXTDATA->init();
		GOBJECTMANAGER->init();
		GQUESTMANAGER->init();
	}

	return S_OK;
}

void gameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		GOBJECTMANAGER->releaseSingleton();
		GQUESTMANAGER->releaseSingleton();
	}
	

	//DC 해제해준다
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, false);

}

void gameNode::render(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	// DC Handle의 약자 화면에 뭔갈 뿌려주는 역할을 담당
	HDC hdc;
	
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		//switch (wParam)
		//{
		//case VK_ESCAPE:
		//	PostQuitMessage(0);
		//	break;
		//}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}