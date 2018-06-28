// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <exception>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <functional>

using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

// TODO: reference additional headers your program requires here
#define SAFE_RELEASE(p) { if(p){(p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p) { if (p) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }

#define MAINGAME GameManager::Get()
#define DEVICE Device::GetDevice()
#define KEYBOARD Keyboard::Get()
#define MOUSE Mouse::Get()
#define TIMER Frames::Get()
#define CAMERA MainCamera::Get()
#define UI TweakBar::Get()

#define COLOR_R 0xffff0000
#define COLOR_G 0xff00ff00
#define COLOR_B 0xff0000ff
#define COLOR_W 0xffffffff

constexpr int winWidth { 1920 };
constexpr int winHeight{ 1000 };

//Core
#include "Size.h"
#include "MyPoint.h"
#include "Rect.h"

//System
#include "Device.h"
#include "Frames.h"
#include "Keyboard.h"
#include "Mouse.h"

//Render header file
#include "Vertex.h"

#include "Camera.h"
#include "FreeView.h"
#include "FollowView.h"
#include "Factory.h"
#include "MainCamera.h"

//Util Header File
#include "World.h"

#include "Component.h"
#include "LaserSource.h"
#include "Gate.h"
#include "Grid.h"
#include "Inventory.h"


#include "GameField.h"
#include "GameState.h"
#include "MapEditor.h"
#include "GameManager.h"