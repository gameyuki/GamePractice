#include"Main\Main.h"
#include"Lib\Render\Render.h"
#include"Lib\DirectInput\DirectInput.h"
#include<dinput.h>

CUSTOMVERTEX g_Player[]
{
	{ 100.f - 64.f, 500.f - 64.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 100.f + 64.f, 500.f - 64.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 100.f + 64.f, 500.f + 64.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 100.f - 64.f, 500.f + 64.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};

void PlayerDraw()
{
	g_pD3Device->SetTexture(0, g_pTexture[PLAYER_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, g_Player, sizeof(CUSTOMVERTEX));

}

void PlayerControl()
{
	KEYSTATE key[256];
	KeyCheckDinput(&key[DIK_SPACE], DIK_SPACE);
	KeyCheckDinput(&key[DIK_RIGHT], DIK_RIGHT);
	KeyCheckDinput(&key[DIK_LEFT], DIK_LEFT);

	if (key[DIK_RIGHT] == ON)
	{
		g_Player[0].x += 5.f;
		g_Player[1].x += 5.f;
		g_Player[2].x += 5.f;
		g_Player[3].x += 5.f;
	}

	if (key[DIK_LEFT] == ON)
	{
		g_Player[0].x -= 5.f;
		g_Player[1].x -= 5.f;
		g_Player[2].x -= 5.f;
		g_Player[3].x -= 5.f;
	}

}