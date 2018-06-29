#pragma once

class Inventory 
{
	vector<Grid> InvenGrid;
	vector<Grid> ColorGrid;
	
	bool colorAvailable{ false };
	float posX;
	float posY;

public:
	int componentNumber{ 6 };
	int colorNumber{ 7 };
	Inventory();
	void InitInventory();
	void LoadInventory();
	void InitCheatInventory();
	void SetPosition(float x, float y);
	void Render();
};