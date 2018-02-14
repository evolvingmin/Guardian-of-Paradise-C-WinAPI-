#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect() : _effectImage(NULL), _effectAnimation(NULL),
_isRunning(false), _x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	//���࿡ �̹����� ������ ����
	if (!effectImage) return E_FAIL;

	//Ȱ��ȭ ���� �ʱ�ȭ
	_isRunning = false;


	//����Ʈ �̹��� ���� ����
	_effectImage = effectImage;

	//����Ʈ ��� �ð�
	_elapsedTime = elapsedTime;

	//�̹��� �ִϸ��̼� ��ü�� ������ ��������
	if (!_effectAnimation) _effectAnimation = new animation;

	//�ִϸ��̼� ���� ����
	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();


	return S_OK;
}
HRESULT effect::init(image* effectImage, int frameW, int frameH, int* arr, int arrlen, int fps, float elapsedTime)
{
	//���࿡ �̹����� ������ ����
	if (!effectImage) return E_FAIL;

	//Ȱ��ȭ ���� �ʱ�ȭ
	_isRunning = false;


	//����Ʈ �̹��� ���� ����
	_effectImage = effectImage;

	//����Ʈ ��� �ð�
	_elapsedTime = elapsedTime;

	//�̹��� �ִϸ��̼� ��ü�� ������ ��������
	if (!_effectAnimation) _effectAnimation = new animation;

	//�ִϸ��̼� ���� ����
	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setPlayFrame(arr, arrlen, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();


	return S_OK;
}
void effect::update(void)
{
	//Ȱ��ȭ ���� �ʾ����� �������ָ� �ȵ�
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(_elapsedTime);

	//����Ʈ �ִϸ��̼��� ����Ǹ� kill���ش�
	if (!_effectAnimation->isPlay()) killEffect();

}

void effect::render(void)
{
	//���� ���� ������ �׷����� �ʴ´�
	if (!_isRunning) return;

	//Effect �ִϸ��̼� �׷���
	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

void effect::release(void)
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::startEffect(int x, int y)
{
	//����Ʈ ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������� ����
	if (!_effectImage || !_effectAnimation) return;

	//x, y��ǥ�� ����Ʈ ž�̹Ƿ� �߾���ǥ�� �ٲ���
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

void effect::killEffect(void)
{
	_isRunning = false;
}