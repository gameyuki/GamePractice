#include"Main\Main.h"
#include<Windows.h>

//ƒxƒNƒgƒ‹V‚Ì’·‚³‚ðfloat‚Å•Ô‚·
float Vector2Length(const D3DXVECTOR2* v)
{
	return D3DXVec2Length(v);
}


float Vector2Dot(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
{
	return D3DXVec2Dot(v1, v2);
}