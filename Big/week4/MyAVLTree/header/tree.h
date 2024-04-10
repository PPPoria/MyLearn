#pragma once
#include<stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int bf = 0;//平衡因子（左减右）
	int value;//数据
	TreeNode* parentNode = NULL;//双亲
	TreeNode* LNode = NULL, * RNode = NULL;//左右孩子指针
}TreeNode;

//TreeNode* root = NULL;


bool insert(TreeNode* newNode);//插入新结点
bool isExistent(int value);//查找是否存在
bool delNode(int value);//删除结点
TreeNode* returnNode();//回调
TreeNode* createNewNode(int value);//创造结点
void preTraversal();//前
void midTraversal();//中
void postTraversal();//后序遍历
void levelTraversal();//层序遍历
void LL_rotate(TreeNode* parent);//右旋
void LR_rotate(TreeNode* parent);//左右旋
void RL_rotate(TreeNode* parent);//右左旋
void RR_rotate(TreeNode* parent);//左旋