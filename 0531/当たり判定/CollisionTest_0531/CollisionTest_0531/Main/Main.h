#ifndef MAIN_H
#define MAIN_H

#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=NULL;}}

#include<windows.h>
#include<d3dx9.h>

/* 頂点構造体 */
typedef struct _CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
}CUSTOMVERTEX;

enum TEXTURE
{
	/*　背景　*/
	BACKGROUND_TEX,
	PLAYER_TEX,
	ENEMY_TEX,
	PARTICLE_TEX,
	TEXMAX
};

typedef struct _CHARCTER_STATE
{
	float x, y, scale, v, angle, zangle;
	bool activflg;
	float k;
	DWORD col;
}CHARCTER_STATE, *LPCHARCTER_STATE;

extern LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	画像の情報を入れておく為の配列
extern IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern IDirect3D9*			  g_pDirect3D;		//	Direct3Dのインターフェイス

#endif