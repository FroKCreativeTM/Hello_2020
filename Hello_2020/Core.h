#pragma once

#pragma warning(disable:4996)

/*
Windows Header
*/
#include <Windows.h>

/*
C/C++ Runtime Header
*/
#include <iostream>
#include <cmath>
#include <ctime>

/*
DirectX Header
*/
#include <d3d9.h>
#include <d3dx9.h>

extern HWND hWnd;
extern bool isRunning;

extern HDC hdc; 
extern const char* gAppName;

const int nWinWidth = 1024;
const int nWinHeight = 768;

extern LPDIRECT3D9             gpD3D;
extern LPDIRECT3DDEVICE9       gpD3DDevice;
extern ID3DXFont* gpFont;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);