#include <stdio.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link; //다른 노드의 주소를 받아야하기때문에 포인트 타입은 ListNode
	//자기참조구조체
}ListNode;

int main() {
	ListNode a, b;
	ListNode* head = &a;
	a.data = 10;
	b.data = 20;
	a.link = &b; // a의 링크부분에 b의 주소를 넣는다.
	b.link = NULL;
	printf("%d\n", a.data);
	printf("%d\n", head->data);
}