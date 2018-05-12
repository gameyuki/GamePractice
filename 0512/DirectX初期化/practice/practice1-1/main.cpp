//--------------------------------------------------
//	include
//--------------------------------------------------
#include<Windows.h>
#include<d3dx9.h>

//--------------------------------------------------
//	��ʂ̑傫��
//--------------------------------------------------
#define WIDTH 1280
#define HEIGHT 720

//--------------------------------------------------
//	��ʂ̖��O
//--------------------------------------------------
#define TITLE TEXT("2D�Q�[��")

//--------------------------------------------------
//	pragma comment
//	���C�u�����������N����
//--------------------------------------------------
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

//--------------------------------------------------
//	�C���^�[�t�F�[�X
//--------------------------------------------------
LPDIRECT3D9 g_pDirect3D = NULL;
LPDIRECT3DDEVICE9 g_pDirect3DDevice = NULL;
D3DDISPLAYMODE g_D3DdisplayMode;

//--------------------------------------------------
//	�E�C���h�E�v���V�[�W��
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
//	�������
//--------------------------------------------------
void FreeDx()
{
	g_pDirect3DDevice->Release();
	g_pDirect3D->Release();
}

//--------------------------------------------------
//	�G���g���|�C���g
//	���̃v���O�����̊J�n�n�_
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInsta, LPSTR _szStr, INT _iCmdShow)
{
	//--------------------------------------------------
	//	�E�C���h�E�̐�������
	//--------------------------------------------------
	HWND hWnd;		//�E�C���h�E�n���h��
	WNDCLASS Wndclass;	//�\���̃^�O��

	//�E�C���h�E�̐ݒ�
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

	if (!RegisterClass(&Wndclass)) return 0;	//�E�B���h�E���̓o�^

	//�E�C���h�E�̍쐬
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
	//							DirectX����������
	//---------------------------------------------------------------------
	//DirectX�I�u�W�F�N�g�̐���
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	//�����`�F�b�N
	if (g_pDirect3D == NULL)
	{
		//�����Ɏ��s������I������
		return 0;
	}

	// DisplayMode�̎擾
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	//DirectX�̃f�o�C�X�𐶐�����ۂɕK�v�ȏ���p��
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

	//�����`�F�b�N
	if (g_pDirect3DDevice == NULL)
	{
		//�����Ɏ��s������DirectX�I�u�W�F�N�g���J�����ďI������
		g_pDirect3D->Release();
		return 0;
	}

	//---------------------------------------------------------------------
	//							�Q�[�����[�v
	//---------------------------------------------------------------------
	
	DWORD SyncOld = timeGetTime();	//	�V�X�e�����Ԃ��擾
	DWORD SyncNow;

	timeBeginPeriod(1);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)	//WM_QUIT(�I��)���b�Z�[�W������܂Ōp��
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//PeekMessage�Ń��b�Z�[�W�����Ă��Ȃ����m�F���ė��Ă��������
		{
			TranslateMessage(&msg);	//���b�Z�[�W��Proc���ǂ߂�悤�ɖ|�󂷂�
			DispatchMessage(&msg);	//���b�Z�[�W��Proc�ɑ��M���Ă���
		}
		else
		{
			SyncNow = timeGetTime();	//���̎��Ԃ��󂯎���Ă���

			if (SyncNow - SyncOld >= 1000 / 60)
			{
				//��ʂ̏���
				g_pDirect3DDevice->Clear(
					0,
					NULL,
					D3DCLEAR_TARGET,
					D3DCOLOR_XRGB(0x00, 0x00, 0x00),
					1.0, 
					0);

				//�`��̊J�n
				g_pDirect3DDevice->BeginScene();

				//�Q�[������

				//�`��̏I��
				g_pDirect3DDevice->EndScene();

				//�\��
				g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);

				SyncOld = SyncNow;	//���̎��Ԃ�O�̎��ԕϐ��ɑ�����Ă���
			}
		}
	}
	timeEndPeriod(1);

	//�Q�[���V�[���̉������

	g_pDirect3DDevice->Release();	// DirectX�̃f�o�C�X�̉��
	g_pDirect3D->Release();			// DirectX�I�u�W�F�N�g�̉��

	return 0;
}