#pragma once

class Inventory
{
	vector<Grid> InvenGrid;
	vector<Grid> ColorGrid;
	
	bool colorAvailable{ false };
	float posX;
	float posY;
	friend class MapEditor;
public:
	int componentNumber{ 7 };
	int colorNumber{ 7 };
	Inventory();
	void InitInventory();
	void LoadInventory();
	void InitEditorInventory();
	void SetPosition(float x, float y);
	void Render();
	void CheckClickinMapEditorMode(LONG x, LONG y);
	void CheckClickInInvMode(LONG x, LONG y);
	void ChangeColor(Grid & compElem, const LONG &y, const LONG &x);
};