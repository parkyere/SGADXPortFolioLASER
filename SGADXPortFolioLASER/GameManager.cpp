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
	if (myState == GameState::MapEditorEditMode) 
	{
		myGameField.InitGrid(8, 8);
		myInventory.InitInventory();
		myMapMakingTool.SetPosition(800.f,50.f);
		myMapMakingTool.InitEditorInventory();
	}
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
	switch (myState) 
	{
	case GameState::MapEditorEditMode:
		HAND->UpdateInEditMode();
		if (KEYBOARD->KeyDown(VK_SPACE)) 
		{
			HAND->ClearHand();
			myState = GameState::MapEditorTestMode;
		}
		break;
	case GameState::MapEditorTestMode:
		myGameField.Update();
		if (KEYBOARD->KeyDown(VK_ESCAPE))
		{
			callGameField().clearBeamPulses();
			myState = GameState::MapEditorEditMode;
		}
		break;

	case GameState::GamePlayEditMode:
		HAND->UpdateInEditMode();
		break;
	case GameState::GamePlayRunMode:
		break;

	case GameState::IntroMode:
		break;
	default:
		throw new exception("Unknown Game State!");
	}

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
	myMapMakingTool.Render();
	HAND->Render();
}

void GameManager::Destroy()
{
}
void GameManager::CheckClick(LONG x, LONG y) 
{
	switch (myState)
	{
	case GameState::MapEditorEditMode:
		myGameField.CheckClick(x, y);
		myMapMakingTool.CheckClickinMapEditorMode(x, y);
		break;
	case GameState::MapEditorTestMode:

		break;
	case GameState::GamePlayEditMode:

		break;
	case GameState::GamePlayRunMode:

		break;

	case GameState::IntroMode:

		break;
	default:
		throw new exception("Unknown Game State!");
	}
}
