#pragma once

class MapEditor 
{
	int levelNum{0};
	int inventorySize{12};

	static shared_ptr<MapEditor> instance;
	MapEditor();

public:
	static shared_ptr<MapEditor> GetInstance();
	void SetLevelNum(int levelNum);
	void SetState();
	void SaveMap();
	void LoadMap();
};