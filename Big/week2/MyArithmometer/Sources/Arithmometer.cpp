#include"Arithmometer.h"
#include<stdlib.h>
#include<stdio.h> 

//LS* popFromTop(LS* ls) {}

//�ж����ȼ�
bool isPriority(LS* infix, char c) {
	if (infix == NULL) return 1;
	if (infix->c == '(') return 1;
	if ((c == '*' || c == '/') && (infix->c == '+' || infix->c == '-')) return 1;
	return 0;
}

//��׺ת��׺
LS* InfixToSuffix() {
	LS* infix = NULL, * suffix = NULL, * p = NULL;
	char c = NULL;
	int n = 0;
	bool key = 0;

	while (c != '=') {
		c = NULL;
		n = 0;
		key = 0;

		//���ַ���ת�����β��洢����
		while (c == NULL) {
			scanf_s("%c", &c);
			if ('0' <= c && c <= '9') {
				n *= 10;
				n += c - '0';
				c = NULL;
				key = 1;//��¼�����Ƿ����
			}
		}

		//�������������ڣ��򲻿����νڵ�
		if (key) {
			p = (LS*)malloc(sizeof(LS));
			p->n = n * 1.0;
			p->next = suffix;
			suffix = p;
		}

		p = (LS*)malloc(sizeof(LS));
		//������ж�
		if (c == '(') {//������ֱ����ջ
			p->c = c;
			p->next = infix;
			infix = p;
		}
		else if (c == ')') {//������������ջ����Ϊ��������м�ķ��ŵ��ź�
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
		else if (c != '=') {//�ж����ȼ������
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
	//����ջ�ڵ�ʣ�����һһ��ջ
	while (infix) {
		p = infix;
		infix = infix->next;
		p->next = suffix;
		suffix = p;
	}
	return suffix;
}

//ת��������ڼ���
float CalculateWithSymbol(LS* numberNode1, LS* symbolrNode, LS* numberNode2) {
	if (symbolrNode->c == '*') return (float)numberNode1->n * numberNode2->n;
	if (symbolrNode->c == '/') return (float)numberNode1->n / numberNode2->n;
	if (symbolrNode->c == '+') return (float)numberNode1->n + numberNode2->n;
	if (symbolrNode->c == '-') return (float)numberNode1->n - numberNode2->n;
}

//��׺����
float Compute(LS* suffix) {
	LS* p1, * p2; LS* temp = suffix;
	while (suffix->next->next->next != NULL) {//�ж��Ƿ�ʣ��������
		p1 = p2 = suffix;
		while (p1->next != NULL) {//�ҳ���ײ��ķ���
			if (p1->next->c == '+' || p1->next->c == '-' || p1->next->c == '*' || p1->next->c == '/')
				p2 = p1;
			p1 = p1->next;
		}
		p1 = p2->next->next->next;//����
		p1->n = CalculateWithSymbol(p1, p2->next, p2->next->next);
		free(p2->next->next);//�ͷſռ�
		free(p2->next);
		p2->next = p1;
	}
	return CalculateWithSymbol(suffix->next->next, suffix, suffix->next);//�������������������
}