#include"BackGround\BackGround.h"
#include"Collision\Collision.h"
#include"Player\Player.h"
#include"Main\Main.h"
#include"Enemy\Enemy.h"
#include"HANABI\Hanabi.h"

void GameRun()
{
	PlayerControl();
	BackDraw();

	//Œã‚Å’¼‚µ‚Ü‚·
	if(CollisionKK(g_Player[0].x, g_Player[2].x,g_Player[0].y, g_Player[2].y,g_Enemy[0].x,g_Enemy[2].x, g_Enemy[0].y,g_Enemy[2].y))
	{
		
		AHANABI();
	}

	PlayerDraw();
	EnemyDraw();
}