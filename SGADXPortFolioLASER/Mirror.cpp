#include "stdafx.h"

Mirror::Mirror()
{
	componentName = "Mirror";
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(-0.5f*Grid::gridSize, 0.5f*Grid::gridSize, 0x00000000);
	ComponentShape.emplace_back(0.5f*Grid::gridSize, -0.5f*Grid::gridSize, 0x00000000);
}

Mirror::Mirror(float x, float y, Direction myDir) : Mirror{}
{
	SetDir(myDir);
	SetPos(x, y);
}

void Mirror::Render()
{
	vector<Vertex> tempVertex;
	int shapeIndex = ComponentShape.size();

	for (int i = 0; i<shapeIndex; i++)
	{
		tempVertex.push_back(ComponentShape[i]);
		tempVertex[i].position = { tempVertex[i].position[0] + xPos, tempVertex[i].position[1] + yPos, 0.f };
	}

	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 1, &tempVertex[0], sizeof(Vertex));
}

void Mirror::beamComing(shared_ptr<BeamPulse> inBeam)
{
	BeamColor BeamColorToReflect = inBeam->GetColor();
	Direction BeamDirection = inBeam->getDirection();
	auto thisTime = steady_clock::now();
	switch (ComponentDirection) 
	{
	case Direction::Up:
	case Direction::Down:
		switch (BeamDirection) 
		{
		case Direction::Up: 
			//Reflect to Right
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Right, BeamColorToReflect, thisTime);
			break;
		case Direction::Down: 
			//Reflect to Left
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Left, BeamColorToReflect, thisTime);
			break;
			
		case Direction::Right: 
			//Reflect to Up
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Up, BeamColorToReflect, thisTime);
			break;
		case Direction::Left:
			//Reflect to Down
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Down, BeamColorToReflect, thisTime);
			break;
		}
		break;
	case Direction::Right:
	case Direction::Left:
		switch (BeamDirection)
		{
		case Direction::Up: 
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Left, BeamColorToReflect, thisTime);
			break;
		case Direction::Down: 
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Right, BeamColorToReflect, thisTime);
			break;
		case Direction::Right:
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Down, BeamColorToReflect, thisTime);
			break;
		case Direction::Left: 
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Up, BeamColorToReflect, thisTime);
			break;
		}
		break;
	default:
		throw new exception("Internal Error - Mirror must have a direction!");
	}
}

