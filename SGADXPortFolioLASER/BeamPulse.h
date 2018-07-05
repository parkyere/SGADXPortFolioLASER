#pragma once

struct BeamPulse :public Component, public SingleColored
{
	float beamLength;

	float beamSpeed;
	float initX;
	float initY;
public:
	static float beamThickness;
	time_point<steady_clock> firedTime;
	BeamPulse();
	BeamPulse(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime);
	void Update(time_point<steady_clock>& thisTime);
	void Render() override;
};