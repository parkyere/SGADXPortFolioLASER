#include "stdafx.h"

Camera::Camera()
{
	position = { 0, 0 };
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{
}

void Camera::Update()
{

}

void Camera::UpdateViewMatrix()
{
	D3DXMatrixTranslation(&view, position.x, position.y, 0.0f);
	Device::SetView(&view);
}