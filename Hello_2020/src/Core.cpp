#include "Core.h"

HWND hWnd;
bool isRunning = true;

HDC hdc;
extern const char* gAppName = "Hello 2020";

// D3D 관련
LPDIRECT3D9             gpD3D		= NULL;				// D3D
LPDIRECT3DDEVICE9       gpD3DDevice = NULL;				// D3D 장치

// 폰트
ID3DXFont* gpFont					= NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);