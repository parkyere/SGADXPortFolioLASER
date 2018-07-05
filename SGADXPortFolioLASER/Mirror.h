#pragma once
class Mirror : public Gate
{
public:
	Mirror();
	Mirror(float x, float y, Direction myDir);
	void Render();
	void beamComing(shared_ptr<BeamPulse> inBeam) override;
};

