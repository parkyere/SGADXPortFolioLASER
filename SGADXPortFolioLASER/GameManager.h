#pragma once


class GameManager 
{
	static shared_ptr<GameManager> instance;
	GameField myGameField;
	GameState myState{ GameState::MapEditorEditMode };
	Inventory myInventory;
	Inventory myMapMakingTool;
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
	inline GameField& callGameField() { return myGameField; }
	void Destroy();
	void CheckClick(LONG x, LONG y);
};