#pragma once

int SortTiming(void(*Sort)(int*, int), int num[], int length);//计时器
bool ReadTestData(int num[]);//读取文件，若无则创建
bool isOrderly(int num[], int length);//判断该数组的length长度内是否有序（通常为从小到大/正序）
void InsertSort(int num[], int length);//插入排序
void MergeSort(int num[], int length);//归并排序
void QuickSort(int num[], int length);//三值取中优化快速排序(非递归)
void CountSort(int num[], int length);//计数排序
void RadixCountSort(int num[], int length);//基数计数排序
