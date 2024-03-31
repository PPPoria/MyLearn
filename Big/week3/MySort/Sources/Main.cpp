#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.system.h>
#include"SortHeader.h"

//int tempNum[20] = { 41,41,334,500,169,724,478,358,962,464,705,145,281,827,961,191,915,942,827,436 };
int testNum[200000];//堆空间中开二十万个数(每个数小于十万）
int main() {
	ReadTestData(testNum);

	void (*IS)(int*, int) = &InsertSort;
	void (*MS)(int*, int) = &MergeSort;
	void (*QS)(int*, int) = &QuickSort;
	void (*CS)(int*, int) = &CountSort;
	void (*RS)(int*, int) = &RadixCountSort;

	int t;
	printf("\n-------嘿嘿，终于是完成了(′▽` )-------\n\n");
	printf("以下为四种情况以五种排序的的用时\n10000，50000，200000，100*2000\n");

	printf("\n插入排序:\n");
	t = 0;
	for (int i = 0; i < 2000; i++) t += SortTiming(IS, testNum, 1000);
	printf("%3dms%7dms%7dms%7dms\n", SortTiming(IS, testNum, 10000), SortTiming(IS, testNum, 50000), SortTiming(IS, testNum, 200000), t);

	printf("\n归并排序:\n");
	t = 0;
	for (int i = 0; i < 2000; i++) t += SortTiming(MS, testNum, 1000);
	printf("%3dms%7dms%7dms%7dms\n", SortTiming(MS, testNum, 10000), SortTiming(MS, testNum, 50000), SortTiming(MS, testNum, 200000), t);

	printf("\n非递快速排序:\n");
	t = 0;
	for (int i = 0; i < 2000; i++) t += SortTiming(QS, testNum, 1000);
	printf("%3dms%7dms%7dms%7dms\n", SortTiming(QS, testNum, 10000), SortTiming(QS, testNum, 50000), SortTiming(QS, testNum, 200000), t);

	printf("\n计数排序:\n");
	t = 0;
	for (int i = 0; i < 2000; i++) t += SortTiming(CS, testNum, 1000);
	printf("%3dms%7dms%7dms%7dms\n", SortTiming(CS, testNum, 10000), SortTiming(CS, testNum, 50000), SortTiming(CS, testNum, 200000), t);

	printf("\n基数计数排序:\n");
	t = 0;
	for (int i = 0; i < 2000; i++) t += SortTiming(RS, testNum, 1000);
	printf("%3dms%7dms%7dms%7dms\n", SortTiming(RS, testNum, 10000), SortTiming(RS, testNum, 50000), SortTiming(RS, testNum, 200000), t);


	putchar('\n');
	system("pause");
	return 0;
}