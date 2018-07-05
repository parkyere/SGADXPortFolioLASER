#pragma once
class ColorAdder : public Gate
{
public:
	ColorAdder();
	ColorAdder(float x, float y, Direction myDir);
	void Render() override;
	void beamComing(shared_ptr<BeamPulse> inBeam) override;
};