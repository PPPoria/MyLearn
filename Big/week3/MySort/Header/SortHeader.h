#pragma once

int SortTiming(void(*Sort)(int*, int), int num[], int length);//��ʱ��
bool ReadTestData(int num[]);//��ȡ�ļ��������򴴽�
bool isOrderly(int num[], int length);//�жϸ������length�������Ƿ�����ͨ��Ϊ��С����/����
void InsertSort(int num[], int length);//��������
void MergeSort(int num[], int length);//�鲢����
void QuickSort(int num[], int length);//��ֵȡ���Ż���������(�ǵݹ�)
void CountSort(int num[], int length);//��������
void RadixCountSort(int num[], int length);//������������
