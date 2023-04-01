#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 20

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}

//Underflow
int is_empty(StackType* s) {
	return (s->top == -1);
}

//Overflow
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) {//peek 함수는 top의 값에 변화가 없다.
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)];
}

int prec(char ch) {
	if (ch == '+' || ch == '-') {
		return 2;
	}
	else if (ch == '(' || ch == ')') {
		return 1;
	}
	else if (ch == '*' || ch == '/') {
		return 3;
	}
}

void infix_to_postfix(const char exp[]) {
	StackType s;
	char ch;
	char op_top;
	init_stack(&s);
	int len = strlen(exp);
	for (int i = 0; i < len; i++) {
		ch = exp[i];
		//ch가 연산자인지 구분.
		switch (ch) {
		case '+': case '-': case '*': case '/': //스택 안에있는 연산자보다 들어갈 연산자의 우선순위가 더 낮을때
			while (!is_empty(&s) && prec(peek(&s)) >= prec(ch)) 	//안에있는 연산자를 pop하고 프린트한다. 그리고 들어갈 연산자를 밀어넣는다.
				printf("%c", pop(&s));
			push(&s, ch);
			break;

		case '(':
			push(&s, ch);
			break;
		case ')': // '('까지 찾아가서 출력하기
			op_top = pop(&s);
			while (op_top != '(') {
				printf("%c", op_top);
				op_top = pop(&s);
			}
			break;
		default:
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) {
		printf("%c", pop(&s));
	}
}

int main() {
	const char* s = "(3+2)*8+4";
	infix_to_postfix(s);
}
"32+8*4+"