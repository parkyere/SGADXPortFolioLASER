#include "stdafx.h"

float Grid::gridSize{ 50.f };

void Grid::Render()
{

	DEVICE->SetFVF(InnerVertex[0].fvf);

	//Render inBox
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2, InnerVertex, sizeof(Vertex));

	//Render BoundBox
	//DEVICE->SetFVF(BoundVertex[0].fvf);
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
	myGridComponent->SetPos(gridPosX+0.5f*Grid::gridSize, gridPosY + 0.5f*Grid::gridSize);
	
}

shared_ptr<Component> Grid::GetGridComponent()
{
	return myGridComponent;
}
