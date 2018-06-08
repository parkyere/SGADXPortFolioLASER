#pragma once

class Frames
{
private:
	static shared_ptr<Frames> instance;

	LPD3DXFONT font;

	bool isTimerStopped;

	INT64 ticksPerSecond;
	INT64 currentTime;
	INT64 lastTime;
	INT64 lastFPSUpdate;
	INT64 fpsUpdateInterval;

	UINT frameCount;
	float runningTime;
	float timeElapsed;
	float framePerSecond;

	Frames();


public:
	~Frames();
	static shared_ptr<Frames> Get();
	static void Delete();

	void Update();
	void Render();

	void Start();
	void Stop();

	bool IsTimerStopped() const { return isTimerStopped; }
	float FramePerSecond() const { return framePerSecond; }
	float RunningTime() const { return runningTime; }
	float TimeElapsed() const
	{
		return isTimerStopped ? 0.0f : timeElapsed;
	}
};