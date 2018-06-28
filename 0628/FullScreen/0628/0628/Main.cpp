#include<Windows.h>
#include<d3dx9.h>

#define TITLE TEXT ("Test")
#define WIDTH	1280
#define	HEIGHT	720

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

IDirect3DDevice9*	  g_pD3Device;
D3DPRESENT_PARAMETERS 	  g_D3dPresentParameters;
D3DDISPLAYMODE		  g_D3DdisplayMode;
IDirect3D9*		  g_pDirect3D;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wp)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsta, LPSTR szStr, INT iCmdShow)
{
	WNDCLASS Wndclass;
	HWND hWnd;
	MSG msg;

	//ウィンドウの設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TITLE;

	RegisterClass(&Wndclass);

	hWnd = CreateWindow(
		TITLE,
		TITLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)return 0;

	//DirectX オブジェクトの生成
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//ディスプレイモードの設定
	g_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &g_D3DdisplayMode);

	//ZeroMemory(&g_D3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	//g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	//g_D3dPresentParameters.BackBufferCount = 1;
	//g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//g_D3dPresentParameters.Windowed = TRUE;

	ZeroMemory(&g_D3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferWidth = 2256;
	g_D3dPresentParameters.BackBufferHeight = 1504;
	g_D3dPresentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3dPresentParameters.MultiSampleQuality = 0;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.hDeviceWindow = hWnd;
	g_D3dPresentParameters.Windowed = FALSE;
	g_D3dPresentParameters.EnableAutoDepthStencil = FALSE;
	g_D3dPresentParameters.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
	g_D3dPresentParameters.Flags = 0;
	g_D3dPresentParameters.FullScreen_RefreshRateInHz = 0;
	g_D3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//デバイスの作成
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, 
		&g_pD3Device);

	DWORD CurrentTime = timeGetTime();
	DWORD PrevTime = timeGetTime();

	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			CurrentTime = timeGetTime();

			if (PrevTime - CurrentTime >= 1000 / 60)
			{
				//画面の消去
				g_pD3Device->Clear(0, NULL,
					D3DCLEAR_TARGET,
					D3DCOLOR_XRGB(0x00, 0x00, 0x00),
					1.0, 0);

				g_pD3Device->BeginScene();

				g_pD3Device->EndScene();

				g_pD3Device->Present(NULL, NULL, NULL, NULL);

				CurrentTime = PrevTime;
			}
		}
	}
	timeEndPeriod(1);

	return (int)msg.wParam;
}