#include<stdio.h>
#include<windows.system.h>
#include"MyBookLink.h"

//Ĭ�ϳ���
#define N 10

void window(book* sHead, book* dHead) {
	printf("~~��㺬ISBN���������ͼ۸񣬷������Ĭ��������Ϊ10���������ݶ�����������~~\n\n");
	printf("��������1--��  2--ɾ  3--��ż����  4--�Ƿ���  5--��ת\n˫������6--��  7--ɾ\n����ͨ�ã�8--��  9--��  10--��ӡ�����鼮ISBN�źͼ۸�\n"); printf("��ѡ���ܣ�\n");
	int choice;
	while (!scanf_s("%d", &choice)) getchar();
	switch (choice)
	{
	case 1: {
		int ISBN, n; float price;
		printf("���������ӵ����鼮�ڱ��е�λ���Լ�ISBN�źͼ۸񣺣����ÿո������\n");
		scanf_s("%d%d%f", &n, &ISBN, &price);
		sHead = addSingleNode(sHead, n, ISBN, price);
		printf("OK!\n");
		break;
	}
	case 2: {
		int n;
		printf("��������Ҫɾ�����鼮��λ�ã��������������ȣ�\n");
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
		printf("���������ӵ����鼮�ڱ��е�λ���Լ�ISBN�źͼ۸񣺣����ÿո������\n");
		scanf_s("%d%d%f", &n, &ISBN, &price);
		dHead = addDoubleNode(dHead, n, ISBN, price);
		printf("OK!\n");
		break;
	}
	case 7: {
		int n;
		printf("��������Ҫɾ�����鼮��λ�ã��������������ȣ�\n");
		scanf_s("%d", &n);
		dHead = deleteDoubleNode(sHead, n);
		printf("OK!\n");
		break;
	}
	case 8: {
		int ISBN;
		printf("Ϊ�˷��㣬��֧���鼮ISBN�ţ����������ң������룺");
		scanf_s("%d", &ISBN);
		sHead = check(sHead, ISBN);
		dHead = check(dHead, ISBN);
		break;
	}
	case 9: {
		int ISBN;
		printf("Ϊ�˷��㣬��֧���鼮ISBN�ţ����������ң������룺");
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