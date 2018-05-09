#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//�J�[�h�̖���
#define CARDNUMBER 52

int g_Card = CARDNUMBER;

//�c��
int Residue = 0;

//�J�[�h�̃}�[�N�̎��
enum Mark
{
	HEART,
	DIA,
	SPADES,
	CLOVER
};

struct State
{
	//��D
	int Hand[9];
	//�}�[�N
	int Mark;
	//���v��
	int total;
	//�J�E���g
	int Count;
	//�d���`�F�b�N�p(�J�[�h)
	int CardStack[10];
	//�d���`�F�b�N�p(�}�[�N)
	int MarkStack[10];
	//A�p�ϐ�
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
		printf("�������n�[�g��%d�������܂����B\n", g_Player.Hand[g_Player.Count]);
		break;
	case DIA:
		printf("�������_�C����%d�������܂����B\n", g_Player.Hand[g_Player.Count]);
		break;
	case SPADES:
		printf("�������X�y�[�h��%d�������܂����B\n", g_Player.Hand[g_Player.Count]);
		break;
	case CLOVER:
		printf("�������N���[�o�[��%d�������܂����B\n", g_Player.Hand[g_Player.Count]);
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
		printf("�G���n�[�g��%d�������܂����B\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	case DIA:
		printf("�G���_�C����%d�������܂����B\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	case SPADES:
		printf("�G���X�y�[�h��%d�������܂����B\n", g_Enemy.Hand[g_Enemy.Count]);
		break;
	case CLOVER:
		printf("�G���N���[�o�[��%d�������܂����B\n", g_Enemy.Hand[g_Enemy.Count]);
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

		printf("Player�̍��̍��v��%d�ł�\n", _total->total);

		g_Player.Count++;
	}
	else
	{
		_total->total += _total->Hand[g_Enemy.Count];

		printf("Enemy�̍��̍��v��%d�ł�\n", _total->total);

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
	printf("�M���̍��v��%d�ł��B\n", g_Player.total);
	printf("�G�̍��v��%d�ł��B\n", g_Enemy.total);
	printf("\n");
}

//�O����
void Prepara()
{
	printf("���������������������@�u���b�N�W���b�N�ւ悤�����I�@������������������������\n");
	printf("�Q�[�����J�n���܂�\n");
	printf("�ŏ��ɓ񖇔z���܂�\n");

	PlayerDraw();
	TotalDraw(&g_Player,true);
	PlayerDraw();
	TotalDraw(&g_Player, true);

	if (!TotalCheck(&g_Player))
	{
		printf("gameover\n");
		printf("\n");
		printf("�M���̕����ł�\n");
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
		printf("�G�̕����ł�\n");
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
		printf("����1�������܂���?(y/n)\n");
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
			printf("�M���̕����ł�\n");
			getchar();
			exit(1);
		}

		if (!TotalCheck(&g_Enemy))
		{
			printf("gameclear\n");
			printf("\n");
			printf("�G�̕����ł�\n");
			getchar();
			exit(1);
		}
	}

	//�G����̃^�[��
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
			printf("�G�̕����ł�\n");
			getchar();
			exit(1);
		}
	}

	HandPrint();

	//����
	while (1)
	{
		if (g_Player.total == g_Enemy.total)
		{
			printf("��������\n");
			getchar();
			exit(1);
		}
		else if(g_Player.total < g_Enemy.total)
		{
			printf("�G�̏����ł�!\n");
			getchar();
			exit(1);
		}
		else if(g_Player.total > g_Enemy.total)
		{
			printf("�����I\n");
			printf("�M���̏����ł�!\n");
			getchar();
			exit(1);
		}
	}

	while (1);
}