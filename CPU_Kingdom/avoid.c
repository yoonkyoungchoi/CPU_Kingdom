#include "avoidgame.h"

//사용자 정의 세미콜론 없어야함
#define CT 29
#define WIDTH 59
#define HEIGHT 20
#define TRUE 1
#define FALSE 0
#define LV1 100
#define LV2 50
#define LV3 17
#define LV4 5
#define ESC 27

//전역변수 선언
Snow snow[WIDTH - CT];
Player one;
clock_t start, c;
double time1;
double max_time = 0, cn;
int revelnum;
int nowrevel;
int speed;
int len = WIDTH - CT;

//// 초기값 ////
void init()
{
    int i;
    for (i = 0; i < len; i++)
        snow[i].con = FALSE;
    //플레이어 위치는 중앙
    one.x = (WIDTH * 2) / 2;
}

//// 피할 적들 처리 ////
/* 적 생성 */
void CreateEnemy()
{
    int i;

    for (i = 0; i < len; i++)
    {
        //해당 인덱스[i]에 적이 없으면 (FALSE 이면 실행)
        if (!snow[i].con)
        {
            //가로 (x축) 무작위로 적 출현, 세로(y축)은 출현 위치 항상 일치
            snow[i].x = (rand() % (WIDTH + 3)) + CT;
            snow[i].y = HEIGHT - 2;
            //적이 출현한 인덱스 [i]의 상태 = TRUE로 변경
            snow[i].con = TRUE;
            return;
        }
    }
}
/* 적의 움직임 */
int FallEnemy()
{
    int i;
    for (i = 0; i < len; i++)
    {
        //해당 인덱스 [i]에 적이 있으면 (TRUE라면) 움직임 실행
        if (snow[i].con)
        {
            snow[i].y--;
            if ((snow[i].y == 0) && (snow[i].x == one.x)) return TRUE;
        }
    }
    return FALSE;

}
/* 피하기 성공한 적(바닥에 떨어진 적) 삭제 */
void DelEnemy()
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (snow[i].con && snow[i].y < 0)
            snow[i].con = FALSE;
    }
}
/* 플레이어가 적에게 닿을 경우 (패배) */
int DamagedPlayer()
{
    int i;
    for (i = 0; i < len; i++)
    {
        //적의 상태가 TRUE && 적의 위치가 y=0 즉 바닥 && 적의 x축 위치 = 플레이어의 x축 위치
        if ((snow[i].con && snow[i].y == 0) && (snow[i].x == one.x || snow[i].x - 1 == one.x))
            return TRUE;
    }
    //닿지 않았으면 FALSE 반환
    return FALSE;
}

