#pragma once

#include "Core.h"

class WindowsHeader
{
public : 
	int WinClass(HINSTANCE hInstance);
	int WinCreate(HINSTANCE hInstance, const char* strWinName, int nWinWidth, int nWinHeight);
	int WinLoop(MSG msg, HINSTANCE hInstance);
};

