#pragma once
#include<stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int bf = 0;//ƽ�����ӣ�����ң�
	int value;//����
	TreeNode* parentNode = NULL;//˫��
	TreeNode* LNode = NULL, * RNode = NULL;//���Һ���ָ��
}TreeNode;

//TreeNode* root = NULL;


bool insert(TreeNode* newNode);//�����½��
bool isExistent(int value);//�����Ƿ����
bool delNode(int value);//ɾ�����
TreeNode* returnNode();//�ص�
TreeNode* createNewNode(int value);//������
void preTraversal();//ǰ
void midTraversal();//��
void postTraversal();//�������
void levelTraversal();//�������
void LL_rotate(TreeNode* parent);//����
void LR_rotate(TreeNode* parent);//������
void RL_rotate(TreeNode* parent);//������
void RR_rotate(TreeNode* parent);//����