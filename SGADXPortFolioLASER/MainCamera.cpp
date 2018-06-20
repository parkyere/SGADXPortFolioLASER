#include "stdafx.h"

MainCamera* MainCamera::instance{ nullptr };

MainCamera::MainCamera():
	free{ nullptr }, follow{ nullptr }
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	UpdateProjectionMatrix();
}

MainCamera::~MainCamera()
{
	Factory* freeFactory = new FreeFactory();
	freeFactory->DeleteCamera(free);
	SAFE_DELETE(freeFactory);

	Factory* followFactory = new FollowFactory();
	followFactory->DeleteCamera(follow);
	SAFE_DELETE(followFactory);
}

void MainCamera::SetMainCamera(shared_ptr<Camera> camera)
{
	assert(camera != NULL);
	main = camera;
}

MainCamera* MainCamera::Get()
{
	if (instance == nullptr)
		instance = new MainCamera;

	return instance;
}

void MainCamera::Delete()
{
	SAFE_DELETE(instance);
}

void MainCamera::UpdateProjectionMatrix()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f,
		(float)viewport.Width, (float)viewport.Height,
		0.0f, -1, 1);

	Device::SetProjection(&projection);
}

void MainCamera::Update()
{
	if (main != nullptr)
	{
		shared_ptr<FreeView> tempFree = dynamic_pointer_cast<FreeView>(main);
		if (tempFree != nullptr)
		{
			if (KEYBOARD->KeyPress(VK_CONTROL))
			{
				if (KEYBOARD->KeyPress(VK_UP))
					tempFree->MoveUp();
				if (KEYBOARD->KeyPress(VK_DOWN))
					tempFree->MoveDown();
				if (KEYBOARD->KeyPress(VK_LEFT))
					tempFree->MoveLeft();
				if (KEYBOARD->KeyPress(VK_RIGHT))
					tempFree->MoveRight();
			}
		}
		main->Update();
	}
}

void MainCamera::ChangeSpotPoint(ISpotPoint * spotPoint)
{
	assert(follow != nullptr);
	follow->ChangeSpotPoint(spotPoint);
}

void MainCamera::SetFreePosition(D3DXVECTOR2 position)
{
	shared_ptr<FreeView> free = dynamic_pointer_cast<FreeView>(main);
	if (free != nullptr)
	{
		free->SetPosition(position);
		free->UpdateViewMatrix();
	}
}

void MainCamera::SetFreeCamera()
{
	if (free == nullptr)
	{
		shared_ptr<Factory> factory = shared_ptr<FreeFactory>{ new FreeFactory };
		free = dynamic_pointer_cast<FreeView>( factory->CreateCamera() );
		(dynamic_pointer_cast<FreeFactory>(factory)).reset();
	}
	SetMainCamera(free);
}

void MainCamera::SetFollowCamera()
{
	if (follow == nullptr)
	{
		shared_ptr<Factory> factory = shared_ptr<FollowFactory>{ new FollowFactory };
		follow = dynamic_pointer_cast<FollowView>(factory->CreateCamera());
		(dynamic_pointer_cast<FollowFactory>(factory)).reset();
	}
	SetMainCamera(follow);
}
