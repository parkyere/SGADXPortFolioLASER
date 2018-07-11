#include "stdafx.h"


shared_ptr<MapEditor> MapEditor::instance{ nullptr };

MapEditor::MapEditor()
{
}

shared_ptr<MapEditor> MapEditor::GetInstance()
{
	if (instance == nullptr) 
	{
		instance = shared_ptr<MapEditor>{ new MapEditor };
	}
	return instance;
}

void MapEditor::SetLevelNum(int levelNum)
{
	MAINGAME->callGameField().levelNum = levelNum;
}

string MapEditor::QuerySaveFileNameAndPath()
{
	wchar_t filename[MAX_PATH];
	OPENFILENAME sfn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&sfn, sizeof(sfn));
	sfn.lStructSize = sizeof(sfn);
	sfn.hwndOwner = MAINGAME->getHandle();  // If you have a window to center over, put its HANDLE here
	sfn.lpstrFilter = L"XML for Map file(*.xml)\0*.xml\0";
	sfn.lpstrFile = filename;
	sfn.nMaxFile = MAX_PATH;
	sfn.lpstrTitle = L"Save file name";
	sfn.Flags = OFN_DONTADDTORECENT;
	GetSaveFileName(&sfn);

	string filenameClassicString;
	filenameClassicString.assign(filename, filename + 260);
	return filenameClassicString;
}

void MapEditor::SetState()
{
}

void MapEditor::SaveMap()
{
	string fileName = QuerySaveFileNameAndPath();
	//Init 
	Xml::XMLDocument* document = new Xml::XMLDocument;
	Xml::XMLNode* node = document->NewElement("LaserOptiXMapFile");
	document->InsertFirstChild(node);
	Xml::XMLElement* element = nullptr;

	CreateHeader(element, document, node);

	int gridX = MAINGAME->callGameField().fieldXSize;
	int gridY = MAINGAME->callGameField().fieldYSize;

	for (int i=0; i<gridX ; i++) 
	{
		for (int j=0;j< gridY ; j++) 
		{
			if (MAINGAME->callGameField().myGrid[i][j].GetGridComponent() != nullptr)
			{
				ParseFieldToXmlFile(i, j, element, document, node);
			}
		}
	}
	int compNum = MAINGAME->myInventory.componentNumber;
	for (int i=0; i<compNum;i++) 
	{
		if (MAINGAME->myInventory.InvenGrid[i].GetGridComponent() != nullptr) 
		{
			ParseInvComponent(i, element, document, node);
		}
	}
	document->SaveFile(fileName.c_str());
	delete document;
}

void MapEditor::ParseFieldToXmlFile(int i, int j, Xml::XMLElement * element, Xml::XMLDocument * document, Xml::XMLNode * node)
{
	shared_ptr<Component> gridElem = MAINGAME->callGameField().myGrid[i][j].GetGridComponent();
	string ElemName = gridElem->getName();
	if (ElemName == "LaserSource")
	{
		SaveLaserSourceToXmlFile(gridElem, element, document, ElemName, i, j, node, "MapComponent");
	}
	else if (ElemName == "BeamSplitter")
	{
		SaveBeamSplitterToXmlFile(gridElem, element, document, ElemName, i, j, node, "MapComponent");
	}
	else if (ElemName == "ColorAdder")
	{
		SaveColorAdderToXmlFile(gridElem, element, document, ElemName, i, j, node, "MapComponent");
	}
	else if (ElemName == "ColorChanger")
	{
		SaveColorChangerToXmlFile(gridElem, element, document, ElemName, i, j, node, "MapComponent");
	}
	else if (ElemName == "Mirror")
	{
		SaveMirrorToXmlFile(gridElem, element, document, ElemName, i, j, node, "MapComponent");
	}
	else if (ElemName == "Goal")
	{
		SaveGoalToXmlFile(gridElem, element, document, ElemName, i, j, node, "MapComponent");
	}
	else if (ElemName == "Obstacle")
	{
		SaveObstacleToXmlFile(element, document, ElemName, i, j, node, "MapComponent");
	}
	else
	{
		throw new exception("Unrecognized component type!");
	}
}

