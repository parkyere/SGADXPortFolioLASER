#pragma once

class GameField 
{
	vector< vector<Grid> > myGrid;
public:
	void InitGrid(int x, int y);
	void Render();
};