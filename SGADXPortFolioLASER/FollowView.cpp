#include "stdafx.h"

FollowView::FollowView()
{
	spotPoint = NULL;
}

void FollowView::Update()
{
	if (spotPoint == NULL)
		return;

	D3DXVECTOR2 location, size;
	spotPoint->GetSpotPoint(&location, &size);

	D3DXVECTOR2 temp = location;
	temp.x -= (float)winWidth * 0.5f;
	temp.y -= (float)winHeight * 0.5f;

	temp.x += size.x * 0.5f;
	temp.y += size.y * 0.5f;

	position = -temp;
	UpdateViewMatrix();
}
