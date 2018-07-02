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

void Grid::ReceiveMyTick()
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
			MAINGAME->callGameField().AddPulse(mySource->Fire());
		}
	}
}
