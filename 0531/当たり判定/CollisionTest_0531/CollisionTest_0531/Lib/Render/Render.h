#ifndef  RENDER_H
#define	 RENDER_H

#include<d3d9.h>

void SetTexture();
void LoadTexture();
void DrawVertex(CHARCTER_STATE Obj, TEXTURE texture_ID, DWORD alpha = 0xffffffff);

#endif