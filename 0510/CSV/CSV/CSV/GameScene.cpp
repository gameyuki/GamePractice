#include <d3d9.h>
#include <d3dx9.h>
#include "GameScene.h"
#include <stdio.h>


//	ゲームシーンの画像情報を入れておく配列
LPDIRECT3DTEXTURE9			g_pGameTexture[GAMESCENE_MAX];	
KEYSTATE Key[KEYMAX];

int PreKey[KEYMAX] = { 0 };

int KeyState[4] = { 0 };

PLAYERSTATE g_playerState = { 520.f, 480.f, 64.f, 64.f, false, false, false };

int map[MAP_HEIGHT][MAP_WIDTH];

// ゲームシーンの制御関数
void GameSceneControl()
{
	KeyCheck(VK_LEFT, LEFT);
	KeyCheck(VK_RIGHT, RIGHT);
	KeyCheck(VK_UP, UP);
	KeyCheck(VK_DOWN, DOWN);
	KeyCheck('Z', FIRE);

	if (Key[LEFT] == ON)
	{
		g_playerState.IsLeft = true;
		g_playerState.PosX -= 3.f;
	}
	if (Key[RIGHT] == ON)
	{
		g_playerState.IsLeft = false;
		g_playerState.PosX += 3.f;
	}
}

// ゲームシーンの描画関数
void GameSceneDraw()
{
	// バックグラウンドの頂点情報を作成する
	CUSTOMVERTEX backGround[4]
	{
		{ 0.f,   0.f,   1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1280.f, 0.f,   1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1280.f, 720.f, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ 0.f,   720.f, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	// 頂点情報の指定
	g_pDirect3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	// 画面の消去
	g_pDirect3DDevice->Clear(0, NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0x00, 0x00, 0x00),1.0, 0);
	// 描画を開始
	g_pDirect3DDevice->BeginScene();

	// テクスチャをステージに割り当てる
	g_pDirect3DDevice->SetTexture(0, g_pGameTexture[BACKGROUND_TEX]);
	// 描画
	g_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, backGround, sizeof(CUSTOMVERTEX));

	MapDraw();

	PlayerDraw();

	// 描画を終了
	g_pDirect3DDevice->EndScene();
	// 画面に表示
	g_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}

// ゲームシーンの初期化関数
void GameSceneInit()
{
	// 描画の設定
	g_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	g_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);


	// テクスチャを読込
	D3DXCreateTextureFromFile(
		g_pDirect3DDevice,
		"RabbitHouse.png",
		&g_pGameTexture[BACKGROUND_TEX]);

	D3DXCreateTextureFromFile(
		g_pDirect3DDevice,
		"mapGround.jpg",
		&g_pGameTexture[MAP_GROUND_TEX]);

	D3DXCreateTextureFromFile(
		g_pDirect3DDevice,
		"chara.png",
		&g_pGameTexture[PLAYER_RIGHT_TEX]);

	D3DXCreateTextureFromFile(
		g_pDirect3DDevice,
		"chara_reverse.png",
		&g_pGameTexture[PLAYER_LEFT_TEX]);

	MapLoad("map.csv");
}

// ゲームシーンの解放関数
void GameSceneFree()
{
	// テクスチャを解放
	for (int i = 0; i < GAMESCENE_MAX; i++)
	{
		g_pGameTexture[i]->Release();
	}
}

void MapLoad(const char* mapdata)
{
	FILE*  pFile;
	fopen_s(&pFile, mapdata, "r");

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			fscanf_s(pFile, "%d,", &map[i][j], _countof(map));
		}
	}
	fclose(pFile);
}

void PlayerDraw()
{
	CUSTOMVERTEX player[4]
	{
		{ g_playerState.PosX - g_playerState.RectX / 2, g_playerState.PosY - g_playerState.RectY / 2, 1.f, 1.f, 0xFFFFFFFF, 0.0f, 0.0f  },
		{ g_playerState.PosX + g_playerState.RectX / 2, g_playerState.PosY - g_playerState.RectY / 2, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 0.0f },
		{ g_playerState.PosX + g_playerState.RectX / 2, g_playerState.PosY + g_playerState.RectY / 2, 1.f, 1.f, 0xFFFFFFFF, 0.25f, 1.0f },
		{ g_playerState.PosX - g_playerState.RectX / 2, g_playerState.PosY + g_playerState.RectY / 2, 1.f, 1.f, 0xFFFFFFFF, 0.0f, 1.0f }
	};

	if (g_playerState.IsLeft)
	{
		g_pDirect3DDevice->SetTexture(0, g_pGameTexture[PLAYER_LEFT_TEX]);
	}
	else
	{
		g_pDirect3DDevice->SetTexture(0, g_pGameTexture[PLAYER_RIGHT_TEX]);
	}
	// 描画
	g_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, player, sizeof(CUSTOMVERTEX));
}

void MapDraw()
{
	CUSTOMVERTEX g_mapTip1[] =
	{
		{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
		{ 64.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.5f, 0.0f },
		{ 64.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.5f, 1.0f },
		{ 0.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
	};

	CUSTOMVERTEX g_mapTip2[] =
	{
		{ 0.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.5f, 0.0f },
		{ 64.0f, 0.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
		{ 64.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
		{ 0.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.5f, 1.0f },
	};

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{

			if (map[y][x] == 1)
			{
				CUSTOMVERTEX drawMapVertex[4];
				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i] = g_mapTip1[i];
				}

				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i].x += (x * TIPSIZE);
					drawMapVertex[i].y += (y * TIPSIZE);
				}
				// テクスチャをステージに割り当てる
				g_pDirect3DDevice->SetTexture(0, g_pGameTexture[MAP_GROUND_TEX]);
				// 描画
				g_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, drawMapVertex, sizeof(CUSTOMVERTEX));
			}
			else if (map[y][x] == 2)
			{
				CUSTOMVERTEX drawMapVertex[4];
				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i] = g_mapTip2[i];
				}

				for (int i = 0; i < 4; i++)
				{
					drawMapVertex[i].x += (x * TIPSIZE);
					drawMapVertex[i].y += (y * TIPSIZE);
				}

				// テクスチャをステージに割り当てる
				g_pDirect3DDevice->SetTexture(0, g_pGameTexture[MAP_GROUND_TEX]);
				// 描画
				g_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, drawMapVertex, sizeof(CUSTOMVERTEX));
			}
		}
	}
}

void KeyCheck(int VK, KEYKIND st) {
	if ((GetKeyState(VK) & 0x8000) != 0) {
		if (PreKey[st] == 0) {
			Key[st] = PUSH;
		}
		else {
			Key[st] = ON;
		}
		PreKey[st] = 1;
	}
	else {
		if (PreKey[st] == 0) {
			Key[st] = OFF;
		}
		else {
			Key[st] = RELEASE;
		}
		PreKey[st] = 0;
	}
}
