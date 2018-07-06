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
		if (inBeam->getXpos() > gridPosX+0.5f*gridSize-BeamPulse::beamThickness && inBeam->getXpos() < gridPosX + 0.5f*gridSize+ BeamPulse::beamThickness)
		{
			if (inBeam->getYpos()<(gridPosY + 0.5f*gridSize ) && inBeam->getYpos() > (gridPosY + 0.5f*gridSize -BeamPulse::beamThickness) )
			{
				return Direction::Up;
			}
		}
		break;
	case Direction::Down:
		if (inBeam->getXpos() > gridPosX + 0.5f*gridSize - BeamPulse::beamThickness && inBeam->getXpos() < gridPosX + 0.5f*gridSize + BeamPulse::beamThickness)
		{
			if (inBeam->getYpos()>(gridPosY + 0.5f*gridSize) && inBeam->getYpos() < (gridPosY + 0.5f*gridSize + BeamPulse::beamThickness))
			{
				return Direction::Down;
			}
		}
		break;
	case Direction::Left:
		if (inBeam->getYpos() > gridPosY +0.5f*gridSize- BeamPulse::beamThickness && inBeam->getYpos() < gridPosY +0.5f*gridSize+ BeamPulse::beamThickness)
		{
			if (inBeam->getXpos()>(gridPosX + 0.5f*gridSize-BeamPulse::beamThickness) && inBeam->getXpos()< (gridPosX+0.5f*gridSize))
			{
				return Direction::Left;
			}
		}
		break;
	case Direction::Right:
		if (inBeam->getYpos() > gridPosY + 0.5f*gridSize - BeamPulse::beamThickness && inBeam->getYpos() < gridPosY + 0.5f*gridSize + BeamPulse::beamThickness)
		{
			if (inBeam->getXpos()<(gridPosX + 0.5f*gridSize + 0.9f*BeamPulse::beamThickness) && inBeam->getXpos() > (gridPosX + 0.5f*gridSize) )
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
			MAINGAME->callGameField().CallGenerator(gridPosX+0.5f*gridSize, gridPosY + 0.5f*gridSize, mySource->getDirection(), mySource->GetColor(), thisTime);
		}
	}
	if (auto myColorAdder = dynamic_pointer_cast<ColorAdder>(myGridComponent))
	{
		bool& isRed		= myColorAdder->gotRed;
		bool& isGreen	= myColorAdder->gotGreen;
		bool& isBlue		= myColorAdder->gotBlue;
		if (isRed && !isGreen && !isBlue) 
		{//Red
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::Red, thisTime);
		}
		else if(!isRed && isGreen && !isBlue)
		{//Green
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::Green, thisTime);
		}
		else if(!isRed && !isGreen && isBlue)
		{//Blue
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::Blue, thisTime);
		}
		else if(!isRed && isGreen && isBlue)
		{//Cyan
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::Cyan, thisTime);
		}
		else if(isRed && !isGreen && isBlue)
		{//Magenta
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::Magenta, thisTime);
		}
		else if(isRed && isGreen && !isBlue)
		{//Yellow
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::Yellow, thisTime);
		}
		else if(isRed && isGreen && isBlue)
		{//White
			MAINGAME->callGameField().CallGenerator(gridPosX + 0.5f*gridSize, gridPosY + 0.5f*gridSize, myColorAdder->getDirection(), BeamColor::White, thisTime);
		}
		else 
		{//NoColor
		}
		isRed = isGreen = isBlue = false;
	}
}
