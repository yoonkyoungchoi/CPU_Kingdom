#include "pushpull.h"
#include <conio.h>
#include<windows.h>

// _getch() value of ESC key
#define ESC 27
#define A 65
#define a 97
#define L 76
#define l 108

void start_game(void);
void game_fun(void);
char key;
char t_name1[20];
char t_name2[20];
int x = 40;
int y = 11;
int win = 0;
int win_lose = 0;

void pushpull(void) {
	char t_name1;
	char t_name2;
	system("cls"); 

	do {
		gotoxy(37, 5);
		printf("★★★★★★★★★★ 줄다리기 ★★★★★★★★★★\n");
		gotoxy(37, 6);
		printf("★");
		gotoxy(85, 6);
		printf("★");
		gotoxy(37, 7);
		printf("★         A키와 L키를 마구마구 연타!!          ★\n");
		gotoxy(37, 8);
		printf("★ 줄을 가장 빨리 자기쪽으로 당기는 게임입니다! ★\n");
		gotoxy(37, 9);
		printf("★                 단판 승부!                   ★\n");
		gotoxy(37, 10);
		printf("★");
		gotoxy(85, 10);
		printf("★");
		gotoxy(37, 11);
		printf("★");
		gotoxy(85, 11);
		printf("★");
		gotoxy(37, 12);
		printf("★  ESC를 누르면 다시 게임선택으로 돌아갑니다!  ★ ");
		gotoxy(37, 13);
		printf("★          이름은 6자 이내로 지어주세요!       ★");
		gotoxy(37, 14);
		printf("★★★★★★★★★★★★★★★★★★★★★★★★★\n");
		do {
			x = 40;
			start_game(x, y);
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

	gotoxy(28, 8);
	printf("%s", t_name1);
	gotoxy(86, 8);
	printf("%s", t_name2);

	gotoxy(30, 10);
	printf("●");
	gotoxy(29, 11);
	printf("＼|/");
	gotoxy(30, 12);
	printf(" |");
	gotoxy(30, 13);
	printf("/＼");

	gotoxy(87, 10);
	printf(" ●");
	gotoxy(86, 11);
	printf("＼|/");
	gotoxy(87, 12);
	printf(" |");
	gotoxy(87, 13);
	printf("/＼");

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

	gotoxy(45, 19);
	printf("메뉴로 돌아가려면 ESC를 눌러주세요\n");

	char menu_key = _getch();
	if (menu_key == ESC) {
		pushpull();
	}

}

void start_game() {
	gotoxy(47, 17);
	printf("시작 전 팀 이름을 정해주세요!\n");
	gotoxy(47, 18);
	printf("첫번째 팀 이름입력 후 엔터!> ");
	scanf_s("%s", &t_name1,20);
	gotoxy(47, 19);
	printf("두번째 팀 이름입력 후 엔터!> ");
	scanf_s("%s", &t_name2, 20);
	system("cls");
	line(x, y);
}

void game_fun() {
	char click = _getch();
	if (click == ESC) {
		pushpull();
	}
	switch (click) {
		case A: case a: // A
			x -= 2;
			line(x, y);
			Sleep(100);
			if (x == 28) {
				gotoxy(57, 15);
				printf("%s 승리!", t_name1);
				gotoxy(48, 17);
				printf("2초 뒤 메인화면으로 돌아갑니다.");
				Sleep(2000);
				pushpull();
			}

		case L: case l: // L
			x += 2;
			line(x, y);
			Sleep(100);
			if (x == 52) {
				gotoxy(57, 15);
				printf("%s 승리!", t_name2);
				gotoxy(48, 17);
				printf("2초 뒤 메인화면으로 돌아갑니다.");
				Sleep(2000);
				pushpull();
			}
		}
}
	