void MapEditor::ParseInvComponent(int i, Xml::XMLElement * element, Xml::XMLDocument * document, Xml::XMLNode * node)
{
	shared_ptr<Component> gridElem = MAINGAME->myInventory.InvenGrid[i].GetGridComponent();
	string ElemName = gridElem->getName();
	if (ElemName == "LaserSource")
	{
		SaveLaserSourceToXmlFile(gridElem, element, document, ElemName, i,0, node, "InventoryComponent");
	}
	else if (ElemName == "BeamSplitter")
	{
		SaveBeamSplitterToXmlFile(gridElem, element, document, ElemName, i,0, node, "InventoryComponent");
	}
	else if (ElemName == "ColorAdder")
	{
		SaveColorAdderToXmlFile(gridElem, element, document, ElemName, i, 0, node, "InventoryComponent");
	}
	else if (ElemName == "ColorChanger")
	{
		SaveColorChangerToXmlFile(gridElem, element, document, ElemName, i, 0, node, "InventoryComponent");
	}
	else if (ElemName == "Mirror")
	{
		SaveMirrorToXmlFile(gridElem, element, document, ElemName, i, 0, node, "InventoryComponent");
	}
	else if (ElemName == "Goal")
	{
		SaveGoalToXmlFile(gridElem, element, document, ElemName, i, 0, node, "InventoryComponent");
	}
	else if (ElemName == "Obstacle")
	{
		SaveObstacleToXmlFile(element, document, ElemName, i, 0, node, "InventoryComponent");
	}
	else
	{
		throw new exception("Unrecognized component type!");
	}
}

void MapEditor::SaveObstacleToXmlFile(Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent)
{
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "False");
	element->SetAttribute("isDoubleColored", "False");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	node->InsertEndChild(element);
}

void MapEditor::SaveGoalToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent)
{
	shared_ptr<Goal> myGoal = dynamic_pointer_cast<Goal>(gridElem);
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "True");
	element->SetAttribute("isDoubleColored", "False");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	ParseSingleColorToXml(myGoal, element);
	ParseDirectionToXml(myGoal, element);

	node->InsertEndChild(element);
}

void MapEditor::ParseSingleColorToXml(std::shared_ptr<SingleColored> mySingleColored, Xml::XMLElement * element)
{
	switch (mySingleColored->GetColor())
	{
	case BeamColor::Red:
		element->SetAttribute("Color", "Red");
		break;
	case BeamColor::Green:
		element->SetAttribute("Color", "Green");
		break;
	case BeamColor::Blue:
		element->SetAttribute("Color", "Blue");
		break;
	case BeamColor::Cyan:
		element->SetAttribute("Color", "Cyan");
		break;
	case BeamColor::Magenta:
		element->SetAttribute("Color", "Magenta");
		break;
	case BeamColor::Yellow:
		element->SetAttribute("Color", "Yellow");
		break;
	case BeamColor::White:
		element->SetAttribute("Color", "White");
		break;
	default:
		throw new exception("Unrecognized color!");
	}
}

void MapEditor::SaveMirrorToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent)
{
	shared_ptr<Mirror> myMirror = dynamic_pointer_cast<Mirror>(gridElem);
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "False");
	element->SetAttribute("isDoubleColored", "False");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	ParseDirectionToXml(myMirror, element);

	node->InsertEndChild(element);
}

void MapEditor::SaveColorChangerToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent)
{
	shared_ptr<ColorChanger> myChanger = dynamic_pointer_cast<ColorChanger>(gridElem);
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "False");
	element->SetAttribute("isDoubleColored", "True");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	switch (myChanger->GetColorIn())
	{
	case BeamColor::Red:
		element->SetAttribute("ColorIn", "Red");
		break;
	case BeamColor::Green:
		element->SetAttribute("ColorIn", "Green");
		break;
	case BeamColor::Blue:
		element->SetAttribute("ColorIn", "Blue");
		break;
	case BeamColor::Cyan:
		element->SetAttribute("ColorIn", "Cyan");
		break;
	case BeamColor::Magenta:
		element->SetAttribute("ColorIn", "Magenta");
		break;
	case BeamColor::Yellow:
		element->SetAttribute("ColorIn", "Yellow");
		break;
	case BeamColor::White:
		element->SetAttribute("ColorIn", "White");
		break;
	default:
		throw new exception("Unrecognized color!");
	}
	switch (myChanger->GetColorOut())
	{
	case BeamColor::Red:
		element->SetAttribute("ColorOut", "Red");
		break;
	case BeamColor::Green:
		element->SetAttribute("ColorOut", "Green");
		break;
	case BeamColor::Blue:
		element->SetAttribute("ColorOut", "Blue");
		break;
	case BeamColor::Cyan:
		element->SetAttribute("ColorOut", "Cyan");
		break;
	case BeamColor::Magenta:
		element->SetAttribute("ColorOut", "Magenta");
		break;
	case BeamColor::Yellow:
		element->SetAttribute("ColorOut", "Yellow");
		break;
	case BeamColor::White:
		element->SetAttribute("ColorOut", "White");
		break;
	default:
		throw new exception("Unrecognized color!");
	}
	ParseDirectionToXml(myChanger, element);
	node->InsertEndChild(element);
}

