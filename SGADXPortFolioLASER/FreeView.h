#pragma once

class FreeView : public Camera
{
private:
	float speed;

	friend class FreeFactory;
	FreeView();

public:
	void Move(D3DXVECTOR2 translation);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void SetPosition(D3DXVECTOR2 position)
	{
		this->position = position;
	}
};