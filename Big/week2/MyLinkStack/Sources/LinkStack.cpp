#include<stdio.h>
#include<stdlib.h>
#include"LinkStack.h"
#include <cassert>


//初始化栈
Status initLStack(LinkStack* s) {
	s->top = NULL;
	s->count = -1;
	return SUCCESS;
}

//判断栈是否为空
Status isEmptyLStack(LinkStack* s) {
	if (s->top) return ERROR;
	return SUCCESS;
}

//得到栈顶元素
Status getTopLStack(LinkStack* s, ElemType* e) {
	if (isEmptyLStack(s)) return ERROR;
	*e = s->top->data;
	return SUCCESS;
}

//清空栈
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

//销毁栈
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

//检测栈长度
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

//入栈
Status pushLStack(LinkStack* s, ElemType data) {
	StackNode* ptr;
	ptr = (StackNode*)malloc(sizeof(LinkStack));
	assert(ptr);
	ptr->data = data;
	ptr->next = s->top;
	s->top = ptr;//移动栈顶指针
	s->count += 1;
	return SUCCESS;
}

//出栈
Status popLStack(LinkStack* s, ElemType* data) {
	if (isEmptyLStack(s)) return ERROR;
	*data = s->top->data;//将即将出栈的数据传出
	StackNode* ptr;
	ptr = s->top;
	s->top = s->top->next;//移动栈顶指针
	free(ptr);
	return SUCCESS;
}