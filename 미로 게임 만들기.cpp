#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "stack.h"
#define MAX_SIZE 10

typedef struct {
	int score;
	int count;
	element NowPos;
	char maze[MAX_SIZE][MAX_SIZE];
}GameData;

int CheckMaze(char maz[MAX_SIZE][MAX_SIZE]) {
	element here = { 1,0 };
	int count = 0;
	StackType s;
	init_stack(&s);
	char maze[MAX_SIZE][MAX_SIZE];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			maze[i][j] = maz[i][j];
		}
	}

	while (maze[here.r][here.c] != 'x') {
		if (maze[here.r][here.c] == 1) {
			return 0;
		}
		maze[here.r][here.c] = '.';
		//미로의 전후좌우 조사
		//우
		if (maze[here.r + 1][here.c] != '1' && maze[here.r + 1][here.c] != '.' && maze[here.r + 1][here.c] != '|' && maze[here.r + 1][here.c] != '-') {
			push_loc(&s, ++here.r, here.c);
			count++;
		}
		//하
		else if (maze[here.r][here.c + 1] != '1' && maze[here.r][here.c + 1] != '.' && maze[here.r][here.c ] != '|' && maze[here.r][here.c + 1] != '-') {
			push_loc(&s, here.r, ++here.c);
			count++;
		}
		//좌
		else if (maze[here.r - 1][here.c] != '1' && maze[here.r - 1][here.c] != '.' && maze[here.r - 1][here.c] != '|' && maze[here.r - 1][here.c] != '-') {
			push_loc(&s, --here.r, here.c);
			count++;
		}
		//상
		else if (maze[here.r][here.c - 1] != '1' && maze[here.r][here.c - 1] != '.' && maze[here.r][here.c - 1] != '|' && maze[here.r][here.c - 1] != '-') {
			push_loc(&s, here.r, --here.c);
			count++;
		}

		else if (is_empty(&s)) {
			return 0;
		}
		else {
			here = pop(&s);
			count++;
		}
	}
	return 1; //미로 검사 통과!
}

void RanMaze(char maze[MAX_SIZE][MAX_SIZE], int k) {
	for (int i = 0; i < 10; i++) {
		maze[i][0] = '|';
		maze[i][9] = '|';
		maze[0][i] = '-';
		maze[9][i] = '-';
	}
	maze[9][0] = '-';
reset:
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			//k=3 어려움 난이도시 벽이 생성률 70%
			//k=2 보통 난이도시 벽 생성률 50%
			//k=1 쉬움 난이도시 벽 생성률 30%
			if (rand() % 100 >= 30 + (k-3) * -20) {
				maze[i][j] = '1';
			}
			else if (rand() % 100 < 10) {
				//약 10프로 확률로 폭탄부여
				maze[i][j] = 'B';
			}
			else {
				maze[i][j] = '0';
			}

		}
	}
	maze[9][8] = 'x';
	maze[1][0] = 'E';
	if (CheckMaze(maze) == 0) {
		goto reset;
	}
}

void PrtMaze(char maze[MAX_SIZE][MAX_SIZE]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 || i == 9) {
				printf("%c-", maze[i][j]);
			}
			else {
				printf("%c ", maze[i][j]);
			}
		}
		printf("\n");
	}
}

int Check_Ready() {//게임준비작업, 룰설명
	int n;
	int k;
	printf("게임을 플레이 하실 준비가 되셨다면 1을 입력해주세요 : ");
	scanf("%d", &n);
	if (n == 1) {
		printf("게임을 시작합니다!\n");
		printf("--------Game Rule--------\n");
		printf("움직일때마다 1점, 폭탄을 밟으면 -3점입니다.\n");
		printf("왔던길을 되돌아가는 행동에는 점수가 증가되지 않습니다!\n");
		printf("게임난이도를 설정해주세요!\n");
		printf("1단계: (낮음) | 2단계: (보통) | 3단계: (높음)\n");
		scanf("%d", &k);
		printf("-------------------------\n");
		printf("10초후 게임이 시작됩니다!\n");
		Sleep(10);
		for (int i = 10; i > 0; i--) {
			printf("%d ", i);
			Sleep(1000);
		}
		system("cls");
		return k;
	}
	else {
		printf("플레이할 준비를 마치시면 다시 실행해주세요!");
		Sleep(3000);
		return 0;
	}
}

