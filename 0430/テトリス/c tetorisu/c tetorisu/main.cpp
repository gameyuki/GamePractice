//*****************************************
//	include
//	��{�w�b�_�[���܂߂�
//*****************************************
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#include"Sub.h"

//*****************************************
//	�O���[�o���ϐ�
//*****************************************
//���̃u���b�N
int g_Block[BLOCK_HEIGHT][BLOCK_WIDTH];
//���X�e�[�W
int g_Stage[FIELD_HEIGHT][FIELD_WIDTH];
//�{�X�e�[�W
int g_Field[FIELD_HEIGHT][FIELD_WIDTH];

//�u���b�N�̉��ʒu
int g_Block_x;

//�u���b�N�̏c�ʒu
int g_Block_y;

//�����u���b�N�̎��
int g_BlockId = 0;

//�����蔻��p�t���O
bool g_CollisionFlg = false;

//�u���b�N�Đ����p�t���O
bool g_Make_BlockFlg = false;

//�Q�[���I�[�o�[�p�t���O
bool g_GameOverFlg = false;

//��������p�z��
int g_ClearLine_Point[20];

//��������p�z��
bool g_ClearFlg = false;

//�N���A�p�J�E���g
int g_ClearCount = 0;

//��]�p�J�E���g
int g_Turn_Point = 0;

//��]�p�z��
int g_Turn_Block[BLOCK_HEIGHT][BLOCK_WIDTH];


//*****************************************
//	����������
//*****************************************
void Init()
{
	int i, j;

	//����̕ǂ�����Ă���
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
//	�����u���b�N��o�^
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
//	�{�X�e�[�W�ɉ��X�e�[�W�Ɖ��u���b�N���d�ˍ��킹��
//**************************************************
void Make_Field()
{
	int i, j, x, y;

	//���X�e�[�W��{�X�e�[�W�Ɉڂ��Ă���
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			g_Field[i][j] = g_Stage[i][j];
		}
	}

	//�����u���b�N��{�X�e�[�W�Ɉڂ��Ă���
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
//	��ʕ\��
//*****************************************
void Draw_Field()
{
	int i, j;

	system("cls");

	for (i = 0; i < FIELD_HEIGHT - 2; i++)
	{
		for (j = 2; j < FIELD_WIDTH - 2; j++)
		{
			if (g_Field[i][j] == 9)		//<<��
			{
				printf("��");
			}
			else if (g_Field[i][j] == 1)	//<<�����u���b�N
			{
				printf("��");
			}
			else
			{
				printf("�@");	//<<��
			}
		}

		printf("\n");
	}
}

//*****************************************
//	�O�{�X�e�[�W����
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
//	�u���b�N��������
//*****************************************
void Fall_Block()
{
	if (g_Make_BlockFlg)
	{
		g_Block_y++;
	}
}

//*****************************************
//	�����蔻��
//*****************************************
void Collsion_Left()	//<<��
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

void CollsionRight()	//<<�E
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

void Collison_Bottom()	//<<��
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

void Collision_Center()	//<<��
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

//��]��̓����蔻��
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
//	��]
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
//	������T��
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
//	���͎�t
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
//	���ԉ҂�
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
//	�u���b�N�̌Œ�
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
//	�Q�[���I�[�o�[����
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
//	���C������
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