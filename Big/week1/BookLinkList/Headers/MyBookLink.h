#pragma once
typedef struct BookNode {
	int ISBN;
	float price;
	struct BookNode* prior;
	struct BookNode* next;
} book;
book* createSingleLinkList(int n);
book* createDoubleLinkList(int n);
book* tailOfList(book* head);

book* addSingleNode(book* head, int n, int ISBN, float price);
book* deleteSingleNode(book* head, int n);
book* addDoubleNode(book* head, int n, int ISBN, float price);
book* deleteDoubleNode(book* head, int n);
book* check(book* head, int ISBN);
book* modify(book* head, int ISBN);
book* oddEvenInterchange(book* head);
book* midpoint(book* head);
book* reverse(book* head);

void linkListPrint(book* head);
bool isCircular(book* head);
