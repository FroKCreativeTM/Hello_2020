#include "Graphics.h"

bool Graphics::InitEverything(HWND hWnd, int nWinWidth, int nWinHeight)
{
	// D3D를 초기화
	// 모델, 셰이더, 텍스쳐 등의 D3D 자원을 로딩한다.
	if (!InitD3D(hWnd, nWinWidth, nWinHeight))
	{
		return false;
	}

	// 모델, 쉐이더, 텍스처등을 로딩
	if (!LoadAssets())
	{
		return false;
	}

	// 폰트를 로딩
	// 디버그 정보를 위한 폰트이다.
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
	// D3D 객체
	gpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!gpD3D)
	{
		return false;
	}

	// D3D장치를 생성하는데 필요한 구조체를 채워넣는다.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth				= nWinWidth;				// ★
	d3dpp.BackBufferHeight				= nWinHeight;				// ★
	d3dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;			// ★
	d3dpp.BackBufferCount				= 1;
	d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality			= 0;

	// 백버퍼를 스왑할 때의 효과. 성능상 D#DSWAPEFFECT_DISCARD를 쓰는 것이
	// 좋은 편이다.
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;	// ★
	d3dpp.hDeviceWindow					= hWnd;
	d3dpp.Windowed						= TRUE;
	d3dpp.EnableAutoDepthStencil		= TRUE;						// ★
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D24X8;
	d3dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	d3dpp.FullScreen_RefreshRateInHz	= 0;

	// 모니터의 주사율과 백버퍼를 스왑하는 빈도 관계
	// 모니터가 수직 동기 될 때마다 백버퍼를 스왑해준다.
	// 게임에서는 성능상 모느터의 수직 동기를 기다리지 않고 
	// 곧바로 스왑해주는 경우가 많다. (D3DPRESENT IMMEDIATE)
	// 단 이럴 땐 전 프레임과 현재 프레임이 서로 찢겨 보이는 부작용이 있다.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	// ★


	// 위 정보를 가지고 D3D장치를 생성한다.
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
	// 아무 것도 적재하지 않는다.
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

	// .fx 파일은 버텍스 쉐이더와 픽셀 쉐이더를 모두 포함하고 있는 텍스트 파일이다.
	// 다음 함수를 통해서 로딩 및 컴파일을 한다.
	// 만약 HLSL에 문법적 오류가 있다면 함수 호출 도중 셰이더 컴파일 에러가 발생하며
	// 마지막 매개변수를 통해 메시지를 불러올 수 있다.
	D3DXCreateEffectFromFile(gpD3DDevice, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	// 쉐이더 로딩에 실패한 경우 output창에 쉐이더
	// 컴파일 에러를 출력한다.
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
		OutputDebugString("텍스처 로딩 실패: ");
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
		OutputDebugString("모델 로딩 실패: ");
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
	D3DCOLOR bgColour = D3DCOLOR_ARGB(255, r, g, b);	// 배경색상 - 파랑

	// 파란색으로 지운다
	gpD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), bgColour, 1.0f, 0);

	// 장면 그리기 시작
	gpD3DDevice->BeginScene();
	{
		RenderScene();				// 3D 물체등을 그린다.
		RenderInfo();				// 디버그 정보 등을 출력한다.
	}
	gpD3DDevice->EndScene();

	gpD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphics::RenderScene()
{
}

void Graphics::RenderInfo()
{
	// 텍스트 색상
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	// 텍스트를 출력할 위치
	RECT rct;
	rct.left = (nWinWidth / 2) - 75;
	rct.right = rct.left + (nWinWidth / 3);
	rct.top = (nWinHeight / 2) - 75;
	rct.bottom = rct.top + nWinHeight / 3;

	// 키 입력 정보를 출력
	gpFont->DrawText(NULL, "잘가 2019년\n\n어서와 2020년!\n\nESC: 프로그램 종료", -1, &rct, 0, fontColor);
}

void Graphics::Cleanup()
{
	// 폰트를 release 한다.
	if (gpFont)
	{
		gpFont->Release();
		gpFont = NULL;
	}

	// 위 LoadAsset으로 로딩한 순서대로
	// 모델을 release 한다.

	// 쉐이더를 release 한다.

	// 텍스처를 release 한다.

	// D3D를 release 한다.
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
