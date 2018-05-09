#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//カードの枚数
#define CARDNUMBER 52

int g_Card = CARDNUMBER;

//残数
int Residue = 0;

//カードのマークの種類
enum Mark
{
	HEART,
	DIA,
	SPADES,
	CLOVER
};

struct State
{
	//手札
	int Hand[9];
	//マーク
	int Mark;
	//合計数
	int total;
	//カウント
	int Count;
	//重複チェック用(カード)
	int CardStack[10];
	//重複チェック用(マーク)
	int MarkStack[10];
	//A用変数
	bool Acecheck;
};

State g_Player = { NULL };
State g_Enemy = { NULL };

void PlayerDraw()
{
	int r = 0;
	int mark = 0;

	while (1)
	{
		r = rand() % 13 + 1;
		mark = rand() % 4;

		g_Player.CardStack[g_Player.Count] = r;
		g_Player.MarkStack[g_Player.Count] = mark;

		for (int i = 0; i < g_Player.Count; i++)
		{
			if (g_Player.MarkStack[i] == mark)
			{
				if (g_Player.CardStack[i] == r)
				{
					continue;
				}
			}
		}

		if (r == 1)
		{
			g_Player.Acecheck = true;
		}

		if ((r > 10) || (r == 1))
		{
			r = 10;
		}

		break;
	}

	g_Player.Hand[g_Player.Count] = r;

	switch (mark)
	{
	case HEART:
		printf("自分がハートの%dを引きました。\n", g_Player.Hand[g_Player.Count]);
		break;
	case DIA:
		printf("自分がダイヤの%dを引きました。\n", g_Player.Hand[g_Player.Count]);
		break;
	case SPADES:
		printf("自分がスペードの%dを引きました。\n", g_Player.Hand[g_Player.Count]);
		break;
	case CLOVER:
		printf("自分がクローバーの%dを引きました。\n", g_Player.Hand[g_Player.Count]);
		break;
	default:
		exit(1);
		break;
	}

	g_Card--;
}

void EnemyDraw()
{
	int r = 0;
	int mark = 0;

	while (1)
	{
		r = rand() % 13 + 1;
		mark = rand() % 4;

		g_Enemy.CardStack[g_Enemy.Count] = r;
		g_Enemy.MarkStack[g_Enemy.Count] = mark;

		for (int i = 0; i < g_Enemy.Count; i++)
		{
			if (g_Enemy.MarkStack[i] == mark)
			{
				if (g_Enemy.CardStack[i] == r)
				{
					continue;
				}
			}
		}

		if (r == 1)
		{
			g_Enemy.Acecheck = true;
		}

		if ((r > 10) || (r == 1))
		{
			r = 10;
		}

		break;
	}

	g_Enemy.Hand[g_Enemy.Count] = r;

	switch (mark)
	{
	case HEART:
		printf("敵がハートの%dを引きました。\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	case DIA:
		printf("敵がダイヤの%dを引きました。\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	case SPADES:
		printf("敵がスペードの%dを引きました。\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	case CLOVER:
		printf("敵がクローバーの%dを引きました。\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	default:
		exit(1);
		break;
	}

	g_Card--;
}

void TotalDraw(State* _total,bool chr)
{
	if (chr)
	{
		_total->total += _total->Hand[g_Player.Count];

		printf("Playerの今の合計は%dです\n", _total->total);

		g_Player.Count++;
	}
	else
	{
		_total->total += _total->Hand[g_Enemy.Count];

		printf("Enemyの今の合計は%dです\n", _total->total);

		g_Enemy.Count++;
	}
}

bool TotalCheck(State* _total)
{
	if (_total->total > 21)
	{
		if (_total->Acecheck)
		{
			_total->total -= 9;
			return true;
		}

		return false;
	}

	return true;
}

void HandPrint()
{
	printf("\n");
	printf("貴方の合計は%dです。\n", g_Player.total);
	printf("敵の合計は%dです。\n", g_Enemy.total);
	printf("\n");
}

//前準備
void Prepara()
{
	printf("☆★☆★☆★☆★☆★　ブラックジャックへようこそ！　☆★☆★☆★☆★☆★☆★\n");
	printf("ゲームを開始します\n");
	printf("最初に二枚配られます\n");

	PlayerDraw();
	TotalDraw(&g_Player,true);
	PlayerDraw();
	TotalDraw(&g_Player, true);

	if (!TotalCheck(&g_Player))
	{
		printf("gameover\n");
		printf("\n");
		printf("貴方の負けです\n");
		getchar();
		exit(1);
	}

	printf("\n");
	EnemyDraw();
	TotalDraw(&g_Enemy,false);
	EnemyDraw();
	TotalDraw(&g_Enemy, false);

	if (!TotalCheck(&g_Enemy))
	{
		printf("gameclear\n");
		printf("\n");
		printf("敵の負けです\n");
		getchar();
		exit(1);
	}
}

int main(void)
{
	srand((unsigned int)time(NULL));
	char c;

	printf("\n");
	Prepara();
	HandPrint();

	while (1)
	{
		printf("もう1枚引きますか?(y/n)\n");
		gets_s(&c, 2);
		if (c == 'y')
		{
			PlayerDraw();
		}
		else if (c == 'n')
		{
			break;
		}
		else
		{
			continue;
		}

		TotalDraw(&g_Player, true);

		if (!TotalCheck(&g_Player))
		{
			printf("gameover\n");
			printf("\n");
			printf("貴方の負けです\n");
			getchar();
			exit(1);
		}

		if (!TotalCheck(&g_Enemy))
		{
			printf("gameclear\n");
			printf("\n");
			printf("敵の負けです\n");
			getchar();
			exit(1);
		}
	}

	//敵さんのターン
	{
		while (1)
		{
			if (g_Enemy.total > 17)
			{
				break;
			}
			else if (g_Enemy.total <= 15)
			{
				EnemyDraw();
				TotalDraw(&g_Enemy, false);
			}
			else
			{
				break;
			}
		}

		if (!TotalCheck(&g_Enemy))
		{
			printf("gameclear\n");
			printf("\n");
			printf("敵の負けです\n");
			getchar();
			exit(1);
		}
	}

	HandPrint();

	//勝負
	while (1)
	{
		if (g_Player.total == g_Enemy.total)
		{
			printf("引き分け\n");
			getchar();
			exit(1);
		}
		else if(g_Player.total < g_Enemy.total)
		{
			printf("敵の勝ちです!\n");
			getchar();
			exit(1);
		}
		else if(g_Player.total > g_Enemy.total)
		{
			printf("勝利！\n");
			printf("貴方の勝ちです!\n");
			getchar();
			exit(1);
		}
	}

	while (1);
}