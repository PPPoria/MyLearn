#pragma once
#include<stdio.h>

typedef struct LS {
	float n = 0;
	char c = NULL;
	LS* next = NULL;
}LS;

//LS* popFromTop(LS* ls);//��ջ
bool isPriority(LS* infix, char c);//�ж����ȼ�
LS* InfixToSuffix();//��׺ת��׺
float CalculateWithSymbol(LS* numberNode1, LS* symbolrNode, LS* numberNode2);//ת��������ڼ���
float Compute(LS* suffix);//�ܺ�׺����