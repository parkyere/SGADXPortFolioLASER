#include "stdafx.h"

float Grid::gridSize{ 50.f };

void Grid::Render()
{

	DEVICE->SetFVF(InnerVertex[0].fvf);

	//Render inBox
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2, InnerVertex, sizeof(Vertex));

	//Render BoundBox
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, BoundVertex, sizeof(Vertex));
	
	//Render itemInBox if something is in
	if (myGridComponent != nullptr)
	{
		myGridComponent->Render();
	}
}

void Grid::SetGridComponent(shared_ptr<Component> inGridComponent) 
{
	myGridComponent=inGridComponent;
	if (myGridComponent->getDirection() != Direction::NoDirection)
	{
		myGridComponent->SetDir(Direction::Up);
	}
	else 
	{
		myGridComponent->SetDir(Direction::NoDirection);
	}
	myGridComponent->SetPos(gridPosX+0.5f*Grid::gridSize, gridPosY + 0.5f*Grid::gridSize);
}

shared_ptr<Component> Grid::GetGridComponent()
{
	return myGridComponent;
}

bool Grid::CheckClick(LONG x, LONG y) 
{
	if (gridPosX<(float)x && (float)x < gridPosX + gridSize) 
	{
		if (gridPosY<(float)y && (float)y < gridPosY + gridSize)
		{
			return true;
		}
	}
	return false;
}

Direction Grid::CheckBeam(shared_ptr<BeamPulse> inBeam)
{
	switch (inBeam->getDirection()) 
	{
	case Direction::Up:
		if (inBeam->getXpos() > gridPosX && inBeam->getXpos() < gridPosX+gridSize)
		{
			if (inBeam->getYpos()<(gridPosY + 0.5f*gridSize) && inBeam->getYpos() > (gridPosY -0.1f*gridSize) )
			{
				return Direction::Up;
			}
		}
		break;
	case Direction::Down:
		if (inBeam->getXpos() > gridPosX && inBeam->getXpos() < gridPosX + gridSize)
		{
			if (inBeam->getYpos()>(gridPosY + 0.5f*gridSize) && inBeam->getYpos() < (gridPosY + 1.1f*gridSize))
			{
				return Direction::Down;
			}
		}
		break;
	case Direction::Left:
		if (inBeam->getYpos() > gridPosY && inBeam->getYpos() < gridPosY + gridSize)
		{
			if (inBeam->getXpos()<(gridPosX + 0.5f*gridSize) && inBeam->getXpos() > (gridPosX-0.1f*gridSize))
			{
				return Direction::Left;
			}
		}
		break;
	case Direction::Right:
		if (inBeam->getYpos() > gridPosY && inBeam->getYpos() < gridPosY + gridSize)
		{
			if (inBeam->getXpos()>(gridPosX + 0.5f*gridSize) && inBeam->getXpos() < (gridPosX + 1.1f*gridSize))
			{
				return Direction::Right;
			}
		}
		break;
	case Direction::NoDirection:
		throw new exception("Directionless beam detected: It is Bug!");
		break;
	}
	return Direction::NoDirection;
}

void Grid::ReceiveMyTick(time_point<steady_clock>& thisTime)
{
	if (auto mySource = dynamic_pointer_cast<LaserSource>(myGridComponent)) 
	{
		if (mySource->isFiredBefore1Tick)
		{
			mySource->isFiredBefore1Tick = false;
			return;
		}
		else 
		{
			mySource->isFiredBefore1Tick = true;
			MAINGAME->callGameField().AddPulse(mySource->Fire(thisTime));
		}
	}
}
