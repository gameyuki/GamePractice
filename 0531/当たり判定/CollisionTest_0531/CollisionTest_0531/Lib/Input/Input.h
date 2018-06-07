#ifndef INPUT_H
#define	INPUT_H

#include<Windows.h>
#include<string>
#include<XInput.h>

namespace inputNS
{
	const int KEYS_ARRY_LEN = 256;

	const UCHAR	KEYS_DOWN = 1;
	const UCHAR KEYS_PRESSED = 2;
}

class Input
{
public:
	Input();
	~Input();

	bool KeyDown();
	bool KeysPressed();
	std::string TexIn;

private:

};

Input::Input()
{
}

Input::~Input()
{
}

#endif