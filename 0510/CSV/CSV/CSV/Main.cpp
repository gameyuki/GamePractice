#include <windows.h>
#include <d3d9.h>

#include "GameScene.h"

#pragma comment(lib, "d3dx9.lib");

#define WINDOW_W 1280					// �E�B���h�E��
#define WINDOW_H 720					// �E�B���h�E����
#define WINDOW_TITLE TEXT("2D�Q�[��")	// �E�B���h�E��


LPDIRECT3D9			g_pDirect3D;		// DirectX�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9	g_pDirect3DDevice;	// DirectX�f�o�C�X�̃|�C���^
D3DDISPLAYMODE		g_D3DdisplayMode;

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY) 
	{ 
		PostQuitMessage(0); 
		return 0;
	}

	return DefWindowProc(hWnd, mes, wParam, lParam);
}


// �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//---------------------------------------------------------------------
	//							�E�B���h�E��������
	//---------------------------------------------------------------------

	MSG msg;			// ���b�Z�[�W���i�[����\����
	HWND hWnd;			// �E�B���h�E�n���h��
	WNDCLASS winc;

	//Windows���̐ݒ�
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WINDOW_TITLE;	//�N���X��
	
	//Window�̓o�^
	if (!RegisterClass(&winc)) return 0;
	//Window�̐���
	hWnd = CreateWindow(
		WINDOW_TITLE,						//�E�B���h�E�̃N���X��
		WINDOW_TITLE, 						//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̉������̈ʒux
		CW_USEDEFAULT,						// �E�B���h�E�̏c�����̈ʒuy
		WINDOW_W,							// Width�i���j
		WINDOW_H,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
		);
	if (!hWnd) return 0;

	
	ShowWindow(hWnd,SW_SHOW);

	//---------------------------------------------------------------------
	//							DirectX����������
	//---------------------------------------------------------------------

	// DirectX�I�u�W�F�N�g����
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	// �I�u�W�F�N�g�̐����ɐ����������`�F�b�N
	if (g_pDirect3D == NULL)
	{
		// �����Ɏ��s������I������
		return 0;
	}
	
	// DisplayMode�̎擾
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	// DirectX�̃f�o�C�X�𐶐�����ۂɕK�v�ȏ���p��
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	
	d3dpp.BackBufferFormat = g_D3DdisplayMode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;


	// DirectX�̃f�o�C�X����
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&d3dpp, 
		&g_pDirect3DDevice);

	// DirectX�̃f�o�C�X�𐶐��ł������`�F�b�N
	if (g_pDirect3DDevice == NULL)
	{
		// �����Ɏ��s������DirectX�I�u�W�F�N�g��������ďI������
		g_pDirect3D->Release();
		return 0;
	}



	
	//---------------------------------------------------------------------
	//							�Q�[�����[�v
	//---------------------------------------------------------------------

	GameSceneInit();	// �Q�[���V�[���̏������֐�

	DWORD SyncOld = timeGetTime();	//	�V�X�e�����Ԃ��擾
	DWORD SyncNow;

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
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60) //	1�b�Ԃ�60�񂱂̒��ɓ���
			{
				GameSceneControl();		// �Q�[���V�[���̐���֐�
				GameSceneDraw();		// �Q�[���V�[���̕`��֐�

				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	GameSceneFree();				// �Q�[���V�[���̉���֐�

	g_pDirect3DDevice->Release();	// DirectX�̃f�o�C�X�̉��
	g_pDirect3D->Release();			// DirectX�I�u�W�F�N�g�̉��

	return 0;
}
