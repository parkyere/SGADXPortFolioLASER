#include "stdafx.h"

Inventory::Inventory()
{
	SetPosition(50.f, 800.f);
}

void Inventory::InitInventory()
{
	for (int i = 0; i< componentNumber; i++)
	{
		InvenGrid.emplace_back(posX + i * Grid::gridSize, posY);
	}
}

void Inventory::LoadInventory()
{
}

void Inventory::InitEditorInventory()
{
	colorAvailable = true;
	for(int i=0; i< componentNumber; i++)
	{
		InvenGrid.emplace_back(posX+ i * Grid::gridSize,posY );
	}
	InvenGrid[0].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<LaserSource> {new LaserSource}));
	InvenGrid[1].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<BeamSplitter>{new BeamSplitter}));
	InvenGrid[2].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<ColorChanger>{new ColorChanger}));
	InvenGrid[3].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<ColorAdder>  {new ColorAdder}));
	InvenGrid[4].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<Goal>        {new Goal}));
	InvenGrid[5].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<Mirror>      {new Mirror}));
	InvenGrid[6].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<Obstacle>    {new Obstacle}));

	for (int i = 0; i< colorNumber; i++)
	{
		ColorGrid.emplace_back(posX + i * Grid::gridSize, posY+ Grid::gridSize);
		ColorGrid[i].SetGridComponent(dynamic_pointer_cast<Component>(shared_ptr<ColorObject> {new ColorObject}));
	}
	dynamic_pointer_cast<ColorObject>(ColorGrid[0].GetGridComponent())->SetColor(BeamColor::Red);
	dynamic_pointer_cast<ColorObject>(ColorGrid[1].GetGridComponent())->SetColor(BeamColor::Green);
	dynamic_pointer_cast<ColorObject>(ColorGrid[2].GetGridComponent())->SetColor(BeamColor::Blue);
	dynamic_pointer_cast<ColorObject>(ColorGrid[3].GetGridComponent())->SetColor(BeamColor::Cyan);
	dynamic_pointer_cast<ColorObject>(ColorGrid[4].GetGridComponent())->SetColor(BeamColor::Magenta);
	dynamic_pointer_cast<ColorObject>(ColorGrid[5].GetGridComponent())->SetColor(BeamColor::Yellow);
	dynamic_pointer_cast<ColorObject>(ColorGrid[6].GetGridComponent())->SetColor(BeamColor::White);
}


void Inventory::SetPosition(float x, float y)
{
	posX = x;
	posY = y;
}

void Inventory::Render()
{
	for (Grid& itemBox : InvenGrid) 
	{
		itemBox.Render();
	}
	if (colorAvailable) 
	{
		for (Grid& colorBox : ColorGrid) 
		{
			colorBox.Render();
		}
	}
}

void Inventory::CheckClickinMapEditorMode(LONG x, LONG y)
{
	for (Grid& compElem : InvenGrid) 
	{
		if (compElem.CheckClick(x, y) == true) 
		{
			if (HAND->isColorInHand) 
			{
				ChangeColor(compElem, y, x);
			}
			else 
			{
				if (HAND->isEmpty()) 
				{
					//Pick Item
					HAND->xPos = (float)x;
					HAND->yPos = (float)y;
					HAND->handDirection = compElem.GetGridComponent()->getDirection();

					shared_ptr<LaserSource> invLaserSource = dynamic_pointer_cast<LaserSource>(compElem.GetGridComponent());
					if (invLaserSource != nullptr) 
					{
						HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<LaserSource>(*invLaserSource));
					}
					else 
					{
						shared_ptr<BeamSplitter> invBeamSplitter = dynamic_pointer_cast<BeamSplitter>(compElem.GetGridComponent());
						if (invBeamSplitter != nullptr) 
						{
							HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<BeamSplitter>(*invBeamSplitter));
						}
						else 
						{
							shared_ptr<ColorChanger> invColorChanger = dynamic_pointer_cast<ColorChanger>(compElem.GetGridComponent());
							if (invColorChanger != nullptr) 
							{
								HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<ColorChanger>(*invColorChanger));
							}
							else 
							{
								shared_ptr<ColorAdder> invColorAdder = dynamic_pointer_cast<ColorAdder>(compElem.GetGridComponent());
								if (invColorAdder != nullptr)
								{
									HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<ColorAdder>(*invColorAdder));
								}
								else 
								{
									shared_ptr<Goal> invGoal = dynamic_pointer_cast<Goal>(compElem.GetGridComponent());
									if (invGoal != nullptr) 
									{
										HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<Goal>(*invGoal));
									}
									else 
									{
										shared_ptr<Mirror> invMirror = dynamic_pointer_cast<Mirror>(compElem.GetGridComponent());
										if (invMirror != nullptr) 
										{
											HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<Mirror>(*invMirror));
										}
										else 
										{
											shared_ptr<Obstacle> invObstacle = dynamic_pointer_cast<Obstacle>(compElem.GetGridComponent());
											if (invObstacle != nullptr)
											{
												HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<Obstacle>(*invObstacle));
											}
											else 
											{
												throw new exception("Unknown element is clicked!");
											}
										}
									}
								}
							}
						}
					}
					HAND->ComponentInHand->Magnify(HAND->handScale);
					HAND->isColorInHand = false;
				}
				else if(HAND->isColorInHand == false && (compElem.GetGridComponent() == nullptr) )
				{
					Direction tempDirection = HAND->ComponentInHand->getDirection();
					compElem.SetGridComponent(HAND->ComponentInHand);
					HAND->ComponentInHand.reset();
					compElem.GetGridComponent()->Magnify(1.0f / (HAND->handScale));
					compElem.GetGridComponent()->SetDir(tempDirection);
					
				}
			}
		}
	}
	if (colorAvailable) 
	{
		for (Grid& colorElem : ColorGrid)
		{
			if (colorElem.CheckClick(x, y) == true)
			{
				if (HAND->isEmpty())
				{
					//Pick Color
					HAND->xPos = (float)x;
					HAND->yPos = (float)y;
					HAND->handDirection = Direction::NoDirection;
					BeamColor clickedColor = dynamic_pointer_cast<SingleColored>(colorElem.GetGridComponent())->GetColor();
					HAND->ComponentInHand = dynamic_pointer_cast<Component>(shared_ptr<ColorObject>{new ColorObject{(float)x,(float)y,clickedColor}});
					HAND->ComponentInHand->Magnify(HAND->handScale);
					HAND->isColorInHand = true;
				}
			}
		}
	}
}

