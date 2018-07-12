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
	friend class MapEditor;

public:
	LPDIRECT3DTEXTURE9 texture;
	static shared_ptr<GameManager> Get();
	void Initialize(HINSTANCE instance, HWND handle);
	void PrepareGame();
	void PrepareEditor();

	void LoadLevel(int levNum);
	void ReloadLevel();
	void LoadNextLevel();
	HINSTANCE getInstance();
	HWND getHandle();
	inline GameState getState() 
	{
		return myState;
	}
	inline void setState(GameState state)
	{
		myState = state;
	}
	void Update();
	void Render();
	inline GameField& callGameField() { return myGameField; }
	void Destroy();
	void CheckClick(LONG x, LONG y);
};