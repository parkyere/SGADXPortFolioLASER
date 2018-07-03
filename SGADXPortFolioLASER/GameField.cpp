#include "stdafx.h"

GameField::GameField()
{
	systemStart = steady_clock::now();
	tick = 1000LL / ((long long int)numStatePerSec);
}

void GameField::InitGrid(int x, int y)
{
	myGrid = vector< vector<Grid> >(x);
	for (int i=0; i<x; i++ )
	{
		for (int j=0; j<y; j++) 
		{
			myGrid[i].emplace_back(50.f+i*Grid::gridSize, 50.f+j*Grid::gridSize);
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
	for (BeamPulse& singlePulse : PulseList) 
	{
		singlePulse.Render();
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
	for (BeamPulse& singleBeam : PulseList) 
	{
		singleBeam.Update(timeNow);
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

void GameField::AddPulse(BeamPulse pulseToAdd)
{
	PulseList.emplace_back(pulseToAdd);
}
