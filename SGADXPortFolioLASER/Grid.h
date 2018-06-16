#pragma once

class Grid 
{
private:
	float gridSize{ 40.f };
	float gridPosX;
	float gridPosY;
	shared_ptr<Component> myGridComponent;
public:
	Grid();
	Grid(float x, float y);

};