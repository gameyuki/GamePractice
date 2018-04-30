//*****************************************
//	include
//	基本ヘッダーを含める
//*****************************************
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#include"Sub.h"

//*****************************************
//	グローバル変数
//*****************************************
//次のブロック
int g_Block[BLOCK_HEIGHT][BLOCK_WIDTH];
//仮ステージ
int g_Stage[FIELD_HEIGHT][FIELD_WIDTH];
//本ステージ
int g_Field[FIELD_HEIGHT][FIELD_WIDTH];

//ブロックの横位置
int g_Block_x;

//ブロックの縦位置
int g_Block_y;

//落下ブロックの種類
int g_BlockId = 0;

//当たり判定用フラグ
bool g_CollisionFlg = false;

//ブロック再生成用フラグ
bool g_Make_BlockFlg = false;

//ゲームオーバー用フラグ
bool g_GameOverFlg = false;

//横列消去用配列
int g_ClearLine_Point[20];

//横列消去用配列
bool g_ClearFlg = false;

//クリア用カウント
int g_ClearCount = 0;

//回転用カウント
int g_Turn_Point = 0;

//回転用配列
int g_Turn_Block[BLOCK_HEIGHT][BLOCK_WIDTH];


//*****************************************
//	初期化処理
//*****************************************
void Init()
{
	int i, j;

	//周りの壁を作っている
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			g_Stage[i][0] = 9;
			g_Stage[i][1] = 9;
			g_Stage[i][2] = 9;
			g_Stage[20][j] = 9;
			g_Stage[21][j] = 9;
			g_Stage[22][j] = 9;
			g_Stage[i][15] = 9;
			g_Stage[i][16] = 9;
			g_Stage[i][17] = 9;
		}
	}

	g_Block_x = 7;
	g_Block_y = 0;
	g_CollisionFlg = false;
	g_GameOverFlg = false;
	g_Make_BlockFlg = false;
	g_ClearFlg = true;
	g_BlockId = 0;
	g_ClearCount = 0;

	srand((unsigned int)time(NULL));
}

void Init2()
{
	g_Block_x = 7;
	g_Block_y = 0;
	g_Make_BlockFlg = false;
}

//*****************************************
//	落下ブロックを登録
//*****************************************
void Make_Block()
{
	int x, y;

	if (!g_Make_BlockFlg)
	{
		g_BlockId = (rand() % 6);

		for (y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (x = 0; x < BLOCK_WIDTH; x++)
			{
				g_Block[y][x] = g_Blocks[(g_BlockId * BLOCK_HEIGHT) + y][x];
			}
		}

		g_Make_BlockFlg = true;
	}
}

//**************************************************
//	本ステージに仮ステージと仮ブロックを重ね合わせる
//**************************************************
void Make_Field()
{
	int i, j, x, y;

	//仮ステージを本ステージに移している
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			g_Field[i][j] = g_Stage[i][j];
		}
	}

	//落下ブロックを本ステージに移している
	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			g_Field[g_Block_y + y][g_Block_x + x] += g_Block[y][x];
		}
	}
}

void Make_Field2()
{
	int i, j;

	for (i = 0; i<FIELD_HEIGHT; i++) 
	{
		for (j = 0; j<FIELD_WIDTH; j++) 
		{
			g_Field[i][j] = g_Stage[i][j];
		}
	}
}

//*****************************************
//	画面表示
//*****************************************
void Draw_Field()
{
	int i, j;

	system("cls");

	for (i = 0; i < FIELD_HEIGHT - 2; i++)
	{
		for (j = 2; j < FIELD_WIDTH - 2; j++)
		{
			if (g_Field[i][j] == 9)		//<<壁
			{
				printf("■");
			}
			else if (g_Field[i][j] == 1)	//<<落下ブロック
			{
				printf("□");
			}
			else
			{
				printf("　");	//<<空白
			}
		}

		printf("\n");
	}
}

