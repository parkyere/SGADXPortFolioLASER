#pragma once

class Grid 
{
private:
	shared_ptr<Component> myGridComponent;
	Vertex InnerVertex[4];
	Vertex BoundVertex[5];

public:
	float gridPosX;
	float gridPosY;
	static float gridSize;
	Grid(float x, float y) : gridPosX{ x }, gridPosY{ y }, myGridComponent{ nullptr }
	{
		BoundVertex[0] = Vertex{ x                  ,y                  , -0.1f , 0xff000000 };
		BoundVertex[1] = Vertex{ x + Grid::gridSize ,y                  , -0.1f , 0xff000000 };
		BoundVertex[2] = Vertex{ x + Grid::gridSize ,y + Grid::gridSize , -0.1f , 0xff000000 };
		BoundVertex[3] = Vertex{ x                  ,y + Grid::gridSize , -0.1f , 0xff000000 };
		BoundVertex[4] = Vertex{ x                  ,y                  , -0.1f , 0xff000000 };
												    
		InnerVertex[0] = Vertex{ x                  ,y                 , 0.8f , 0xff777777 };
		InnerVertex[1] = Vertex{ x + Grid::gridSize ,y                 , 0.8f , 0xff777777 };
		InnerVertex[2] = Vertex{ x                  ,y + Grid::gridSize, 0.8f , 0xff777777 };
		InnerVertex[3] = Vertex{ x + Grid::gridSize ,y + Grid::gridSize, 0.8f , 0xff777777 };
	}

	Grid() : Grid::Grid{ 0.f,0.f }
	{
	}

	void Render();
	void SetGridComponent(shared_ptr<Component> inGridComponent);
	shared_ptr<Component>& GetGridComponent();
	bool CheckClick(LONG x, LONG y);
	Direction CheckBeam(shared_ptr<BeamPulse> inBeam);
	Direction CheckBeamFaster(shared_ptr<BeamPulse> inBeam);
	void ReceiveMyTick(time_point<steady_clock>& thisTime);
};

