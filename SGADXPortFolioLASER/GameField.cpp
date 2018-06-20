#include "stdafx.h"

void GameField::InitGrid(int x, int y)
{
	myGrid = vector< vector<Grid> >(x);
	//for (vector<Grid>& singleLine : myGrid) 
	//{
	//	singleLine = vector<Grid>(x);
	//}
	for (int j=0; j<x; j++ )
	{
		for (int i=0; i<y; i++) 
		{
			myGrid[j].emplace_back(x*Grid::gridSize, y*Grid::gridSize);
		}
	}
	return;
}

void GameField::Render()
{
}
