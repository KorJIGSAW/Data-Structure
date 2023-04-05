#include <stdio.h>
#include <stdlib.h>

// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
// ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 100

typedef int element;


typedef struct {
	element* data;
	//크기를 얼마나 확장시킬건지
	int capacity;
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element *)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == s->capacity);
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		//메모리를 추가 요청함
		s->capacity = s->capacity * 2;
		//realloc -> realloc(어디에?, 얼마만큼?;
		s->data = (element *)realloc(s ->data, s->capacity*sizeof(element));
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

//실행중에 메모리할당 -> 동적할당
//프로그램 4.5 동적 배열 스택 프로그램(117쪽)
int main(void)
{
	StackType s;
	
	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("pop value = %d\n", pop(&s));
}
