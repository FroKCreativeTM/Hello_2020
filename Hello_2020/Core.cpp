#include "Core.h"

HWND hWnd;
bool isRunning = true;

HDC hdc;
extern const char* gAppName = "Hello 2020";

// D3D ����
LPDIRECT3D9             gpD3D		= NULL;				// D3D
LPDIRECT3DDEVICE9       gpD3DDevice = NULL;				// D3D ��ġ

// ��Ʈ
ID3DXFont* gpFont					= NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);