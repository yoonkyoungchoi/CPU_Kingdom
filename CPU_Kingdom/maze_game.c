#include "maze_game.h"

// 키보드
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

// 미로 찾기 단계
#define STEP1 19
#define STEP2 21
#define STEP3 25
#define STEP4 27

// 기타 필요한 것
#define DELAY 100
#define EXIT 50

// 전역변수
int** maze;
int num1 = 0;
int num2 = 1;
int* x1 = &num1;
int* y1 = &num2;
int score = 0;

// 함수 선언
COORD getCursor(void);
void removeCursor(void);
void textcolor(int color_number);
void showBoard(int row, int col);
void showCharacter(void);
int detect(int x, int y);
void RemoveCharacter_Set(int x, int y);
void character_static(void);
void ShowInfo(void);
void secondView(void);


// 현재 커서 위치 가져오기
COORD getCursor(void)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO pos;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
	curPoint.X = pos.dwCursorPosition.X;
	curPoint.Y = pos.dwCursorPosition.Y;
	return curPoint;
}

// 커서 없애기
void removeCursor(void)
{
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

// 색 변화주기
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

// 미로 랜덤 생성 (21-03-18)
void showBoard(int row, int col)
{
	system("cls");
	int i, j, k = 0;
	COORD cur = getCursor();

	struct room {
		int r;
		int c;
	}*unknown;

	struct candidate_room {
		int r;
		int c;
		int d;
	}*candidate;


	int view_i, view_j, d, chk_cnt;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} }; //상하좌우

	//2차원 배열처럼 사용할 maze 생성
	maze = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) maze[i] = (int*)malloc(sizeof(int) * col);


	//미로 방 전체 개수. 벽을 제외한 방의 개수 
	chk_cnt = (row / 2) * (col / 2);

	//미지 리스트 준비
	unknown = (struct room*)malloc(sizeof(struct room) * chk_cnt);

	//후보 미로 리스트 준비
	candidate = (struct candidate_room*)malloc(sizeof(struct candidate_room) * chk_cnt);

	//미로 행렬 전체를 벽(0)으로 채우고, 모든 방을 미지 리스트에 차례로 삽입 
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			maze[i][j] = 0;
			if (i % 2 == 1 && j % 2 == 1) {
				unknown[k].r = i;
				unknown[k].c = j;
				k++;
			}
		}
	}

	srand((unsigned int)time(NULL));

	//임의의 방을 선택하고 미로 표시
	k = (int)rand() % chk_cnt;
	maze[unknown[k].r][unknown[k].c] = 1;

	//미지 리스트에서 제외. 끝 방의 좌표를 k 방으로 이동
	chk_cnt--; //미지 리스트에서 하나 줄임
	unknown[k].r = unknown[chk_cnt].r;
	unknown[k].c = unknown[chk_cnt].c;

	//미지 리스트에 방이 남아 있으면 반복
	while (chk_cnt > 0) {

		//임의의 방을 선택
		k = (int)rand() % chk_cnt;
		i = unknown[k].r;
		j = unknown[k].c;

		//후보 미로 리스트에 추가 
		k = 0;
		candidate[k].r = i;
		candidate[k].c = j;
		maze[i][j] = 2;

		//미로 만날 때까지 반복
		while (1) {

			d = (int)rand() % 4;
			view_i = i + move[d][0];
			view_j = j + move[d][1];

			//미로 범위 밖이면 다시 방향 정함 
			if (view_i < 1 || view_i > row - 2 || view_j < 1 || view_j > col - 2) continue;

			//미로 범위내 이면 방향 저장하고
			candidate[k].d = d;
			//다음 이동할 방을 일단 후보에 추가 
			k++;
			candidate[k].r = view_i;
			candidate[k].c = view_j;
			//다음 방이 미지이면 전진하고 후보 미로임을 표시 
			if (maze[view_i][view_j] == 0) {
				i = view_i;
				j = view_j;
				maze[i][j] = 2;
			}
			else if (maze[view_i][view_j] == 1)break; //미로를 만나면 빠져나감

			else { //maze[view_i][view_j] == 2 일 때, 후보 미로를 만났으므로 사이클을 제거함
				//이전 후보
				k--;
				do { //(view_i, view_j)를 만날 때까지 취소해 나감
					//이전으로 되돌아 가면서 후보(2)를 취소(0)함
					maze[candidate[k].r][candidate[k].c] = 0;
					k--;
				} while (candidate[k].r != view_i || candidate[k].c != view_j);
				//사이클의 원점으로 돌아와 다시 미로 찾아 나섬
				i = view_i;
				j = view_j;
			}
		}

		//임의 지점에서 미로를 만난 지점까지 미로 표시하고 미로방마다 미지리스트에서 제거함 
		for (i = 0; i < k; i++) {
			maze[candidate[i].r][candidate[i].c] = 1;
			switch (candidate[i].d) {
			case 0: maze[candidate[i].r - 1][candidate[i].c] = 1; break;
			case 1: maze[candidate[i].r + 1][candidate[i].c] = 1; break;
			case 2: maze[candidate[i].r][candidate[i].c - 1] = 1; break;
			case 3: maze[candidate[i].r][candidate[i].c + 1] = 1;
			}
			//미지 리스트에서 하나 줄임
			chk_cnt--;
			//후보 위치 탐색
			for (j = 0; j < chk_cnt; j++) if (candidate[i].r == unknown[j].r && candidate[i].c == unknown[j].c) break;
			//후보가 미로로 변경되면서 리스트에서 제외. 끝 방의 좌표를 j 방으로 이동
			unknown[j].r = unknown[chk_cnt].r;
			unknown[j].c = unknown[chk_cnt].c;
		}
	}
	// 동적할당 후 free()
	free(unknown);
	free(candidate);

	// 시작 배열 좌표
	maze[0][1] = 2;

	// 미로 크기에 따라 ♥ 위치 다르게 설정
	if (row == STEP1) {
		maze[13][17] = 3;
		for (int i = 0; i < row; i += 3) {
			for (int j = 0; j < row; j += 5) {
				if (maze[i][j] != 0) {
					maze[i][j] = 4;
				}
			}
		}
	}
	else if (row == STEP2) {
		maze[19][19] = 3;
		for (int i = 0; i < row; i += 3) {
			for (int j = 0; j < row; j += 5) {
				if (maze[i][j] != 0) {
					maze[i][j] = 4;
				}
			}
		}
		maze[5][5] = 4;
	}
	else if (row == STEP3) {
		maze[21][23] = 3;
		for (int i = 0; i < row; i += 3) {
			for (int j = 0; j < row; j += 5) {
				if (maze[i][j] != 0) {
					maze[i][j] = 4;
				}
			}
		}
	}
	else if (row == STEP4) {
		maze[25][25] = 3;
		for (int i = 0; i < row; i += 3) {
			for (int j = 0; j < row; j += 5) {
				if (maze[i][j] != 0) {
					maze[i][j] = 4;
				}
			}
		}
	}

	//미로를 출력함	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
		{
			gotoxy(10 + (j * 2), 2 + i);
			if (maze[i][j] == 0) {
				textcolor(8);
				printf("■");
			}
			else if (maze[i][j] == 3) {
				textcolor(12);
				printf("★");
			}
			else if (maze[i][j] == 4) {
				textcolor(9);
				printf("♥");
			}
			else printf("　");
		}
		printf("\n");
	}
	ShowInfo();
	gotoxy(cur.X, cur.Y);
}

