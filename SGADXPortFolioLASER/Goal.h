#pragma once

class Goal : public Gate, public SingleColored
{

public:
	Goal();
	Goal(float x, float y, Direction myDir, BeamColor myColor);
	void Render() override;
	void beamComing(shared_ptr<BeamPulse> inBeam) override;
};