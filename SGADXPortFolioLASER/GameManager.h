#pragma once

enum class GameState 
{
	IntroMode,
	MapEditorEditMode,
	MapEditorTestMode,
	GamePlayEditMode,
	GamePlayRunMode
};

class GameManager 
{
	static shared_ptr<GameManager> instance;
	GameField myGameField;
	GameState myState{ GameState::MapEditorEditMode };
	Inventory myInventory;
	HINSTANCE gameInstance;
	HWND gameHandle;
	GameManager();
	
public:
	static shared_ptr<GameManager> Get();
	void Initialize(HINSTANCE instance, HWND handle);
	HINSTANCE getInstance();
	HWND getHandle();
	void Update();
	void Render();
	void Destroy();
};