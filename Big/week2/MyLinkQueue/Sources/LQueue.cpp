#include<stdio.h>
#include<stdlib.h>
#include"LQueue.h"
#include<cassert>
#include<string.h>
#include<windows.system.h>

void InitLQueue(LQueue* Q) {
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
}

void DestoryLQueue(LQueue* Q) {
	if (IsEmptyLQueue(Q)) return;//检测是否非空
	Node* ptr;
	ptr = Q->front;
	while (ptr) {//递归销毁
		Q->front = Q->front->next;
		free(ptr->data);
		free(ptr);
		ptr = Q->front;
	}
	InitLQueue(Q);//完成后则进行初始化
}

Status IsEmptyLQueue(const LQueue* Q) {
	if (Q->front == NULL) return TRUE;
	return FALSE;
}

Status GetHeadLQueue(LQueue* Q, void** e) {
	if (IsEmptyLQueue(Q) || Q->front->data == NULL) return FALSE;
	*e = Q->front->data;
	return TRUE;
}

int LengthLQueue(LQueue* Q) {
	Node* ptr;
	int length = 0;
	ptr = Q->front;
	while (ptr) {//递归
		ptr = ptr->next;
		length++;
	}
	return length;
}

Status EnLQueue(LQueue* Q, void* data) {
	Node* ptr;
	ptr = (Node*)malloc(sizeof(Node));
	assert(ptr);
	ptr->data = data;
	ptr->next = NULL;
	if (IsEmptyLQueue(Q)) {//若队空，则头尾结点尾同一个结点
		Q->front = Q->rear = ptr;
		return TRUE;
	}
	Q->rear->next = ptr;//否则直接尾接即可
	Q->rear = ptr;
	return TRUE;
}

Status DeLQueue(LQueue* Q) {
	if (IsEmptyLQueue(Q)) return FALSE;//空队则无法进行出队
	Node* ptr;
	ptr = Q->front;
	Q->front = Q->front->next;
	free(ptr);
	if (IsEmptyLQueue(Q))//若出队后已无结点，则初始化
		InitLQueue(Q);
	return TRUE;
}

void ClearLQueue(LQueue* Q) {
	if (IsEmptyLQueue(Q)) return;
	Node* ptr;
	ptr = Q->front;
	while (ptr) {
		free(ptr->data);
		ptr->data = NULL;
		ptr = ptr->next;
	}
}

Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q)) {
	if (IsEmptyLQueue(Q)) return FALSE;
	Node* ptr;
	ptr = Q->front;
	while (ptr) {
		(*foo)(ptr);
		ptr = ptr->next;
	}
	return TRUE;
}

void LPrint(void* data) {
	if (type == 'f') printf("%.3f\n", *(float*)data);
	else if (type == 's') printf("%s\n", (char*)data);
}

int main() {
	LQueue Q;
	InitLQueue(&Q);
	char f[] = "float", s[] = "string";
	while (type == '?') {
		printf("请输入想要存储的数据的类型，目前仅支持float或string：");
		scanf_s("%s", datatype, 30);
		//printf("%s\n", datatype);
		//printf("%d\n", strcmp(datatype, f));
		//printf("%d\n", strcmp(datatype, s));
		if (!strcmp(datatype, "float")) type = 'f';
		else if (!strcmp(datatype, "string")) type = 's';
	}
	//system("pause");
	system("cls");
	while (true) {
		int choise = 0;
		//void* userInput;
		printf("\n-----当前数据类型为<%s>,队的长度为 %d -----\n\n", datatype, Q.length);
		printf("1--进队    2--出队    3--求对头元素\n4--清空队  5--销毁队\n");
		printf("请输入选择：");
		scanf_s("%d", &choise);
		switch (choise) {
		case 1: {
			void* data;
			printf("请输入数据：");
			if (type == 'f') {
				data = (float*)malloc(sizeof(float));
				scanf_s("%f", (float*)data);
			}
			else {
				data = (char*)malloc(30 * sizeof(char));
				scanf_s("%s", (char*)data, 30);
			}
			assert(data);
			EnLQueue(&Q, data);
			break;
		}
		case 2: {
			printf("OK!\n");
			DeLQueue(&Q);
			break;
		}
		case 3: {
			void* data;
			if (GetHeadLQueue(&Q, &data))
				LPrint(data);
			else printf("NULL\n");
			break;
		}
		case 4: {
			printf("OK!\n");
			ClearLQueue(&Q);
			break;
		}
		case 5: {
			printf("OK!\n");
			DestoryLQueue(&Q);
			break;
		}
		default:break;
		}
		Q.length = LengthLQueue(&Q);
		system("pause");
		system("cls");
	}
	return 0;
}