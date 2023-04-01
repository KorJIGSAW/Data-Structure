//미로를 랜덤으로 생성하기
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
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

int Check_Ready() {//게임준비작업, 룰설명
	int n;
	printf("게임을 플레이 하실 준비가 되셨다면 1을 입력해주세요 : ");
	scanf("%d", &n);
	if (n == 1) {
		printf("게임을 시작합니다!\n");
		printf("움직일때마다 1점, 폭탄을 밟으면 -3점입니다.\n");
		printf("왔던길을 되돌아가는 행동에는 점수가 증가되지 않습니다!\n");
		printf("10초후 게임이 시작됩니다!\n");
		Sleep(10);
		for (int i = 10; i > 0; i--) {
			printf("%d ", i);
			
		}
		system("cls");
		return 1;
	}
	else {
		printf("플레이할 준비를 마치시면 다시 실행해주세요!");
		Sleep(3000);
		return 0;
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
			else if (rand()% 100< 10) {
				//약 10프로 확률로 폭탄부여
				maze[i][j] = 'B'; 
			}
			else {
				maze[i][j] = '0';
			}
		}
	}
}

int main() {
	if (Check_Ready()) {
	reset:
		srand((unsigned)time(NULL));
		int r, c, count = 0;
		int key1, key2, score = 0;
		char maze[MAX_SIZE][MAX_SIZE];
		RanMaze(maze);
		//scanf_s("%d", &r);
		StackType s;
		init_stack(&s);

		maze[9][8] = 'x';
		maze[1][0] = 'e';
		while (maze[here.r][here.c] != 'x') {
			/*
			if (maze[here.r][here.c] == 1) {
				printf("실패\n");
				return 0;
			}*/

			maze[here.r][here.c] = '.';
			//미로출력, 2차배열로 출력 함수
			printf("0 : 길, 1 : 벽\n"); //길, 벽 설명
			PrtMaze(maze);

			printf("점수 : %d    ", score);
			printf("풀 수 없는 미로라면 r 또는 R을 입력\n\n");

			key1 = _getch();
			if (key1 == 'r' || key1 == 'R') {
				goto reset;
			}
			key2 = _getch();

			//방향키 입력받아서 움직이기
			if (key1 == 224) {
				switch (key2) {
				case 72://상
					if (maze[here.r - 1][here.c] != '1' && maze[here.r - 1][here.c] != '.') {
						//push_loc(&s, --here.r, here.c);
						count++;
						score++;
					}
					else if (maze[here.r - 1][here.c] == '1') {
						printf("막혀있습니다.\n");
						Sleep(1000);
						system("cls");
						continue;
					}
				case 80://하
					if (maze[here.r + 1][here.c] == '1') {
						printf("막혀있습니다.\n");
						Sleep(1000);
						system("cls");
						continue;
					}
					else if (maze[here.r + 1][here.c] != '1' && maze[here.r + 1][here.c] != '.') {
						push_loc(&s, ++here.r, here.c);
						count++;
						score++;
					}

				case 75://좌
					if (maze[here.r][here.c - 1] != '1' && maze[here.r][here.c - 1] != '.') {
						push_loc(&s, here.r, --here.c);
						count++;
						score++;
					}
					else if (maze[here.r][here.c - 1] == '1') {
						printf("막혀있습니다.\n");
						Sleep(1000);
						system("cls");
						continue;
					}
				case 77://우
					if (maze[here.r][here.c + 1] != '1' && maze[here.r][here.c + 1] != '.') {
						push_loc(&s, here.r, ++here.c);
						count++;
						score++;
					}
					else if (maze[here.r][here.c + 1] == '1') {
						printf("막혀있습니다.\n");
						Sleep(1000);
						system("cls");
						continue;
					}
				}
			}
			else if (is_empty(&s)) {
				printf("실패\n");
				return 0;
			}
			else {
				here = pop(&s);
				count++;
			}

			system("cls");
		}
	exit:
		printf("%d번을 움직여서 탈출\n", count);
		printf("최단거리 : %d\n", s.top + 2);
		printf("점수 : %d", score);
	}
}

//위, 아래를 움직일 때 막혀있습니다 프린트 오류
//폭탄 밟을때 -3점 추가
//cls 최적화
//한번씩 방향키 입력시 실패 출력 문제
//UI 예쁘게
//점수 = 100 - 움직인거리
