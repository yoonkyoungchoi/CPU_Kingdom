#include "avoidgame.h"

//����� ���� �����ݷ� �������
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

//�������� ����
Snow snow[WIDTH - CT];
Player one;
clock_t start, c;
double time1;
double max_time = 0, cn;
int revelnum;
int nowrevel;
int speed;
int len = WIDTH - CT;

//// �ʱⰪ ////
void init()
{
    int i;
    for (i = 0; i < len; i++)
        snow[i].con = FALSE;
    //�÷��̾� ��ġ�� �߾�
    one.x = (WIDTH * 2) / 2;
}

//// ���� ���� ó�� ////
/* �� ���� */
void CreateEnemy()
{
    int i;

    for (i = 0; i < len; i++)
    {
        //�ش� �ε���[i]�� ���� ������ (FALSE �̸� ����)
        if (!snow[i].con)
        {
            //���� (x��) �������� �� ����, ����(y��)�� ���� ��ġ �׻� ��ġ
            snow[i].x = (rand() % (WIDTH + 3)) + CT;
            snow[i].y = HEIGHT - 2;
            //���� ������ �ε��� [i]�� ���� = TRUE�� ����
            snow[i].con = TRUE;
            return;
        }
    }
}
/* ���� ������ */
int FallEnemy()
{
    int i;
    for (i = 0; i < len; i++)
    {
        //�ش� �ε��� [i]�� ���� ������ (TRUE���) ������ ����
        if (snow[i].con)
        {
            snow[i].y--;
            if ((snow[i].y == 0) && (snow[i].x == one.x)) return TRUE;
        }
    }
    return FALSE;

}
/* ���ϱ� ������ ��(�ٴڿ� ������ ��) ���� */
void DelEnemy()
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (snow[i].con && snow[i].y < 0)
            snow[i].con = FALSE;
    }
}
/* �÷��̾ ������ ���� ��� (�й�) */
int DamagedPlayer()
{
    int i;
    for (i = 0; i < len; i++)
    {
        //���� ���°� TRUE && ���� ��ġ�� y=0 �� �ٴ� && ���� x�� ��ġ = �÷��̾��� x�� ��ġ
        if ((snow[i].con && snow[i].y == 0) && (snow[i].x == one.x || snow[i].x - 1 == one.x))
            return TRUE;
    }
    //���� �ʾ����� FALSE ��ȯ
    return FALSE;
}

