#include<Windows.h>
#include<d3dx9.h>
#include"BackGround.h"
#include"Main\Main.h"

#define WIDTH	1280
#define	HEIGHT	720

void BackDraw()
{
	// BackGround��BackGround2�͈ꕔ�̒l���Ⴄ�����ŏ����͓����Ȃ̂�
	// �֐������ɒ��킵�Ăق���
	/*�w�i*/
	CUSTOMVERTEX BackGround[]
	{
		{ 0.0f, 0.0f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ WIDTH, 0.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ WIDTH, HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.0f, HEIGHT, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	g_pD3Device->SetTexture(0, g_pTexture[BACKGROUND_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, BackGround, sizeof(CUSTOMVERTEX));

}