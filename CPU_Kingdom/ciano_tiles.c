// The Game Made by Hadam Cho

#include "ciano_tiles.h"

// _getch() values
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// default coordinates
#define X 113
#define Y 25

// line spacing (menu)
#define DISTANCE 3

// menu coordinates
#define FIRST (Y + 2 + DISTANCE)
#define LAST (FIRST + 3 * DISTANCE)

// tile size
#define TILE_WIDTH 14
#define TILE_HEIGHT 6

// column
#define TILE_LINE 5

// global variables
// player name
char name[20];
// game score, fail count, current step
int score, fail, step = 1;

// functions
// menu
void draw_menu(void);
int select_menu(void);
void menu_process(int selected_menu);
// game
void game_process(void);
void get_player_name(void);
void draw_rectangle(void);
void game_ready(void);
void game_start(void);
void print_score(void);
// manual
void manual(void);
// modules
void print_str(int* x, int* y, char* str);
void print_tile(int x, int y);
void remove_tile(int x, int y);

void ciano_tiles(void) {
	system("cls");

	// draw menu
	draw_menu();

	// user select a menu
	int selected_menu = select_menu();

	// check selected menu
	menu_process(selected_menu);
}

void print_tile(int x, int y) {
	gotoxy(x, y);
	printf("■■■■■■■");
	gotoxy(x, y + 1);
	printf("■■■■■■■");
	gotoxy(x, y + 2);
	printf("■■■■■■■");
}

void remove_tile(int x, int y) {
	gotoxy(x, y);
	printf("              ");
	gotoxy(x, y + 1);
	printf("              ");
	gotoxy(x, y + 2);
	printf("              ");
}

// y += DISTANCE;
// gotoxy(x, y);
// printf("%s", str);
void print_str(int* x, int* y, char* str) {
	*y += DISTANCE;
	gotoxy(*x, *y);
	printf("%s", str);
}

// draw menu (chohadam 21-03-20)
void draw_menu(void) {
	int x = X;
	int y = Y;

	y -= DISTANCE;
	print_str(&x, &y, "      CIANO TILES");

	y += 2;
	print_str(&x, &y, "          시작");

	print_str(&x, &y, "        게임 방법");

	print_str(&x, &y, "          랭킹");

	print_str(&x, &y, "          종료");
}

// select menu (chohadam 21-03-20)
int select_menu(void) {
	// Enter, Up, Down
	char pressed_key;

	// set x, y
	int x = X;
	int y = FIRST;

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
			y -= DISTANCE;
			// press the UP key on the first menu
			if (y < FIRST) {
				// go to last menu
				y = LAST;
			}
			break;
		
		// ↓
		case DOWN:
			y += DISTANCE;
			// press the DOWN key on the last menu
			if (y > LAST) {
				// go to first menu
				y = FIRST;
			}
			break;

		default:
			break;
		}
	} while (pressed_key != ENTER);

	return y;
}

// check selected menu (chohadam, 21-03-20)
void menu_process(int selected_menu) {
	// start
	if (selected_menu == FIRST) {
		game_process();
	}
	// game manual
	else if (selected_menu == FIRST + DISTANCE) {
		manual();
	}
	// ranking
	else if (selected_menu == FIRST + DISTANCE * 2) {
		ciano_tiles();
	}
	// end
	else if (selected_menu == LAST) {
		return;
	}
	// error
	else {
		printf("Something Wrong");
		exit(1);
	}
}

// start game (chohadam, 21-03-22)
void game_process(void) {
	get_player_name();
	draw_rectangle();
	game_ready();
	game_start();
	_getch();
	ciano_tiles();
}

// input player name (chohadam, 21-03-23)
void get_player_name(void) {
	// clear console
	system("cls");

	// set x, y
	int x = X;
	int y = Y;

	// print description
	print_str(&x, &y, "이름을 입력해주세요.");
	print_str(&x, &y, ">> ");
	
	// input player name
	scanf_s("%s", &name, 20);
	fflush(stdin);
}

// draw the area where tiles down (chohadam, 21-03-22)
void draw_rectangle(void) {
	int x = X - 70;
	int y = Y - 13;

	int width = TILE_WIDTH / 2 * TILE_LINE + 2;
	int height = TILE_HEIGHT * 6 - 1;

	// clear console
	system("cls");

	// ┌――――┐
	gotoxy(x, y);
	printf("┌");
	for (int i = 1; i < width; i++) {
		printf("―");
	}
	printf("┐");

	// ｜      ｜
	// ├――――┤
	for (int i = 1; i < height; i++) {
		gotoxy(x, y + i);
		if (i == height - 4) {
			// ├――――┤
			printf("├");
			for (int j = 1; j < width; j++) {
				printf("―");
			}
			printf("┤");
		}
		else {
			// ｜      ｜
			printf("｜");

			for (int j = 1; j < width - 1; j++) {
				printf("　");
			}
			printf(" ");

			printf("｜");
		}
	}

	// └――――┘
	gotoxy(x, y + height);
	printf("└");
	for (int i = 1; i < width; i++) {
		printf("―");
	}
	printf("┘");
}

// game ready description (chohadam, 21-03-22)
void game_ready(void) {
	int x = X - 50;
	int y = Y + 5;

	// print description
	gotoxy(x, y);
	printf(">>   아무 키나 누르면 게임이 시작됩니다.");

	_getch();

	// remove description
	gotoxy(x, y);
	printf("                                        ");
}

