#pragma once
class BeamSplitter : public Gate, public SingleColored
{
public:
	bool BeamDetectedBefore1Tick{ false };
	BeamSplitter();
	BeamSplitter(float x, float y, Direction myDir, BeamColor myColor);
	void Render();
	void beamComing(shared_ptr<BeamPulse> inBeam) override;
};