#include "stdafx.h"

FreeView::FreeView()
{
	speed = 200;
}

void FreeView::Move(D3DXVECTOR2 translation)
{
	position += translation * TIMER->TimeElapsed();
	UpdateViewMatrix();
}

void FreeView::MoveUp()
{
	Move(D3DXVECTOR2(0, -1)*speed);
}

void FreeView::MoveDown()
{
	Move(D3DXVECTOR2(0, 1)*speed);
}

void FreeView::MoveLeft()
{
	Move(D3DXVECTOR2(-1, 0)*speed);
}

void FreeView::MoveRight()
{
	Move(D3DXVECTOR2(1, 0)*speed);
}
