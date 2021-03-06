// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <commdlg.h>
#include <Shobjidl.h>
#include <Mmsystem.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <exception>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <thread>

using namespace std;
using namespace std::chrono;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comdlg32.lib")

// TODO: reference additional headers your program requires here
#define SAFE_RELEASE(p) { if(p){(p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p) { if (p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }

#define MAINGAME GameManager::Get()
#define DEVICE Device::GetDevice()
#define KEYBOARD Keyboard::Get()
#define MOUSE Mouse::Get()
#define HAND Hand::Get()
#define MAPEDITOR MapEditor::GetInstance()
#define BACKGROUND BackGround::Get()
#define INTROSCENE IntroScene::Get()

#define COLOR_R 0xffff0000
#define COLOR_G 0xff00ff00
#define COLOR_B 0xff0000ff
#define COLOR_W 0xffffffff

constexpr int winWidth { 1920 };
constexpr int winHeight{ 1000 };

//Core
#include "Size.h"
#include "MyPoint.h"
#include "Xml.h"

//System
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"

//Render header file
#include "Vertex.h"

#include "Component.h"
#include "BeamPulse.h"
#include "ColorObject.h"
#include "LaserSource.h"

#include "Gate.h"
#include "Goal.h"
#include "BeamBeingAbsorbed.h"
#include "BeamBeingGenerated.h"
#include "ColorAdder.h"
#include "ColorChanger.h"
#include "BeamSplitter.h"
#include "Mirror.h"
#include "Grid.h"
#include "Inventory.h"
#include "IntroScene.h"
#include "Hand.h"
#include "GameField.h"
#include "GameState.h"
#include "MapEditor.h"
#include "BackGround.h"
#include "GameManager.h"

struct guarded_thread : thread 
{
	using thread::thread;
	~guarded_thread() 
	{
		if (joinable()) join();
	}
};