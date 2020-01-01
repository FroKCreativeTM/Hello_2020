#include "Graphics.h"

bool Graphics::InitEverything(HWND hWnd, int nWinWidth, int nWinHeight)
{
	// D3D�� �ʱ�ȭ
	// ��, ���̴�, �ؽ��� ���� D3D �ڿ��� �ε��Ѵ�.
	if (!InitD3D(hWnd, nWinWidth, nWinHeight))
	{
		return false;
	}

	// ��, ���̴�, �ؽ�ó���� �ε�
	if (!LoadAssets())
	{
		return false;
	}

	// ��Ʈ�� �ε�
	// ����� ������ ���� ��Ʈ�̴�.
	if (FAILED(D3DXCreateFont(gpD3DDevice, 20, 10, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, (DEFAULT_PITCH | FF_DONTCARE),
		"Arial", &gpFont)))
	{
		return false;
	}

	return true;
}

bool Graphics::InitD3D(HWND hWnd, int nWinWidth, int nWinHeight)
{
	// D3D ��ü
	gpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!gpD3D)
	{
		return false;
	}

	// D3D��ġ�� �����ϴµ� �ʿ��� ����ü�� ä���ִ´�.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth				= nWinWidth;				// ��
	d3dpp.BackBufferHeight				= nWinHeight;				// ��
	d3dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;			// ��
	d3dpp.BackBufferCount				= 1;
	d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality			= 0;

	// ����۸� ������ ���� ȿ��. ���ɻ� D#DSWAPEFFECT_DISCARD�� ���� ����
	// ���� ���̴�.
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;	// ��
	d3dpp.hDeviceWindow					= hWnd;
	d3dpp.Windowed						= TRUE;
	d3dpp.EnableAutoDepthStencil		= TRUE;						// ��
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D24X8;
	d3dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	d3dpp.FullScreen_RefreshRateInHz	= 0;

	// ������� �ֻ����� ����۸� �����ϴ� �� ����
	// ����Ͱ� ���� ���� �� ������ ����۸� �������ش�.
	// ���ӿ����� ���ɻ� ������� ���� ���⸦ ��ٸ��� �ʰ� 
	// ��ٷ� �������ִ� ��찡 ����. (D3DPRESENT IMMEDIATE)
	// �� �̷� �� �� �����Ӱ� ���� �������� ���� ���� ���̴� ���ۿ��� �ִ�.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	// ��


	// �� ������ ������ D3D��ġ�� �����Ѵ�.
	if (FAILED(gpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &gpD3DDevice)))
	{
		return false;
	}

	return true;
}

bool Graphics::LoadAssets()
{
	// �ƹ� �͵� �������� �ʴ´�.
	return true;
}

LPD3DXEFFECT Graphics::LoadShader(const char* filename)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	// .fx ������ ���ؽ� ���̴��� �ȼ� ���̴��� ��� �����ϰ� �ִ� �ؽ�Ʈ �����̴�.
	// ���� �Լ��� ���ؼ� �ε� �� �������� �Ѵ�.
	// ���� HLSL�� ������ ������ �ִٸ� �Լ� ȣ�� ���� ���̴� ������ ������ �߻��ϸ�
	// ������ �Ű������� ���� �޽����� �ҷ��� �� �ִ�.
	D3DXCreateEffectFromFile(gpD3DDevice, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// ���̴� �ε��� ������ ��� outputâ�� ���̴�
	// ������ ������ ����Ѵ�.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void* ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete[] str;
		}
	}

	return ret;
}

LPDIRECT3DTEXTURE9 Graphics::LoadTexture(const char* filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if (FAILED(D3DXCreateTextureFromFile(gpD3DDevice, filename, &ret)))
	{
		OutputDebugString("�ؽ�ó �ε� ����: ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	}

	return ret;
}

LPD3DXMESH Graphics::LoadModel(const char* filename)
{
	LPD3DXMESH ret = NULL;
	if (FAILED(D3DXLoadMeshFromX(filename, D3DXMESH_SYSTEMMEM, gpD3DDevice, NULL, NULL, NULL, NULL, &ret)))
	{
		OutputDebugString("�� �ε� ����: ");
		OutputDebugString(filename);
		OutputDebugString("\n");
	};

	return ret;
}

void Graphics::PlayDemo()
{
	Update();
	RenderFrame();
}

void Graphics::Update()
{
}

void Graphics::RenderFrame()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	long r = sin(tm.tm_sec) * 255;
	long g = cos(tm.tm_sec) * 255;
	long b = 0;
	D3DCOLOR bgColour = D3DCOLOR_ARGB(255, r, g, b);	// ������ - �Ķ�

	// �Ķ������� �����
	gpD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), bgColour, 1.0f, 0);

	// ��� �׸��� ����
	gpD3DDevice->BeginScene();
	{
		RenderScene();				// 3D ��ü���� �׸���.
		RenderInfo();				// ����� ���� ���� ����Ѵ�.
	}
	gpD3DDevice->EndScene();

	gpD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphics::RenderScene()
{
}

void Graphics::RenderInfo()
{
	// �ؽ�Ʈ ����
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	// �ؽ�Ʈ�� ����� ��ġ
	RECT rct;
	rct.left = (nWinWidth / 2) - 75;
	rct.right = rct.left + (nWinWidth / 3);
	rct.top = (nWinHeight / 2) - 75;
	rct.bottom = rct.top + nWinHeight / 3;

	// Ű �Է� ������ ���
	gpFont->DrawText(NULL, "�߰� 2019��\n\n��� 2020��!\n\nESC: ���α׷� ����", -1, &rct, 0, fontColor);
}

void Graphics::Cleanup()
{
	// ��Ʈ�� release �Ѵ�.
	if (gpFont)
	{
		gpFont->Release();
		gpFont = NULL;
	}

	// �� LoadAsset���� �ε��� �������
	// ���� release �Ѵ�.

	// ���̴��� release �Ѵ�.

	// �ؽ�ó�� release �Ѵ�.

	// D3D�� release �Ѵ�.
	if (gpD3DDevice)
	{
		gpD3DDevice->Release();
		gpD3DDevice = NULL;
	}

	if (gpD3D)
	{
		gpD3D->Release();
		gpD3D = NULL;
	}
}
