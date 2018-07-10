#pragma once

class MapEditor 
{
	int levelNum{0};
	int inventorySize{12};

	static shared_ptr<MapEditor> instance;
	MapEditor();

public:
	static shared_ptr<MapEditor> GetInstance();
	void SetLevelNum(int levelNum);
	string QuerySaveFileNameAndPath();
	void SetState();
	void SaveMap();
	void ParseFieldToXmlFile(int i, int j, Xml::XMLElement * element, Xml::XMLDocument * document, Xml::XMLNode * node);
	void ParseInvComponent(int i, Xml::XMLElement * element, Xml::XMLDocument * document, Xml::XMLNode * node);
	void ParseSingleColorToXml(std::shared_ptr<SingleColored> myComponent, Xml::XMLElement * element);
	void ParseDirectionToXml(std::shared_ptr<Component> mySource, Xml::XMLElement * element);
	void SaveObstacleToXmlFile(Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void SaveGoalToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void SaveMirrorToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void SaveColorChangerToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void SaveColorAdderToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void SaveBeamSplitterToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement * element, Xml::XMLDocument * document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void SaveLaserSourceToXmlFile(std::shared_ptr<Component> &gridElem, Xml::XMLElement* element, Xml::XMLDocument* document, std::string &ElemName, int i, int j, Xml::XMLNode * node, string whatComponent);
	void CreateHeader(Xml::XMLElement * &element, Xml::XMLDocument * document, Xml::XMLNode * node);
	void LoadMap();
};