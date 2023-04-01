//미로를 랜덤으로 생성하기
#include <stdio.h>
#include <time.h>
#include "stack.h"
#define MAX_SIZE 10

element here = { 1,0 };
element entry = { 1,0 };


void PrtMaze(char maze[MAX_SIZE][MAX_SIZE]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
}

//벽면은 1로 초기화 나머지 안쪽은 랜덤성 0,1부여
void RanMaze(char maze[MAX_SIZE][MAX_SIZE]) {
	for (int i = 0; i < 10; i++) {
		maze[i][0] = '1';
		maze[0][i] = '1';
		maze[i][9] = '1';
		maze[9][i] = '1';
	}

	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			//약 70프로 확률로 1부여
			if (rand() % 100 >= 70) {
				maze[i][j] = '1';
			}
			else {
				maze[i][j] = '0';
			}
		}
	}
}

int main() {
	srand((unsigned)time(NULL));
	int r, c, count = 0;
	char maze[MAX_SIZE][MAX_SIZE];
	RanMaze(maze);
	//scanf_s("%d", &r);
	StackType s;
	init_stack(&s);
	maze[9][8] = 'x';
	maze[1][0] = 'e';
	while (maze[here.r][here.c] != 'x') {
		if (maze[here.r][here.c] == 1) {
			printf("실패\n");
			return 0;
		}
		maze[here.r][here.c] = '.';
		//미로출력, 2차배열로 출력 함수
		PrtMaze(maze);
		//미로의 전후좌우 조사
		//우
		if (maze[here.r+1][here.c] != '1' && maze[here.r+1][here.c] != '.') {
			push_loc(&s, ++here.r, here.c);
			count++;
		}
		//하
		else if (maze[here.r][here.c + 1] != '1' && maze[here.r][here.c + 1] != '.') {
			push_loc(&s, here.r, ++here.c);
			count++;
		}
		//좌
		else if (maze[here.r - 1][here.c] != '1' && maze[here.r - 1][here.c] != '.') {
			push_loc(&s, --here.r , here.c);
			count++;
		}
		//상
		else if (maze[here.r][here.c - 1] != '1' && maze[here.r][here.c - 1] != '.') {
			push_loc(&s, here.r, --here.c);
			count++;
		}

		else if (is_empty(&s)) {
			printf("실패\n");
			return 0;
		}
		else {
			here = pop(&s);
			count++;
		}
		printf("\n\n");
	}
	printf("%d번을 움직여서 탈출\n", count);
	printf("최단거리 : %d", s.top + 2);

	return 0;
}