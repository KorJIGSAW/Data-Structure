#include <stdio.h>
#include <stdlib.h>

typedef int element;
//노드 구조 정의
typedef struct ListNode{
	element data;
	struct ListNode* link; // ListNode로 하면안된다 // 자기참조구조체
}ListNode;

ListNode * insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //동적할당
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode * delete_first(ListNode *head) {
	ListNode* removed = head;
	head = head->link; // head = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode *head) {
	for (ListNode* p = head; p != NULL; p = p->link) {//헤드에서 출발해서 p->link가 NULL이 아닐때까지 p를 p->link로 변환한다.
		printf("%d->", p->data);
	}
	printf("\n");
}

ListNode * search_list(ListNode *head, element x) {
	ListNode * p = head;
	while (p != NULL) {
		if (p->data == x) {
			return p;
		}
		p = p->link; // p의 데이터 값이 x가 아니라면 그 다음 link가 가리키는 값이랑 비교해야하므로 값을 변환해줘야한다.
	}
	return NULL;
}

int main() {
	ListNode* head = NULL;
	head = insert_first(head, 10);
	head = insert_first(head, 20);
	head = insert_first(head, 30);
	head = insert_first(head, 40);
	head = insert_first(head, 50);

	ListNode* s = search_list(head, 20);
	if (s != NULL) {
		printf("데이터가 존재함\n");
	}
	else {
		printf("데이터가 존재하지 않음\n");
	}

	print_list(head);

	head = delete_first(head);
	
	print_list(head);
}