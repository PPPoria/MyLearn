#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include"SortHeader.h"

//计时器
int SortTiming(void(*Sort)(int*, int), int num[], int length) {
	int* temp = (int*)malloc(length * sizeof(int));
	for (int i = 0; i < length; i++) temp[i] = num[i];
	int st;
	st = clock();
	Sort(temp, length);
	st = clock() - st;
	//isOrderly(temp, length) ? putchar('Y') : putchar('N');
	free(temp);
	return st;
}

//读取文件，若无则创建
bool ReadTestData(int num[]) {
	FILE* fp;
	//fp = fopen("testdata.txt", "r");
	if (fopen_s(&fp, "testdata.txt", "r")) {
		fopen_s(&fp, "testdata.txt", "w");
		for (int i = 0; i < 200000; i++) fprintf(fp, "%d ", rand() % 100000);
		fclose(fp);
		fopen_s(&fp, "testdata.txt", "r");
	}
	for (int i = 0; i < 200000; i++) fscanf_s(fp, "%d", num + i);
	fclose(fp);
	return 1;
}

//判断该数组的length长度内是否有序
bool isOrderly(int num[], int length) {
	for (int i = 1; i < length; i++) {
		if (num[i] < num[i - 1]) return 0;
	}
	return 1;
}

//插入排序
void InsertSort(int num[], int length) {
	int j;
	int insertNum;
	for (int i = 1; i < length; i++) {
		j = i;
		insertNum = num[i];//将需要插入的数取出
		while (j && insertNum < num[j - 1]) {//将插入位置之后的数往取出数的空位移动
			num[j] = num[j - 1];
			j--;
		}
		num[j] = insertNum;//插入
	}
}

//归并排序
void MergeSort(int num[], int length) {
	int* temp1 = num;
	int* temp2 = (int*)malloc(length * sizeof(int));
	for (int lengthPerGroup = 1; lengthPerGroup < length; lengthPerGroup *= 2) {
		for (int startOfGroup = 0; startOfGroup < length; startOfGroup += lengthPerGroup * 2) {
			//取该小组的范围
			int low = startOfGroup;
			int k = low;
			int mid = startOfGroup + lengthPerGroup;
			mid = mid < length ? mid : length;//防止超出范围
			int high = startOfGroup + lengthPerGroup * 2;
			high = high < length ? high : length;//同上

			//将该小组再分左右两组排序并合并
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				temp2[k++] = temp1[start1] < temp1[start2] ? temp1[start1++] : temp1[start2++];
			//将这左右中剩余元素排序进小组中
			while (start1 < end1)
				temp2[k++] = temp1[start1++];
			while (start2 < end2)
				temp2[k++] = temp1[start2++];
		}
		//指针地址交换，确保上面循环中的temp1为待排序数组、temp2为已排序数组
		int* temp = temp1;
		temp1 = temp2;
		temp2 = temp;
		//即现在的temp1为经过上面循环后部分排序好的数组
	}

	if (temp1 != num) {
		for (int i = 0; i < length; i++)
			num[i] = temp1[i];
		temp2 = temp1;
	}
	free(temp2);
}

//快速排序
void QuickSort(int num[], int length) {
	int key;
	//三值取中（史山运算）
	key = num[0] > num[length - 1] ? num[0]<num[length / 2] ? 0 : num[length / 2]>num[length - 1] ? length / 2 : length - 1 : num[0] > num[length / 2] ? 0 : num[length / 2] > num[length - 1] ? length - 1 : length / 2;
	//把该中值放在首位，确保指针运动规律不变
	if (key != 0) {
		num[key] += num[0];
		num[0] = num[key] - num[0];
		num[key] = num[key] - num[0];
	}

	//模拟栈的作用，记录需要回溯的数据，分别是low和high
	int* stack = (int*)malloc(length * sizeof(int));
	for (int i = 0; i < length; i++) stack[i] = -1;
	//入栈
	stack[0] = 0;
	stack[1] = length - 1;
	int count = 2;

	while (count) {
		//printf("%d\n", count / 2);
		//模拟出栈
		int low = stack[count - 2];
		int high = stack[count - 1];
		stack[count - 1] = stack[count - 2] = -1;
		count -= 2;

		//填坑法
		int value = num[low];
		int i = low, j = high;
		while (j > i) {
			while (num[j] >= value && j > i) j--;
			j > i ? num[i] = num[j] : NULL;
			while (num[i] <= value && j > i) i++;
			j > i ? num[j] = num[i] : NULL;
		}
		num[i] = value;//i为所求中间值

		//模拟递归入栈
		if (low < i - 1) {
			stack[count++] = low;
			stack[count++] = i - 1;
		}
		if (i + 1 < high) {
			stack[count++] = i + 1;
			stack[count++] = high;
		}
	}
	free(stack);
	stack = NULL;
}

//计数排序
void CountSort(int num[], int length) {
	//初始化计数数组
	int* countNum = (int*)malloc(100000 * sizeof(int));
	for (int i = 0; i < 100000; i++) countNum[i] = 0;
	//计数
	for (int i = 0; i < length; i++) {
		countNum[num[i]]++;
	}
	//排序
	for (int i = 0, j = 0; i < length; i++) {
		while (countNum[j] == 0) j++;
		countNum[j]--;
		num[i] = j;
	}
	free(countNum);
}

//基数计数排序
void RadixCountSort(int num[], int length) {
	//创建临时数组和计数器
	int* temp1 = num;
	int* temp2 = (int*)malloc(length * sizeof(int));
	int* countNum = (int*)malloc(10 * sizeof(int));
	for (int Radix = 1; Radix <= 10000; Radix *= 10) {
		//每次计数前需要对计数器初始化
		for (int i = 0; i < 10; i++) countNum[i] = 0;
		//计数
		for (int i = 0; i < length; i++) countNum[(temp1[i] / Radix) % 10]++;
		//记录相对位置
		for (int i = 1; i < 10; i++) countNum[i] += countNum[i - 1];
		//在该Radix下排序
		for (int i = length - 1; i >= 0; i--) {
			int k = (temp1[i] / Radix) % 10;
			temp2[countNum[k] - 1] = temp1[i];
			countNum[k]--;
		}
		//指针地址交换，确保上面循环中的temp1为待排序数组、temp2为已排序数组
		int* temp = temp1;
		temp1 = temp2;
		temp2 = temp;
	}
	if (temp1 != num) {
		for (int i = 0; i < length; i++)
			num[i] = temp1[i];
		temp2 = temp1;
	}
	free(temp2);
}