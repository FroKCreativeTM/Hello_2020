#include "WindowsHeader.h"
#include "Graphics.h"

Graphics* sGraphics = nullptr;

int WindowsHeader::WinClass(HINSTANCE hInstance)
{

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize					= sizeof(WNDCLASSEX);
	wc.hbrBackground			= (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor					= LoadCursor(hInstance, IDC_ARROW);
	wc.hIcon					= LoadIcon(hInstance, IDI_APPLICATION);
	wc.hInstance				= hInstance;
	wc.lpfnWndProc				= WndProc;
	wc.lpszClassName			= "Hello 2020";
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error : Cannot register windows class", "Error", MB_OK);
		return 0;
	}

	return 0;
}

int WindowsHeader::WinCreate(HINSTANCE hInstance, const char* strWinName, int nWinWidth, int nWinHeight)
{
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	hWnd = CreateWindow(strWinName, strWinName, style
		, CW_USEDEFAULT, 0, nWinWidth, nWinHeight, GetDesktopWindow()
		, NULL, hInstance, NULL);

	POINT ptDiff;
	RECT rcClient, rcWindow;

	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWindow);
	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
	MoveWindow(hWnd, rcWindow.left, rcWindow.top, nWinWidth + ptDiff.x, nWinHeight + ptDiff.y, TRUE);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	// D3D를 비롯한 모든 것을 초기화한다.
	if (!sGraphics->InitEverything(hWnd, nWinWidth, nWinHeight))
		PostQuitMessage(1);

	if (!hWnd)
	{
		MessageBox(NULL, "Error : Cannot Create windows rectangle", "Error", MB_OK);
		return 0;
	}

	return 0;
}

int WindowsHeader::WinLoop(MSG msg, HINSTANCE hInstance)
{
	while (isRunning)
	{
		if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			sGraphics->PlayDemo();
		}
	}

	UnregisterClass(gAppName, hInstance);
	return 0;
}
