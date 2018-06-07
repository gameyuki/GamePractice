#include"Main\Main.h"
#include<math.h>


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

bool CollisionCircle(CHARCTER_STATE* pObj1, CHARCTER_STATE* pObj2)
{
	float kyori = (sqrt(pObj1->x - pObj2->x) + sqrt(pObj1->y - pObj2->y));
	return false;
}