// start block down (chohadam, 21-03-24)
void game_start(void) {
	// draw rectangle x - 2
	// draw rectangle y - 1
	int x = X - 68;
	int y = Y - 12;

	int rnd = rand() % TILE_LINE;
	int tile_y = y;
	int tile_x[TILE_LINE] = {
		x,
		x + TILE_WIDTH,
		x + TILE_WIDTH * 2,
		x + TILE_WIDTH * 3,
		x + TILE_WIDTH * 4
	};

	// 유저 영역 시작
	int user_y = Y - 13 + TILE_HEIGHT * 6 - 4;
	int user_x = x;

	// setting use random
	srand((unsigned int)time(NULL));

	// default delay time
	int delay = 40;

	char pressed_key;
	while ((pressed_key = get_key()) != ESC) {
		// print name, score, fail, step, etc.
		print_score();

		// print user tile
		print_tile(user_x, user_y);

		// print tile during delay time
		print_tile(tile_x[rnd], tile_y);
		Sleep(delay);
		remove_tile(tile_x[rnd], tile_y);

		// 시작점 + (타일 높이 * 6) - 유저 영역 - 위 아래
		if (tile_y < y + TILE_HEIGHT * 6 - 6 - 3) {
			// falling
			tile_y += 1;
		}
		else {
			if (tile_x[rnd] == user_x) {
				// tile position == user tile position
				score += 100;
			}
			else {
				// fail
				score -= 50;
				fail += 1;
				if (fail == 5) {
					// game over
					break;
				}
			}
			// get random number
			rnd = rand() % TILE_LINE;
			// top
			tile_y = y;
		}

		// remove user tile
		remove_tile(user_x, user_y);
		// move user tile
		move_arrow_key(
			pressed_key,
			&user_x,
			&user_y,
			TILE_WIDTH,
			user_y,
			user_y,
			x,
			x + TILE_WIDTH * 4
		);

		// set step and delay time
		if (score >= 500 && score < 1500) {
			// stage 2
			step = 2;
			delay = 30;
		}
		else if (score >= 1500 && score < 3000) {
			// stage 3
			step = 3;
			delay = 20;
		}
		else if (score >= 3000 && score < 5000) {
			// stage 4
			step = 4;
			delay = 10;
		}
		else if (score >= 5000) {
			// stage 5
			step = 5;
			delay = 5;
		}
	}
}

// print score, fail, step, etc. (chohadam, 21-03-24)
void print_score(void) {
	int x = X + 55;
	int y = Y - 7;

	// string temp
	char str[20];

	sprintf_s(str, sizeof(str), "[  %s  ] 님", name);
	print_str(&x, &y, str);

	sprintf_s(str, sizeof(str), "%d단계", step);
	print_str(&x, &y, str);

	y += DISTANCE;
	sprintf_s(str, sizeof(str), "점수\t\t\t%5d", score);
	print_str(&x, &y, str);

	sprintf_s(str, sizeof(str), "실패\t\t\t%5d", fail);
	print_str(&x, &y, str);

	print_str(&x, &y, "이동\t\t\t← →");

	print_str(&x, &y, "종료\t\t\t  ESC");
}

// print game manual (chohadam, 21-03-21)
void manual(void) {
	// clear console
	system("cls");

	// set x, y
	int x = X - 55;
	int y = Y - 8;

	// draw game screenshot
	print_tile(x, y);

	y += DISTANCE * 2;
	print_str(&x, &y, "      │      ");
	y -= DISTANCE - 1;
	print_str(&x, &y, "      ↓      ");

	y += DISTANCE * 2;
	print_tile(x, y);
	y -= 2;
	x -= 6;
	print_str(&x, &y, "←");
	y -= DISTANCE;
	x += 24;
	print_str(&x, &y, "→");

	x = X - 20;
	y = Y - 9;
	print_str(&x, &y, "1단계");
	y += 1;
	print_str(&x, &y, "점수\t\t0");
	print_str(&x, &y, "실패\t\t0");
	y += 1;
	print_str(&x, &y, "이동\t\t← →");
	print_str(&x, &y, "종료\t\tESC");


	// draw description
	x = X + 40;
	y = Y - 13;

	y -= DISTANCE;
	print_str(&x, &y, "각 칸에 내려오는 타일과 같은 위치에");

	print_str(&x, &y, "블럭을 가져다 놓으면");

	print_str(&x, &y, "점수가 100점씩 올라갑니다.");

	print_str(&x, &y, "실패할 경우 50점 감점되며");

	print_str(&x, &y, "5번 실패할 경우 게임이 종료되고");

	print_str(&x, &y, "점수가 기록됩니다.");

	y += DISTANCE;
	print_str(&x, &y, "점수가 오를 수록 타일이 내려오는");

	print_str(&x, &y, "속도가 빨라집니다.");

	y += DISTANCE;
	print_str(&x, &y, "지금 바로 1등하러 GO GO!");

	y += DISTANCE * 3;
	x -= 45;
	print_str(&x, &y, ">> 아무 키나 누르면 메뉴로 이동합니다.");

	_getch();

	// go to the menu
	ciano_tiles();
}