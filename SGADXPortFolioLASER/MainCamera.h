#pragma once

class MainCamera
{
private:
	shared_ptr<Camera> main;
	shared_ptr<FreeView> free;
	shared_ptr<FollowView> follow;

	D3DXMATRIX projection;
	static MainCamera* instance;

	MainCamera();
	~MainCamera();
	friend class shared_ptr<MainCamera>;
	void SetMainCamera(shared_ptr<Camera> camera);
public:
	static MainCamera* Get();
	static void Delete();

	void UpdateProjectionMatrix();

	void Update();

	void ChangeSpotPoint(ISpotPoint* spotPoint);
	void SetFreePosition(D3DXVECTOR2 position);

	void SetFreeCamera();
	void SetFollowCamera();

	shared_ptr<Camera> GetMain()
	{
		return main;
	}
};