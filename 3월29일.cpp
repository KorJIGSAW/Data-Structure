#include "stack3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_matching(const char* in) {
	StackType s;
	char ch, open_ch;
	int n = strlen(in);
	init_stack(&s);

	for (int i = 0; i < n; i++) {
		ch = in[i]; // '{'
		switch (ch) {
		case '(': case '{': case '[':
			push(&s, ch);
			break;
		case ')': case '}': case ']':
			//pop했을때 비어있다면 0을 돌려준다.
			if (is_empty(&s)) {
				return 0;
			}
			open_ch = pop(&s);
			//짝이 맞지 않을 때 return 0;
			if (open_ch == '(' && ch != ')' || open_ch == '{' && ch != '}' || open_ch == '[' && ch != ']') {
				return 0;
			}
			break;
		}
		
	}
	if (!is_empty(&s)) {
		return 0;
	}
	return 1;
}

int main() {
	//포인터에 바로 문자열을 담을 때는 자료형 앞에 상수인 const를 선언해주어야한다.
	const char* p = "{A[(i+1)]=0;}";
	if (check_matching(p))
		printf("%s\n : 성공!", p);
	else
		printf("%s\n : 실패!", p);
}

