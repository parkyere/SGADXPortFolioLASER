#include "stdafx.h"

shared_ptr<Hand> Hand::instance{ nullptr };

Hand::Hand() : handDirection{ Direction::NoDirection }, xPos{ 0.f }, yPos{ 0.f }, ComponentInHand{nullptr}
{
}

shared_ptr<Hand> Hand::Get()
{
	if (instance== nullptr) 
	{
		instance = shared_ptr<Hand>{ new Hand };
	}
	return instance;
}

void Hand::Render()
{
	if (isEmpty())
	{
		return;
	}
	else 
	{
		ComponentInHand->Render();
	}
}

void Hand::UpdateInEditMode()
{
	if (isEmpty()) 
	{
		return;
	}
	else 
	{
		if (KEYBOARD->KeyPress(VK_ESCAPE)) 
		{
			ClearHand();
		}
		if (KEYBOARD->KeyDown(VK_RETURN))
		{
			ComponentInHand->RightRotateDirection();
			handDirection = ComponentInHand->getDirection();
		}
	}
}

void Hand::ClearHand()
{
	ComponentInHand.reset();
	handDirection = Direction::NoDirection;
	isColorInHand = false;
}
