#pragma once

#include "Core.h"

class Graphics
{
public :
	// �ʱ�ȭ ����
	bool InitEverything(HWND hWnd, int nWinWidth, int nWinHeight);
	bool InitD3D(HWND hWnd, int nWinWidth, int nWinHeight);
	bool LoadAssets();
	LPD3DXEFFECT LoadShader(const char* filename);
	LPDIRECT3DTEXTURE9 LoadTexture(const char* filename);
	LPD3DXMESH LoadModel(const char* filename);

	// ���ӷ��� ����
	void PlayDemo();
	void Update();

	// ������ ����
	void RenderFrame();
	void RenderScene();
	void RenderInfo();

	// ������ ����
	void Cleanup();
};