void MapEditor::SaveColorAdderToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent)
{
	shared_ptr<ColorAdder> myAdder = dynamic_pointer_cast<ColorAdder>(gridElem);
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "False");
	element->SetAttribute("isDoubleColored", "False");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	ParseDirectionToXml(myAdder, element);

	node->InsertEndChild(element);
}

void MapEditor::SaveBeamSplitterToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement* element, Xml::XMLDocument* document, std::string &ElemName, int i, int j, Xml::XMLNode* node, string whatComponent)
{
	shared_ptr<BeamSplitter> mySplitter = dynamic_pointer_cast<BeamSplitter>(gridElem);
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "True");
	element->SetAttribute("isDoubleColored", "False");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	ParseSingleColorToXml(mySplitter, element);
	ParseDirectionToXml(mySplitter, element);

	node->InsertEndChild(element);
}

void MapEditor::SaveLaserSourceToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement* element, Xml::XMLDocument* document, std::string& ElemName, int i, int j, Xml::XMLNode* node, string whatComponent)
{
	shared_ptr<LaserSource> mySource = dynamic_pointer_cast<LaserSource>(gridElem);
	element = document->NewElement(whatComponent.c_str());
	element->SetAttribute("ComponentName", ElemName.c_str());
	element->SetAttribute("isSingleColored", "True");
	element->SetAttribute("isDoubleColored", "False");
	element->SetAttribute("PosX", i);
	element->SetAttribute("PosY", j);
	ParseSingleColorToXml(mySource, element);
	ParseDirectionToXml(mySource, element);

	node->InsertEndChild(element);
}

void MapEditor::ParseDirectionToXml(std::shared_ptr<Component> myComponent, Xml::XMLElement * element)
{
	switch (myComponent->getDirection())
	{
	case Direction::Up:
		element->SetAttribute("Direction", "Up");
		break;
	case Direction::Down:
		element->SetAttribute("Direction", "Down");
		break;
	case Direction::Right:
		element->SetAttribute("Direction", "Right");
		break;
	case Direction::Left:
		element->SetAttribute("Direction", "Left");
		break;
	default:
		throw new exception("Unrecognized direction!");
		break;
	}
}

void MapEditor::CreateHeader(Xml::XMLElement * &element, Xml::XMLDocument * document, Xml::XMLNode * node)
{
	element = document->NewElement("MapInfo");
	element->SetAttribute("Level", MAINGAME->callGameField().levelNum);
	element->SetAttribute("Xsize", MAINGAME->callGameField().fieldXSize);
	element->SetAttribute("Ysize", MAINGAME->callGameField().fieldYSize);
	element->SetAttribute("InvenSize", MAINGAME->myInventory.componentNumber);
	node->InsertEndChild(element);
}

string MapEditor::QueryLoadFileNameAndPath() 
{
	wchar_t filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = MAINGAME->getHandle();  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = L"XML for Map file(*.xml)\0*.xml\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Load file name";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	string FileNameClassicString;
	FileNameClassicString.assign(filename, filename + 260);
	return FileNameClassicString;
}

