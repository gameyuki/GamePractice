#include<stdio.h>
#include<time.h>
#include<Windows.h>

void main(void)
{
	//コンテニュー用
	int t = -1;
	char tc[128];

	do
	{
		int n1, n2, i;
		char c[128];

		//画面初期化
		system("cls");

		//敵の数字を乱数で決めている
		srand((unsigned)time(NULL));
		n1 = rand() % 100;

		printf("****************************************\n");
		printf("* 今コンピュータが数字を１つ選びました *\n");
		printf("* 選んだ数字を当ててください           *\n");
		printf("* 数字の範囲は 0 から 99 までです      *\n");
		printf("****************************************\n");

		for (i = 0; i < 10; i++)
		{
			printf("\n数字:");
			fflush(stdout);
			gets_s(c);

			if (c[0] == 'h')
			{
				if (c[1] == 'n')
				{
					if (c[2] == 't')
					{
						printf("%d\n", n1 - 10);
						continue;
					}
				}
			}

			n2 = atoi(c);

			//判定処理
			if (n1 == n2)
			{
				break;
			}
			if (n1 < n2)
			{
				printf("大きすぎます\n");
			}
			else
			{
				printf("小さすぎます\n");
			}
		}

		//何回目でクリアしたか
		if (i <= 10)
		{
			printf("%d回目で当たり\n", i);
		}
		else
		{
			printf("アウト!!\n正解は%dでした\n", n1);
		}

		//煽り文

		switch (i)
		{
		case 1:
			printf("パーフェクト!!!\n\n\n\n\n");
			break;
		case 2:
			printf("凄いぞ！！！\n\n\n\n\n");
			break;
		case 3:
			printf("惜しいぞ！！\n\n\n\n\n");
			break;
		case 4:
			printf("もう少しです\n\n\n\n\n");
			break;
		case 5:
			printf("ナイス！\n\n\n\n\n");
			break;
		case 6:
			printf("いい線いってる！\n\n\n\n\n");
			break;
		case 7:
			printf("いけるいける！\n\n\n\n\n");
			break;
		case 8:
			printf("勝ったな(確信)\n\n\n\n\n");
			break;
		case 9:
			printf("ファイト！！\n\n\n\n\n");
			break;
		case 10:
			printf("頑張って！！\n\n\n\n\n");
			break;
		}

		//コンテニュー文
		printf("もう一度やりますか？\n");
		printf("Yes 0 : No 1\n");
		gets_s(tc);
		t = atoi(tc);

		//この関数でもいける
		//scanf_s("%d",&t);

	} while (t == 0);

	printf("バイバーイ\n");
}