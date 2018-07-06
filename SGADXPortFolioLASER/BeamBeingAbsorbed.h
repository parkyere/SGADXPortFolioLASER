#pragma once
class BeamBeingAbsorbed : public Component, public SingleColored 
{
private:
	time_point<steady_clock> firedTime;
	float beamLength;
	float beamSpeed;
	float thickness;
public:

	BeamBeingAbsorbed();
	BeamBeingAbsorbed(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime);
	BeamBeingAbsorbed(shared_ptr<BeamPulse> inBeam, time_point<steady_clock>& thisTime);
	bool UpdateNCheckForDelete(time_point<steady_clock>& thisTime);
	void Render() override;
};