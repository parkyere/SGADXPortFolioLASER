#include "stdafx.h"

GameField::GameField()
{
	systemStart = steady_clock::now();
	tick = 1000LL / ((long long int)numStatePerSec);
}

void GameField::InitGrid(int x, int y)
{
	fieldXSize = x;
	fieldYSize = y;
	myGrid = vector< vector<Grid> >(x);
	for (int i=0; i<x; i++ )
	{
		for (int j=0; j<y; j++) 
		{
			myGrid[i].emplace_back(Grid::gridSize +i*Grid::gridSize, Grid::gridSize +j*Grid::gridSize);
		}
	}
}

void GameField::Render()
{
	for (vector<Grid>& currentLine : myGrid) 
	{
		for (Grid& currentGrid : currentLine) 
		{
			currentGrid.Render();
		}
	}
	for (shared_ptr<BeamPulse>& singlePulse : PulseList) 
	{
		singlePulse->Render();
	}
}

void GameField::CheckClick(LONG x, LONG y)
{
	for (vector<Grid>& col: myGrid) 
	{
		for (Grid& elem : col) 
		{
			if (elem.CheckClick(x, y) == true) 
			{
				if (elem.GetGridComponent() == nullptr) 
				{
					if (HAND->isEmpty() == false)
					{
						if (HAND->isColorInHand == false)
						{
							Direction tempDirection = HAND->ComponentInHand->getDirection();
							elem.SetGridComponent(HAND->ComponentInHand);
							HAND->ComponentInHand.reset();
							elem.GetGridComponent()->Magnify(1.0f / (HAND->handScale));
							elem.GetGridComponent()->SetDir(tempDirection);
						}
					}
				}
			}
		}
	}
}

bool GameField::CheckBeamInGrid(vector<shared_ptr<BeamPulse> >::iterator inBeam)
{
	for (vector<Grid>& col : myGrid)
	{
		for (Grid& elem : col)
		{
			shared_ptr<Component> tempComponent = elem.GetGridComponent();
			if (tempComponent != nullptr)
			{
				shared_ptr<Gate> myGate = dynamic_pointer_cast<Gate>(tempComponent);
				if (myGate != nullptr)
				{
					if (elem.CheckBeam(*inBeam)!= Direction::NoDirection)
					{
						return true;
					}
				}
			}
		}
	}
}

void GameField::Update()
{
	auto timeNow = steady_clock::now();
	long long int timeElapsed = duration_cast<milliseconds>(timeNow-systemStart).count();
	currentNumState = timeElapsed / tick;
	if (beforeNumState != currentNumState) 
	{
		beforeNumState = currentNumState;
		BroadcastMyTickMessage(timeNow);
	}
	//for (shared_ptr<BeamPulse>& element : PulseList) 
	//{
	//	element->Update(timeNow);
	//}
	//
	//PulseList.erase(remove_if(PulseList.begin(), PulseList.end(), 
	//	[&](shared_ptr<BeamPulse>& elem) { return ( ((elem->getXpos() > Grid::gridSize*(1.5f + fieldXSize)) || (elem->getXpos() < 0.5f*Grid::gridSize)) || 
	//		((elem->getYpos() > Grid::gridSize*(1.5f + fieldXSize)) || (elem->getYpos() < 0.5f*Grid::gridSize) ) );} )
	//	, PulseList.end());
	//for (auto it = PulseList.begin() ; it != PulseList.end(); ) 
	//{
	//	float tempXPos = it->getXpos();
	//	float tempYPos = it->getYpos();
	//	if ( ((tempXPos > Grid::gridSize* (1.5f + fieldXSize)) || (tempXPos < 0.5f*Grid::gridSize))
	//		||   ( (tempYPos > Grid::gridSize* (1.5f+ fieldYSize) ) || ( tempYPos < 0.5f*Grid::gridSize) )) 
	//	{
	//		it= PulseList.erase(it);
	//	}
	//	else 
	//	{
	//		it++;
	//	}
	////	if ( ( (tempXPos > Grid::gridSize* (1.5f+ fieldXSize) ) || ( tempXPos < 0.5f*Grid::gridSize) )
	////	||   ( (tempYPos > Grid::gridSize* (1.5f+ fieldYSize) ) || ( tempYPos < 0.5f*Grid::gridSize) ) )
	////	{
	////		it = PulseList.erase(it);
	////	}
	////	else 
	////	{
	////		it++;
	////	}
	//}

	//Wall check
	for (auto it = PulseList.begin(); it != PulseList.end();)
	{
		(*it)->Update(timeNow);
		float tempX = (*it)->getXpos();
		float tempY = (*it)->getYpos();
		if (((tempX > Grid::gridSize* (1.5f + fieldXSize)) || (tempX  < 0.5f*Grid::gridSize))
			||   ( (tempY > Grid::gridSize* (1.5f+ fieldYSize) ) || ((tempY < 0.5f*Grid::gridSize) )))
		{
			it = PulseList.erase(it);
		}
		else if (CheckBeamInGrid(it)) 
		{
			it = PulseList.erase(it);
		}
		else 
		{
			it++;
		}
	}
}

void GameField::BroadcastMyTickMessage(time_point<steady_clock>& thisTime )
{
	for (vector<Grid>& currentLine : myGrid)
	{
		for (Grid& currentGrid : currentLine)
		{
			currentGrid.ReceiveMyTick(thisTime);;
		}
	}
}

void GameField::AddPulse(shared_ptr<BeamPulse> pulseToAdd)
{
	PulseList.emplace_back(pulseToAdd);
}
