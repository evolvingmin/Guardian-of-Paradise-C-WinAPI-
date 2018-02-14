#include "stdafx.h"
#include "dialogWindow.h"
#include "Player.h"

dialogWindow::dialogWindow()
{
}


dialogWindow::~dialogWindow()
{
}
HRESULT dialogWindow::init()
{
	_isActive = false;
	_windowImage = IMAGEMANAGER->findImage("dialogwindow");

	_x = WINSIZEX / 2 - _windowImage->getWidth() / 2 + DIALOG_WINDOW_INTERVAL_X;
	_y = 500 + DIALOG_WINDOW_INTERVAL_Y;
	_width = _windowImage->getWidth() - DIALOG_WINDOW_INTERVAL_X * 2;
	_height = _windowImage->getHeight() - DIALOG_WINDOW_INTERVAL_Y* 2;
	_fontSize = 30;
	_dialogText = new gameFont;
	_dialogText->init(WHITE, _x, _y, _width, _height, _fontSize, ALIGNMENT_LEFT);


	return S_OK;
}
void dialogWindow::release(void)
{
	SAFE_RELEASE(_dialogText);
}
void dialogWindow::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_dialogText->isPageOver())
			_isActive = false;
		else
			_dialogText->IncreaseCurrentPage();


	}

	if (GQUESTMANAGER->getIsInGame())
	{
		if (GQUESTMANAGER->getPlayer()->getAttackInteraction() && !GQUESTMANAGER->IsSaveWindowActive())
			_isActive = false;
	}

}
void dialogWindow::render(void)
{
	if (_isActive)
	{
		_windowImage->render(getMemDC(), WINSIZEX / 2 - _windowImage->getWidth() / 2, 500);
	//Rectangle(getMemDC(), _x, _y, _x + _width, _y + _height);
		_dialogText->render();

	}

}
void dialogWindow::setTextToWindow(string filepath)
{

	HANDLE file;
	DWORD read;
	ZeroMemory(buffer, sizeof(buffer));

	file = CreateFile(("dialog//" + filepath).c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, buffer, sizeof(buffer), &read, NULL);

	//ÀÐ¾î ¿ÔÀ¸¸é ÆÄ½ÌÇØ¾ßÂ¡



	
	_dialogText->setText(buffer);
	//if (buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\r')
	CloseHandle(file);


}