void up(GameData &gd) {
	if (gd.maze[gd.NowPos.r - 1][gd.NowPos.c] == '1' || gd.maze[gd.NowPos.r - 1][gd.NowPos.c] == '|' || gd.maze[gd.NowPos.r - 1][gd.NowPos.c] == '-') {//막히면?
		printf("막혀있습니다.\n");
		return;
	}
	if (gd.maze[gd.NowPos.r - 1][gd.NowPos.c] == 'B') {//폭탄이면?
		printf("폭탄을 밟았습니다! 3점 차감!\n");
		gd.score -= 3;
	}
	gd.maze[gd.NowPos.r][gd.NowPos.c] = '0';
	gd.count++;
	gd.NowPos.r--;
	gd.score--;
}

void down(GameData &gd) {
	if (gd.maze[gd.NowPos.r + 1][gd.NowPos.c] == '1' || gd.maze[gd.NowPos.r + 1][gd.NowPos.c] == '|' || gd.maze[gd.NowPos.r + 1][gd.NowPos.c] == '-') {//막히면?
		printf("막혀있습니다.\n");
		return;
	}
	if (gd.maze[gd.NowPos.r + 1][gd.NowPos.c] == 'B') {//폭탄이면?
		printf("폭탄을 밟았습니다! 3점 차감!\n");
		gd.score -= 3;
	}
	gd.maze[gd.NowPos.r][gd.NowPos.c] = '0';
	gd.count++;
	gd.NowPos.r++;
	gd.score--;
}

void left(GameData &gd) {
	if (gd.maze[gd.NowPos.r][gd.NowPos.c - 1] == '1' || gd.maze[gd.NowPos.r][gd.NowPos.c - 1] == '|' || gd.maze[gd.NowPos.r][gd.NowPos.c - 1] == '-') {//막히면?
		printf("막혀있습니다.\n");
		return;
	}
	if (gd.maze[gd.NowPos.r][gd.NowPos.c - 1] == 'B') {//폭탄이면?
		printf("폭탄을 밟았습니다! 3점 차감!\n");
		gd.score -= 3;
	}
	gd.maze[gd.NowPos.r][gd.NowPos.c] = '0';
	gd.count++;
	gd.NowPos.c--;
	gd.score--;
}

void right(GameData &gd) {
	if (gd.maze[gd.NowPos.r][gd.NowPos.c + 1] == '1' || gd.maze[gd.NowPos.r][gd.NowPos.c + 1] == '|' || gd.maze[gd.NowPos.r][gd.NowPos.c + 1] == '-') {//막히면?
		printf("막혀있습니다.\n");
		return;
	}
	if (gd.maze[gd.NowPos.r][gd.NowPos.c + 1] == 'B') {//폭탄이면?
		printf("폭탄을 밟았습니다! 3점 차감!\n");
		gd.score -= 3;
	}
	gd.maze[gd.NowPos.r][gd.NowPos.c] = '0';
	gd.count++;
	gd.NowPos.c++;
	gd.score--;
}

int main() {
	srand((unsigned)time(NULL));
	element Destination;
	Destination = { 9, 8 };
	GameData GD;
	int k;
	
	if (k = Check_Ready()) {
		GD.NowPos = { 1,0 };
		system("cls");
		RanMaze(GD.maze, k);
		GD.score = 100;
		GD.count = 0;
		while (GD.NowPos.r != 9 || GD.NowPos.c != 8) {//NowPos가 Destination에 도달하지 않았다면 반복.
			GD.maze[GD.NowPos.r][GD.NowPos.c] = '.';
			PrtMaze(GD.maze);
			//점수랑 지나온 거리 결과 출력
			if (GD.score <= 0) {
				printf("탈락!");
				break;
			}
			printf("점수 : %d    움직인 횟수 : %d\n", GD.score, GD.count);
			//한번씩 방향키 입력받기
			int key1, key2;
			key1 = _getch();
			key2 = _getch();
			system("cls");
			if (key1 == 224) {
				switch (key2) {
				case 72://상
					up(GD);
					break;
				case 80://하
					down(GD);
					break;
				case 75://좌
					left(GD);
					break;
				case 77://우
					right(GD);
					break;
				}
			}
		}
		PrtMaze(GD.maze);
		printf("축하합니다! 클리어 했어요!\n");
		printf("당신의 점수 : %d    총 움직인 횟수 : %d\n", GD.score, GD.count);
	}
}