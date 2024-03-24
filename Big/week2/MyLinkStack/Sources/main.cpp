#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.system.h>
#include"LinkStack.h"

int main() {
	srand((unsigned int)time(NULL));//��ʼ������
	int length = 0;
	ElemType data;
	LinkStack linkStack;//��ʼ����ջ
	initLStack(&linkStack);
	while (true) {
		int choise = 0;
		printf("\n-----OK����������Ȼ��Ϊ�˷��㣬���ݾ�Ϊ�������-----\n\n");
		printf("1--��ջ    2--��ջ    3--��ջ��Ԫ��\n4--���ջ  5--����ջ\n\n");
		printf("��ǰջ��Ϊ %d����ѡ���ܣ�", length);
		while (!scanf_s("%d", &choise)) getchar();
		switch (choise) {
		case 1: {
			int num = -1;
			while (num < 0) {
				printf("��������Ҫ��ջ��������");
				scanf_s("%d", &num);
			}
			while (num--)pushLStack(&linkStack, rand());
			break;
		}
		case 2: {
			int num = -1;
			while (num < 0) {
				printf("��������Ҫ��ջ�����������ڻ����ջ����ȫ����ջ����");
				scanf_s("%d", &num);
			}
			printf("��ջ�������£�\n");
			if (num >= length) num = length;
			while (num--) {
				popLStack(&linkStack, &data);
				printf("%d\n", data);
			}
			break;
		}
		case 3: {
			if (getTopLStack(&linkStack, &data))
				printf("ջ��Ԫ��Ϊ%d\n", data);
			break;
		}
		case 4: {
			printf("OK!\n");
			clearLStack(&linkStack);
			break;
		}
		case 5: {
			printf("OK!\n");
			destroyLStack(&linkStack);
			break;
		}
		default:break;
		};
		LStackLength(&linkStack, &length);
		system("pause");
		system("cls");
	}
}