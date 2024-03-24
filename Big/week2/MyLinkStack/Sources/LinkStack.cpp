#include<stdio.h>
#include<stdlib.h>
#include"LinkStack.h"
#include <cassert>


//��ʼ��ջ
Status initLStack(LinkStack* s) {
	s->top = NULL;
	s->count = -1;
	return SUCCESS;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack* s) {
	if (s->top) return ERROR;
	return SUCCESS;
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack* s, ElemType* e) {
	if (isEmptyLStack(s)) return ERROR;
	*e = s->top->data;
	return SUCCESS;
}

//���ջ
Status clearLStack(LinkStack* s) {
	if (isEmptyLStack(s)) return ERROR;
	StackNode* ptr;
	ptr = s->top;
	while (ptr) {
		ptr->data = 0;
		ptr = ptr->next;
	}
	return SUCCESS;
}

//����ջ
Status destroyLStack(LinkStack* s) {
	if (isEmptyLStack(s)) return SUCCESS;
	StackNode* ptr;
	ptr = s->top;
	while (ptr) {
		s->top = s->top->next;
		free(ptr);
		ptr = s->top;
	}
	return SUCCESS;
}

//���ջ����
Status LStackLength(LinkStack* s, int* length) {
	StackNode* ptr;
	ptr = s->top;
	*length = 0;
	while (ptr) {
		(*length)++;
		ptr = ptr->next;
	}
	return SUCCESS;
}

//��ջ
Status pushLStack(LinkStack* s, ElemType data) {
	StackNode* ptr;
	ptr = (StackNode*)malloc(sizeof(LinkStack));
	assert(ptr);
	ptr->data = data;
	ptr->next = s->top;
	s->top = ptr;//�ƶ�ջ��ָ��
	s->count += 1;
	return SUCCESS;
}

//��ջ
Status popLStack(LinkStack* s, ElemType* data) {
	if (isEmptyLStack(s)) return ERROR;
	*data = s->top->data;//��������ջ�����ݴ���
	StackNode* ptr;
	ptr = s->top;
	s->top = s->top->next;//�ƶ�ջ��ָ��
	free(ptr);
	return SUCCESS;
}