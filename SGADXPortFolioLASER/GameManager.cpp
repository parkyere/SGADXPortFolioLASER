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
	myGameField.InitGrid(8, 8);
	myInventory.InitCheatInventory();
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
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);
	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f,
		viewport.Width, viewport.Height, 0.0f, -1, 1);
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	myGameField.Render();
	myInventory.Render();
}

void GameManager::Destroy()
{
}
