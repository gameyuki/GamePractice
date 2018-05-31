#include"Main\Main.h"


bool CollisionKK(float ax1, float ax2, float ay1, float ay2, float bx1, float bx2, float by1, float by2)
{
	if ((ax1 < bx2) &&
		(bx1 < ax2) &&
		(ay1 < by2) &&
		(by1 < ay2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//bool CollisionSS(CHARCTER_STATE* pObj1, CHARCTER_STATE* pObj2)
//{
//	return;
//}