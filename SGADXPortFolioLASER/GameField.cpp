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
	for (shared_ptr<BeamBeingAbsorbed>& singleBeamToDelete : DisappearingPulseList)
	{
		singleBeamToDelete->Render();
	}
	for (shared_ptr<BeamBeingGenerated>& singleBeamToMake : AppearingPulseList)
	{
		singleBeamToMake->Render();
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
					//Check for BeamAdder
					if (auto myAdder = dynamic_pointer_cast<ColorAdder>(myGate)) 
					{
						if (elem.CheckBeamFaster(*inBeam) != Direction::NoDirection)
						{
							shared_ptr<BeamPulse> tempBeamInfo = *inBeam;
							auto timeNow = steady_clock::now();
							DisappearingPulseList.push_back(shared_ptr<BeamBeingAbsorbed>(new BeamBeingAbsorbed{ tempBeamInfo, timeNow }));
							//DisappearingPulseList.push_back(shared_ptr<BeamBeingAbsorbed>
							//	(new BeamBeingAbsorbed{ elem.GetGridComponent()->getXpos(),elem.GetGridComponent()->getYpos(),tempBeamInfo->getDirection(),tempBeamInfo->GetColor(), timeNow }));
							myAdder->tempAnimEffect.push_back(shared_ptr<BeamBeingGenerated>{new BeamBeingGenerated{ tempBeamInfo, timeNow }});
							PulseList.erase(inBeam);
							myAdder->beamComing(tempBeamInfo);
							return true;
						}
					}
					else if (elem.CheckBeam(*inBeam)!= Direction::NoDirection)
					{
						shared_ptr<BeamPulse> tempBeamInfo = *inBeam;
						auto timeNow = steady_clock::now();
						DisappearingPulseList.push_back(shared_ptr<BeamBeingAbsorbed>(new BeamBeingAbsorbed{ tempBeamInfo, timeNow }));
						PulseList.erase(inBeam);
						myGate->beamComing(tempBeamInfo);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void GameField::Update()
{
	time_point<steady_clock> timeNow = steady_clock::now();
	long long int timeElapsed = duration_cast<milliseconds>(timeNow-systemStart).count();
	currentNumState = timeElapsed / tick;
	if (beforeNumState != currentNumState) 
	{
		beforeNumState = currentNumState;
		BroadcastMyTickMessage(timeNow);
	}

	//Wall check
	for (UINT i=0; i< PulseList.size(); ) 
	{
		shared_ptr<BeamPulse> it = PulseList.at(i);
		it->Update(timeNow);
		float tempX = it->getXpos();
		float tempY = it->getYpos();
		if (((tempX > Grid::gridSize* (1.5f + fieldXSize)) || (tempX  < 0.5f*Grid::gridSize))
					||   ( (tempY > Grid::gridSize* (1.5f+ fieldYSize) ) || ((tempY < 0.5f*Grid::gridSize) )))
		{
			DisappearingPulseList.push_back(shared_ptr<BeamBeingAbsorbed>(new BeamBeingAbsorbed{ it,timeNow }));
			PulseList.erase(PulseList.begin()+i);
		}
		else if (CheckBeamInGrid(PulseList.begin()+i))
		{
		}
		else 
		{
			i++;
		}
	}
	//Disappearing Pulse
	for (vector<shared_ptr<BeamBeingAbsorbed> >::iterator it = DisappearingPulseList.begin(); it!= DisappearingPulseList.end();) 
	{
		if ((*it)->UpdateNCheckForDelete(timeNow))
		{
			it = DisappearingPulseList.erase(it);
		}
		else 
		{
			it++;
		}
	}
	//Generating Pulse
	for (vector<shared_ptr<BeamBeingGenerated> >::iterator it = AppearingPulseList.begin(); it != AppearingPulseList.end();)
	{
		if ((*it)->UpdateNCheckForDelete(timeNow))
		{
			AddPulse((*it)->ReleaseBeam(timeNow));
			it = AppearingPulseList.erase(it);
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

void GameField::CallGenerator(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime)
{
	AppearingPulseList.push_back(shared_ptr<BeamBeingGenerated>{new BeamBeingGenerated{ x, y, myDir, myColor, inFiredTime }});
}

void GameField::clearBeamPulses()
{
	PulseList.clear();
	AppearingPulseList.clear();
	DisappearingPulseList.clear();
}