//// �÷��̾� ó�� ////
/* Ű �ٿ� ó�� */ 
int isKeyDown(int key)
{
    //***GetAsyncKey�� Ű�� ���ȴٸ� �ֻ��� ��Ʈ�� 1�� ����, ������ Ű�� ���ȴٸ� ������ ��Ʈ�� 1�� ����
    //0x8000�� �ֻ��� ��Ʈ -> 16������ 2��Ʈ�� 4�� ���� ��Ʈ -> 0x8000 = 1000 0000 0000 0000�� �ǹ�
    // �� ������ ��Ʈ�� 0x0001 -> 0000 0000 0000 0001
    // ���� (GetAsyncKeyState(key) & 0x8000) != 0 �� ���� Ű�� �����ִٸ� ��(TRUE)
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

/* �÷��̾� �̵� (��/��) */
int MovePlayer()
{
    //���� ����Ű �Է� ��
    if (isKeyDown(VK_LEFT))
        one.x--;
    //������ ����Ű �Է� ��
    if (isKeyDown(VK_RIGHT))
        one.x++;
    if (DamagedPlayer()) return TRUE; 
    if (isKeyDown(VK_ESCAPE))
        main();
    //��ġ ���� ����
    if (one.x < CT)
        one.x = CT;
    if (one.x > WIDTH * 2 - CT - 1)
        one.x = WIDTH * 2 - CT - 1;
    return FALSE;
}

//// ���� ȭ�� ��� ////
void PrintGame()
{
    //��� ȭ�� clear
    system("cls");

    //gotoxy(0, HEIGHT + 2); // (WIDTH /2) - 7
    //���� ���
    //printf("\n");
    gotoxy(CT, 1);
    switch (nowrevel) {
    case 1: {printf("��\tLv.1\t��");  break; }
    case 2: {printf("��\tLv.2\t��");  break; }
    case 3: {printf("��\tLv.3\t��");  break; }
    default: {printf("��\tLv.4\t��"); break; }
    }
    printf("\t      CPU ���ϱ� ����\t      "); //�߰� title
    //����ð� ���
    printf("��    %.1f��   ��\n", cn);
    gotoxy(CT, 2);
    int i;
    for (i = CT; i < WIDTH; i++)
        printf("����");//��

    for (i = 0; i < len; i++)
    {
        if (snow[i].con)
        {
            //�� ��ġ�� ���� ���
            gotoxy(snow[i].x, HEIGHT - snow[i].y);
            printf("o");
        }
    }
    //�÷��̾� ���
    gotoxy(one.x, HEIGHT);
    printf("��");

    //�ٴ� ���
    gotoxy(CT, HEIGHT + 1);
    for (i = CT; i < WIDTH + 1; i++)
        printf("��");//��
    printf("\n");
    //�̸� �ֱ�
    //gotoxy(93, 30);
    //printf(" by ������ ������ ����� ");

}

//Ÿ�̸� �Լ� : clock();
//Ÿ�̸� ����
void startTimer() {
    start = clock();
}
//Ÿ�̸� ��
void endTimer() {
    system("cls");

    clock_t end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ

}

//���� �������� �޴�
bool Outgame(void) {
    bool Bet;
    int wt = 45, push;    //���߾� ������ 

    //����ð� ���
    PlaySound(NULL, 0, 0);
    gotoxy(wt, 5);
    printf("��������������������������������������������������\n");
    gotoxy(wt, 6);
    printf("��                       ��\n");
    gotoxy(wt, 7);
    if (time1 < 10.0)  printf("��   ����ð� :  %0.1lf��   ��\n", time1); //10�̸��̸� �տ� 0���̱�
    else  printf("��   ����ð� : %0.1lf��   ��\n", time1); //���� ���ڸ��� �״��
    gotoxy(wt, 8);
    printf("��                       ��\n");
    gotoxy(wt, 9);
    printf("�� �����������릢\n");

    //�ְ��� ���ϱ�
    if (time1 > max_time) { max_time = time1; }

    //�ְ��� ���
    gotoxy(wt, 10);
    printf("��                       ��\n");
    gotoxy(wt, 11);
    if (max_time < 10.0) printf("��   �ְ��� :  %0.1lf��   ��\n", max_time); //10�̸��̸� �տ� 0���̱�
    else printf("��   �ְ��� : %0.1lf��   ��\n", max_time); //���� ���ڸ��� �״��
    gotoxy(wt, 12);
    printf("��                       ��\n");
    gotoxy(wt, 13);
    printf("�� �����������릢\n");
    gotoxy(wt, 14);
    printf("��                       ��\n");
    gotoxy(wt, 15);
    printf("��   �׸��ϱ�   �ٽ��ϱ� ��\n");
    gotoxy(wt, 16);
    printf("��                       ��\n");
    gotoxy(wt, 17);
    printf("��     Y      :     N    ��");
    gotoxy(wt, 18);
    printf("��������������������������������������������������\n");
    //�̸� �ֱ�
    //gotoxy(93, 30);
    //printf(" by ������ ����� ������");



    //Y/N �߿� �ϳ��� ���������� �ݺ�
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

//���� ��� ����
int startMenu(void) {
	PlaySound(TEXT("avoid.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");
    int ws = 38;

    /*gotoxy(ws, 3); Ÿ��Ʋ �����κ� �׵θ�
    for (int i = 0; i < 45; i++)
        printf(".");  */

        //���� ��� �׵θ�
    for (int i = 5; i < 18; i++) {
        gotoxy(ws, i);
        printf(".");
    }
    //�ʹ� �����
    gotoxy(ws, 4);
    printf("+++++++++++++++++���� ���ϱ� ���ӡ�+++++++++++++++");
    gotoxy(ws + 7, 6);
    printf(" ��  �� ����/������ �� ����Ű  ��");
    gotoxy(ws + 1, 7);
    printf(" o  �������� �����̸� ���� ���� ��Ƴ�������! o");
    gotoxy(ws + 21, 9);
    printf(" �� �� ��");
    gotoxy(ws + 9, 11);
    printf(" �������Ϸ��� �ƹ�Ű�� �������䡷");
    gotoxy(ws + 6, 17);
    printf("*  ESC�� ������ �������� ���ư��ϴ�. *");

    //�ؿ��κ� �׵θ�
    gotoxy(ws, 18);
    for (int i = 0; i < 50; i++)
        printf("+");
    //������ ��� �׵θ�
    for (int i = 5; i < 18; i++) {
        gotoxy(ws + 49, i);
        printf(".");
    }
    gotoxy(93, 30);
    print_by_name("������ ������ �����");

    while (1) {
        if (_kbhit()) break;
    }
}
//������ �� �޴�
int revel() {
    system("cls");
    startMenu();
    /*gotoxy(50, 6);
    printf("++++++++++++++++++++++++++");
    gotoxy(50, 7);
    printf(" |   �� ���ϱ� ����     |");
    gotoxy(50, 8);
    printf("++++++++++++++++++++++++++");*/
    //���� ���� ���� ���
    int ws = 48, push;
    gotoxy(ws + 5, 13);
    printf("��  * �������� *  ��");
    gotoxy(ws + 3, 15);
    printf("   ��    ��    ��   �� ");


    /*0�̳� (0x0000) : ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
    0x8000 : ������ ���� ���� ���� ȣ�� �������� ���� ����
    0x8001 : ������ ���� ���� �ְ� ȣ�� �������� ���� ����
    1�̳� (0x0001) :������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����*/

    while (1) {
        //���� ���ڸ� �����ų� ����Ű�е��� ���ڸ� �������� ����
        push = _getch();
        if (push == '1') {
            revelnum = LV1; //1�ܰ�
            nowrevel = 1;
            break;
        }
        else if (push == '2') {
            revelnum = LV2;  //2�ܰ�
            nowrevel = 2;
            break;
        }
        else if (push == '3') {
            revelnum = LV3;  //3�ܰ�
            nowrevel = 3;
            break;
        }
        else if (push == '4') {
            revelnum = LV4;   //4�ܰ�
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

//��� ����
bool ing() {
    init();
    //system("color f0");
    //���� �����ϱ�
    int speed = revel();
    startTimer(); //Ÿ�̸� ����

    do {
        //�Ź� ������ ������ �ٸ� ���� �ֱ� ���� �õ尪 ����
        srand((int)malloc(NULL));

        CreateEnemy();  //������
        if (FallEnemy()) break;    //�� �����̱�
        DelEnemy();     //������ �� ���ֱ�
        if (MovePlayer()) break;   //����� ������
        if (DamagedPlayer()) break;
        PrintGame();    //ȭ�� �����

        //����ð� ���ϱ�
        c = clock();
        cn = (double)(c - start) / CLOCKS_PER_SEC;

        //������ �ӵ� ������ ���� Sleep ����
        Sleep(speed);

    } while (!(DamagedPlayer()));     //���� ������ �ݺ�
    endTimer(); //Ÿ�̸� ����
    return Outgame(); // �ٽ��ϱ� �޴� ȣ��
}
//// main �Լ� ////
void main_avoid(void)
{
    bool t;

    //���� ���๮ ȣ��- �׸��ϱ� ������ ������ �ݺ�
    do {
        t = ing();
    } while (t);

}