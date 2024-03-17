#include<stdio.h>
#include<windows.system.h>
#include"MyBookLink.h"

//默认长度
#define N 10

void window(book* sHead, book* dHead) {
	printf("~~结点含ISBN（整数）和价格，方便起见默认链表长度为10且所有数据都是随机输入的~~\n\n");
	printf("单向链表：1--增  2--删  3--奇偶互换  4--是否环形  5--逆转\n双向链表：6--增  7--删\n二者通用：8--查  9--改  10--打印所有书籍ISBN号和价格\n"); printf("请选择功能：\n");
	int choice;
	while (!scanf_s("%d", &choice)) getchar();
	switch (choice)
	{
	case 1: {
		int ISBN, n; float price;
		printf("请输入增加的新书籍在表中的位置以及ISBN号和价格：（均用空格隔开）\n");
		scanf_s("%d%d%f", &n, &ISBN, &price);
		sHead = addSingleNode(sHead, n, ISBN, price);
		printf("OK!\n");
		break;
	}
	case 2: {
		int n;
		printf("请输入需要删除的书籍的位置：（不大于链表长度）\n");
		scanf_s("%d", &n);
		sHead = deleteSingleNode(sHead, n);
		printf("OK!\n");
		break;
	}
	case 3: {
		sHead = oddEvenInterchange(sHead);
		printf("OK!\n");
		break;
	}
	case 4: {
		if (isCircular(sHead)) printf("YES\n");
		else printf("NO\n");
		break;
	}
	case 5: {
		sHead = reverse(sHead);
		printf("OK!\n");
		break;
	}
	case 6: {
		int ISBN, n; float price;
		printf("请输入增加的新书籍在表中的位置以及ISBN号和价格：（均用空格隔开）\n");
		scanf_s("%d%d%f", &n, &ISBN, &price);
		dHead = addDoubleNode(dHead, n, ISBN, price);
		printf("OK!\n");
		break;
	}
	case 7: {
		int n;
		printf("请输入需要删除的书籍的位置：（不大于链表长度）\n");
		scanf_s("%d", &n);
		dHead = deleteDoubleNode(sHead, n);
		printf("OK!\n");
		break;
	}
	case 8: {
		int ISBN;
		printf("为了方便，仅支持书籍ISBN号（整数）查找，请输入：");
		scanf_s("%d", &ISBN);
		sHead = check(sHead, ISBN);
		dHead = check(dHead, ISBN);
		break;
	}
	case 9: {
		int ISBN;
		printf("为了方便，仅支持书籍ISBN号（整数）查找，请输入：");
		scanf_s("%d", &ISBN);
		sHead = modify(sHead, ISBN);
		dHead = modify(dHead, ISBN);
	}
	case 10: {
		linkListPrint(sHead);
		printf("\n");
		linkListPrint(dHead);
		system("pause");
		break;
	}
	default:
		break;
	}
	Sleep(2000);
	system("cls");
	window(sHead, dHead);
}

int main() {
	book* sHead, * dHead;
	sHead = createSingleLinkList(N);
	dHead = createDoubleLinkList(N);
	window(sHead, dHead);

	return 0;
}