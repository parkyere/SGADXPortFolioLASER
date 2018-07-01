#pragma once


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
	inline GameState getState() 
	{
		return myState;
	}
	void Update();
	void Render();
	void Destroy();
	void CheckClick(LONG x, LONG y);
};