void MapEditor::LoadMap()
{
	string fileName = QueryLoadFileNameAndPath();
	Xml::XMLDocument* document = new Xml::XMLDocument;
	Xml::XMLError error;
	error = document->LoadFile(fileName.c_str());
	assert(error == Xml::XML_SUCCESS);

	Xml::XMLElement* root = document->FirstChildElement("LaserOptiXMapFile");
	Xml::XMLElement* mapInfo = root->FirstChildElement("MapInfo");
	int levNum = mapInfo->IntAttribute("Level");
	int xSize = mapInfo->IntAttribute("Xsize");
	int ySize = mapInfo->IntAttribute("Ysize");
	int invSize = mapInfo->IntAttribute("InvenSize");

	MAINGAME->callGameField().levelNum = levNum;
	MAINGAME->callGameField().InitGrid(xSize, ySize);
	MAINGAME->myInventory.componentNumber = invSize;
	MAINGAME->myInventory.InitInventory();
	Xml::XMLElement* mapComponent = nullptr;
	for (mapComponent = root->FirstChildElement("MapComponent"); mapComponent !=nullptr ; mapComponent = mapComponent->NextSiblingElement("MapComponent"))
	{
		string compName = mapComponent->Attribute("ComponentName");
		int xPos = mapComponent->IntAttribute("PosX");
		int yPos = mapComponent->IntAttribute("PosY");

		if (compName == "LaserSource") 
		{
			BeamColor srcColor = ReadColorFromText(mapComponent->Attribute("Color"));
			Direction srcDir = ReadDirectionFromText(mapComponent->Attribute("Direction"));
			shared_ptr<LaserSource> tempSrc = shared_ptr<LaserSource>{ new LaserSource(0.f,0.f,srcDir,srcColor) };
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempSrc));
			MAINGAME->callGameField().myGrid[xPos][yPos].GetGridComponent()->SetDir(srcDir);

		}
		else if (compName == "BeamSplitter") 
		{
			BeamColor splitterColor = ReadColorFromText(mapComponent->Attribute("Color"));
			Direction splitterDir = ReadDirectionFromText(mapComponent->Attribute("Direction"));
			shared_ptr<BeamSplitter> tempSplitter = shared_ptr<BeamSplitter>{ new BeamSplitter(0.f,0.f,splitterDir,splitterColor) };
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempSplitter));
			MAINGAME->callGameField().myGrid[xPos][yPos].GetGridComponent()->SetDir(splitterDir);
		}
		else if (compName == "ColorChanger")
		{
			BeamColor converterColorIn = ReadColorFromText(mapComponent->Attribute("ColorIn"));
			BeamColor converterColorOut = ReadColorFromText(mapComponent->Attribute("ColorOut"));
			Direction converterDir = ReadDirectionFromText(mapComponent->Attribute("Direction"));
			shared_ptr<ColorChanger> tempChanger = shared_ptr<ColorChanger>{ new ColorChanger(0.f,0.f,converterDir,converterColorIn,converterColorOut) };
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempChanger));
			MAINGAME->callGameField().myGrid[xPos][yPos].GetGridComponent()->SetDir(converterDir);
		}
		else if (compName == "Mirror")
		{
			Direction mirrorDir = ReadDirectionFromText(mapComponent->Attribute("Direction"));
			shared_ptr<Mirror> tempMirror = shared_ptr<Mirror>{ new Mirror(0.f,0.f,mirrorDir) };
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempMirror));
			MAINGAME->callGameField().myGrid[xPos][yPos].GetGridComponent()->SetDir(mirrorDir);
		}
		else if (compName == "ColorAdder")
		{
			Direction adderDir = ReadDirectionFromText(mapComponent->Attribute("Direction"));
			shared_ptr<ColorAdder> tempAdder = make_shared<ColorAdder>(0.f,0.f,adderDir);
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempAdder));
			MAINGAME->callGameField().myGrid[xPos][yPos].GetGridComponent()->SetDir(adderDir);
		}
		else if (compName == "Obstacle")
		{
			shared_ptr<Obstacle> tempObs = make_shared<Obstacle>(0.f, 0.f);
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempObs));
		}
		else if (compName == "Goal")
		{
			BeamColor goalColor = ReadColorFromText(mapComponent->Attribute("Color"));
			Direction goalDir = ReadDirectionFromText(mapComponent->Attribute("Direction"));
			shared_ptr<Goal> tempGoal = make_shared<Goal>(0.f, 0.f, goalDir,goalColor);
			MAINGAME->callGameField().myGrid[xPos][yPos].SetGridComponent(dynamic_pointer_cast<Component>(tempGoal));
			MAINGAME->callGameField().myGrid[xPos][yPos].GetGridComponent()->SetDir(goalDir);
		}
		else
		{
			throw new exception("Unknown MapComponent detected. Check parsing algorithm!");
		}
	}
	Xml::XMLElement* invComponent = nullptr;
	for (invComponent = root->FirstChildElement("InventoryComponent"); invComponent != nullptr ; invComponent=invComponent->NextSiblingElement("InventoryComponent") )
	{
		string compName = invComponent->Attribute("ComponentName");
		int xPos = invComponent->IntAttribute("PosX");
		//int yPos = invComponent->IntAttribute("PosY");

		if (compName == "LaserSource")
		{
			BeamColor srcColor = ReadColorFromText(invComponent->Attribute("Color"));
			Direction srcDir = ReadDirectionFromText(invComponent->Attribute("Direction"));
			shared_ptr<LaserSource> tempSrc = shared_ptr<LaserSource>{ new LaserSource(0.f,0.f,srcDir,srcColor) };
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempSrc));
			MAINGAME->myInventory.InvenGrid[xPos].GetGridComponent()->SetDir(srcDir);

		}
		else if (compName == "BeamSplitter")
		{
			BeamColor splitterColor = ReadColorFromText(invComponent->Attribute("Color"));
			Direction splitterDir = ReadDirectionFromText(invComponent->Attribute("Direction"));
			shared_ptr<BeamSplitter> tempSplitter = shared_ptr<BeamSplitter>{ new BeamSplitter(0.f,0.f,splitterDir,splitterColor) };
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempSplitter));
			MAINGAME->myInventory.InvenGrid[xPos].GetGridComponent()->SetDir(splitterDir);
		}
		else if (compName == "ColorChanger")
		{
			BeamColor converterColorIn = ReadColorFromText(invComponent->Attribute("ColorIn"));
			BeamColor converterColorOut = ReadColorFromText(invComponent->Attribute("ColorOut"));
			Direction converterDir = ReadDirectionFromText(invComponent->Attribute("Direction"));
			shared_ptr<ColorChanger> tempChanger = shared_ptr<ColorChanger>{ new ColorChanger(0.f,0.f,converterDir,converterColorIn,converterColorOut) };
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempChanger));
			MAINGAME->myInventory.InvenGrid[xPos].GetGridComponent()->SetDir(converterDir);
		}
		else if (compName == "Mirror")
		{
			Direction mirrorDir = ReadDirectionFromText(invComponent->Attribute("Direction"));
			shared_ptr<Mirror> tempMirror = shared_ptr<Mirror>{ new Mirror(0.f,0.f,mirrorDir) };
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempMirror));
			MAINGAME->myInventory.InvenGrid[xPos].GetGridComponent()->SetDir(mirrorDir);
		}
		else if (compName == "ColorAdder")
		{
			Direction adderDir = ReadDirectionFromText(invComponent->Attribute("Direction"));
			shared_ptr<ColorAdder> tempAdder = make_shared<ColorAdder>(0.f, 0.f, adderDir);
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempAdder));
			MAINGAME->myInventory.InvenGrid[xPos].GetGridComponent()->SetDir(adderDir);
		}
		else if (compName == "Obstacle")
		{
			shared_ptr<Obstacle> tempObs = make_shared<Obstacle>(0.f, 0.f);
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempObs));
		}
		else if (compName == "Goal")
		{
			BeamColor goalColor = ReadColorFromText(invComponent->Attribute("Color"));
			Direction goalDir = ReadDirectionFromText(invComponent->Attribute("Direction"));
			shared_ptr<Goal> tempGoal = make_shared<Goal>(0.f, 0.f, goalDir, goalColor);
			MAINGAME->myInventory.InvenGrid[xPos].SetGridComponent(dynamic_pointer_cast<Component>(tempGoal));
			MAINGAME->myInventory.InvenGrid[xPos].GetGridComponent()->SetDir(goalDir);
		}
		else
		{
			throw new exception("Unknown MapComponent detected. Check parsing algorithm!");
		}
	}
	//Stopped here
	delete document;
}
BeamColor MapEditor::ReadColorFromText(string colorText) 
{
	if (colorText == "Red")
	{
		return BeamColor::Red;
	}
	else if (colorText == "Green")
	{
		return BeamColor::Green;
	}
	else if (colorText == "Blue")
	{
		return BeamColor::Blue;
	}
	else if (colorText == "Cyan")
	{
		return BeamColor::Cyan;
	}
	else if (colorText == "Magenta")
	{
		return BeamColor::Magenta;
	}
	else if (colorText == "Yellow")
	{
		return BeamColor::Yellow;
	}
	else if (colorText == "White")
	{
		return BeamColor::White;
	}
	else 
	{
		throw new exception("Unknown color detected in XML savefile!");
		return BeamColor::White;
	}
}
Direction MapEditor::ReadDirectionFromText(string directionText) 
{
	if (directionText == "Up") 
	{
		return Direction::Up;
	}
	else if (directionText == "Down")
	{
		return Direction::Down;
	}
	else if (directionText == "Right")
	{
		return Direction::Right;
	}
	else if (directionText == "Left")
	{
		return Direction::Left;
	}
	else
	{
		throw new exception("Unknown direction detected in XML savefile!");
		return Direction::NoDirection;
	}
}
