#pragma once

class Grid 
{
private:
	
	float gridPosX;
	float gridPosY;
	shared_ptr<Component> myGridComponent;
public:
	static float gridSize;
	constexpr Grid() : gridPosX{ 0.f }, gridPosY{ 0.f }, myGridComponent{ nullptr }
	{
	}
	constexpr Grid(float x, float y) : gridPosX{ x }, gridPosY{ y }, myGridComponent{ nullptr } 
	{
	}
};

