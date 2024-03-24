#include"Arithmometer.h"
#include<stdlib.h>
#include<stdio.h> 

//LS* popFromTop(LS* ls) {}

//判断优先级
bool isPriority(LS* infix, char c) {
	if (infix == NULL) return 1;
	if (infix->c == '(') return 1;
	if ((c == '*' || c == '/') && (infix->c == '+' || infix->c == '-')) return 1;
	return 0;
}

//中缀转后缀
LS* InfixToSuffix() {
	LS* infix = NULL, * suffix = NULL, * p = NULL;
	char c = NULL;
	int n = 0;
	bool key = 0;

	while (c != '=') {
		c = NULL;
		n = 0;
		key = 0;

		//将字符串转成整形并存储起来
		while (c == NULL) {
			scanf_s("%c", &c);
			if ('0' <= c && c <= '9') {
				n *= 10;
				n += c - '0';
				c = NULL;
				key = 1;//记录数字是否出现
			}
		}

		//若是两符号相邻，则不开整形节点
		if (key) {
			p = (LS*)malloc(sizeof(LS));
			p->n = n * 1.0;
			p->next = suffix;
			suffix = p;
		}

		p = (LS*)malloc(sizeof(LS));
		//各情况判断
		if (c == '(') {//左括号直接入栈
			p->c = c;
			p->next = infix;
			infix = p;
		}
		else if (c == ')') {//右括号无须入栈，作为输出括号中间的符号的信号
			free(p);
			while (infix->c != '(') {
				p = infix;
				infix = infix->next;
				p->next = suffix;
				suffix = p;
			}
			p = infix;
			infix = infix->next;
			free(p);
		}
		else if (c != '=') {//判断优先级以输出
			p->c = c;
			while (!isPriority(infix, c)) {
				p->next = infix;
				infix = infix->next;
				p->next->next = suffix;
				suffix = p->next;
			}
			p->next = infix;
			infix = p;
		}

		//printf("%d%c\n", suffix->n, suffix->c);
	}
	free(p);
	//最后把栈内的剩余符号一一出栈
	while (infix) {
		p = infix;
		infix = infix->next;
		p->next = suffix;
		suffix = p;
	}
	return suffix;
}

//转变符号用于计算
float CalculateWithSymbol(LS* numberNode1, LS* symbolrNode, LS* numberNode2) {
	if (symbolrNode->c == '*') return (float)numberNode1->n * numberNode2->n;
	if (symbolrNode->c == '/') return (float)numberNode1->n / numberNode2->n;
	if (symbolrNode->c == '+') return (float)numberNode1->n + numberNode2->n;
	if (symbolrNode->c == '-') return (float)numberNode1->n - numberNode2->n;
}

//后缀计算
float Compute(LS* suffix) {
	LS* p1, * p2; LS* temp = suffix;
	while (suffix->next->next->next != NULL) {//判断是否还剩下两个数
		p1 = p2 = suffix;
		while (p1->next != NULL) {//找出最底部的符号
			if (p1->next->c == '+' || p1->next->c == '-' || p1->next->c == '*' || p1->next->c == '/')
				p2 = p1;
			p1 = p1->next;
		}
		p1 = p2->next->next->next;//运算
		p1->n = CalculateWithSymbol(p1, p2->next, p2->next->next);
		free(p2->next->next);//释放空间
		free(p2->next);
		p2->next = p1;
	}
	return CalculateWithSymbol(suffix->next->next, suffix, suffix->next);//对最后两个数进行运算
}