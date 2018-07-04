#pragma once

struct BeamPulse :public Component, public SingleColored
{
	float beamLength;
	float beamThickness{ 4.f };
	float beamSpeed;
	float initX;
	float initY;
public:
	time_point<steady_clock> firedTime;
	BeamPulse();
	BeamPulse(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime);
//	BeamPulse(const float x, const float y, const Direction myDir, const BeamColor myColor, const time_point<steady_clock>& inFiredTime);
//	BeamPulse(const BeamPulse& copyingOne);
	void Update(time_point<steady_clock>& thisTime);
	void Render() override;
	//BeamPulse& operator=(BeamPulse right) 
	//{
	//	return right;
	//return BeamPulse{ right.initX, right.initY, right.ComponentDirection ,right.SingleColor, right.firedTime };
	//}
};