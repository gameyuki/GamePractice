#include"Main\Main.h"
#include<Windows.h>

//�x�N�g��V�̒�����float�ŕԂ�
float Vector2Length(const D3DXVECTOR2* v)
{
	return D3DXVec2Length(v);
}

//�x�N�g��V1��V2�̃h�b�g�ς�float�Ƃ��ĕԂ�
float Vector2Dot(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
{
	return D3DXVec2Dot(v1, v2);
}

//�x�N�g��V��P�ʃx�N�g���ϊ�����
void Vector2Normalize(D3DXVECTOR2* v)
{
	D3DXVec2Normalize(v, v);
}