//*****************************************
//	前本ステージ消去
//*****************************************
void Clear_Field()
{
	int i, j;

	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			g_Field[i][j] = 0;
		}
	}
}

//*****************************************
//	ブロック落下処理
//*****************************************
void Fall_Block()
{
	if (g_Make_BlockFlg)
	{
		g_Block_y++;
	}
}

//*****************************************
//	当たり判定
//*****************************************
void Collsion_Left()	//<<左
{
	int x, y;

	g_CollisionFlg = false;

	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			if (g_Block[y][x] != 0)
			{
				if (g_Stage[g_Block_y + y][g_Block_x + (x - 1)] != 0)
				{
					g_CollisionFlg = true;
				}
			}
		}
	}
}

void CollsionRight()	//<<右
{
	int x, y;

	g_CollisionFlg = false;

	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			if (g_Block[y][x] != 0)
			{
				if (g_Stage[g_Block_y + y][g_Block_x + (x + 1)] != 0)
				{
					g_CollisionFlg = true;
				}
			}
		}
	}
}

void Collison_Bottom()	//<<底
{
	int x, y;

	g_CollisionFlg = false;

	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			if (g_Block[y][x] != 0)
			{
				if (g_Stage[g_Block_y + (y + 1)][g_Block_x + x] != 0)
				{
					g_CollisionFlg = true;
				}
			}
		}
	}
}

void Collision_Center()	//<<上
{
	int x, y;

	g_CollisionFlg = false;

	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			if (g_Block[y][x] != 0)
			{
				if (g_Stage[g_Block_y + y][g_Block_x + x] != 0)
				{
					g_CollisionFlg = true;
				}
			}
		}
	}
}

//回転後の当たり判定
void Collision_Turn()
{
	int x, y;

	g_CollisionFlg = false;

	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++) 
		{
			if (g_Turn_Block[y][x] != 0)
			{
				if (g_Stage[g_Block_y + y][g_Block_x + x] != 0)
				{
					g_CollisionFlg = true;
				}
			}
		}
	}
}

//*****************************************
//	回転
//*****************************************
void Turn_Right()
{
	int x, y;

	g_Turn_Point++;

	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			g_Turn_Block[y][x] = g_Blocks[(g_BlockId * BLOCK_HEIGHT) + y][(g_Turn_Point % 4 * BLOCK_WIDTH) + x];
		}
	}

	Collision_Turn();

	if (!g_CollisionFlg)
	{
		for (y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (x = 0; x < BLOCK_WIDTH; x++)
			{
				g_Block[y][x] = g_Turn_Block[y][x];
			}
		}
	}
	else
	{
		g_Turn_Point--;
	}
}

void Turn_Left()
{
	int x, y;

	g_Turn_Point += 3;

	for (y = 0; y < BLOCK_HEIGHT;  y++ ) 
	{
		for (x = 0; x < BLOCK_WIDTH;  x++ ) 
		{
			g_Turn_Block[y][x] =	g_Blocks[(g_BlockId * BLOCK_HEIGHT) + y][(g_Turn_Point % 4 * BLOCK_WIDTH) + x];
		}
	}

	Collision_Turn();

	if (g_CollisionFlg == 0) 
	{
		for (y = 0; y < BLOCK_HEIGHT; y++ )
		{
			for (x = 0; x < BLOCK_WIDTH; x++ )
			{
				g_Block[y][x] = g_Turn_Block[y][x];
			}
		}
	}
	else
	{
		g_Turn_Point -= 3;
	}
}

