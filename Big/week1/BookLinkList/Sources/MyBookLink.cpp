#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"MyBookLink.h"

book* createSingleLinkList(int n) {
	book* head = NULL, * p1 = NULL, * p2 = NULL;
	//srand((unsigned int)time(NULL));//产生随机种子

	//若想要生产的链表结点数为零，则返回NULL
	if (n == 0) return NULL;

	head = p1 = p2 = (book*)malloc(sizeof(book));
	//检查指针是否为空,防止异常
	assert(head);
	//随机赋值
	p1->ISBN = rand() % 100000;
	p1->price = (float)(rand() % 1000) / 10.0;
	//单链表无须使用prior指针，在此为了方便就简单赋值NULL
	p1->prior = NULL;
	for (int i = 1; i < n; i++) {
		p2 = (book*)malloc(sizeof(book));
		assert(p2);
		p2->ISBN = rand() % 100000;
		p2->price = (float)(rand() % 1000) / 10.0;
		p2->prior = NULL;

		p1->next = p2;
		p1 = p2;
	}
	p1->next = NULL;

	return head;
}
book* createDoubleLinkList(int n) {
	book* head = NULL, * p1 = NULL, * p2 = NULL;
	//srand((unsigned int)time(NULL));//产生随机种子

	//若想要生产的链表结点数为零，则返回NULL
	if (n == 0) return NULL;

	head = p1 = p2 = (book*)malloc(sizeof(book));
	//检查指针是否为空
	assert(head);
	//随机赋值
	p1->ISBN = rand() % 100000;
	p1->price = (float)(rand() % 1000) / 10.0;
	//头结点prior不指向任何结点
	p1->prior = NULL;
	for (int i = 1; i < n; i++) {
		p2 = (book*)malloc(sizeof(book));
		assert(p2);
		p2->ISBN = rand() % 100000;
		p2->price = (float)(rand() % 1000) / 10.0;
		p2->prior = p1;

		p1->next = p2;
		p1 = p2;
	}
	p1->next = NULL;

	return head;
}
book* tailOfList(book* head) {
	book* tail = head;
	//无头结点即返回NULL
	if (tail == NULL) return NULL;
	//指针遍历
	while (tail->next) tail = tail->next;
	return tail;
}

