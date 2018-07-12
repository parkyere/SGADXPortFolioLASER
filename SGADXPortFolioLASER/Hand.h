#pragma once
class Hand 
{
	static shared_ptr<Hand> instance;
	Hand();
public:
	static shared_ptr<Hand> Get();
	shared_ptr<Component> ComponentInHand;
	Direction handDirection;
	float xPos;
	float yPos;
	float handScale{0.5f};
	bool isColorInHand{ false };
	inline bool isEmpty() 
	{
		return ComponentInHand == nullptr;
	}
	void Render();
	void UpdateInMapEditMode();
	void UpdateInPlayEditMode();
	void ClearHand();
};