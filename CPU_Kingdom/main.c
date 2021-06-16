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

void draw_main(void);
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

void draw_main(void) {
	system("cls");

	// default x, y
	int x = 6;
	int y = 2;

	print_auto_y(&x, &y, "                       |>>>");
	print_auto_y(&x, &y, "                       |");
	print_auto_y(&x, &y, "         |>>>      _  _|_  _         |>>>");
	print_auto_y(&x, &y, "         |        |;| |;| |;|        |");
	print_auto_y(&x, &y, "     _  _|_  _    ＼＼.  .  /    _  _|_  _");
	print_auto_y(&x, &y, "    |;|_|;|_|;|    ＼＼: , /    |;|_|;|_|;|");
	print_auto_y(&x, &y, "    ＼＼..    /     ||;   .|    ＼＼.  .  /");
	print_auto_y(&x, &y, "     ＼＼. , /      ||:  . |     ＼＼:   /");
	print_auto_y(&x, &y, "      ||:   |_   _  ||_ ._ |     _||:   |");
	print_auto_y(&x, &y, "      ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |");
	print_auto_y(&x, &y, "      ||:   ||.    .     .      . ||:  .|");
	print_auto_y(&x, &y, "      ||: . || .     . .   .  ,   ||:   |");
	print_auto_y(&x, &y, "      ||:   ||:  ,  _______   .   ||: , |");
	print_auto_y(&x, &y, "      ||:   || .   /+++++++＼   . ||:   |");
	print_auto_y(&x, &y, "      ||:   ||.    |+++++++| .    ||: . |");
	print_auto_y(&x, &y, "   __ ||: . ||: ,  |+++++++|.  . _||_   |");
	print_auto_y(&x, &y, "`~    '--~~__|.    |+++++__|----~    ~`---,");
	print_auto_y(&x, &y, "             ~---__|,--~'");

	x = 52;
	y = 4;
	print_auto_y(&x, &y, "                   _____   _____    _    _");
	print_auto_y(&x, &y, "                  / ____| |  __ ＼ | |  | |");
	print_auto_y(&x, &y, "                 | |      | |__) | | |  | |");
	print_auto_y(&x, &y, "                 | |      |  ___/  | |  | |");
	print_auto_y(&x, &y, "                 | |____  | |      | |__| |");
	print_auto_y(&x, &y, "                 ＼_____| |_|      ＼_____/");

	y += 2;
	print_auto_y(&x, &y, "  _  ___  _____   _   __   _____    _____     ____     __   __");
	print_auto_y(&x, &y, " | |/  / |_   _| | ＼ | | / ____|  |  __ ＼  / __ ＼  |  ＼/  |");
	print_auto_y(&x, &y, " | '  /    | |   |  ＼| | | |  __  | |  | | | |  | |  | ＼  / |");
	print_auto_y(&x, &y, " |  <      | |   | . `  | | | |_ | | |  | | | |  | |  | |＼/| |");
	print_auto_y(&x, &y, " | . ＼  ,_| |_  | |＼  | | |__| | | |__| | | |__| |  | |   | |");
	print_auto_y(&x, &y, " |_|＼_＼|_____| |_| ＼_| ＼_____| |_____/  ＼____/   |_|   |_|");

	x = 15;
	y = 24;
	print_auto_y(&x, &y, "① 피아노 타일");
	y += 3;
	print_auto_y(&x, &y, "⑤ 뱀 피하기");

	x = 40;
	y = 24;
	print_auto_y(&x, &y, "② 절대음감");
	y += 3;
	print_auto_y(&x, &y, "⑥ 눈 피하기");

	x = 65;
	y = 24;
	print_auto_y(&x, &y, "③ 미로 탈출");
	y += 3;
	print_auto_y(&x, &y, "⑦ 청기백기");

	x = 90;
	y = 24;
	print_auto_y(&x, &y, "④ 줄다리기");
	y += 3;
	print_auto_y(&x, &y, "⑧ 종료");
}

// select the game (chohadam, 21-06-16)
int select_game(void) {
	draw_main();

	int select_x[4] = { 12, 37, 62, 87 };
	int select_y[2] = { 22, 26 };

	// default menu 1
	int select = 1;

	int i, j, x, y;

	int key = 0;
	while (key != ENTER) {
		// 1, 5 | 2, 6 | 3, 7 | 4, 8
		i = (select - 1) % 4;
		x = select_x[i];
		// 1, 2, 3, 4 | 5, 6, 7, 8
		j = select <= 4 ? 0 : 1;
		y = select_y[j];

		// print rectangle
		print_auto_y(&x, &y, "┌─────────────────┐");
		print_auto_y(&x, &y, "│");		
		gotoxy(x + 18, y - 1); printf("│");
		print_auto_y(&x, &y, "│");
		gotoxy(x + 18, y - 1); printf("│");
		print_auto_y(&x, &y, "│");
		gotoxy(x + 18, y - 1); printf("│");
		print_auto_y(&x, &y, "└─────────────────┘");

		// ↑, ↓, ←, →
		key = _getch();

		switch (key) {
		case RIGHT:
			select = select == 8 ? 8 : select + 1;
			break;

		case LEFT:
			select = select == 1 ? 1 : select - 1;
			break;

		case UP:
			if (select > 4) {
				select -= 4;
			}
			break;

		case DOWN:
			if (select <= 4) {
				select += 4;
			}
			break;
		}

		// remove rectangle
		y -= 5;
		print_auto_y(&x, &y, "                    ");
		print_auto_y(&x, &y, "  ");
		gotoxy(x + 18, y - 1); printf("  ");
		print_auto_y(&x, &y, "  ");
		gotoxy(x + 18, y - 1); printf("  ");
		print_auto_y(&x, &y, "  ");
		gotoxy(x + 18, y - 1); printf("  ");
		print_auto_y(&x, &y, "                    ");
	}

	return select;
}
