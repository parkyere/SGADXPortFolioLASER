#include "stdafx.h"

shared_ptr<Device> Device::instance = nullptr;
LPDIRECT3DDEVICE9 Device::device = NULL;

shared_ptr<Device> Device::Get(HWND hwnd)
{
	if (instance == nullptr)
		instance = shared_ptr<Device>(new Device{ hwnd });
	return instance;
}

shared_ptr<Device> Device::Get() noexcept
{
	if (instance == nullptr) 
		throw new exception;
	return instance;
}

void Device::Delete()
{
	instance.reset();
}

void Device::SetWorld(D3DXMATRIX * world)
{
	device->SetTransform(D3DTS_WORLD, world);
}

void Device::SetView(D3DXMATRIX * view)
{
	device->SetTransform(D3DTS_VIEW, view);
}

void Device::SetProjection(D3DXMATRIX * projection)
{
	device->SetTransform(D3DTS_PROJECTION, projection);
}

void Device::StartAlphaRender()
{
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

void Device::EndAlphaRender()
{
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void Device::BeginScene(DWORD clearColor)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER , clearColor, 1.0f, 0);
	device->BeginScene();
}

void Device::EndScene() //후면버퍼
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

Device::Device(HWND hwnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	assert(d3d != NULL);

	D3DPRESENT_PARAMETERS param = { 0 };
	param.Windowed = TRUE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.AutoDepthStencilFormat = D3DFMT_D16;
	param.EnableAutoDepthStencil = TRUE;

	//후면 버퍼를 잠글수 있게 한다. 성능 떨어지는 원인이 된다.
	param.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//vSync(Vertical Synchronization) : 수직 동기
	//그래픽 카드의 영상프레임을 화면 재생률에 맞춰 전송하는 기능
	//수직동기를 키면 60프래임으로 고정

	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//vSync끔

	HRESULT hr;
	hr = d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT //주화면쓸거냐 보조화면쓸거냐
		, D3DDEVTYPE_HAL //하드
		, hwnd //핸들 (중요!!)핸들에서 렌더링된다
		, D3DCREATE_HARDWARE_VERTEXPROCESSING //정점처리 누가할거냐(하드웨어가한다)
		, &param //추가정보 설정
		, &device
	);
	
	assert(SUCCEEDED(hr));
}

Device::~Device()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
}
