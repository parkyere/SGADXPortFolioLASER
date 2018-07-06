#pragma once
class BeamBeingGenerated : public Component, public SingleColored
{
private:
	time_point<steady_clock> firedTime;
	float beamLength;
	float beamSpeed;
	float thickness;
public:
	BeamBeingGenerated();
	BeamBeingGenerated(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime);
	BeamBeingGenerated(shared_ptr<BeamPulse> inBeam, time_point<steady_clock>& inTime);
	bool UpdateNCheckForDelete(time_point<steady_clock>& thisTime);
	void Render() override;
	shared_ptr<BeamPulse> ReleaseBeam(time_point<steady_clock>& thisTime);
};