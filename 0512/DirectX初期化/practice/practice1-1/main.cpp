//--------------------------------------------------
//	include
//--------------------------------------------------
#include<Windows.h>
#include<d3dx9.h>

//--------------------------------------------------
//	画面の大きさ
//--------------------------------------------------
#define WIDTH 1280
#define HEIGHT 720

//--------------------------------------------------
//	画面の名前
//--------------------------------------------------
#define TITLE TEXT("2Dゲーム")

//--------------------------------------------------
//	pragma comment
//	ライブラリをリンクする
//--------------------------------------------------
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//--------------------------------------------------
//	インターフェース
//--------------------------------------------------
LPDIRECT3D9 g_pDirect3D = NULL;
LPDIRECT3DDEVICE9 g_pDirect3DDevice = NULL;
D3DDISPLAYMODE g_D3DdisplayMode;

//--------------------------------------------------
//	ウインドウプロシージャ
//--------------------------------------------------
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wp, LPARAM _lp)
{
	switch (_msg)
	{
	case WM_KEYDOWN:
		switch (_wp)
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

	return DefWindowProc(_hWnd, _msg, _wp, _lp);
}

//--------------------------------------------------
//	解放処理
//--------------------------------------------------
void FreeDx()
{
	g_pDirect3DDevice->Release();
	g_pDirect3D->Release();
}

//--------------------------------------------------
//	エントリポイント
//	このプログラムの開始地点
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInsta, LPSTR _szStr, INT _iCmdShow)
{
	//--------------------------------------------------
	//	ウインドウの生成処理
	//--------------------------------------------------
	HWND hWnd;		//ウインドウハンドル
	WNDCLASS Wndclass;	//構造体タグ名

	//ウインドウの設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = _hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TITLE;

	if (!RegisterClass(&Wndclass)) return 0;	//ウィンドウ情報の登録

	//ウインドウの作成
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
		_hInstance,
		NULL
	);
	if (!hWnd)return 0;

	ShowWindow(hWnd, SW_SHOW);

	//---------------------------------------------------------------------
	//							DirectX初期化処理
	//---------------------------------------------------------------------
	//DirectXオブジェクトの生成
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//成功チェック
	if (g_pDirect3D == NULL)
	{
		//生成に失敗したら終了する
		return 0;
	}

	// DisplayModeの取得
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	//DirectXのデバイスを生成する際に必要な情報を用意
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferFormat = g_D3DdisplayMode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	// DirectXのデバイス生成
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pDirect3DDevice);

	//生成チェック
	if (g_pDirect3DDevice == NULL)
	{
		//生成に失敗したらDirectXオブジェクトを開放して終了する
		g_pDirect3D->Release();
		return 0;
	}

	//---------------------------------------------------------------------
	//							ゲームループ
	//---------------------------------------------------------------------
	
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;

	timeBeginPeriod(1);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)	//WM_QUIT(終了)メッセージが来るまで継続
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//PeekMessageでメッセージが来ていないか確認して来ていたら入る
		{
			TranslateMessage(&msg);	//メッセージをProcが読めるように翻訳する
			DispatchMessage(&msg);	//メッセージをProcに送信している
		}
		else
		{
			SyncNow = timeGetTime();	//今の時間を受け取っている

			if (SyncNow - SyncOld >= 1000 / 60)
			{
				//画面の消去
				g_pDirect3DDevice->Clear(
					0,
					NULL,
					D3DCLEAR_TARGET,
					D3DCOLOR_XRGB(0x00, 0x00, 0x00),
					1.0, 
					0);

				//描画の開始
				g_pDirect3DDevice->BeginScene();

				//ゲーム処理

				//描画の終了
				g_pDirect3DDevice->EndScene();

				//表示
				g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

				SyncOld = SyncNow;	//今の時間を前の時間変数に代入している
			}
		}
	}
	timeEndPeriod(1);

	//ゲームシーンの解放処理

	g_pDirect3DDevice->Release();	// DirectXのデバイスの解放
	g_pDirect3D->Release();			// DirectXオブジェクトの解放

	return 0;
}