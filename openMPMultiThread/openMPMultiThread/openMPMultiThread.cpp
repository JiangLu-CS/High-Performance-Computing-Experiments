#include <iostream>
#include <omp.h>
#include <fstream>
#include <ctime>
#define size 1000
using namespace std;

int* b;
#pragma warning(disable : 4996)
int* a, n, thread_count;
void QSort(int begin, int end) {
	if (begin >= end) return;
	// 枢轴元素就需求最前里面的那个
	int i = begin, j = end, key = a[begin]; // 坑在begin点 
	while (i < j) {
		while (i < j && a[j] >= key) --j;
		if (i < j) a[i] = a[j];
		while (i < j && a[i] <= key) ++i;
		if (i < j) a[j] = a[i];
	}
	a[i] = key;
	QSort(begin, i - 1);
	QSort(i + 1, end);
}
void sort() {
	// 分成thread_count段;
	int* keys = new int[thread_count];
	bool* finished = new bool[thread_count];
	int localn = n / thread_count, i;
	for (i = 0; i < thread_count; ++i) {
		keys[i] = i * localn; // begin keys
		finished[i] = false;
	}
#pragma omp parallel for num_threads (thread_count) default(none) shared(a, n,localn) private(i)
	for (i = 0; i < thread_count; ++i) {
		if (i < thread_count - 1) {
			QSort(i * localn, (i + 1) * localn - 1);
		}
		else {
			QSort(i * localn, n - 1);
		}
	}


	bool allfinished = false, first = true;
	int min = 0, minkey_index, globalindex = 0;
	while (!allfinished) {
		allfinished = false;
		first = true;
		// choose min index
		for (i = 0; i < thread_count; ++i) {
			if (finished[i]) continue;
			if (first) {
				min = a[keys[i]]; first = false; minkey_index = i;
			}
			else if (a[keys[i]] < min) {
				min = a[keys[i]]; minkey_index = i;
			}
		}
		if (first) { break; }

		a[globalindex++] = min;

		keys[minkey_index]++;
		if (minkey_index == thread_count - 1 && keys[minkey_index] == n) finished[minkey_index] = true;
		else if (minkey_index < thread_count - 1 && keys[minkey_index] == (minkey_index + 1) * localn)
		{
			finished[minkey_index] = true;
		}
	}

	delete[]finished;
	delete[]keys;
}

int main(int argc, char** argv) {
	if (argc < 2)
		cout << "hehe";
		return 0;
	thread_count = strtol(argv[1], NULL, 10);
	int i;
	//ifstream cin("input.txt");
	//cin >> n;
	//a = new int[n];
	//output = new int[n];
	//for (i = 0; i < n; ++i) cin >> a[i];
	srand(396);
	printf("排序前的随机数组为 :\n");
	b = (int*)malloc(size * sizeof(int));
	a = (int*)malloc(size * sizeof(int));
	for (i = 0; i < size; i++)
	{
		b[i] = (int)rand();
		a[i] = b[i];
		if (i < 100)
			printf("%d ", a[i]);
	}
	cout << "reading finish\n";
	clock_t starttime, endtime;
	starttime = clock();
	sort();
	endtime = clock();
	cout << "sort finished\n";
	//ofstream out("output.txt");
	//for (i = 0; i < n; ++i) out << output[i] << " ";
	printf("排序后的有序数组为 :\n");
	for (i = 0; i < size; i++)
		if (i < 100)
			printf("%d ", a[i]);
	printf("... ...\n");
	cout << "Total time sorted: " << (double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

}
