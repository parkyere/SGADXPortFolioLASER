#pragma once

class GameField
{
	vector< vector<Grid> > myGrid;
	vector< BeamPulse > PulseList;
	time_point<steady_clock> systemStart;
	long long int tick;
public:
	int numStatePerSec{4};
	long long int beforeNumState{ 0 };
	long long int currentNumState{ 0 };
	GameField();
	void InitGrid(int x, int y);
	void Render();
	void CheckClick(LONG x, LONG y);
	void Update();
	void BroadcastMyTickMessage(time_point<steady_clock>& thisTime);
	void AddPulse(BeamPulse pulseToAdd);
};