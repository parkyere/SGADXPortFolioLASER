#include "stdafx.h"

Inventory::Inventory()
{
	SetPosition(50.f, 800.f);
	InitCheatInventory();
	
}

void Inventory::InitInventory()
{
}

void Inventory::LoadInventory()
{
}

void Inventory::InitCheatInventory()
{
	for(int i=0; i< componentNumber; i++)
	{
		InvenGrid.emplace_back(posX+ i * Grid::gridSize,posY );
	}
	InvenGrid[0].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<LaserSource>{new LaserSource}));
	
	//(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->RightRotateDirection();
	//(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->RightRotateDirection();
	//(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->RightRotateDirection();
	//(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->RightRotateDirection();
	(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->SetDir(Direction::Up);
	(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->SetPos(posX+0.5f*Grid::gridSize,posY+0.5f*Grid::gridSize);
	(dynamic_pointer_cast<LaserSource>(InvenGrid[0].GetGridComponent()))->SetColor(BeamColor::Green);
}

void Inventory::SetPosition(float x, float y)
{
	posX = x;
	posY = y;
}

void Inventory::Render()
{
	for (Grid& itemBox : InvenGrid) 
	{
		itemBox.Render();
	}
}
