#include "stdafx.h"

shared_ptr<GameManager> GameManager::instance{nullptr};

GameManager::GameManager() 
{
	myState = GameState::IntroMode;
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
	INTROSCENE;
	//if (myState == GameState::MapEditorEditMode) 
	//{
	//	myGameField.InitGrid(8, 8);
	//	myInventory.InitInventory();
	//	myMapMakingTool.SetPosition(800.f,50.f);
	//	myMapMakingTool.InitEditorInventory();
	//}

}

void GameManager::PrepareGame()
{
	MAPEDITOR->LoadMap("tutorial01.xml");
}

void GameManager::PrepareEditor()
{
}

void GameManager::LoadLevel(int levNum)
{
	switch (levNum) 
	{
	case 0:
		MAPEDITOR->LoadMap("tutorial01.xml");
		break;
	case 1:
		MAPEDITOR->LoadMap("tutorial02.xml");
		break;
	case 2:
		MAPEDITOR->LoadMap("tutorial03.xml");
		break;
	case 3:
		MAPEDITOR->LoadMap("tutorial04.xml");
		break;
	case 4:
		MAPEDITOR->LoadMap("tutorial05.xml");
		break;
	case 5:
		MAPEDITOR->LoadMap("tutorial06.xml");
		break;
	case 6:
		MAPEDITOR->LoadMap("level1.xml");
		break;
	case 7:
		MAPEDITOR->LoadMap("level2.xml");
		break;
	case 8:
		MAPEDITOR->LoadMap("level3.xml");
		break;
	default:
		break;
	}
}

void GameManager::ReloadLevel()
{
	LoadLevel(myGameField.levelNum);
}

void GameManager::LoadNextLevel()
{
	LoadLevel(myGameField.levelNum+1);
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
		HAND->UpdateInMapEditMode();
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
		HAND->UpdateInPlayEditMode();
		if (KEYBOARD->KeyDown(VK_SPACE))
		{
			HAND->ClearHand();
			myState = GameState::GamePlayRunMode;
		}
		else if (KEYBOARD->KeyDown(VK_ESCAPE))
		{
			MAINGAME->ReloadLevel();
		}
		break;
	case GameState::GamePlayRunMode:
		myGameField.Update();
		if (KEYBOARD->KeyDown(VK_ESCAPE))
		{
			callGameField().clearBeamPulses();
			myState = GameState::GamePlayEditMode;
			MAINGAME->ReloadLevel();
		}
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

	BACKGROUND->Render();
	DEVICE->SetTexture(0, NULL);
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
		myInventory.CheckClickInInvMode(x, y);
		break;
	case GameState::MapEditorTestMode:

		break;
	case GameState::GamePlayEditMode:
		myGameField.CheckClick(x, y);
		myInventory.CheckClickInInvMode(x, y);
		break;
	case GameState::GamePlayRunMode:

		break;

	case GameState::IntroMode:

		break;
	default:
		throw new exception("Unknown Game State!");
	}
}
