#pragma once

class GameManager 
{
	GameField myGameField;
	GameState myState;
	Inventory myInventory;
	HINSTANCE gameInstance;
	HWND gameHandle;
public:
	GameManager(HINSTANCE instance, HWND handle);
	void Initialize();
	void Update();
	void Render();
	void Destroy();
};