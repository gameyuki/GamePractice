#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//�J�[�h�̖���
#define CARDNUMBER 52

//���s
#define PL printf("\n")

//�J�[�h�̃}�[�N�̎��
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

//�L�����N�^�[�̃X�e�[�^�X
struct CharState
{
	//���O
	char m_Name[8];
	//��D
	int m_Hand[9];
	//�}�[�N
	int m_Mark;
	//���v��
	int m_Total;
	//�J�E���g
	int m_Count;
	//�d���`�F�b�N�p(�J�[�h)
	int m_CardStack[10];
	//�d���`�F�b�N�p(�}�[�N)
	int m_MarkStack[10];
	//A�p�ϐ�
	bool m_AceCheck;
};

//���̃J�[�h�̑���
int g_Card = CARDNUMBER;

//�O���[�o���ϐ�
CharState g_Player = { NULL };
CharState g_Enemy = { NULL };

//�d���`�F�b�N�S�J�[�h�p
int g_AllCardStack[53] = { NULL };
int g_AllMarkStack[4] = { NULL };

int g_Counter = 0;

//�J�[�h�h���[
void Draw(CharState* _pcharacter)
{
	int r = 0;
	int Mark = 0;
	int i = 0;

	while (1)
	{
		r = rand() % 13 + 1;
		Mark = rand() % 4;

		//���������d���`�F�b�N�ł��Ă��Ȃ�
		_pcharacter->m_CardStack[_pcharacter->m_Count] = r;
		_pcharacter->m_MarkStack[_pcharacter->m_Count] = Mark;

		//g_AllCardStack[g_Counter] = r;
		
		//���������d���`�F�b�N�ł��Ă��Ȃ�
		////�d���`�F�b�N
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

		//J,Q,K��10�Ƃ���
		if (r > 10)
		{
			r = 10;
		}

		//A��11
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
		printf("%s�̓n�[�g��%d�������܂����B\n",_pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	case DIA:
		printf("%s�̓_�C����%d�������܂����B\n", _pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	case SPADES:
		printf("%s�̓X�y�[�h��%d�������܂����B\n", _pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	case KURABU:
		printf("%s�̓N���u��%d�������܂����B\n", _pcharacter->m_Name, _pcharacter->m_Hand[_pcharacter->m_Count]);
		break;
	default:
		exit(1);
		break;
	}

	//���v��
	_pcharacter->m_Total += _pcharacter->m_Hand[_pcharacter->m_Count];
	_pcharacter->m_Count++;
	g_Counter++;
	g_Card--;
}

//��D�̍��v��������
void PrintTotal(CharState* _chr)
{
	printf("%s�̎�D�̍��v��%d�ł��B\n", _chr->m_Name, _chr->m_Total);
}

//�o�[�X�g�`�F�b�N
void CheckBurst(CharState* _pcharacter)
{
	bool Burst = false;

	if (_pcharacter->m_Total > 21)
	{
		if (_pcharacter->m_AceCheck)
		{
			printf("A������܂��A11��1�ɕς��܂�\n");
			_pcharacter->m_Total -= 10;
			PrintTotal(_pcharacter);
			_pcharacter->m_AceCheck = false;
			return;
		}

		printf("�o�[�X�g!!!\n");
		printf("GameOver\n");
		printf("\n");
		printf("%s�̕����ł�\n", _pcharacter->m_Name);
		getchar();
		exit(1);
	}
}

//��D���J
void OpenHands(CharState* _chr)
{
	for (int i = 0; i < _chr->m_Count; i++)
	{
		printf("%d\t", _chr->m_Hand[i]);
	}
	printf("\n");
}

//Player�̃^�[��
void PlayerTurn()
{

	char c;

	while (1)
	{
		printf("\n����1�������܂���?(y/n)\n");
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

//�G����̃^�[��	
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

//�O����
void Prepare()
{
	srand((unsigned)time(NULL));
	printf("���������������������@�u���b�N�W���b�N�ւ悤�����I�@������������������������\n");
	printf("���O����͂��Ă�������\n");
	gets_s(g_Player.m_Name);
	strcpy_s(g_Enemy.m_Name, "Enemy");
	printf("�Q�[�����J�n���܂�\n");
	printf("�ŏ��ɓ񖇔z���܂�\n");
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

//��������
void Battle()
{
	//����
	while (1)
	{
		if (g_Player.m_Total == g_Enemy.m_Total)
		{
			printf("\n��������\n");
			getchar();
			exit(1);
		}
		else if (g_Player.m_Total < g_Enemy.m_Total)
		{
			printf("\n�G�̏����ł�!\n");
			getchar();
			exit(1);
		}
		else if (g_Player.m_Total > g_Enemy.m_Total)
		{
			printf("�����I\n");
			printf("\n�M���̏����ł�!\n");
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