//*****************************************
//	消去列探し
//*****************************************
void Search_Line()
{
	int i,j;

	for (i = 0; i < FIELD_HEIGHT - 3; i++)
	{
		g_ClearLine_Point[i] = 0;
	}

	for (i = 0; i < FIELD_HEIGHT - 3; i++)
	{
		for (j = 3; j < FIELD_WIDTH - 3; j++)
		{
			if (g_Stage[i][j] == 0)
			{
				g_ClearLine_Point[i] = 1;
				break;
			}
		}
	}

	for (i = 0; i<FIELD_HEIGHT - 3; i++)
	{
		if (g_ClearLine_Point[i] == 0)
		{
			g_ClearFlg = false;
			break;
		}
	}
}

void Clear_Line()
{
	int i, j;
	int Remain_Line_Point[20] = { 0 };
	int Remain_Line_Index = 0;

	if (g_ClearCount < 2)
	{
		for (i = 0; i < FIELD_HEIGHT - 3; i++)
		{
			if (g_ClearLine_Point[i] == 0)
			{
				for (j = 3; j < FIELD_WIDTH - 3; j++)
				{
					g_Stage[i][j] = 0;
				}
			}
		}

		g_ClearCount++;
	}
	else
	{
		for (i = FIELD_HEIGHT - 4; i > 0; i--)
		{
			if (g_ClearLine_Point[i] != 0)
			{
				Remain_Line_Point[Remain_Line_Index] = i;
				Remain_Line_Index++;
			}
		}

		Remain_Line_Index = 0;

		for (i = FIELD_HEIGHT - 4; i >= 0; i--) 
		{
			for (j = 3; j<FIELD_WIDTH - 3; j++)
			{
				g_Stage[i][j] =	g_Stage[Remain_Line_Point[Remain_Line_Index]][j];
			}
			Remain_Line_Index++;
		}

		g_ClearFlg = true;
		g_ClearCount = 0;

		Init2();
	}
}

//*****************************************
//	入力受付
//*****************************************
void Get_Key()
{
	int Key = 0;

	if (_kbhit())
	{
		Key = _getch();
		if (Key == 0 || Key == 224)
		{
			Key = _getch();

			switch (Key)
			{
			case 0x4b:
				Collsion_Left();
				if (!g_CollisionFlg)
				{
					g_Block_x--;
				}

				break;
			case 0x4d:
				CollsionRight();
				if (!g_CollisionFlg)
				{
					g_Block_x++;
				}

				break;
			case 0x50:
				Collison_Bottom();
				while (!g_CollisionFlg)
				{
					g_Block_y++;
					Collison_Bottom();
				}

				break;
			case 0x48:
				Turn_Right();

				break;
			/*case 'z':
				Turn_Left();

				break;*/
			default :
				break;
			}
		}
	}
}

//*****************************************
//	時間稼ぎ
//*****************************************
void Timer()
{
	int x, y;

	for (y = 0; y < 10000; y++)
	{
		for (x = 0; x < 10000; x++)
		{
		}
	}
}

//*****************************************
//	ブロックの固定
//*****************************************
void Save_Block()
{
	int x, y;
	for (y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (x = 0; x < BLOCK_WIDTH; x++)
		{
			g_Stage[g_Block_y + y][g_Block_x + x] += g_Block[y][x];
		}
	}
}

void Fix_Block()
{
	int x, y;

	Collison_Bottom();

	if (g_CollisionFlg)
	{
		Save_Block();
		Search_Line();
		if (g_ClearFlg)
		{
			Init2();
		}
	}
}

//*****************************************
//	ゲームオーバー処理
//*****************************************
void GameOver()
{
	Collision_Center();

	if (g_CollisionFlg)
	{
		g_GameOverFlg = true;
	}
}

//*****************************************
//	メイン処理
//*****************************************
int main()
{
	Init();
	
	while (!g_GameOverFlg)
	{
		Clear_Field();

		if (g_ClearFlg)
		{
			Make_Block();
			GameOver();
			Get_Key();
			Make_Field();
			Fix_Block();
			Fall_Block();
		}
		else
		{
			Clear_Line();
			Make_Field2();
		}

		Draw_Field();
		Timer();
	}

	printf("GameOver\n");
	getchar();
}