void Inventory::CheckClickInInvMode(LONG x, LONG y)
{
	for (Grid& compElem : InvenGrid)
	{
		if (compElem.CheckClick(x, y) == true)
		{
			if (HAND->isEmpty())
			{
				//Pick Item
				HAND->xPos = (float)x;
				HAND->yPos = (float)y;
				HAND->handDirection = compElem.GetGridComponent()->getDirection();

				shared_ptr<LaserSource> invLaserSource = dynamic_pointer_cast<LaserSource>(compElem.GetGridComponent());
				if (invLaserSource != nullptr)
				{
					HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<LaserSource>(*invLaserSource));
					compElem.GetGridComponent().reset();
				}
				else
				{
					shared_ptr<BeamSplitter> invBeamSplitter = dynamic_pointer_cast<BeamSplitter>(compElem.GetGridComponent());
					if (invBeamSplitter != nullptr)
					{
						HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<BeamSplitter>(*invBeamSplitter));
						compElem.GetGridComponent().reset();
					}
					else
					{
						shared_ptr<ColorChanger> invColorChanger = dynamic_pointer_cast<ColorChanger>(compElem.GetGridComponent());
						if (invColorChanger != nullptr)
						{
							HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<ColorChanger>(*invColorChanger));
							compElem.GetGridComponent().reset();
						}
						else
						{
							shared_ptr<ColorAdder> invColorAdder = dynamic_pointer_cast<ColorAdder>(compElem.GetGridComponent());
							if (invColorAdder != nullptr)
							{
								HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<ColorAdder>(*invColorAdder));
								compElem.GetGridComponent().reset();
							}
							else
							{
								shared_ptr<Goal> invGoal = dynamic_pointer_cast<Goal>(compElem.GetGridComponent());
								if (invGoal != nullptr)
								{
									HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<Goal>(*invGoal));
									compElem.GetGridComponent().reset();
								}
								else
								{
									shared_ptr<Mirror> invMirror = dynamic_pointer_cast<Mirror>(compElem.GetGridComponent());
									if (invMirror != nullptr)
									{
										HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<Mirror>(*invMirror));
										compElem.GetGridComponent().reset();
									}
									else
									{
										shared_ptr<Obstacle> invObstacle = dynamic_pointer_cast<Obstacle>(compElem.GetGridComponent());
										if (invObstacle != nullptr)
										{
											HAND->ComponentInHand = dynamic_pointer_cast<Component>(make_shared<Obstacle>(*invObstacle));
											compElem.GetGridComponent().reset();
										}
										else
										{
											throw new exception("Unknown element is clicked!");
										}
									}
								}
							}
						}
					}
				}
				HAND->ComponentInHand->Magnify(HAND->handScale);
				HAND->isColorInHand = false;
			}
			else if (HAND->isColorInHand == false && (compElem.GetGridComponent() == nullptr))
			{
				Direction tempDirection = HAND->ComponentInHand->getDirection();
				compElem.SetGridComponent(HAND->ComponentInHand);
				HAND->ComponentInHand.reset();
				compElem.GetGridComponent()->Magnify(1.0f / (HAND->handScale));
				compElem.GetGridComponent()->SetDir(tempDirection);
			}
		}
	}
}

void Inventory::ChangeColor(Grid & compElem, const LONG &y, const LONG &x)
{
	shared_ptr<Component> componentInGrid = compElem.GetGridComponent();
	shared_ptr<SingleColored> mySingleColored = dynamic_pointer_cast<SingleColored>(componentInGrid);

	if (mySingleColored != nullptr)
	{
		mySingleColored->SetColor((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
	}
	else
	{
		shared_ptr<ColorChanger> myColorChanger = dynamic_pointer_cast<ColorChanger>(componentInGrid);
		if (myColorChanger != nullptr)
		{
			Direction inGridDirection = componentInGrid->getDirection();
			switch (inGridDirection)
			{
			case Direction::Up:
				if ((float)y >compElem.gridPosY + 0.5f*Grid::gridSize)
				{
					myColorChanger->SetColorIn((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				else
				{
					myColorChanger->SetColorOut((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				break;
			case Direction::Down:
				if ((float)y >compElem.gridPosY + 0.5f*Grid::gridSize)
				{
					myColorChanger->SetColorOut((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				else
				{
					myColorChanger->SetColorIn((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				break;
			case Direction::Left:
				if ((float)x >compElem.gridPosX + 0.5f*Grid::gridSize)
				{
					myColorChanger->SetColorIn((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				else
				{
					myColorChanger->SetColorOut((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				break;
			case Direction::Right:
				if ((float)x >compElem.gridPosX + 0.5f*Grid::gridSize)
				{
					myColorChanger->SetColorOut((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				else
				{
					myColorChanger->SetColorIn((dynamic_pointer_cast<SingleColored>(HAND->ComponentInHand))->GetColor());
				}
				break;
			default:
				throw new exception("Color changer must have a direction!");
				break;
			}
		}
	}
}
