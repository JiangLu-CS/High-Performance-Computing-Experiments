
#include<ctime>
#define SIZE 10000
#include<iostream>
#include  <omp.h>
void quickSort(int* num, int low, int high);
int Partition(int* num, int low, int high);
int i = 0;
int size = SIZE;
int* data;
int* data1;


int main()
{

	clock_t startTime, endTime;
	srand(396);
	data = (int*)malloc(size * sizeof(int));
	data1 = (int*)malloc(size * sizeof(int));
	printf("排序前的随机数组为 :\n");
	for (i = 0; i < size; i++)
	{
		data[i] = (int)rand();
		data1[i] = data[i];
		if (i < 100)
			printf("%d ", data[i]);
	}
	printf("... ...\n");
	startTime = clock();
	std::cout << startTime;

	quickSort(data, 0, size-1);
	endTime = clock();
	std::cout << endTime;
	int j;

	printf("排序后的有序数组为 :\n");
	for (i = 0; i < size; i++)
		if (i < 100)
			printf("%d ", data[i]);
	printf("... ...\n");
	double clock = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	std::cout << "runtime:";
	std::cout << clock;
	std::cout << omp_get_thread_num();
	return 0;
}


void quickSort(int* num, int low, int high)
{
	if (low < high)
	{
		int split = Partition(num, low, high);
#pragma omp parallel sections
		{
#pragma omp section//负责这个区域的线程对前面部分进行排序
			quickSort(num, low, split - 1);
#pragma omp section//负责这个区域的线程对后面部分进行排序
			quickSort(num, split + 1, high);
		}

	}

}

int Partition(int* num, int low, int high)
{
	int temp = num[low];//作为中轴
	while (low < high)
	{
		while (low < high && num[high] >= temp)high--;
		num[low] = num[high];
		while (low < high && num[low] <= temp)low++;
		num[high] = num[low];
	}
	num[low] = temp;
	return low;//返回中轴的位置，再进行分离
}