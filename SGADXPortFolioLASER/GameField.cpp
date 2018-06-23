#include "stdafx.h"

void GameField::InitGrid(int x, int y)
{
	myGrid = vector< vector<Grid> >(x);
	//for (vector<Grid>& singleLine : myGrid) 
	//{
	//	singleLine = vector<Grid>(x);
	//}
	for (int i=0; i<x; i++ )
	{
		for (int j=0; j<y; j++) 
		{
			myGrid[i].emplace_back(i*Grid::gridSize, j*Grid::gridSize);
		}
	}
}

void GameField::Render()
{
	for (vector<Grid>& currentLine : myGrid) 
	{
		for (Grid& currentGrid : currentLine) 
		{
			currentGrid.Render();
		}
	}
}
