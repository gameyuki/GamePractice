#include"Main\Main.h"
#include"Hanabi.h"
#include"Lib\Render\Render.h"

#define ParticleMAX 1000000

CHARCTER_STATE g_Particle[1000000];
CHARCTER_STATE g_wkP;
CHARCTER_STATE g_Fire;

static float jumpPower = 7.5f;
static float Gravity = 0.60f;
static float Time = 0;

void AHANABI()
{
	float vx, vy;
	static int A, R, G, B;
	int i = 0;
	static bool flg = true;
	static float bx, by, bv;

	if (flg)
	{
		//花火の初期値
		bx = 280.f + rand() % 1000;
		by = 50.f + rand() % 650;
		bv = rand() % 5 + 1.f;
		//何層目の描画かどうか
		for (int cnt = 0; cnt < 5; cnt++)
		{
			//玉の数
			for (int j = 0; j < 90; i++, j++)
			{
				if (g_Particle[i].activflg == false)
				{
					g_Particle[i].activflg = true;
					g_Particle[i].x = bx;
					g_Particle[i].y = by;
					g_Particle[i].scale = 1.98f;
					//何層目かによって初速度を変えている
					//その層の中でも乱数で速度をバラバラにしている
					g_Particle[i].v = cnt * 0.3f + bv + (rand() % 100) / 100.f;
					g_Particle[i].angle = j * 4 + rand() % 4;
					//ここを聞く
					g_Particle[i].k = 0.015 + (10 - cnt) * 0.003f;
					G = 0x7f * ((cnt + (rand() % 3)) % 3);
					R = 0x7f * ((cnt + (rand() % 3)) % 3);
					B = 0x7f * ((cnt + (rand() % 3)) % 3);
					A = 0xff;
					g_Particle[i].col = A * 0x1000000 + R * 0x10000 + G * 0x100 + B;
				}
			}
		}
		//全部描画した判定
		flg = false;
	}


	//描画部分
	for (int i = 0; i < 1000000; i++)
	{
		//消す場所
		if (g_Particle[i].col == 0xffffffff)
		{
			g_Particle[i].activflg = false;
		}

		//最初初期化されていない奴は描画しない
		if (g_Particle[i].activflg == false)
		{
			continue;
		}


		//ここで角度分落として行っている
		vx = g_Particle[i].v * cos(D3DXToRadian(g_Particle[i].angle));
		g_Particle[i].x += vx;

		vy = g_Particle[i].v * sin(D3DXToRadian(g_Particle[i].angle));
		//重力をかけている
		g_Particle[i].y -= vy - Gravity;

		//三平方の定理
		//ここ聞く用に
		g_Particle[i].v = sqrt(pow(vx, 2.0) + pow(vy, 2.0)) - g_Particle[i].k * g_Particle[i].v;

		//角度を求めている
		//なるほどわからん
		//atanは何処からの角度を求めているのか
		g_Particle[i].angle = D3DXToDegree(atan2(vy, vx));

		A = g_Particle[i].col / 0x1000000;
		A -= 2;

		//色が真っ白(透明)になったら消えるように
		//Aが0以下ってどんな時?
		if (A > 0)
		{
			g_Particle[i].col = g_Particle[i].col % 0x1000000 + A * 0x1000000;
		}
		else
		{
			g_Particle[i].activflg = false;
		}

		//描画
		DrawVertex(g_Particle[i], PARTICLE_TEX, g_Particle[i].col);
		g_wkP = g_Particle[i];
		for (int ang = 5; ang < 90; ang += 10)
		{
			g_wkP.x = bx + (g_Particle[i].x - bx) * sin(D3DXToRadian(ang + rand() % 10));
			g_wkP.y = by + (g_Particle[i].y - by) * cos(D3DXToRadian(85 - ang + rand() % 10));
			DrawVertex(g_wkP, PARTICLE_TEX, g_Particle[i].col);
		}
	}

	int chk;

	for (chk = 0; chk < 1000000; chk++)
	{
		//一個でも生きていたらアウト
		if (g_Particle[chk].activflg == true)
			break;
	}

	//一万以上になるには必ず上の文を抜けなければならない、つまり全部消えている
	if (chk >= 1000000) flg = true;

}