// 정보 보여주기
void ShowInfo(void) {
	int info_x = 75;
	int info_x1 = 90;
	// 세부 정보 출력(21-04-02)
	textcolor(15);
	gotoxy(info_x, 1);
	printf("________________");
	gotoxy(info_x, 3); printf("|");				gotoxy(info_x1, 3); printf("|");
	gotoxy(info_x, 4); printf("|");				gotoxy(info_x1, 4); printf("|");
	gotoxy(info_x, 5); printf("|");				gotoxy(info_x1, 5); printf("|");
	gotoxy(info_x, 6);
	printf("________________");

	textcolor(15);
	gotoxy(info_x + 3, 4);
	printf("점수 :");

	gotoxy(77, 9);
	textcolor(9);
	printf("♥");
	gotoxy(80, 9);
	textcolor(15);
	printf(" : 점수");

	gotoxy(77, 11);
	textcolor(12);
	printf("★ ");
	gotoxy(80, 11);
	textcolor(15);
	printf(" : 출구");
}

// ● 출력 (21-03-29)
void showCharacter(void)
{
	COORD cur = getCursor();

	textcolor(14);
	printf("●");
	gotoxy(cur.X, cur.Y);
}

// 현재 캐릭터 상태(21-03-26)
int detect(int x, int y)
{

	// 커서 위치 얻기 
	COORD cur = getCursor();
	if (x == 2) {
		*x1 = *x1 + y;
		*y1 = *y1 + 1;
	}
	else if (x == -2) {
		*x1 = *x1 + y;
		*y1 = *y1 + (-1);
	}
	else {
		*x1 = *x1 + y;
		*y1 = *y1 + x;
	}

	// 미로의 범위를 벗어났을 때
	if (!((*x1 >= 0 && *x1 < 25) && (*y1 >= 0 && *y1 < 25)))
	{
		return 1;
	}


	if (maze[*x1][*y1] == 0) {   // 벽일 때
		if (x == 2) {
			*x1 = *x1 - y;
			*y1 = *y1 - 1;
		}
		else if (x == -2) {
			*x1 = *x1 - y;
			*y1 = *y1 - (-1);
		}
		else {
			*x1 = *x1 - y;
			*y1 = *y1 - x;
		}
		return 1;
	}

	// ★(출구)에 도착했을 때
	else if (maze[*x1][*y1] == 3) {
		system("cls");
		gotoxy(50, 50);
		for (int helper = 0; helper <= 15; helper++) {
			gotoxy(50, 30); textcolor(helper); //막 승리했다고 띄워주면 마무리되겠죠?
			printf("★탈출했습니다!★");
			Sleep(100);
		}
		secondView();
	}

	// ♥(점수)를 얻었을 때
	else if (maze[*x1][*y1] == 4) {
		score += 10;
		maze[*x1][*y1] = 7;
		COORD cur = getCursor();

		printf("  ");
		gotoxy(cur.X + x, cur.Y + y);

		gotoxy(86, 4);
		textcolor(10);
		printf("%d", score);
		gotoxy(cur.X + x, cur.Y + y);
	}

	else     // 벽이 아닐 때
		return 0;
}

