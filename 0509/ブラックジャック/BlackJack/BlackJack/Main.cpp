#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//カードの枚数
#define CARDNUMBER 52

//改行
#define PL printf("\n")

//カードのマークの種類
enum Mark
{
	HEART,
	DIA,
	SPADES,
	KURABU
};

typedef struct
{
	int m_number;
	Mark  m_Mark;
}CARD;

CARD g_Cards[52];

//キャラクターのステータス
struct CharState
{
	//名前
	char m_Name[8];
	//手札
	int m_Hand[9];
	//マーク
	int m_Mark;
	//合計数
	int m_Total;
	//カウント
	int m_Count;
	//重複チェック用(カード)
	int m_CardStack[10];
	//重複チェック用(マーク)
	int m_MarkStack[10];
	//A用変数
	bool m_AceCheck;
};

//今のカードの総数
int g_Card = CARDNUMBER;

//グローバル変数
CharState g_Player = { NULL };
CharState g_Enemy = { NULL };

//重複チェック全カード用
int g_AllCardStack[53] = { NULL };
int g_AllMarkStack[4] = { NULL };

int g_Counter = 0;

//カードドロー
void Draw(CharState* _pcharacter)
{
	int r = 0;
	int Mark = 0;
	int i = 0;

	while (1)
	{
		r = rand() % 13 + 1;
		Mark = rand() % 4;

		//自分しか重複チェックできていない
		_pcharacter->m_CardStack[_pcharacter->m_Count] = r;
		_pcharacter->m_MarkStack[_pcharacter->m_Count] = Mark;

		//g_AllCardStack[g_Counter] = r;
		
		//自分しか重複チェックできていない
		////重複チェック
		for (i = 0; i < _pcharacter->m_Count; i++)
		{
			if (_pcharacter->m_MarkStack[i] == Mark)
			{
				if (_pcharacter->m_CardStack[i] == r)
				{
					break;
				}
			}
		}

		//for (i = 0; i < g_Counter; i++)
		//{
		//	if (g_AllMarkStack[i] == Mark)
		//	{
		//		if (g_AllCardStack[i] == r)
		//		{
		//			break;
		//		}
		//	}
		//}

		if (i < _pcharacter->m_Count) continue;

		//J,Q,Kは10とする
		if (r > 10)
		{
			r = 10;
		}

		//Aは11
		if (r == 1)
		{
			_pcharacter->m_AceCheck = true;
			r = 11;
		}

		break;
	}

	_pcharacter->m_Hand[_pcharacter->m_Count] = r;

	switch (Mark)
	{
	case HEART:
		printf("%sはハートの%dを引きました。\n",_pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	case DIA:
		printf("%sはダイヤの%dを引きました。\n", _pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	case SPADES:
		printf("%sはスペードの%dを引きました。\n", _pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	case KURABU:
		printf("%sはクラブの%dを引きました。\n", _pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	default:
		exit(1);
		break;
	}

	//合計数
	_pcharacter->m_Total += _pcharacter->m_Hand[_pcharacter->m_Count];
	_pcharacter->m_Count++;
	g_Counter++;
	g_Card--;
}

//手札の合計を見せる
void PrintTotal(CharState* _chr)
{
	printf("%sの手札の合計は%dです。\n", _chr->m_Name, _chr->m_Total);
}

//バーストチェック
void CheckBurst(CharState* _pcharacter)
{
	bool Burst = false;

	if (_pcharacter->m_Total > 21)
	{
		if (_pcharacter->m_AceCheck)
		{
			printf("Aがあります、11か1に変わります\n");
			_pcharacter->m_Total -= 10;
			PrintTotal(_pcharacter);
			_pcharacter->m_AceCheck = false;
			return;
		}

		printf("バースト!!!\n");
		printf("GameOver\n");
		printf("\n");
		printf("%sの負けです\n", _pcharacter->m_Name);
		getchar();
		exit(1);
	}
}

//手札公開
void OpenHands(CharState* _chr)
{
	for (int i = 0; i < _chr->m_Count; i++)
	{
		printf("%d\t", _chr->m_Hand[i]);
	}
	printf("\n");
}

//Playerのターン
void PlayerTurn()
{

	char c;

	while (1)
	{
		printf("\nもう1枚引きますか?(y/n)\n");
		scanf_s("%c", &c);
		getchar();

		//gets_s(&c ,1);
		if (c == 'y')
		{
			Draw(&g_Player);
		}
		else if (c == 'n')
		{
			break;
		}
		else
		{
			continue;
		}

		PrintTotal(&g_Player);

		CheckBurst(&g_Player);
	}

}

//敵さんのターン	
void EnemyTurn()
{
	while (1)
	{
		if (g_Enemy.m_Total > 17)
		{
			break;
		}
		else if (g_Enemy.m_Total <= 15)
		{
			Draw(&g_Enemy);
			printf("\n");
			PrintTotal(&g_Enemy);
		}
		else
		{
			break;
		}
	}
}

//前準備
void Prepare()
{
	srand((unsigned)time(NULL));
	printf("☆★☆★☆★☆★☆★　ブラックジャックへようこそ！　☆★☆★☆★☆★☆★☆★\n");
	printf("名前を入力してください\n");
	gets_s(g_Player.m_Name);
	strcpy_s(g_Enemy.m_Name, "Enemy");
	printf("ゲームを開始します\n");
	printf("最初に二枚配られます\n");
	printf("\n");

	Draw(&g_Player);
	Draw(&g_Player);
	PrintTotal(&g_Player);

	CheckBurst(&g_Player);

	printf("\n");
	Draw(&g_Enemy);
	Draw(&g_Enemy);
	PrintTotal(&g_Enemy);
	printf("\n");

	CheckBurst(&g_Enemy);

	PrintTotal(&g_Player);
	PrintTotal(&g_Enemy);
}

//勝負処理
void Battle()
{
	//勝負
	while (1)
	{
		if (g_Player.m_Total == g_Enemy.m_Total)
		{
			printf("\n引き分け\n");
			getchar();
			exit(1);
		}
		else if (g_Player.m_Total < g_Enemy.m_Total)
		{
			printf("\n敵の勝ちです!\n");
			getchar();
			exit(1);
		}
		else if (g_Player.m_Total > g_Enemy.m_Total)
		{
			printf("勝利！\n");
			printf("\n貴方の勝ちです!\n");
			getchar();
			exit(1);
		}
	}
}

int main(void)
{
	char c;
	printf("\n");
	Prepare();

	PlayerTurn();
	EnemyTurn();

	CheckBurst(&g_Enemy);

	PrintTotal(&g_Player);
	PrintTotal(&g_Enemy);

	Battle();

	while (1);
}