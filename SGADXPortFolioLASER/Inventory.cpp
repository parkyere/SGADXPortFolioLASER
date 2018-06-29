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
	colorAvailable = true;
	for(int i=0; i< componentNumber; i++)
	{
		InvenGrid.emplace_back(posX+ i * Grid::gridSize,posY );
	}
	InvenGrid[0].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<LaserSource> {new LaserSource}));
	InvenGrid[1].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<BeamSplitter>{new BeamSplitter}));
	InvenGrid[2].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<ColorChanger>{new ColorChanger}));
	InvenGrid[3].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<Mirror>      {new Mirror}));
	
	for (int i = 0; i< colorNumber; i++)
	{
		ColorGrid.emplace_back(posX + i * Grid::gridSize, posY+ Grid::gridSize);
		ColorGrid[i].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<ColorObject> {new ColorObject}));
	}
	dynamic_pointer_cast<ColorObject>(ColorGrid[0].GetGridComponent())->SetColor(BeamColor::Red);
	dynamic_pointer_cast<ColorObject>(ColorGrid[1].GetGridComponent())->SetColor(BeamColor::Green);
	dynamic_pointer_cast<ColorObject>(ColorGrid[2].GetGridComponent())->SetColor(BeamColor::Blue);
	dynamic_pointer_cast<ColorObject>(ColorGrid[3].GetGridComponent())->SetColor(BeamColor::Cyan);
	dynamic_pointer_cast<ColorObject>(ColorGrid[4].GetGridComponent())->SetColor(BeamColor::Magenta);
	dynamic_pointer_cast<ColorObject>(ColorGrid[5].GetGridComponent())->SetColor(BeamColor::Yellow);
	dynamic_pointer_cast<ColorObject>(ColorGrid[6].GetGridComponent())->SetColor(BeamColor::White);
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
	if (colorAvailable) 
	{
		for (Grid& colorBox : ColorGrid) 
		{
			colorBox.Render();
		}
	}
}
