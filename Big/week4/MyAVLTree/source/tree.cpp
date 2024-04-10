#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

extern TreeNode* root = NULL;

//插入新结点
bool insert(TreeNode* newNode) {
	if (newNode == NULL) return FALSE;
	if (root == NULL) {
		root = newNode;
		return TRUE;
	}

	TreeNode* cur, * parent;
	cur = root;
	parent = NULL;

	//找到插入位置
	while (cur) {
		parent = cur;
		if (newNode->value < parent->value) cur = parent->LNode;
		else cur = parent->RNode;
	}

	//插入结点
	if (newNode->value < parent->value) {
		parent->LNode = newNode;
		newNode->parentNode = parent;
	}
	else {
		parent->RNode = newNode;
		newNode->parentNode = parent;
	}

	//调整平衡因子
	cur = newNode;
	while (parent) {
		if (cur == parent->LNode) parent->bf++;
		else parent->bf--;

		if (parent->bf == 0) break;//高度不变则退出
		if (parent->bf == 1 || parent->bf == -1) {//高度改变且未失衡则继续向上检查其双亲
			cur = parent;
			parent = parent->parentNode;
		}
		else {//失衡则进行旋转平衡
			if (parent->bf == 2) {
				if (cur->bf == 1) LL_rotate(parent);
				else LR_rotate(parent);
			}
			else {
				if (cur->bf == 1) RL_rotate(parent);
				else RR_rotate(parent);
			}
			break;
		}
	}
	return TRUE;
}

//查找是否存在
bool isExistent(int value) {
	TreeNode* p = root;
	while (p) {
		if (value == p->value) return TRUE;
		if (value < p->value) p = p->LNode;
		else p = p->RNode;
	}
	return FALSE;
}

//删除结点
bool delNode(int value) {
	//找到要修改的结点
	TreeNode* cur = root;
	TreeNode* parent = cur;
	while (cur) {
		if (value == cur->value) break;
		if (value < cur->value) cur = cur->LNode;
		else cur = cur->RNode;
	}
	if (cur == NULL) return FALSE;

	//找其直接后继
	int* delValuePtr = &(cur->value);
	if (cur->RNode) {
		parent = cur = cur->RNode;
		while (cur) {
			parent = cur;
			cur = cur->LNode;
		}
		cur = parent;
	}

	//交换value
	*delValuePtr = cur->value;

	//将直接后继删去
	if (cur == root) {
		if (cur->LNode) root = cur->LNode;
		else root = NULL;
		free(cur);
		return TRUE;
	}
	parent = cur->parentNode;
	if (cur->RNode) {
		cur->RNode->parentNode = parent;
		if (cur == parent->LNode) { parent->LNode = cur->RNode; free(cur); cur = parent->LNode; parent->bf--; }
		if (cur == parent->RNode) { parent->RNode = cur->RNode; free(cur); cur = parent->RNode; parent->bf++; }
	}
	else if (cur->LNode) {
		cur->LNode->parentNode = parent;
		if (cur == parent->LNode) { parent->LNode = cur->LNode; free(cur); cur = parent->LNode; parent->bf--; }
		if (cur == parent->RNode) { parent->RNode = cur->LNode; free(cur); cur = parent->RNode; parent->bf++; }
	}
	else {
		if (cur == parent->LNode) { parent->LNode = NULL; parent->bf--; }
		if (cur == parent->RNode) { parent->RNode = NULL; parent->bf++; }
		free(cur);
		cur = NULL;
	}

	//调整平衡因子
	while (parent) {
		if (parent->bf == -1) break;//不破坏平衡
		if (parent->bf == 0) {//parent平衡了，说明再往上的平衡可能被破坏，则继续检查
			cur = parent;
			parent = parent->parentNode;
			if (parent)
				if (cur == parent->LNode) parent->bf--;
				else parent->bf++;
		}
		else {//失衡则进行旋转平衡
			if (parent->bf == 2) {
				if (parent->LNode->bf == -1) LR_rotate(parent);
				else LL_rotate(parent);
			}
			else {
				if (parent->RNode->bf == 1) RL_rotate(parent);
				else RR_rotate(parent);
			}
			break;
		}
	}
	return TRUE;
}

//回调
TreeNode* returnNode() {
	return root;
}

//创造结点
TreeNode* createNewNode(int value) {
	if (isExistent(value)) return NULL;
	TreeNode* newNode;
	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->value = value;
	newNode->bf = 0;
	newNode->LNode = NULL;
	newNode->RNode = NULL;
	newNode->parentNode = NULL;
	return newNode;
}

