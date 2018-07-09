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

void MapEditor::SetState()
{
}

void MapEditor::SaveMap()
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
	ofn.lpstrTitle = L"Save file name";
	ofn.Flags = OFN_DONTADDTORECENT|OFN_FILEMUSTEXIST;
	GetSaveFileName(&ofn);
}
