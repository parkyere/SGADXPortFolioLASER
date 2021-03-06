// SGADXPortFolioLASER.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SGADXPortFolioLASER.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND winHandle;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
/*
void musicPlay() 
{
	while(true)
		::PlaySound(L"OrdosBriefing.wav", NULL, SND_FILENAME | SND_LOOP);
}
*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SGADXPORTFOLIOLASER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SGADXPORTFOLIOLASER));

    MSG msg;

	Device::Get(winHandle);
	guarded_thread musicThread{ []() {
		while (true)
		::PlaySound(L"OrdosBriefing.wav", NULL, SND_FILENAME | SND_LOOP); 
	} };
	MAINGAME->Initialize(hInst,winHandle);
	// Main message loop:
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (MAINGAME->getState() != GameState::IntroMode) 
		{
			KEYBOARD->Update();
			MOUSE->Update();
			//DX 업데이트 및 렌더링
			MAINGAME->Update();

			Device::Get()->BeginScene(0xFFFFFFFF);
			Device::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			MAINGAME->Render(); //비긴신과 엔드신사이에서 렌더링
			Device::Get()->EndScene();
		}
		else 
		{
			KEYBOARD->Update();
			MOUSE->Update();
			INTROSCENE->Update();
			Device::Get()->BeginScene(0xFFFFFFFF);
			//Device::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			INTROSCENE->Render(); //비긴신과 엔드신사이에서 렌더링
			Device::Get()->EndScene();
		}

	}
	//Device::Delete();
	KEYBOARD->Delete();
	MOUSE->Delete();
	musicThread.detach();
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SGADXPORTFOLIOLASER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SGADXPORTFOLIOLASER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   winHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW xor WS_THICKFRAME xor WS_MAXIMIZEBOX,
      0, 0, winWidth, winHeight, nullptr, nullptr, hInstance, nullptr);
   //::SetMenu(winHandle, NULL);
   if (!winHandle)
   {
      return FALSE;
   }

   ShowWindow(winHandle, nCmdShow);
   UpdateWindow(winHandle);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (MAINGAME->getState() == GameState::IntroMode) 
	{
		switch (message) 
		{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			MAINGAME->setState(GameState::GamePlayEditMode);
			MAINGAME->PrepareGame();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	else 
	{
		switch (message)
		{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_FILE_SAVE:
			{
				MAPEDITOR->SaveMap();
			}
			break;
			case ID_FILE_LOAD:
			{
				MAPEDITOR->LoadMap();
			}
			break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			MAINGAME->CheckClick(LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_MOUSEMOVE:
			if (HAND->isEmpty()) break;
			else
			{
				HAND->xPos = (float)LOWORD(lParam);
				HAND->yPos = (float)HIWORD(lParam);
				HAND->ComponentInHand->SetPos(HAND->xPos + 0.8f*Grid::gridSize, HAND->yPos + 0.8f*Grid::gridSize);
				break;
			}

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
    
    return 0;
}