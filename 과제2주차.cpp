#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct com {
	double x;
	double y;
};

struct com sum(struct com complex1, struct com complex2) {
	struct com complex3;
	complex3.x = complex1.x + complex2.x;
	complex3.y = complex1.y + complex2.y;

	return complex3;
}

struct com sub(struct com complex1, struct com complex2) {
	struct com complex3;
	complex3.x = complex1.x - complex2.x;
	complex3.y = complex1.y - complex2.y;

	return complex3;
}

struct com mul(struct com complex1, struct com complex2) {
	struct com complex3;
	complex3.x = complex1.x * complex2.x - complex1.y * complex2.y;
	complex3.y = complex1.y * complex2.x + complex1.x * complex2.y;

	return complex3;
}

struct com div(struct com complex1, struct com complex2) {
	struct com complex3;
	//mother는 복소수의 나눗셈 에서의 분모
	//(complex2.x + complex2.yi)분모에 (complex2.x - complex2.yi)가 곱해지면서
	//분모는 (complex2.x)^2 - (complex2.y)^2가 된다.
	double mother = (complex2.x) * (complex2.x) + (complex2.y) * (complex2.y);
	//분자는 분모의 켤레복소수가 곱해졌으므로
	//(complex1.x + complex1.yi) * (complex2.x - complex2.yi)가 된다.
	complex3.x = (complex1.x * complex2.x + complex1.y * complex2.y) / mother;
	complex3.y = (complex1.y * complex2.x - complex1.x * complex2.y) / mother;

	return complex3;
}

void print(struct com complex3) {
	if (complex3.x == 0 && complex3.y != 0) {
		printf("%lfi\n", complex3.y);
	}
	else if (complex3.x != 0 && complex3.y != 0) {
		if (complex3.y > 0) {
			printf("%lf +%lfi\n", complex3.x, complex3.y);
		}
		else {
			printf("%lf %lfi\n", complex3.x, complex3.y);
		}
	}
	else if (complex3.x != 0 && complex3.y == 0) {
		printf("%lf\n", complex3.x);
	}
}

int main() {
	struct com complex1;
	struct com complex2;
	struct com complex3;
	int num;
	while (1) {
		printf("***복소수 연산***\n");
		printf("1. 데이터 입력\n");
		printf("2. 복소수 덧셈\n");
		printf("3. 복소수 뺄셈\n");
		printf("4. 복소수 곱셈\n");
		printf("5. 복소수 나눗셈\n");
		printf("6. 프로그램 종료\n\n");
		printf("◆작업할 번호를 입력 >> ");
		scanf("%d", &num);

		if (num == 1) {
			scanf("%lf", &complex1.x);
			scanf("%lf", &complex1.y);
			scanf("%lf", &complex2.x);
			scanf("%lf", &complex2.y);
		}
		else if (num == 2) {
			complex3 = sum(complex1, complex2);
			print(complex3);
		}
		else if (num == 3) {
			complex3 = sub(complex1, complex2);
			print(complex3);
		}
		else if (num == 4) {
			complex3 = mul(complex1, complex2);
			print(complex3);
		}
		else if (num == 5) {
			complex3 = div(complex1, complex2);
			print(complex3);
		}
		else if (num == 6) {
			break;
		}
	}
}