book* addSingleNode(book* head, int n, int ISBN, float price) {
	book* p1, * p2;
	p1 = head;
	//创建并检查
	p2 = (book*)malloc(sizeof(book));
	assert(p2);
	p2->prior = NULL;
	p2->ISBN = ISBN;
	p2->price = price;
	//若传递的链表长度为零，则将新结点当链表头
	if (p1 == NULL) {
		p2->next = NULL;
		return p2;
	}
	//当n小于等于一时，将新结点作为新头结点
	if (n <= 1) {
		p2->next = p1;
		head = p2;
		return head;
	}
	//i取2可以让指针指向目标位置的前一个结点
	for (int i = 2; i < n; i++) {
		//当n超过长度时，指针最终指向尾结点，将新结点添加到链表尾
		if (p1->next == NULL) break;
		p1 = p1->next;
	}
	p2->next = p1->next;
	p1->next = p2;
	return head;
}
book* deleteSingleNode(book* head, int n) {
	book* p = head, * temp;
	if (!p) return NULL;
	if (n <= 1) {
		temp = head;
		head = temp->next;
		free(temp);
		return head;
	}
	for (int i = 2; i < n; i++) {
		if (p->next->next == NULL) return head;
		p = p->next;
	}
	temp = p->next;
	p->next = temp->next;
	free(temp);
	return head;
}
book* addDoubleNode(book* head, int n, int ISBN, float price) {
	book* p1, * p2;
	p1 = head;
	//创建并检查
	p2 = (book*)malloc(sizeof(book));
	assert(p2);
	p2->ISBN = ISBN;
	p2->price = price;
	//若传递的链表长度为零，则将新结点当链表头
	if (p1 == NULL) {
		p2->next = NULL;
		p2->prior = NULL;
		return p2;
	}
	//当n小于等于一时，将新结点作为新头结点
	if (n <= 1) {
		p2->prior = NULL;
		p2->next = p1;
		p1->prior = p2;
		head = p2;
		return head;
	}
	//i取2可以让指针指向目标位置的前一个结点
	for (int i = 2; i < n; i++) {
		//当n超过长度时，指针最终指向尾结点，将新结点添加到链表尾
		if (p1->next == NULL) break;
		p1 = p1->next;
	}
	p2->next = p1->next;
	p2->prior = p1;
	p1->next = p2;
	//若新结点的位置不是末尾，则将其下一个结点的prior指向自己,实现双向
	if (p2->next) p2->next->prior = p2;
	return head;
}
book* deleteDoubleNode(book* head, int n) {
	book* p = head, * temp;
	if (!p) return NULL;
	if (n <= 1) {
		temp = head;
		head = temp->next;
		free(temp);
		//改变新表头的prior
		if (head) head->prior = NULL;
		return head;
	}
	for (int i = 2; i < n; i++) {
		if (p->next->next == NULL) return head;
		p = p->next;
	}
	temp = p->next;
	p->next = temp->next;
	free(temp);
	if (p->next) p->next->prior = p;
	return head;
}
book* check(book* head, int ISBN) {
	book* p = head;
	while (p) {
		if (p->ISBN == ISBN) {
			printf("找到力！ISBN号为%d的书籍的价格为%.2f\n！", ISBN, p->price);
			return head;
		}
		p = p->next;
	}
	return head;
}
book* modify(book* head, int ISBN) {
	book* p = head;
	bool key = 0;
	float price;
	while (p) {
		if (p->ISBN == ISBN) {
			key = 1;
			break;
		}
		p = p->next;
	}
	if (key) {
		printf("ISBN号为%d的书籍的原价格为%.2f，请输入新价格：", ISBN, p->price);
		while (!scanf_s("%f", &price)) getchar();
		printf("OK!\n");
	}
	return head;
}
book* oddEvenInterchange(book* head) {
	if (!head) return NULL;
	book* p1, * p2, * p3;
	p1 = p2 = p3 = head;
	int n = 0;
	//计算长度
	while (p1) {
		p1 = p1->next;
		n++;
	}
	p1 = head;
	if (n & 1) {
		printf("长度为奇数，无法交换!\n");
		return head;
	}
	head = head->next;
	if (n == 2) {
		p1->next->next = p1;
		p1->next = NULL;
		return head;
	}
	while (p1->next->next) {
		p2 = p1->next;
		p3 = p2->next;
		p2->next = p1;
		p1->next = p3->next;
		p1 = p2 = p3;
	}
	p1->next->next = p1;
	p1->next = NULL;
	return head;
}
book* midpoint(book* head) {
	if (!head) return head;
	book* slow, * fast;
	slow = fast = head;
	while (fast->next) {
		slow = slow->next;
		fast = fast->next;
		if (fast->next) fast = fast->next;
	}
	return slow;
}
book* reverse(book* head) {
	if (!head) return head;
	book* p1, * p2, * p3;
	p1 = NULL; p2 = p3 = head;
	while (p2->next) {
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	head = p2;
	head->next = p1;
	return head;
}

void linkListPrint(book* head) {
	book* p = head;
	while (p) {
		printf("%8d%8.2f\n", p->ISBN, p->price);
		p = p->next;
	}
}
bool isCircular(book* head) {
	if (!head) return head;
	book* slow, * fast;
	slow = fast = head;
	slow = slow->next;
	fast = fast->next;
	if (fast->next) fast = fast->next;
	while (fast->next) {
		slow = slow->next;
		fast = fast->next;
		if (fast->next) fast = fast->next;
		if (slow == fast) return 1;
	}
	return 0;
}