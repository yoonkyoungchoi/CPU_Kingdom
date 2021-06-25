#include "snake_game.h"

// _getch() value of ESC key
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ENTER 13

#define MAP_X 16
#define MAP_Y 5
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int x_move[100], y_move[100];
int target_x, target_y;
int length;
int speed;
int score;
int best_score = 0;
int last_score = 0;
int dir;
int key;
int status_on = 0;


int choose_mode() {
    system("cls");


    int x = 54;
    int y = 22;

    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y - 1 , "                       /)* ��*)/)                          ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y    , "                   __��������������                         ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 1, "                 �������������� ���� �Ѥ�                   ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 2, "                /���������ܡ�����   ���� |                  ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 3, "                !������������ �� ��      |                  ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 4, "                 `_ �� ������ �� ��   ��/                   ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 5, "                     **�ѣʤѤѤѤѣ�                       ");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 6,  "===============------------------------------==============");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 8,  "=                                                         =");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 9,  "=            ����Ű�� ����ؼ� �����̸� ��������!         =");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 11,  "=������ ���̴� ������ ���� �� ���� ���̰� ���ݾ� �þ��!=");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 13, "=           �ӵ��� ���ݾ� �������� �����ϼ���!            =");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 14, "=                                                         =");
    print(MAP_X + (MAP_WIDTH / 2) - 15, MAP_Y + 15, "===========================================================");
    print(MAP_X + (MAP_WIDTH / 2) - 5, MAP_Y + 17,  ">   �� �� �� �� \n");
    print(MAP_X + (MAP_WIDTH / 2) - 5, MAP_Y + 19,  "       �� �� \n");
    
    void print_auto_y(int* x, int* y, char* str);
    print_by_name("���Ҹ�");



    while (1) {
        int n = keyControl();
        switch (n) {
            case UP: {
                if (y > 22) {
                    gotoxy(x - 2, y);
                    printf(" ");

                    gotoxy(x - 2, y -= 2);
                    printf(">");
                }
                break;
            }
            case DOWN: {
                if (y < 24) {
                    gotoxy(x - 2, y);
                    printf(" ");

                    gotoxy(x - 2, y += 2);
                    printf(">");
                }
                break;
            }
            case ENTER: {
                return y - 22;
            }
        }
    }
    return 0;
}

void snake_game(void) {
	PlaySound(TEXT("snake.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    while (1) {
        int select = choose_mode();
        switch (select) {
        case 0:
            snake_start();
            break;
        case 2:
			PlaySound(NULL, 0, 0);
			main();
            break;
        }
        //system("cls");
    }
}

void snake_start(void) {
    system("cls");

    title();

    while (1) {
        if (_kbhit()) do { key = _getch(); } while (key == 224);
        Sleep(speed);

        switch (key) {
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) ||
                (dir == DOWN && key != UP))
                dir = key;
            key = 0;
            break;
        case ESC:
			main();
			break;
        }
        move(dir);

    }
}

void title(void) {

    int i, j;

    while (_kbhit()) _getch();

    draw_map();
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        for (j = MAP_X + 1; j < MAP_X + MAP_WIDTH - 1; j++) gotoxy(j, i, "  ");
    }

    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "+--------------------------+");
    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6, "|        S N A K E         |");
    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7, "+--------------------------+");

    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, " < PRESS ANY KEY TO START > ");

    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11, "   �� ��,��,��,�� : Move      ");
    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, "   �� ESC : Quit the game             ");

    while (1) {
        if (_kbhit()) {
            key = _getch();
            if (key == ESC) main();
            else break;
        }
        print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, " < PRESS ANY KEY TO START > ");
        Sleep(400);
        print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9, "                            ");
        Sleep(400);

    }
    reset();
}

void reset(void) {
    int i;
    system("cls");
    draw_map();
    while (_kbhit()) _getch();

    dir = LEFT;
    speed = 120;
    length = 5;
    score = 0;
    for (i = 0; i < length; i++) {
        x_move[i] = MAP_WIDTH / 2 + i;
        y_move[i] = MAP_HEIGHT / 2;
        print(MAP_X + x_move[i], MAP_Y + y_move[i], "��");
    }
    print(MAP_X + x_move[0], MAP_Y + y_move[0], "��");
    target();
}

void draw_map(void) {
    int i, j;
    for (i = 0; i < MAP_WIDTH; i++) {
        print(MAP_X + i, MAP_Y, "��");
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        print(MAP_X, i, "��");
        print(MAP_X + MAP_WIDTH - 1, i, "��");
    }
    for (i = 0; i < MAP_WIDTH; i++) {
        print(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, "��");
    }
}

void move(int dir) {
    int i;

    if (x_move[0] == target_x && y_move[0] == target_y) {
        score += 10;
        target();
        length++;
        x_move[length - 1] = x_move[length - 2];
        y_move[length - 1] = y_move[length - 2];
    }
    if (x_move[0] == 0 || x_move[0] == MAP_WIDTH - 1 || y_move[0] == 0 || y_move[0] == MAP_HEIGHT - 1) {
        over();
        return;
    }
    for (i = 1; i < length; i++) {
        if (x_move[0] == x_move[i] && y_move[0] == y_move[i]) {
           over();
            return;
        }
    }

    print(MAP_X + x_move[length - 1], MAP_Y + y_move[length - 1], "  ");
    for (i = length - 1; i > 0; i--) {
        x_move[i] = x_move[i - 1];
        y_move[i] = y_move[i - 1];
    }
    print(MAP_X + x_move[0], MAP_Y + y_move[0], "��");
    if (dir == LEFT) --x_move[0];
    if (dir == RIGHT) ++x_move[0];
    if (dir == UP) --y_move[0];
    if (dir == DOWN) ++y_move[0];
    print(MAP_X + x_move[i], MAP_Y + y_move[i], "��");
}

void over(void) { //�������� �Լ� 
    print(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 5, "+----------------------+");
    print(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 6, "|      GAME OVER..     |");
    print(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    print(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, " YOUR SCORE : ");
    printf("%d", last_score = score);

    print(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, " PRESS ENTER KEY TO RESTART.. ");

    if (score > best_score) {
        best_score = score;
        print(MAP_X + (MAP_WIDTH / 2) - 4, MAP_Y + 10, "�� BEST SCORE ��");
    }
    Sleep(500);
    if (_kbhit()) {
        key = _getch();
        if (key == ENTER)
            title();
        if (key == ESC)
            main();
    }
}

void target(void) {
    int i;

    int target_crush_on = 0;
    int r = 0;
    print(MAP_X, MAP_Y + MAP_HEIGHT + 2, " YOUR SCORE: ");
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

    while (1) {
        target_crush_on = 0;
        srand((unsigned)time(NULL) + r);
        target_x = (rand() % (MAP_WIDTH - 2)) + 1;
        target_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) {
            if (target_x == x_move[i] && target_y == y_move[i]) {
                target_crush_on = 1;
                r++;
                break;
            }
        }

        if (target_crush_on == 1) continue;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        print(MAP_X + target_x, MAP_Y + target_y, "��");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        speed -= 8;
        break;

    }
}

void print(int x_location, int y_location, char* s) {
    COORD pos = { 2 * x_location,y_location };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}