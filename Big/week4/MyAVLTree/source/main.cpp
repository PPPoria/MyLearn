#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
#include<windows.system.h>

//TreeNode* root = NULL;

int main() {
	while (1) {
		printf("\n-------AVLTree-------\n");
		printf("1--��������    2--��������    3--ɾ������\n");
		printf("4--�������    5--�������    6--�������    7--�������\n");
		printf("������ѡ�");
		int chooce;
		scanf_s("%d", &chooce);
		switch (chooce) {
		case 1: {
			printf("֧�ֶ�����룬���ÿո��������0��Ϊ��������\n");
			int value;
			while (1) {
				scanf_s("%d", &value);
				if (value == 0) break;
				insert(createNewNode(value));
			}
			break;
		}
		case 2: {
			printf("��������ҵ�������");
			int value;
			scanf_s("%d", &value);
			if (isExistent(value)) printf("����\n");
			else printf("������\n");
			break;
		}
		case 3: {
			printf("������ɾ����������");
			int value;
			scanf_s("%d", &value);

			if (delNode(value)) printf("�ɹ�\n");
			else printf("����������\n");
			break;
		}
		case 4: {
			preTraversal();
			break;
		}
		case 5: {
			midTraversal();
			break;
		}
		case 6: {
			postTraversal();
			break;
		}
		case 7: {
			levelTraversal();
			break;
		}
		}
		system("pause");
		system("cls");
	}

	return 0;
}