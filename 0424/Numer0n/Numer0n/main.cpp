#include<stdio.h>
#include<time.h>
#include<Windows.h>

void main(void)
{
	//�R���e�j���[�p
	int t = -1;
	char tc[128];

	do
	{
		int n1, n2, i;
		char c[128];

		//��ʏ�����
		system("cls");

		//�G�̐����𗐐��Ō��߂Ă���
		srand((unsigned)time(NULL));
		n1 = rand() % 100;

		printf("****************************************\n");
		printf("* ���R���s���[�^���������P�I�т܂��� *\n");
		printf("* �I�񂾐����𓖂ĂĂ�������           *\n");
		printf("* �����͈̔͂� 0 ���� 99 �܂łł�      *\n");
		printf("****************************************\n");

		for (i = 0; i < 10; i++)
		{
			printf("\n����:");
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

			//���菈��
			if (n1 == n2)
			{
				break;
			}
			if (n1 < n2)
			{
				printf("�傫�����܂�\n");
			}
			else
			{
				printf("���������܂�\n");
			}
		}

		//����ڂŃN���A������
		if (i <= 10)
		{
			printf("%d��ڂœ�����\n", i);
		}
		else
		{
			printf("�A�E�g!!\n������%d�ł���\n", n1);
		}

		//���蕶

		switch (i)
		{
		case 1:
			printf("�p�[�t�F�N�g!!!\n\n\n\n\n");
			break;
		case 2:
			printf("�������I�I�I\n\n\n\n\n");
			break;
		case 3:
			printf("�ɂ������I�I\n\n\n\n\n");
			break;
		case 4:
			printf("���������ł�\n\n\n\n\n");
			break;
		case 5:
			printf("�i�C�X�I\n\n\n\n\n");
			break;
		case 6:
			printf("�����������Ă�I\n\n\n\n\n");
			break;
		case 7:
			printf("�����邢����I\n\n\n\n\n");
			break;
		case 8:
			printf("��������(�m�M)\n\n\n\n\n");
			break;
		case 9:
			printf("�t�@�C�g�I�I\n\n\n\n\n");
			break;
		case 10:
			printf("�撣���āI�I\n\n\n\n\n");
			break;
		}

		//�R���e�j���[��
		printf("������x���܂����H\n");
		printf("Yes 0 : No 1\n");
		gets_s(tc);
		t = atoi(tc);

		//���̊֐��ł�������
		//scanf_s("%d",&t);

	} while (t == 0);

	printf("�o�C�o�[�C\n");
}