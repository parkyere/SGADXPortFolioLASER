#pragma once

class Device
{
public:
	static shared_ptr<Device> Get(HWND hwnd);
	static shared_ptr<Device> Get() noexcept;
	static void Delete();

	static LPDIRECT3DDEVICE9 GetDevice()
	{
		return device;
	}

	static void SetWorld(D3DXMATRIX* world);
	static void SetView(D3DXMATRIX* view);
	static void SetProjection(D3DXMATRIX* projection);
	static void StartAlphaRender();
	static void EndAlphaRender();

	void BeginScene(DWORD clearColor);
	void EndScene();
	~Device();
private:
	Device(HWND hwnd);

	static shared_ptr<Device> instance;

	LPDIRECT3D9 d3d;
	static LPDIRECT3DDEVICE9 device;
};