// ●(캐릭터) 잔상 없애기 (21-03-19)
void RemoveCharacter_Set(int x, int y)
{
	int value = detect(x, y);

	if (value == 0)
	{
		COORD cur = getCursor();

		printf("  ");
		gotoxy(cur.X + x, cur.Y + y);

	}
}

// ●(캐릭터) 움직이기(21-03-19)
void character_static(void)
{
	int kb;
	gotoxy(12, 2);  //케릭터 시작위치
	while (1)
	{
		while (!_kbhit())
		{
			showCharacter();
			Sleep(DELAY);
		}
		kb = _getch();
		switch (kb)
		{
		case UP:
			RemoveCharacter_Set(0, -1);
			break;
		case DOWN:
			RemoveCharacter_Set(0, 1);
			break;
		case RIGHT:
			RemoveCharacter_Set(2, 0);

			break;
		case LEFT:
			RemoveCharacter_Set(-2, 0);
			break;
		case ESC:
			textcolor(15);
			gotoxy(0, 0);
			printf("미로찾기를 끝냅니다.");
			Sleep(1000);
			system("cls");
			secondView();
		}
	}
}

void secondView(void) {
	int secondView_x = 46;
	system("cls");
	int choose;

	gotoxy(secondView_x, 7);
	printf("점수 : %d", score);
	int x = 9;
	gotoxy(secondView_x, x);
	printf("1. 1단계 모드(19x19)\n");
	gotoxy(secondView_x, x + 2);
	printf("2. 2단계 모드(21x21)\n");
	gotoxy(secondView_x, x + 4);
	printf("3. 3단계 모드(25x25) \n");
	gotoxy(secondView_x, x + 6);
	printf("4. 4단계 모드(27x27)\n");
	gotoxy(secondView_x, x + 8);
	printf("5. 종료 하기\n");


	while (1) {
		gotoxy(secondView_x, x + 10);
		printf("원하는 모드를 선택하세요 >> ");
		scanf_s("%d", &choose);

		switch (choose) {
		case 1:
			showBoard(STEP1, STEP1);
			character_static();
			break;
		case 2:
			showBoard(STEP2, STEP2);
			character_static();
			break;
		case 3:
			showBoard(STEP3, STEP3);
			character_static();
			break;
		case 4:
			showBoard(STEP4, STEP4);
			character_static();
			break;
		case 5:
			main();
		default:
			gotoxy(70, 20);
			printf("다시 입력해주세요.");
			continue;
		}
	}
}

void maze_game(void) {
	system("title mazeGame");
	system("cls");
	removeCursor();

	secondView();

	// 동적 할당 후 free()
	free(**maze);
	return 0;
}