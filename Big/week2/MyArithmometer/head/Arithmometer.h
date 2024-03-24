#pragma once
#include<stdio.h>

typedef struct LS {
	float n = 0;
	char c = NULL;
	LS* next = NULL;
}LS;

//LS* popFromTop(LS* ls);//出栈
bool isPriority(LS* infix, char c);//判断优先级
LS* InfixToSuffix();//中缀转后缀
float CalculateWithSymbol(LS* numberNode1, LS* symbolrNode, LS* numberNode2);//转变符号用于计算
float Compute(LS* suffix);//总后缀计算