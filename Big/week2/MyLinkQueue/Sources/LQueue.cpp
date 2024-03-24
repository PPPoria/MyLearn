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
	if (IsEmptyLQueue(Q)) return;//����Ƿ�ǿ�
	Node* ptr;
	ptr = Q->front;
	while (ptr) {//�ݹ�����
		Q->front = Q->front->next;
		free(ptr->data);
		free(ptr);
		ptr = Q->front;
	}
	InitLQueue(Q);//��ɺ�����г�ʼ��
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
	while (ptr) {//�ݹ�
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
	if (IsEmptyLQueue(Q)) {//���ӿգ���ͷβ���βͬһ�����
		Q->front = Q->rear = ptr;
		return TRUE;
	}
	Q->rear->next = ptr;//����ֱ��β�Ӽ���
	Q->rear = ptr;
	return TRUE;
}

Status DeLQueue(LQueue* Q) {
	if (IsEmptyLQueue(Q)) return FALSE;//�ն����޷����г���
	Node* ptr;
	ptr = Q->front;
	Q->front = Q->front->next;
	free(ptr);
	if (IsEmptyLQueue(Q))//�����Ӻ����޽�㣬���ʼ��
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
		printf("��������Ҫ�洢�����ݵ����ͣ�Ŀǰ��֧��float��string��");
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
		printf("\n-----��ǰ��������Ϊ<%s>,�ӵĳ���Ϊ %d -----\n\n", datatype, Q.length);
		printf("1--����    2--����    3--���ͷԪ��\n4--��ն�  5--���ٶ�\n");
		printf("������ѡ��");
		scanf_s("%d", &choise);
		switch (choise) {
		case 1: {
			void* data;
			printf("���������ݣ�");
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