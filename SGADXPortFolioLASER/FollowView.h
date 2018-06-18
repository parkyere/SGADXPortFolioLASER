#pragma once

class ISpotPoint
{
public:
	virtual void GetSpotPoint(D3DXVECTOR2* position,
		D3DXVECTOR2* size) = 0;
};

class FollowView : public Camera
{
private:
	ISpotPoint * spotPoint;

	friend class FollowFactory;
	FollowView();
public:
	void Update();

	void ChangeSpotPoint(ISpotPoint* spotPoint)
	{
		this->spotPoint = spotPoint;
	}
};