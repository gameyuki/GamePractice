#include<Windows.h>
#include<d3dx9.h>
#include"Main\Main.h"

void SetTexture()
{
	/*ここを徹底的に勉強する事*/
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}


void CreateTexture(const char* text, TEXTURE texture_ID)
{
	D3DXCreateTextureFromFileEx(
		g_pD3Device,
		TEXT(text),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		D3DCOLOR_ARGB(255, 0, 255, 0),
		NULL,
		NULL,
		&g_pTexture[texture_ID]);
}

void LoadTexture()
{
	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CreateTexture("プレイヤー.png", PLAYER_TEX);
	CreateTexture("宿題.png", BACKGROUND_TEX);
	CreateTexture("煙.png", PARTICLE_TEX);
	CreateTexture("蜂2.png", ENEMY_TEX);
}

void Rotation(CUSTOMVERTEX* pObj, float angle)
{
	double rad;
	float cx, cy;
	float temp_x;
	float temp_y;

	/* キャラクターの中心座標(x座標、y座標の足した半分)を出している */
	cx = (pObj[0].x + pObj[1].x) / 2;
	cy = (pObj[0].y + pObj[3].y) / 2;

	rad = D3DXToRadian(angle);

	for (int i = 0; i < 4; i++)
	{
		temp_x = pObj[i].x - cx;
		temp_y = pObj[i].y - cy;

		pObj[i].x = (float)(temp_x * cos(rad) - temp_y * sin(rad)) + cx;
		pObj[i].y = (float)(temp_y * cos(rad) + temp_x * sin(rad)) + cy;
	}
}

void DrawVertex(CHARCTER_STATE Obj, TEXTURE texture_ID, DWORD alpha)
{
	CUSTOMVERTEX cv[4];

	cv[0].x = cv[3].x = Obj.x - Obj.scale;
	cv[1].x = cv[2].x = Obj.x + Obj.scale;

	cv[0].y = cv[1].y = Obj.y - Obj.scale;
	cv[2].y = cv[3].y = Obj.y + Obj.scale;

	for (int i = 0; i < 4; i++)
	{
		cv[i].z = 1.f;
		cv[i].rhw = 1.f;
		cv[i].color = alpha;
	}

	cv[0].tu = cv[0].tv = cv[1].tv = cv[3].tu = 0.f;
	cv[1].tu = cv[2].tu = cv[2].tv = cv[3].tv = 1.f;

	g_pD3Device->SetTexture(0, g_pTexture[texture_ID]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, cv, sizeof(CUSTOMVERTEX));
}

