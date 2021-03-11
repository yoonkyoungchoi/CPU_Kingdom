#include "modules.h"

// _getch() value of arrow key (chohadam 21-03-11)
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// coordinate minimum, maximum (chohadam 21-03-11)
#define X_MIN 2
#define Y_MIN 1
#define X_MAX 238
#define Y_MAX 62

// move the cursor funtion (chohadam 21-03-11)
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// find out the pressed key function (chohadam 21-03-11)
int get_key(void) {
	// if keyboard pressed
	if (_kbhit()) {
		// return pressed value
		return _getch();
	}
	return 1;
}

// move to the arrow key function (chohadam 21-03-11)
void move_arrow_key(char key, int* x, int* y) {
	// moving size
	int size = 1;

	switch (key) {
	// pressed ก่
	case UP:
		*y -= size;
		if (*y < Y_MIN) *y = Y_MIN;
		break;
	// pressed ก้
	case DOWN:
		*y += size;
		if (*y > Y_MAX) *y = Y_MAX;
		break;
	// pressed ก็
	case LEFT:
		*x -= size;
		if (*x < X_MIN) *x = X_MIN;
		break;
	// pressed กๆ
	case RIGHT:
		*x += size;
		if (*x > X_MAX) *x = X_MAX;
		break;
	}
}