#include "maze_game.h"

// 키보드
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

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

// 움직이기
//void gotoxy(int x, int y)
//{
//	COORD pos;
//	pos.X = x;
//	pos.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}

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
	if (row == 21) {
		maze[13][19] = 3;
		for (int i = 0; i < row; i += 3) {
			for (int j = 0; j < row; j += 5) {
				if (maze[i][j] != 0) {
					maze[i][j] = 4;
				}
			}
		}
		maze[5][5] = 4;
	}
	else if (row == 25) {
		maze[13][23] = 3;
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
			gotoxy(40 + (j * 2), 10 + i);
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

	// 세부 정보 출력(21-04-02)
	textcolor(15);
	gotoxy(130, 15);
	printf("점수 : %d", score);

	gotoxy(130, 17);
	textcolor(9);
	printf("♥");
	gotoxy(132, 17);
	textcolor(15);
	printf(" : 점수");

	gotoxy(130, 19);
	textcolor(12);
	printf("★ ");
	gotoxy(132, 19);
	textcolor(15);
	printf(" : 출구");


	gotoxy(cur.X, cur.Y);
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
		gotoxy(100, 50);
		for (int helper = 0; helper <= 15; helper++) {
			gotoxy(100, 10); textcolor(helper); //막 승리했다고 띄워주면 마무리되겠죠?
			printf("★탈출했습니다!★");
			Sleep(100);
			//system("pause");
		}
		gotoxy(100, 12);
		printf("점수 : %d", score);
		exit(1);
	}

	// ♥(점수)를 얻었을 때
	else if (maze[*x1][*y1] == 4) {
		score += 10;
		COORD cur = getCursor();
		maze[*x1][*y1] = 5;

		printf("  ");
		gotoxy(cur.X + x, cur.Y + y);

		gotoxy(136, 15);
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
	gotoxy(42, 10);  //케릭터 시작위치
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
		}

	}
}

void maze_game(void) {
	system("title mazeGame");
	system("cls");
	removeCursor();

	int choose;
	gotoxy(70, 10);
	printf("1. 1단계 모드(21x21)\n");
	gotoxy(70, 12);
	printf("2. 2단계 모드(25x25)\n");
	gotoxy(70, 14);
	printf("3. 종료 하기\n");


	while (1) {
		gotoxy(70, 18);
		printf("원하는 모드를 선택하세요 >> ");
		scanf_s("%d", &choose);

		switch (choose) {
		case 1:
			showBoard(21, 21);
			character_static();
			break;
		case 2:
			showBoard(25, 25);
			character_static();
			break;
		case 3:
			exit(1);
		default:
			gotoxy(70, 20);
			printf("다시 입력해주세요.");
			continue;
		}
	}
	// 동적 할당 후 free()
	free(**maze);
}