#pragma once

class Inventory 
{
	vector<Grid> InvenGrid;

	float posX;
	float posY;

public:
	int componentNumber{ 6 };
	Inventory();
	void InitInventory();
	void LoadInventory();
	void InitCheatInventory();
	void SetPosition(float x, float y);
	void Render();
};