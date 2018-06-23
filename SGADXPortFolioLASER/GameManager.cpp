#include "stdafx.h"

shared_ptr<GameManager> GameManager::instance{nullptr};

GameManager::GameManager()
{
}

shared_ptr<GameManager> GameManager::Get()
{
	if (instance == nullptr) 
	{
		instance = shared_ptr<GameManager>{ new GameManager };
	}
	return instance;
}

void GameManager::Initialize(HINSTANCE instance, HWND handle)
{
	gameInstance = instance;
	gameHandle = handle;
	myGameField.InitGrid(10, 11);
}

HINSTANCE GameManager::getInstance()
{
	return gameInstance;
}

HWND GameManager::getHandle()
{
	return gameHandle;
}

void GameManager::Update()
{
	//myState->GameUpdate();
}

void GameManager::Render()
{
	myGameField.Render();
}

void GameManager::Destroy()
{
}
