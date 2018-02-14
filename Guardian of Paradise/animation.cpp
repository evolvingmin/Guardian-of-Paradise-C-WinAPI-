#include "stdafx.h"
#include "animation.h"


animation::animation()
	:_frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIdx(0),
	_play(FALSE)
{
}


animation::~animation()
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임 수
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	//프레임 위치 리스트 셋팅
	_frameList.clear();

	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 리스트에 추가
			_frameList.push_back(framePos);
		}
	}

	//시작은 기본 프레임으로 셋팅해준다
	setDefPlayFrame();

	return S_OK;
}
void animation::release(void)
{

}

//통상적인 플레이
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;


	//루프 여부
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정방향 -> 역방향 <-
	if (reverse)
	{
		//루프 애니메이션이면
		if (_loop)
		{
			//정방향 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 프레임
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//정방향 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 프레임
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//정방향 프레임
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;


	//루프 여부
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정방향 -> 역방향 <-
	if (reverse)
	{
		//루프 애니메이션이면
		if (_loop)
		{
			//정방향 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 프레임
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//정방향 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 프레임
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//정방향 프레임
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);


	//루프 여부
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	//정방향 -> 역방향 <-
	if (reverse)
	{
		//루프 애니메이션이면
		if (_loop)
		{
			//정방향 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 프레임
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//정방향 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 프레임
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//정방향 프레임
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//배열을 통한 플레이
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프 여부 묻는다
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	//루프 여부 묻는다
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	//루프 여부 묻는다
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}


//start와 end를 통한 구간 플레이 2, 8 2~ 8
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프 여부
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if (start == end)
	{
		//시작과 끝 프레임이 같으면
		_playList.clear();
		stop();	//재생할 필요가 없다
		return;
	}

	//시작 프레임이 종료 프레임 보다 큰경우 
	if (start > end)
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}

			}

			//루프 애니메이션이 아니면..
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}

		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//nStart < nEnd
	else
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}

			//루프 애니메이션이 아니면..
			else
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	//루프 여부
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if (start == end)
	{
		//시작과 끝 프레임이 같으면
		_playList.clear();
		stop();	//재생할 필요가 없다
		return;
	}

	//시작 프레임이 종료 프레임 보다 큰경우 
	if (start > end)
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}

			}

			//루프 애니메이션이 아니면..
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}

		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//nStart < nEnd
	else
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}

			//루프 애니메이션이 아니면..
			else
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	//루프 여부
	_loop = loop;

	//플레이 리스트 클리어
	_playList.clear();

	if (start == end)
	{
		//시작과 끝 프레임이 같으면
		_playList.clear();
		stop();	//재생할 필요가 없다
		return;
	}

	//시작 프레임이 종료 프레임 보다 큰경우 
	if (start > end)
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}

			}

			//루프 애니메이션이 아니면..
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}

		else
		{
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//nStart < nEnd
	else
	{
		//다시 되돌아 오는 애니메이션이라면...
		if (reverse)
		{
			//루프 애니메이션이면...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}

			//루프 애니메이션이 아니면..
			else
			{
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}


void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트 시간이 되었다면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;

			if (_nowPlayIdx == _playList.size())
			{
				//루프 플레이
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					//루프가 안돌아갈때
					if (_obj == NULL)
					{
						if (_callbackFunction != NULL) _callbackFunction();
					}
					else
					{
						_callbackFunctionParameter(_obj);
					}


					_nowPlayIdx--;
					_play = FALSE;
				}
			}
		}
	}
}

void animation::start(void)
{
	_play = TRUE;
	_nowPlayIdx = 0;
}

void animation::stop(void)
{
	_play = FALSE;
	_nowPlayIdx = 0;
}

void animation::pause(void)
{
	_play = FALSE;
}

void animation::resume(void)
{
	_play = TRUE;
}