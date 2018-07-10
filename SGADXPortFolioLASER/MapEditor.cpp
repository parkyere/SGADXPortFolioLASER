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
	element->SetAttribute("Level", MAINGAME->gameLevel);
	element->SetAttribute("Xsize", MAINGAME->callGameField().fieldXSize);
	element->SetAttribute("Ysize", MAINGAME->callGameField().fieldYSize);
	element->SetAttribute("InvenSize", MAINGAME->myInventory.componentNumber);
	node->InsertEndChild(element);
}



void MapEditor::LoadMap()
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
	ofn.Flags = OFN_DONTADDTORECENT|OFN_FILEMUSTEXIST;
	GetSaveFileName(&ofn);
}
