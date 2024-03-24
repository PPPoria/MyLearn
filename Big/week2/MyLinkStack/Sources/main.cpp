#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.system.h>
#include"LinkStack.h"

int main() {
	srand((unsigned int)time(NULL));//初始化种子
	int length = 0;
	ElemType data;
	LinkStack linkStack;//初始化链栈
	initLStack(&linkStack);
	while (true) {
		int choise = 0;
		printf("\n-----OK啊，本次依然是为了方便，数据均为随机输入-----\n\n");
		printf("1--入栈    2--出栈    3--求栈顶元素\n4--清空栈  5--销毁栈\n\n");
		printf("当前栈长为 %d，请选择功能：", length);
		while (!scanf_s("%d", &choise)) getchar();
		switch (choise) {
		case 1: {
			int num = -1;
			while (num < 0) {
				printf("请输入想要入栈的数量：");
				scanf_s("%d", &num);
			}
			while (num--)pushLStack(&linkStack, rand());
			break;
		}
		case 2: {
			int num = -1;
			while (num < 0) {
				printf("请输入想要出栈的数量（大于或等于栈长则全部出栈）：");
				scanf_s("%d", &num);
			}
			printf("出栈数据如下：\n");
			if (num >= length) num = length;
			while (num--) {
				popLStack(&linkStack, &data);
				printf("%d\n", data);
			}
			break;
		}
		case 3: {
			if (getTopLStack(&linkStack, &data))
				printf("栈顶元素为%d\n", data);
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