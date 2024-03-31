#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include"SortHeader.h"

//��ʱ��
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

//��ȡ�ļ��������򴴽�
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

//�жϸ������length�������Ƿ�����
bool isOrderly(int num[], int length) {
	for (int i = 1; i < length; i++) {
		if (num[i] < num[i - 1]) return 0;
	}
	return 1;
}

//��������
void InsertSort(int num[], int length) {
	int j;
	int insertNum;
	for (int i = 1; i < length; i++) {
		j = i;
		insertNum = num[i];//����Ҫ�������ȡ��
		while (j && insertNum < num[j - 1]) {//������λ��֮�������ȡ�����Ŀ�λ�ƶ�
			num[j] = num[j - 1];
			j--;
		}
		num[j] = insertNum;//����
	}
}

//�鲢����
void MergeSort(int num[], int length) {
	int* temp1 = num;
	int* temp2 = (int*)malloc(length * sizeof(int));
	for (int lengthPerGroup = 1; lengthPerGroup < length; lengthPerGroup *= 2) {
		for (int startOfGroup = 0; startOfGroup < length; startOfGroup += lengthPerGroup * 2) {
			//ȡ��С��ķ�Χ
			int low = startOfGroup;
			int k = low;
			int mid = startOfGroup + lengthPerGroup;
			mid = mid < length ? mid : length;//��ֹ������Χ
			int high = startOfGroup + lengthPerGroup * 2;
			high = high < length ? high : length;//ͬ��

			//����С���ٷ������������򲢺ϲ�
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				temp2[k++] = temp1[start1] < temp1[start2] ? temp1[start1++] : temp1[start2++];
			//����������ʣ��Ԫ�������С����
			while (start1 < end1)
				temp2[k++] = temp1[start1++];
			while (start2 < end2)
				temp2[k++] = temp1[start2++];
		}
		//ָ���ַ������ȷ������ѭ���е�temp1Ϊ���������顢temp2Ϊ����������
		int* temp = temp1;
		temp1 = temp2;
		temp2 = temp;
		//�����ڵ�temp1Ϊ��������ѭ���󲿷�����õ�����
	}

	if (temp1 != num) {
		for (int i = 0; i < length; i++)
			num[i] = temp1[i];
		temp2 = temp1;
	}
	free(temp2);
}

//��������
void QuickSort(int num[], int length) {
	int key;
	//��ֵȡ�У�ʷɽ���㣩
	key = num[0] > num[length - 1] ? num[0]<num[length / 2] ? 0 : num[length / 2]>num[length - 1] ? length / 2 : length - 1 : num[0] > num[length / 2] ? 0 : num[length / 2] > num[length - 1] ? length - 1 : length / 2;
	//�Ѹ���ֵ������λ��ȷ��ָ���˶����ɲ���
	if (key != 0) {
		num[key] += num[0];
		num[0] = num[key] - num[0];
		num[key] = num[key] - num[0];
	}

	//ģ��ջ�����ã���¼��Ҫ���ݵ����ݣ��ֱ���low��high
	int* stack = (int*)malloc(length * sizeof(int));
	for (int i = 0; i < length; i++) stack[i] = -1;
	//��ջ
	stack[0] = 0;
	stack[1] = length - 1;
	int count = 2;

	while (count) {
		//printf("%d\n", count / 2);
		//ģ���ջ
		int low = stack[count - 2];
		int high = stack[count - 1];
		stack[count - 1] = stack[count - 2] = -1;
		count -= 2;

		//��ӷ�
		int value = num[low];
		int i = low, j = high;
		while (j > i) {
			while (num[j] >= value && j > i) j--;
			j > i ? num[i] = num[j] : NULL;
			while (num[i] <= value && j > i) i++;
			j > i ? num[j] = num[i] : NULL;
		}
		num[i] = value;//iΪ�����м�ֵ

		//ģ��ݹ���ջ
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

//��������
void CountSort(int num[], int length) {
	//��ʼ����������
	int* countNum = (int*)malloc(100000 * sizeof(int));
	for (int i = 0; i < 100000; i++) countNum[i] = 0;
	//����
	for (int i = 0; i < length; i++) {
		countNum[num[i]]++;
	}
	//����
	for (int i = 0, j = 0; i < length; i++) {
		while (countNum[j] == 0) j++;
		countNum[j]--;
		num[i] = j;
	}
	free(countNum);
}

//������������
void RadixCountSort(int num[], int length) {
	//������ʱ����ͼ�����
	int* temp1 = num;
	int* temp2 = (int*)malloc(length * sizeof(int));
	int* countNum = (int*)malloc(10 * sizeof(int));
	for (int Radix = 1; Radix <= 10000; Radix *= 10) {
		//ÿ�μ���ǰ��Ҫ�Լ�������ʼ��
		for (int i = 0; i < 10; i++) countNum[i] = 0;
		//����
		for (int i = 0; i < length; i++) countNum[(temp1[i] / Radix) % 10]++;
		//��¼���λ��
		for (int i = 1; i < 10; i++) countNum[i] += countNum[i - 1];
		//�ڸ�Radix������
		for (int i = length - 1; i >= 0; i--) {
			int k = (temp1[i] / Radix) % 10;
			temp2[countNum[k] - 1] = temp1[i];
			countNum[k]--;
		}
		//ָ���ַ������ȷ������ѭ���е�temp1Ϊ���������顢temp2Ϊ����������
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