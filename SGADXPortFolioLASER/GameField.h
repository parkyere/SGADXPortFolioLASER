#pragma once

class GameField
{
	vector< vector<Grid> > myGrid;
	vector< shared_ptr<BeamPulse> > PulseList;
	vector< shared_ptr<BeamBeingAbsorbed> > DisappearingPulseList;
	vector< shared_ptr<BeamBeingGenerated> > AppearingPulseList;
	time_point<steady_clock> systemStart;
	
public:
	long long int tick;
	int fieldXSize;
	int fieldYSize;

	int numStatePerSec{4};
	long long int beforeNumState{ 0 };
	long long int currentNumState{ 0 };
	GameField();
	void InitGrid(int x, int y);
	void Render();
	void CheckClick(LONG x, LONG y);
	bool CheckBeamInGrid(vector<shared_ptr<BeamPulse> >::iterator  inBeam);
	void Update();
	void BroadcastMyTickMessage(time_point<steady_clock>& thisTime);
	void AddPulse(shared_ptr<BeamPulse> pulseToAdd);
	void CallGenerator(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime);
};