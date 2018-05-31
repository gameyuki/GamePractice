#ifndef DINPUT_H
#define	DINPUT_H

#include<Windows.h>

enum KEYSTATE
{
	PUSH,
	RELEASE,
	ON,
	OFF
};

enum KEYKIND
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FIRE,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	SPACE,
	ESC,
	LSHIFT,
	RSHIFT,
	ESCAPE,
	KEYMAX
};

void KeyCheckDinput(KEYSTATE* Key, int DIK);
HRESULT InitDinputKey(HWND hWnd);
HRESULT InitDinput();
#endif