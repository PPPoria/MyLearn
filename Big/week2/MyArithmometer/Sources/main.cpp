#include"Arithmometer.h"
#include<stdlib.h>
#include<stdio.h> 

int main() {
	LS* p;
	printf("����ȷ������ʽ����=����Ϊ�������ţ����磺6+(4-2)*3+9/3=\n");
	/*
	test:  6+(4-2)*3+9/3
	*/
	p = InfixToSuffix();
	printf("%.3f\n", Compute(p));
	return 0;
}