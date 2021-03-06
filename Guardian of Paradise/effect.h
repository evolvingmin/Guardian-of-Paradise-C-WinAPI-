#pragma once
#include "gameNode.h"

//�ӵ��� ���� ������
class animation;

class effect : public gameNode
{
protected:
	int _x;						//����Ʈ ��ǥ��ġ(x) ����Ʈ
	int _y;						//����Ʈ ��ǥ��ġ(y) ž

	image* _effectImage;		//����Ʈ �̹���
	animation* _effectAnimation;//����Ʈ �ִϸ��̼�
	BOOL _isRunning;			//����Ʈ Ȱ��ȭ ����
	float _elapsedTime;			//����Ʈ ����ð�

public:
	effect();
	virtual ~effect();

	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual HRESULT init(image* effectImage, int frameW, int frameH, int* arr, int arrlen, int fps, float elapsedTime);
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	void startEffect(int x, int y);
	virtual void killEffect(void);

	BOOL getIsRunning(void) { return _isRunning; }
};

