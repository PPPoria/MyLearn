#include"Arithmometer.h"
#include<stdlib.h>
#include<stdio.h> 

int main() {
	LS* p;
	printf("请正确输入算式，‘=’作为结束符号，例如：6+(4-2)*3+9/3=\n");
	/*
	test:  6+(4-2)*3+9/3
	*/
	p = InfixToSuffix();
	printf("%.3f\n", Compute(p));
	return 0;
}