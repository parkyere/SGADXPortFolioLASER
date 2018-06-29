#pragma once
class Mirror : public Gate
{
public:
	Mirror();
	Mirror(float x, float y, Direction myDir);
	void Render();
};

