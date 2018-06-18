#pragma once

class Camera
{
protected:
	D3DXVECTOR2 position;
	D3DXMATRIX view;

	Camera();
	~Camera();
public:
	virtual void Update();
	void UpdateViewMatrix();
};