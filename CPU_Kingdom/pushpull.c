#include "pushpull.h"
#include <conio.h>

// _getch() value of ESC key
#define ESC 27

void start_game(void);
void game_fun(void);
char key;
char t_name1;
char t_name2;
int x = 40;
int y = 11;
int win = 0;
int win_lose = 0;

void pushpull(void) {
	char t_name1;
	char t_name2;
	system("cls"); 

	do {
		gotoxy(35, 5);
		printf("★★★★★★★★★★ 줄다리기 ★★★★★★★★★★\n");
		gotoxy(35, 6);
		printf("★");
		gotoxy(83, 6);
		printf("★");
		gotoxy(35, 7);
		printf("★         A키와 L키를 마구마구 연타!!          ★\n");
		gotoxy(35, 8);
		printf("★ 줄을 가장 빨리 자기쪽으로 당기는 게임입니다! ★\n");
		gotoxy(35, 9);
		printf("★                 단판 승부!                   ★\n");
		gotoxy(35, 10);
		printf("★");
		gotoxy(83, 10);
		printf("★");
		gotoxy(35, 11);
		printf("★");
		gotoxy(83, 11);
		printf("★");
		gotoxy(35, 12);
		printf("★  ESC를 누르면 다시 게임선택으로 돌아갑니다!  ★ ");
		gotoxy(35, 13);
		printf("★");
		gotoxy(83, 13);
		printf("★");
		gotoxy(35, 14);
		printf("★★★★★★★★★★★★★★★★★★★★★★★★★\n");
		do {
			start_game();
			do {
				game_fun();
				} while (key != ESC);
			} while (key != ESC);
	} while (key != ESC);
}

void line(int x, int y)
{
	system("cls");
	int i, line[21] = { 0 };
	line[10] = 1;
	line[4] = 2;
	line[16] = 2;
	gotoxy(31, 13);
	for (i = 0; i < 78; i++)
		printf(" ");

	gotoxy(35, 10);
	printf("%s", &t_name1);
	gotoxy(87, 10);
	printf("%s", &t_name2);

	gotoxy(x, y);
	for (i = 0; i < 21; i++)
		if (line[i] == 0)
			printf("□");
		else if (line[i] == 1)
			printf("■");
		else
			printf("◆");

	gotoxy(58, 8);
	printf("기준점");
	gotoxy(60, 10);
	printf("▼");
	gotoxy(60, 12);
	printf("▲");

	gotoxy(43, 15);
	printf("메뉴로 돌아가려면 ESC를 눌러주세요\n");

	char menu_key = _getch();
	if (menu_key == ESC) {
		pushpull();
	}

}

void start_game() {
	gotoxy(45, 16);
	printf("시작 전 팀 이름을 정해주세요!\n");
	gotoxy(45, 17);
	printf("첫번째 팀 이름입력 후 엔터!> ");
	scanf_s("%s", &t_name1,100);
	gotoxy(45, 18);
	printf("두번째 팀 이름입력 후 엔터!> ");
	scanf_s("%s", &t_name2, 100);
	system("cls");
	line(x, y);

}

void game_fun() {
	char click = _getch();
	if (click == ESC) {
		pushpull();
	}
	switch (click) {
	case 65: case 97: // A
		line(x - 2, y);
		Sleep(100);
		if (x == 46) {
			printf("%s 승리!", &t_name1);
			break;
		}

	case 76: case 108: // L
		line(x + 2, y);
		Sleep(100);
		if (x == 34) {
			printf("%s 승리!", &t_name2);
			break;
		}
	}
}
	