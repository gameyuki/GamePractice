#include<stdio.h>>
#include<stdlib.h>
#include<time.h>
#include<random>

#define INDEXMAX 7

void BubbleSort(int numbers[],int array_size)//����ւ������z��Ƃ��̔z��̗v�f��
{
	int temp;

	/*�v�f���̍Ō�ɂ͕K����ԑ傫�������������Ă���̂Ŕ�r����K�v�͖���*/
	for (int i = 0; i < array_size - 1; i++)
	{
		/*���鐔�͗v�f������1*/
		for (int j = 0; j < array_size - i - 1; j++)
		{
			/*swap�֐��̎��Ƃ����͓���*/
			if (numbers[j] > numbers[j + 1])
			{
				temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
		}
	}
}

void QuickSort(int numbers[], int array_size)
{
	int tmp;

	//���v�f�̑I��

	for (int i = 0; i < array_size; i++)
	{

	}

}

int main()
{
	int a[INDEXMAX];
	std::random_device rand;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < INDEXMAX; i++)
	{
		//a[i] = rand() % 100 + 1;
		a[i] = rand() % 10;
	}

	for (int i = 0; i < INDEXMAX; i++)
	{
		printf("%d��� �� %d ", i+1, a[i]);
	}

	/*����ւ������z��Ƃ��̔z��̗v�f��������*/
	BubbleSort(a, INDEXMAX);

	printf("\n");
	printf("��r��\n");

	for (int i = 0; i < INDEXMAX; i++)
	{
		printf("%d��� �� %d ", i+1,a[i]);
	}

	while (1);
}