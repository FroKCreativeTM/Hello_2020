#include "WindowsHeader.h"
#include "Graphics.h"

WindowsHeader* cWnd = nullptr;
MSG msg;

void ProcessInput(HWND hWnd, WPARAM keyPress)
{
	switch (keyPress)
	{
	// ESC 키가 눌리면 프로그램을 종료한다.
	case VK_ESCAPE:
		PostMessage(hWnd, WM_DESTROY, 0L, 0L);
		break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		ProcessInput(hWnd, wParam);
		break;

	case WM_CREATE : 
		break;

	case WM_CLOSE:
	case WM_DESTROY : 
		PostQuitMessage(0);
		isRunning = false;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmpshow)
{
	cWnd->WinClass(hInstance);
	cWnd->WinCreate(hInstance, gAppName, nWinWidth, nWinHeight);
	cWnd->WinLoop(msg, hInstance);
}