#ifndef MAIN_H
#define MAIN_H

#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=NULL;}}

#include<windows.h>
#include<d3dx9.h>

/* ���_�\���� */
typedef struct _CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
}CUSTOMVERTEX;

enum TEXTURE
{
	/*�@�w�i�@*/
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

extern LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	�摜�̏������Ă����ׂ̔z��
extern IDirect3DDevice9*	  g_pD3Device;		//	Direct3D�̃f�o�C�X
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern IDirect3D9*			  g_pDirect3D;		//	Direct3D�̃C���^�[�t�F�C�X

#endif