#pragma once

class Device
{
public:
	static Device* Get(HWND hwnd = NULL);
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
private:
	Device(HWND hwnd);
	~Device();
	static Device* instance;


	LPDIRECT3D9 d3d;
	static LPDIRECT3DDEVICE9 device;

};