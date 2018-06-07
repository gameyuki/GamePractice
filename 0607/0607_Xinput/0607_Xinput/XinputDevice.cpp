#include<Windows.h>
#include<Xinput.h>
#include"Main.h"
#include"XinputDevice.h"

XINPUT_STATE g_Xinput;
padstate g_padstate[buttomindexMAX];
padstate g_padoldstate[buttomindexMAX] = { padoff };

void Getcontrolle()
{
	XInputGetState(0, &g_Xinput);
}

padstate Getbuttom(buttomindex index)
{
	return g_padstate[index];
}

bool GetLanalog(analog analogstate)
{
	switch (analogstate)
	{
	case ANALOGUP:
		if (g_Xinput.Gamepad.sThumbLY > -65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (g_Xinput.Gamepad.sThumbLY < 65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (g_Xinput.Gamepad.sThumbLX <-65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (g_Xinput.Gamepad.sThumbLX >65535 / 4)
		{
			return true;
		}
		break;
	}
	return false;
}

void checkbuttomstate(WORD buttomID, int buttomindex)
{
	if (g_Xinput.Gamepad.wButtons&buttomID)
	{
		if (g_padoldstate[buttomindex] == padon)
		{
			g_padstate[buttomindex] = padon;
		}
		else
		{
			g_padstate[buttomindex] = padpush;
		}

		g_padoldstate[buttomindex] = padon;
	}
	else
	{
		if (g_padoldstate[buttomindex] == padon)
		{
			g_padstate[buttomindex] = padrelease;
		}
		else
		{
			g_padstate[buttomindex] = padoff;
		}
		g_padoldstate[buttomindex] = padoff;
	}

}