#pragma once

class Factory
{
protected:
	virtual shared_ptr<Camera> Create() = 0;
	virtual void Delete(shared_ptr<Camera> camera) = 0;

public:
	shared_ptr<Camera> CreateCamera()
	{
		return Create();
	}
	void DeleteCamera(shared_ptr<Camera> camera)
	{
		Delete(camera);
	}
};

class FreeFactory : public Factory
{
private:
	shared_ptr<Camera> Create()
	{
		return dynamic_pointer_cast<Camera>(shared_ptr<FreeView>{ new FreeView });
	}
	void Delete(shared_ptr<Camera> camera)
	{
		(dynamic_pointer_cast<FreeView>(camera)).reset();
	}
};

class FollowFactory : public Factory
{
private:
	shared_ptr<Camera> Create()
	{
		shared_ptr<FollowView> myTemp= shared_ptr<FollowView>{new FollowView};
		return dynamic_pointer_cast<Camera>(myTemp);
	}
	void Delete(shared_ptr<Camera> camera)
	{
		(dynamic_pointer_cast<FollowView>(camera)).reset();
	}
};