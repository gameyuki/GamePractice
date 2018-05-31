#include"Main\Main.h"
#include"Lib\Render\Render.h"
#include"Lib\DirectInput\DirectInput.h"
#include<dinput.h>

CUSTOMVERTEX g_Enemy[]
{
	{ 300.f - 64.f, 500.f - 64.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
	{ 300.f + 64.f, 500.f - 64.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ 300.f + 64.f, 500.f + 64.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
	{ 300.f - 64.f, 500.f + 64.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
};

void EnemyDraw()
{
	g_pD3Device->SetTexture(0, g_pTexture[ENEMY_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, g_Enemy, sizeof(CUSTOMVERTEX));
}
