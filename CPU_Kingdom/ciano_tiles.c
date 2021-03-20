// The Game Made by Hadam Cho

#include "ciano_tiles.h"

// _getch() values
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// functions
void draw_menu(int x, int y, int distance);
int select_menu(int x, int y, int distance);
void menu_process(int selected_menu, int first_menu_y, int distance);

void ciano_tiles(void) {
	system("cls");

	// default coordinates
	int x = 110, y = 30;
	char key;

	// line spacing (menu)
	int distance = 3;
	// draw menu
	draw_menu(x, y, distance);

	// user select a menu
	int selected_menu = select_menu(x, y, distance);

	// check selected menu
	menu_process(selected_menu, y + distance + 2, distance);
}

// draw menu (chohadam 21-03-20)
void draw_menu(int x, int y, int distance) {
	gotoxy(x, y);
	printf("  CIANO TILES");
	gotoxy(x, y += distance + 2);
	printf("      시작");
	gotoxy(x, y += distance);
	printf("    게임 방법");
	gotoxy(x, y += distance);
	printf("      랭킹");
	gotoxy(x, y += distance);
	printf("      종료");
}

// select menu (chohadam 21-03-20)
int select_menu(int x, int y, int distance) {
	// Enter, Up, Down
	char pressed_key;
	// menu coordinates
	int first_menu_y = y + distance + 2;
	int last_menu_y = first_menu_y + distance * 3;
	// set y
	y = first_menu_y;

	do {
		gotoxy(x, y);
		// print cursor
		printf("▶");

		pressed_key = _getch();
		// remove cursor
		gotoxy(x, y);
		printf("  ");

		switch (pressed_key) {
		// ↑
		case UP:
			y -= distance;
			// press the UP key on the first menu
			if (y < first_menu_y) {
				// go to last menu
				y = last_menu_y;
			}
			break;
		
		// ↓
		case DOWN:
			y += distance;
			// press the DOWN key on the last menu
			if (y > last_menu_y) {
				// go to first menu
				y = first_menu_y;
			}
			break;

		default:
			break;
		}
	} while (pressed_key != ENTER);

	return y;
}

// check selected menu (chohadam, 21-03-20)
void menu_process(int selected_menu, int first_menu_y, int distance) {
	int last_menu_y = first_menu_y + distance * 4 + 2;
	while (selected_menu != last_menu_y) {
		// start
		if (selected_menu == first_menu_y) {

		}
		// game manual
		else if (selected_menu == first_menu_y + distance) {

		}
		// ranking
		else if (selected_menu == first_menu_y + distance * 2) {

		}
		// end
		else if (selected_menu = last_menu_y) {

		}
		// error
		else {
			printf("Something Wrong");
			exit(1);
		}
	}
}