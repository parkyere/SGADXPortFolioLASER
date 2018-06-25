#include "stdafx.h"

float Grid::gridSize{ 50.f };

void Grid::Render()
{
	//Render inBox
	DEVICE->SetFVF(InnerVertex[0].fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2, InnerVertex, sizeof(Vertex));

	//Render itemInBox if something is in
	if (myGridComponent != nullptr) 
	{
		Direction tempDirection = myGridComponent->getDirection();
		myGridComponent->Render(gridPosX,gridPosY,tempDirection);
	}

	//Render BoundBox
	DEVICE->SetFVF(BoundVertex[0].fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, BoundVertex, sizeof(Vertex));

}

void Grid::SetGridComponent(shared_ptr<Component> myGridComponent) 
{
	this->myGridComponent=myGridComponent;
}

shared_ptr<Component> Grid::GetGridComponent()
{
	return myGridComponent;
}
