#include "pushpull.h"
#include <conio.h>
#include <windows.h>

// _getch() value of ESC key
#define MAGIC_KEY 224
#define ESC 27
#define A 65
#define a 97
#define L 76
#define l 108
#define ENTER 13

void game_fun(void);
void start_game(void);

char key;
char t_name1[20];
char t_name2[20];
int x = 40;
int y = 11;
int win = 0;
int win_lose = 0;
int input = 0;

enum MENU
{
	GAMESTART = 0,
	EXIT
};

enum KEYBOARD
{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

// 게임 시작 메인 함수
void pushpull() {
	system("cls");
	PlaySound(TEXT("push.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1) {
		switch (game()) {
		case GAMESTART:
			x = 40;
			start_game();
			break;

		case EXIT:
			PlaySound(NULL, 0, 0);
			main();
			
			break;
		}
	}
	return 0;
}

// 게임 메인화면 함수
void main_show() {
	system("cls");
	gotoxy(36, 5);
	printf("★★★★★★★★★★ 줄다리기 ★★★★★★★★★");
	printf("★");
	gotoxy(36, 7);
	printf("★         A키와 L키를 마구마구 연타!!          ★");
	gotoxy(36, 9);
	printf("★ 줄을 가장 빨리 자기쪽으로 당기는 게임입니다! ★");
	gotoxy(36, 11);
	printf("★                 단판 승부!                   ★");
	gotoxy(36, 13);
	printf("★  게임종료를 선택해 메뉴화면으로 돌아가세요   ★");
	gotoxy(36, 15);
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★");

	gotoxy(40, 17);
	printf("●");
	gotoxy(39, 18);
	printf("＼|/");
	gotoxy(40, 19);
	printf(" |");
	gotoxy(40, 20);
	printf("/＼");

	x = 6;
	y = 5;
	print_auto_y(&x, &y, " ./＼＿／＼");
	print_auto_y(&x, &y, " ／ _/　_ ＼");
	print_auto_y(&x, &y, " |　━　 ━　i");
	print_auto_y(&x, &y, " ＼= (_人_) ");
	print_auto_y(&x, &y, "   ========");
	print_auto_y(&x, &y, "  ／￣￣⌒＼/⌒)―――――――");
	print_auto_y(&x, &y, ". /　　　　＿／　");
	print_auto_y(&x, &y, ". |　　　＼");
	print_auto_y(&x, &y, "  ＼ ＼_　＼");
	print_auto_y(&x, &y, "   ＼/.＼_/");

	x = 90;
	y = 10;
	print_auto_y(&x, &y, "    ⊂_＼");
	print_auto_y(&x, &y, "	＼＼ Λ＿Λ");
	print_auto_y(&x, &y, "	  ＼(ˇωˇ)    둠칫");
	print_auto_y(&x, &y, "	      > ⌒`");
	print_auto_y(&x, &y, "	      / へ＼");
	print_auto_y(&x, &y, "	     /　/＼＼");
	print_auto_y(&x, &y, "	     /  ノ　＼_つ");
	print_auto_y(&x, &y, "	    /  /");
	print_auto_y(&x, &y, "둠칫     /　/|");
	print_auto_y(&x, &y, "	  (   (`");
	print_auto_y(&x, &y, "	  | |、＼");
	print_auto_y(&x, &y, "	  | | ＼ ⌒)");
	print_auto_y(&x, &y, "	  | |　　) /");
	print_auto_y(&x, &y, "	 ノ )　　L/");
	print_auto_y(&x, &y, "      (___/     둠칫");



	gotoxy(77, 17);
	printf(" ●");
	gotoxy(76, 18);
	printf("＼|/");
	gotoxy(77, 19);
	printf(" |");
	gotoxy(77, 20);
	printf("/＼");

	gotoxy(56, 18);
	printf("게임 시작");
	
	gotoxy(56, 20);
	printf("게임 종료");

	print_by_name("최윤경");
}

// 메뉴 선택 커서 함수
enum MENU game(){
	int y = 0; 
	while (1){
		main_show();

		if (y <= 0)        
		{
			y = 0;
		}
		else if (y >= 4)
		{
			y = 2;
		}

		gotoxy(53, 18 + y); 
		printf(">");

		input = _getch();   

		if (input == MAGIC_KEY) 
		{
			switch (_getch())
			{
			case UP:            
				gotoxy(53, 18 + y);
				printf("  ");
				y = y - 2;
				break;
			case DOWN:           
				gotoxy(53, 18 + y);
				printf("  ");
				y = y + 2;
				break;
			}
		}
		else if (input == 13)
		{
			switch (y)            
			{
			case 0:   
				return GAMESTART;
			case 2:  
				return EXIT;
			}
		}
	}
}


// 줄다리기 그려주는 함수
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

	gotoxy(8, 9);
	printf("  _________");
	gotoxy(9, 10);
	printf("ㅣl  A  lㅣ");
	gotoxy(9, 11);
	printf("ㅣl____ lㅣ");
	gotoxy(9, 12);
	printf("ㅣ/_____ ");
	gotoxy(16, 12);
	printf("＼");
	gotoxy(17, 12);
	printf(" l");

	gotoxy(103, 9);
	printf("  _________");
	gotoxy(104, 10);
	printf("ㅣl  L  lㅣ");
	gotoxy(104, 11);
	printf("ㅣl____ lㅣ");
	gotoxy(104, 12);
	printf("ㅣ/_____ ");
	gotoxy(111, 12);
	printf("＼");
	gotoxy(112, 12);
	printf(" l");

	gotoxy(42, 2);
	printf("움직이지 않는다면 한영키를 바꿔보세요!");

	// x,y함수로 line그려줌 x =40, y = 11
	gotoxy(x, 11);
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

	char end = _getch();
	if (end == ESC) {
		pushpull();
	}

}

void start_game() {
	system("cls");
	gotoxy(47, 10);
	printf("시작 전 팀 이름을 정해주세요!\n");
	gotoxy(47, 12);
	printf("첫번째 팀 이름 > ");
	scanf_s("%s", &t_name1, 20);
	gotoxy(47, 14);
	printf("두번째 팀 이름 > ");
	scanf_s("%s", &t_name2, 20);

	// 이름 입력 후 화면 지우기
	system("cls");
	//line 그려줌
	line(x, y);
	//게임함수 실행
	game_fun();
}

void game_fun() {
	while (1) {
		char click = _getch();

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
			break;

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
			break;
		case ESC:
			pushpull();
		}
	}
}
	