//// 플레이어 처리 ////
/* 키 다운 처리 */ 
int isKeyDown(int key)
{
    //***GetAsyncKey는 키가 눌렸다면 최상위 비트를 1로 설정, 이전에 키가 눌렸다면 최하위 비트를 1로 설정
    //0x8000은 최상위 비트 -> 16진수는 2비트가 4개 모인 비트 -> 0x8000 = 1000 0000 0000 0000를 의미
    // 즉 최하위 비트는 0x0001 -> 0000 0000 0000 0001
    // 따라서 (GetAsyncKeyState(key) & 0x8000) != 0 은 현재 키가 눌려있다면 참(TRUE)
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

/* 플레이어 이동 (좌/우) */
int MovePlayer()
{
    //왼쪽 방향키 입력 시
    if (isKeyDown(VK_LEFT))
        one.x--;
    //오른쪽 방향키 입력 시
    if (isKeyDown(VK_RIGHT))
        one.x++;
    if (DamagedPlayer()) return TRUE; 
    if (isKeyDown(VK_ESCAPE))
        main();
    //위치 범위 제한
    if (one.x < CT)
        one.x = CT;
    if (one.x > WIDTH * 2 - CT - 1)
        one.x = WIDTH * 2 - CT - 1;
    return FALSE;
}

//// 게임 화면 출력 ////
void PrintGame()
{
    //모든 화면 clear
    system("cls");

    //gotoxy(0, HEIGHT + 2); // (WIDTH /2) - 7
    //레벨 출력
    //printf("\n");
    gotoxy(CT, 1);
    switch (nowrevel) {
    case 1: {printf("【\tLv.1\t│");  break; }
    case 2: {printf("【\tLv.2\t│");  break; }
    case 3: {printf("【\tLv.3\t│");  break; }
    default: {printf("【\tLv.4\t│"); break; }
    }
    printf("\t      CPU 피하기 게임\t      "); //중간 title
    //현재시간 출력
    printf("│    %.1f초   】\n", cn);
    gotoxy(CT, 2);
    int i;
    for (i = CT; i < WIDTH; i++)
        printf("──");//▩

    for (i = 0; i < len; i++)
    {
        if (snow[i].con)
        {
            //적 위치에 적군 출력
            gotoxy(snow[i].x, HEIGHT - snow[i].y);
            printf("o");
        }
    }
    //플레이어 출력
    gotoxy(one.x, HEIGHT);
    printf("♀");

    //바닥 출력
    gotoxy(CT, HEIGHT + 1);
    for (i = CT; i < WIDTH + 1; i++)
        printf("▲");//▩
    printf("\n");
    //이름 넣기
    //gotoxy(93, 30);
    //printf(" by 전유리 고에스더 김민주 ");

}

//타이머 함수 : clock();
//타이머 시작
void startTimer() {
    start = clock();
}
//타이머 끝
void endTimer() {
    system("cls");

    clock_t end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC; //초단위 변환

}

//게임 끝났을때 메뉴
bool Outgame(void) {
    bool Bet;
    int wt = 45, push;    //열중앙 조절바 

    //경과시간 출력
    PlaySound(NULL, 0, 0);
    gotoxy(wt, 5);
    printf("┌───────────────────────┐\n");
    gotoxy(wt, 6);
    printf("│                       │\n");
    gotoxy(wt, 7);
    if (time1 < 10.0)  printf("│   경과시간 :  %0.1lf초   │\n", time1); //10미만이면 앞에 0붙이기
    else  printf("│   경과시간 : %0.1lf초   │\n", time1); //앞이 두자리면 그대로
    gotoxy(wt, 8);
    printf("│                       │\n");
    gotoxy(wt, 9);
    printf("│ 〓〓〓〓〓〓〓〓〓〓〓│\n");

    //최고기록 구하기
    if (time1 > max_time) { max_time = time1; }

    //최고기록 출력
    gotoxy(wt, 10);
    printf("│                       │\n");
    gotoxy(wt, 11);
    if (max_time < 10.0) printf("│   최고기록 :  %0.1lf초   │\n", max_time); //10미만이면 앞에 0붙이기
    else printf("│   최고기록 : %0.1lf초   │\n", max_time); //앞이 두자리면 그대로
    gotoxy(wt, 12);
    printf("│                       │\n");
    gotoxy(wt, 13);
    printf("│ 〓〓〓〓〓〓〓〓〓〓〓│\n");
    gotoxy(wt, 14);
    printf("│                       │\n");
    gotoxy(wt, 15);
    printf("│   그만하기   다시하기 │\n");
    gotoxy(wt, 16);
    printf("│                       │\n");
    gotoxy(wt, 17);
    printf("│     Y      :     N    │");
    gotoxy(wt, 18);
    printf("└───────────────────────┘\n");
    //이름 넣기
    //gotoxy(93, 30);
    //printf(" by 고에스더 김민주 전유리");



    //Y/N 중에 하나를 누를때까지 반복
    while (1) {
        push = _getch();
        if (push == 'y') {
            main();
            break;
        }
        if (push == 'n') {
            Bet = true;
            break;

        }
    }
    return Bet;
}

//게임 방법 설명
int startMenu(void) {
	PlaySound(TEXT("avoid.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");
    int ws = 38;

    /*gotoxy(ws, 3); 타이틀 위에부분 테두리
    for (int i = 0; i < 45; i++)
        printf(".");  */

        //왼쪽 기둥 테두리
    for (int i = 5; i < 18; i++) {
        gotoxy(ws, i);
        printf(".");
    }
    //초반 설명글
    gotoxy(ws, 4);
    printf("+++++++++++++++++「눈 피하기 게임」+++++++++++++++");
    gotoxy(ws + 7, 6);
    printf(" ●  ← 왼쪽/오른쪽 → 방향키  ●");
    gotoxy(ws + 1, 7);
    printf(" o  떨어지는 눈덩이를 피해 오래 살아남으세요! o");
    gotoxy(ws + 21, 9);
    printf(" ← ▷ →");
    gotoxy(ws + 9, 11);
    printf(" 《시작하려면 아무키를 누르세요》");
    gotoxy(ws + 6, 17);
    printf("*  ESC를 누르면 메인으로 돌아갑니다. *");

    //밑에부분 테두리
    gotoxy(ws, 18);
    for (int i = 0; i < 50; i++)
        printf("+");
    //오른쪽 기둥 테두리
    for (int i = 5; i < 18; i++) {
        gotoxy(ws + 49, i);
        printf(".");
    }
    gotoxy(93, 30);
    print_by_name("전유리 고에스더 김민주");

    while (1) {
        if (_kbhit()) break;
    }
}
//시작할 때 메뉴
int revel() {
    system("cls");
    startMenu();
    /*gotoxy(50, 6);
    printf("++++++++++++++++++++++++++");
    gotoxy(50, 7);
    printf(" |   눈 피하기 게임     |");
    gotoxy(50, 8);
    printf("++++++++++++++++++++++++++");*/
    //레벨 선택 글자 출력
    int ws = 48, push;
    gotoxy(ws + 5, 13);
    printf("○  * 레벨선택 *  ○");
    gotoxy(ws + 3, 15);
    printf("   ¹    ²    ³   ⁴ ");


    /*0이나 (0x0000) : 이전에 누른 적이 없고 호출 시점에서 안눌린 상태
    0x8000 : 이전에 누른 적이 없고 호출 시점에서 눌린 상태
    0x8001 : 이전에 누른 적이 있고 호출 시점에서 눌린 상태
    1이나 (0x0001) :이전에 누른 적이 있고 호출 시점에서 안눌린 상태*/

    while (1) {
        //위에 숫자를 누르거나 숫자키패드의 숫자를 눌렀을때 조건
        push = _getch();
        if (push == '1') {
            revelnum = LV1; //1단계
            nowrevel = 1;
            break;
        }
        else if (push == '2') {
            revelnum = LV2;  //2단계
            nowrevel = 2;
            break;
        }
        else if (push == '3') {
            revelnum = LV3;  //3단계
            nowrevel = 3;
            break;
        }
        else if (push == '4') {
            revelnum = LV4;   //4단계
            nowrevel = 4;
            break;
        }
        else if (push == ESC) {
            main();
			PlaySound(NULL, 0, 0);
            break;
        }
    }
    return revelnum;
}

//사실 메인
bool ing() {
    init();
    //system("color f0");
    //레벨 선택하기
    int speed = revel();
    startTimer(); //타이머 시작

    do {
        //매번 실행할 때마다 다른 값을 주기 위한 시드값 설정
        srand((int)malloc(NULL));

        CreateEnemy();  //적생성
        if (FallEnemy()) break;    //적 움직이기
        DelEnemy();     //떨어진 적 없애기
        if (MovePlayer()) break;   //사용자 움직임
        if (DamagedPlayer()) break;
        PrintGame();    //화면 만들기

        //현재시간 구하기
        c = clock();
        cn = (double)(c - start) / CLOCKS_PER_SEC;

        //게임의 속도 조절을 위해 Sleep 설정
        Sleep(speed);

    } while (!(DamagedPlayer()));     //닿지 않으면 반복
    endTimer(); //타이머 종료
    return Outgame(); // 다시하기 메뉴 호출
}
//// main 함수 ////
void main_avoid(void)
{
    bool t;

    //게임 실행문 호출- 그만하기 누르기 전까지 반복
    do {
        t = ing();
    } while (t);

}