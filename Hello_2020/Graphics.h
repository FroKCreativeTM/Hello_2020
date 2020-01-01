#pragma once

#include "Core.h"

class Graphics
{
public :
	// 초기화 관련
	bool InitEverything(HWND hWnd, int nWinWidth, int nWinHeight);
	bool InitD3D(HWND hWnd, int nWinWidth, int nWinHeight);
	bool LoadAssets();
	LPD3DXEFFECT LoadShader(const char* filename);
	LPDIRECT3DTEXTURE9 LoadTexture(const char* filename);
	LPD3DXMESH LoadModel(const char* filename);

	// 게임루프 관련
	void PlayDemo();
	void Update();

	// 렌더링 관련
	void RenderFrame();
	void RenderScene();
	void RenderInfo();

	// 뒷정리 관련
	void Cleanup();
};

