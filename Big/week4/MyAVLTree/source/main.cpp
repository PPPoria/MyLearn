#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
#include<windows.system.h>

//TreeNode* root = NULL;

int main() {
	while (1) {
		printf("\n-------AVLTree-------\n");
		printf("1--插入整数    2--查找整数    3--删除整数\n");
		printf("4--先序遍历    5--中序遍历    6--后序遍历    7--层序遍历\n");
		printf("请输入选项：");
		int chooce;
		scanf_s("%d", &chooce);
		switch (chooce) {
		case 1: {
			printf("支持多个输入，请用空格隔开，“0”为结束输入\n");
			int value;
			while (1) {
				scanf_s("%d", &value);
				if (value == 0) break;
				insert(createNewNode(value));
			}
			break;
		}
		case 2: {
			printf("请输入查找的整数：");
			int value;
			scanf_s("%d", &value);
			if (isExistent(value)) printf("存在\n");
			else printf("不存在\n");
			break;
		}
		case 3: {
			printf("请输入删除的整数：");
			int value;
			scanf_s("%d", &value);

			if (delNode(value)) printf("成功\n");
			else printf("整数不存在\n");
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