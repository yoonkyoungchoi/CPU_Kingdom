// use console, cursor ...
#include <Windows.h>
// use exit function
#include <stdlib.h>
// input output ...
#include <stdio.h>

// header files
#include "ciano_tiles.h"
#include "guess_note.h"
#include "maze_game.h"
#include "pushpull.h"
#include "snake_game.h"
#include "modules.h"
#include "avoidgame.h"
#include "bluewhite.h"

// _getch() values (chohadam 21-03-11)
#define ESC 27
#define ENTER 13
// _getch() value of arrow key (chohadam 21-03-11)
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void set_console(void);
void set_cursor(int flag, int size);

int select_game(void);

int main(void) {
	set_console();

	// input value
	int select;
	while (select = select_game()) {
		switch (select)
		{
		case 1:
			ciano_tiles();
			break;

		case 2:
			guess_note();
			break;

		case 3:
			maze_game();
			break;

		case 4:
			pushpull();
			break;

		case 5:
			snake_game();
			break;

		case 6:
			main_avoid();
			break;

		case 7:
			main_bluewhtie();
			break;

		// end game
		case 8:
			exit(1);

		default:
			break;
		}
	}

	return 0;
}

// console settings function (chohadam 21-03-11)
void set_console(void) {
	// set the console size
	system("mode con:cols=120 lines=31");
	// hide cursor
	set_cursor(0, 1);
	// set title
	system("title CPU KINGDOM");
	// clear console
	system("cls");
}

// cursor settings function (chohadam 21-03-11)
void set_cursor(int flag, int size) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = flag;
	cursor.dwSize = size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void print_auto_y(int* x, int* y, char* str) {
	gotoxy(*x, *y);
	printf(str);
	*y += 1;
}

// select the game (chohadam, 21-06-16)
int select_game(void) {
	system("cls");

	// default x, y
	int x = 8;
	int y = 2;

	print_auto_y(&x, &y, "                       |>>>");
	print_auto_y(&x, &y, "                       |");
	print_auto_y(&x, &y, "         |>>>      _  _|_  _         |>>>");
	print_auto_y(&x, &y, "         |        |;| |;| |;|        |");
	print_auto_y(&x, &y, "     _  _|_  _    ＼.    .  /    _  _|_  _");
	print_auto_y(&x, &y, "    |;|_|;|_|;|    ＼:. ,  /    |;|_|;|_|;|");
	print_auto_y(&x, &y, "    ＼..      /     ||;   .|   ＼.    .  /");
	print_auto_y(&x, &y, "     ＼.  ,  /      ||:  . |    ＼:  .  /");
	print_auto_y(&x, &y, "      ||:   |_   _  ||_ ._ |    _||:   |");
	print_auto_y(&x, &y, "      ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |");
	print_auto_y(&x, &y, "      ||:   ||.    .     .      . ||:  .|");
	print_auto_y(&x, &y, "      ||: . || .     . .   .  ,   ||:   |");
	print_auto_y(&x, &y, "      ||:   ||:  ,  _______   .   ||: , |");
	print_auto_y(&x, &y, "      ||:   || .   /+++++++＼   . ||:   |");
	print_auto_y(&x, &y, "      ||:   ||.    |+++++++| .    ||: . |");
	print_auto_y(&x, &y, "   __ ||: . ||: ,  |+++++++|.  . _||_   |");
	print_auto_y(&x, &y, "`~    '--~~__|.    |+++++__|----~    ~`---,");
	print_auto_y(&x, &y, "             ~---__|,--~'");

	x = 54;
	y = 4;
	print_auto_y(&x, &y, "                   _____   _____    _    _");
	print_auto_y(&x, &y, "                  / ____| |  __ ＼ | |  | |");
	print_auto_y(&x, &y, "                 | |      | |__) | | |  | |");
	print_auto_y(&x, &y, "                 | |      |  ___/  | |  | |");
	print_auto_y(&x, &y, "                 | |____  | |      | |__| |");
	print_auto_y(&x, &y, "                 ＼_____| |_|      ＼_____/");

	y += 2;
	print_auto_y(&x, &y, "  _  __   _____   _   _    _____   _____      ____     __   __");
	print_auto_y(&x, &y, " | |/ /  |_   _| | ＼ | | / ____|  |  __ ＼  / __ ＼  |  ＼/  |");
	print_auto_y(&x, &y, " | ' /     | |   |  ＼| | | |  __  | |  | | | |  | |  | ＼  / |");
	print_auto_y(&x, &y, " |  <      | |   | . `  | | | |_ | | |  | | | |  | |  | |＼/| |");
	print_auto_y(&x, &y, " | . ＼  ,_| |_  | |＼  | | |__| | | |__| | | |__| |  | |   | |");
	print_auto_y(&x, &y, " |_|＼_＼|_____| |_| ＼_| ＼_____| |_____/  ＼____/   |_|   |_|");

	x = 10;
	y = 24;
	print_auto_y(&x, &y, "① 피아노 타일");
	y += 2;
	print_auto_y(&x, &y, "⑤ 뱀 피하기");

	x = 30;
	y = 24;
	print_auto_y(&x, &y, "② 절대음감");
	y += 2;
	print_auto_y(&x, &y, "⑥ 눈 피하기");

	x = 50;
	y = 24;
	print_auto_y(&x, &y, "③ 미로 탈출");
	y += 2;
	print_auto_y(&x, &y, "⑦ 청기백기");

	x = 70;
	y = 24;
	print_auto_y(&x, &y, "④ 줄다리기");
	y += 2;
	print_auto_y(&x, &y, "⑧ 종료");

	int select = 1;
	int k = 0;
	while (k != ENTER) {
		x = 87;
		y = 24;
		print_auto_y(&x, &y, "┌─────── 게임 선택 ───────┐");
		print_auto_y(&x, &y, "│                         │");
		gotoxy(x, y);
		printf("│      >      %d           │", select);
		y += 1;
		print_auto_y(&x, &y, "│                         │");
		print_auto_y(&x, &y, "└─────────────────────────┘");

		k = get_key();
		switch (k) {
		case UP: case RIGHT:
			select = select == 8 ? 8 : select + 1;
			break;
		case DOWN: case LEFT:
			select = select == 1 ? 1 : select - 1;
			break;
		}
	}

	return select;
}
