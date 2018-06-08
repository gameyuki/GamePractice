#include<stdio.h>>
#include<stdlib.h>
#include<time.h>
#include<random>

#define INDEXMAX 7

void BubbleSort(int numbers[],int array_size)//入れ替えたい配列とその配列の要素数
{
	int temp;

	/*要素数の最後には必ず一番大きい数字が入っているので比較する必要は無い*/
	for (int i = 0; i < array_size - 1; i++)
	{
		/*見る数は要素数引く1*/
		for (int j = 0; j < array_size - i - 1; j++)
		{
			/*swap関数の時とやり方は同じ*/
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

	//軸要素の選択

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
		printf("%d回目 ＝ %d ", i+1, a[i]);
	}

	/*入れ替えたい配列とその配列の要素数を入れる*/
	BubbleSort(a, INDEXMAX);

	printf("\n");
	printf("比較後\n");

	for (int i = 0; i < INDEXMAX; i++)
	{
		printf("%d回目 ＝ %d ", i+1,a[i]);
	}

	while (1);
}