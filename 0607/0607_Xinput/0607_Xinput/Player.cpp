#include"Main.h"
#include"Render.h"
#include"XinputDevice.h"
#include<XInput.h>

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
	Getcontrolle();
	checkbuttomstate(XINPUT_GAMEPAD_A, buttomA);
	checkbuttomstate(XINPUT_GAMEPAD_B, buttomB);
	checkbuttomstate(XINPUT_GAMEPAD_X, buttomX);
	checkbuttomstate(XINPUT_GAMEPAD_Y, buttomY);
	checkbuttomstate(XINPUT_GAMEPAD_START, buttomstart);
	checkbuttomstate(XINPUT_GAMEPAD_LEFT_SHOULDER, buttomLB);
	checkbuttomstate(XINPUT_GAMEPAD_RIGHT_SHOULDER, buttomRB);

	if (GetLanalog(ANALOGRIGHT))
	{
		for (int i = 0; i < 4; i++)
		{
			g_Player[i].x += 5.f;
		}
	}

	if (GetLanalog(ANALOGLEFT))
	{
		for (int i = 0; i < 4; i++)
		{
			g_Player[i].x -= 5.f;
		}
	}
}