//前
void preTraversal() {
	if (root == NULL) return;
	TreeNode** stack = (TreeNode**)malloc(1000 * sizeof(TreeNode));
	int count = 0;
	stack[0] = root;
	count++;
	//putchar('!');
	while (count) {
		TreeNode* Node = stack[--count];
		printf("%d\n", Node->value);
		if (Node->RNode) stack[count++] = Node->RNode;
		if (Node->LNode) stack[count++] = Node->LNode;
	}
	free(stack);
}

//中
void midTraversal() {
	if (root == NULL) return;
	TreeNode** stack = (TreeNode**)malloc(1000 * sizeof(TreeNode));
	int count = 0;
	TreeNode* Node = root;
	do {
		while (Node) {
			stack[count++] = Node;
			Node = Node->LNode;
		}
		Node = stack[--count];
		printf("%d\n", Node->value);
		Node = Node->RNode;
	} while (count || Node);
	free(stack);
}

//后序遍历
void postTraversal() {
	if (root == NULL) return;
	TreeNode** stack1 = (TreeNode**)malloc(1000 * sizeof(TreeNode));
	TreeNode** stack2 = (TreeNode**)malloc(1000 * sizeof(TreeNode));
	int count1 = 0, count2 = 0;
	TreeNode* Node = root;
	stack1[count1++] = Node;
	while (count1) {
		Node = stack2[count2++] = stack1[--count1];
		if (Node->LNode) stack1[count1++] = Node->LNode;
		if (Node->RNode) stack1[count1++] = Node->RNode;
	}
	while (count2--) {
		printf("%d\n", stack2[count2]->value);
	}
	free(stack1);
	free(stack2);
}

//层序遍历
void levelTraversal() {
	if (root == NULL) return;
	TreeNode** queue = (TreeNode**)malloc(10000 * sizeof(TreeNode));
	int head = 0, tail = 0;
	TreeNode* Node = root;
	queue[tail++] = Node;
	while (head != tail) {
		Node = queue[head++];
		printf("%d\n", Node->value);
		if (Node->LNode) queue[tail++] = Node->LNode;
		if (Node->RNode) queue[tail++] = Node->RNode;
	}
	free(queue);
}

void LL_rotate(TreeNode* parent) {
	TreeNode* grandparent = parent->parentNode, * cur = parent->LNode;
	cur->parentNode = grandparent;

	parent->LNode = cur->RNode;
	if (cur->RNode != NULL)
		cur->RNode->parentNode = parent;
	cur->RNode = parent;
	parent->parentNode = cur;

	if (root == parent) {
		root = cur;
		root->parentNode = NULL;
	}
	else if (parent == grandparent->LNode) grandparent->LNode = cur;
	else grandparent->RNode = cur;
	parent->bf = cur->bf = 0;
}
void LR_rotate(TreeNode* parent) {
	TreeNode* cur = parent->LNode;
	TreeNode* curR = cur->RNode;
	int bf = curR->bf;

	RR_rotate(parent->LNode);
	LL_rotate(parent);

	if (bf == 0)
		curR->bf = cur->bf = parent->bf = 0;
	else if (bf == -1) {
		parent->bf = 0;
		cur->bf = 1;
		curR->bf = 0;
	}
	else if (bf == 1) {
		parent->bf = -1;
		cur->bf = 0;
		curR->bf = 0;
	}
}
void RL_rotate(TreeNode* parent) {
	TreeNode* cur = parent->RNode;
	TreeNode* curL = cur->LNode;
	int bf = curL->bf;

	LL_rotate(parent->RNode);
	RR_rotate(parent);

	if (bf == 0)
		curL->bf = cur->bf = parent->bf = 0;
	else if (bf == -1) {
		parent->bf = 1;
		cur->bf = 0;
		curL->bf = 0;
	}
	else if (bf == 1) {
		parent->bf = 0;
		cur->bf = -1;
		curL->bf = 0;
	}
}
void RR_rotate(TreeNode* parent) {
	TreeNode* grandparent = parent->parentNode, * cur = parent->RNode;
	cur->parentNode = grandparent;

	parent->RNode = cur->LNode;
	if (cur->LNode != NULL)
		cur->LNode->parentNode = parent;
	cur->LNode = parent;
	parent->parentNode = cur;

	if (root == parent) {
		root = cur;
		root->parentNode = NULL;
	}
	else if (parent == grandparent->LNode) grandparent->LNode = cur;
	else grandparent->RNode = cur;
	parent->bf = cur->bf = 0;
}