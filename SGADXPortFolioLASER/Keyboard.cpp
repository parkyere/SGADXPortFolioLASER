#include "stdafx.h"
#include "Keyboard.h"

shared_ptr<Keyboard> Keyboard::instance = nullptr;

shared_ptr<Keyboard> Keyboard::Get()
{
	if (instance == nullptr)
		instance = shared_ptr<Keyboard>(new Keyboard);

	return instance;
}

void Keyboard::Delete()
{
	instance.reset();
}

void Keyboard::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	//0, 1, 128, 129
	//1은 키가 한번 눌려졌음. 다시 키 눌림시 0으로 토글
	//128 - 0상태일때 해당 키가 계속 눌려져있음.
	//129 - 1상태일때 해당 키가 계속 눌려져있음
	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN; //이전 0, 현재 1 - KeyDown
		else if (oldState == 1 && state == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP; //이전 1, 현재 0 - KeyUp
		else if (oldState == 1 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS; //이전 1, 현재 1 - KeyPress
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}
}

Keyboard::Keyboard()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Keyboard::~Keyboard()
{

}
