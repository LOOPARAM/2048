
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#pragma region Define
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define _W 119
#define _S 115
#define _A 97
#define _D 100
#pragma endregion
#pragma region 전역변수들

int map[53][53] = {0};//맵을 만들때 사용할 배열//가로는53 세로는 53

int arr2048[4][4] = {{0,0,0,0 } ,
					 {0,0,0,0 } ,
					 {0,0,0,0 } ,
					 {0,0,0,0 } };//게임 판에 위치하는 숫자를 저장

int Score = 0;//게임 점수를 의미//점수는 합친 블럭들의 합으로 계산한다

bool ifmove = false;
#pragma endregion
#pragma region 함수들
void gotoxy(int x, int y);//커서이동 함수
void Setup();//게임 시작시 실행되는 기본 세팅 함수
int AddRandom();//랜덤 생성 함수
int Show(int x, int y, int a);//바꾼 정보 화면에 표시 함수
void Move();//이동및 합치기 함수
bool GameOver();//이동 불가능 판별 함수
void EndGame();//게임오버 처리

#pragma endregion
int main()
{
#pragma region 기본 세팅
	Setup();
#pragma endregion
#pragma region loop
	while (1)
	{
		//gotoxy(0, 0);
		if (_kbhit()) { Move(); }
		GameOver();
		gotoxy(30, 53); printf("Score : %d       ",Score);
	}
	return 0;
}
#pragma endregion
void gotoxy(int x, int y)//커서이동 함수
{
#pragma region 커서이동
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#pragma endregion
}
void Setup()//코드가 실행되면 제일 먼저 세팅하는 함수
{
#pragma region map모양 설정
	for (int i = 0; i < 53; i++)
	{
		map[0][i] = 1;
		map[i][0] = 1;
		map[52][i] = 1;
		map[i][52] = 1;

		map[i][13] = 1;
		map[i][26] = 1;
		map[i][39] = 1;

		map[13][i] = 1;
		map[26][i] = 1;
		map[39][i] = 1;
	}
#pragma endregion
#pragma region map출력
	for (int i = 0; i < 53; i++)
	{
		for (int j = 0; j < 53; j++)
		{
			gotoxy(i*2, j); printf((map[i][j] == 1) ? "■" : "  ");
		}
	}
#pragma endregion
#pragma region 시드 초기화
	srand(time(NULL));//시드 초기화
#pragma endregion
#pragma region 시작 두개 생성
	AddRandom();
	AddRandom();
#pragma endregion
}
int AddRandom()//랜덤 생성 함수
{
#pragma region 랜덤 값, 생성 가능한 인덱스 세팅

	int Choose2or4Rand = 0;//2는 90% 4는 10%로 선택하게 랜덤값을 저장하는 변수
	Choose2or4Rand = (rand()%100)+1;//1~100중 랜덤의 값을 저장
	int Set2or4 = (Choose2or4Rand <= 90) ? 2 : 4;//90이하면(90%) 2 아니면(10%) 4
	int Count0Index = 0;//arr2048에 값이 0인 인덱스의 수를 저장
	for (int i = 0; i < 4; i++)//arr2048 중 0인 인덱스의 찾는 코드
	{for (int j = 0; j < 4; j++) {if (arr2048[j][i] == 0){Count0Index++;}}}
	if (Count0Index == 0) { return 0; }
	int* ArrCount0Index = (int*)malloc(sizeof(int) * (Count0Index*2));//arr2048에서 0인 인덱스를 저장하는 배열
	int a = 0;
	for (int i = 0; i < 4; i++)//arr2048 중 0인 인덱스를 배열에 저장하는 코드
	{
		for (int j = 0; j < 4; j++) { 
			if (arr2048[j][i] == 0) {
				ArrCount0Index[a*2] = j;
				ArrCount0Index[(a * 2) + 1] = i;
				a++;
			} 
		}
	}
	int CreatRandom = (rand() % Count0Index);
#pragma endregion
#pragma region 지정하고 출력
	arr2048[ArrCount0Index[(CreatRandom * 2)]][ArrCount0Index[(CreatRandom * 2)+1]] = Set2or4;
	Show(ArrCount0Index[CreatRandom * 2], ArrCount0Index[(CreatRandom * 2) + 1], Set2or4);
	return 0;
#pragma endregion
}
int Show(int x, int y, int a)//변경한 수를 map에 표시해주는 함수
{
//(0,0)//(26,0)//(52,0)//(78,0)
//(0,13)//(26,13)//(52,13)//(78,13)
//(0,26)//(26,26)//(52,26)//(78,26)
//(0,39)//(26,39)//(52,39)//(78,39)
#pragma region x,y값 설정
	//map에서 한칸은 ■로 13칸
	x = x * 26;
	y = y * 13;
	if (x < 0 || y < 0)
	{
		return 0;
	}
#pragma endregion
#pragma region 초기화
	if (a == 0)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■                        ■");
		gotoxy(x, y + 4);  printf("■                        ■");
		gotoxy(x, y + 5);  printf("■                        ■");
		gotoxy(x, y + 6);  printf("■                        ■");
		gotoxy(x, y + 7);  printf("■                        ■");
		gotoxy(x, y + 8);  printf("■                        ■");
		gotoxy(x, y + 9);  printf("■                        ■");
		gotoxy(x, y + 10); printf("■                        ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자2
	if (a == 2)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■    ■■■■■■■■    ■");
		gotoxy(x, y + 4);  printf("■                  ■    ■");
		gotoxy(x, y + 5);  printf("■                  ■    ■");
		gotoxy(x, y + 6);  printf("■                  ■    ■");
		gotoxy(x, y + 7);  printf("■    ■■■■■■■■    ■");
		gotoxy(x, y + 8);  printf("■    ■                  ■");
		gotoxy(x, y + 9);  printf("■    ■                  ■");
		gotoxy(x, y + 10); printf("■    ■                  ■");
		gotoxy(x, y + 11); printf("■    ■■■■■■■■    ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자4
	if (a == 4)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■     ■          ■     ■");
		gotoxy(x, y + 4);  printf("■     ■          ■     ■");
		gotoxy(x, y + 5);  printf("■     ■          ■     ■");
		gotoxy(x, y + 6);  printf("■     ■          ■     ■");
		gotoxy(x, y + 7);  printf("■     ■■■■■■■     ■");
		gotoxy(x, y + 8);  printf("■                 ■     ■");
		gotoxy(x, y + 9);  printf("■                 ■     ■");
		gotoxy(x, y + 10); printf("■                 ■     ■");
		gotoxy(x, y + 11); printf("■                 ■     ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자8
	if (a == 8)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■     ■■■■■■■     ■");
		gotoxy(x, y + 4);  printf("■     ■          ■     ■");
		gotoxy(x, y + 5);  printf("■     ■          ■     ■");
		gotoxy(x, y + 6);  printf("■     ■          ■     ■");
		gotoxy(x, y + 7);  printf("■     ■■■■■■■     ■");
		gotoxy(x, y + 8);  printf("■     ■          ■     ■");
		gotoxy(x, y + 9);  printf("■     ■          ■     ■");
		gotoxy(x, y + 10); printf("■     ■          ■     ■");
		gotoxy(x, y + 11); printf("■     ■■■■■■■     ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자16
	if (a == 16)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■                        ■");
		gotoxy(x, y + 4);  printf("■  ■    ■■■■■■    ■");
		gotoxy(x, y + 5);  printf("■  ■    ■              ■");
		gotoxy(x, y + 6);  printf("■  ■    ■              ■");
		gotoxy(x, y + 7);  printf("■  ■    ■■■■■■    ■");
		gotoxy(x, y + 8);  printf("■  ■    ■        ■    ■");
		gotoxy(x, y + 9);  printf("■  ■    ■        ■    ■");
		gotoxy(x, y + 10); printf("■  ■    ■■■■■■    ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자32
	if (a == 32)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■  ■■■■  ■■■■■  ■");
		gotoxy(x, y + 4);  printf("■        ■          ■  ■");
		gotoxy(x, y + 5);  printf("■        ■          ■  ■");
		gotoxy(x, y + 6);  printf("■  ■■■■  ■■■■■  ■");
		gotoxy(x, y + 7);  printf("■        ■  ■          ■");
		gotoxy(x, y + 8);  printf("■        ■  ■          ■");
		gotoxy(x, y + 9);  printf("■  ■■■■  ■■■■■  ■");
		gotoxy(x, y + 10); printf("■                        ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자64
	if (a == 64)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■  ■■■■  ■    ■    ■");
		gotoxy(x, y + 4);  printf("■  ■        ■    ■    ■");
		gotoxy(x, y + 5);  printf("■  ■        ■    ■    ■");
		gotoxy(x, y + 6);  printf("■  ■■■■  ■■■■    ■");
		gotoxy(x, y + 7);  printf("■  ■    ■        ■    ■");
		gotoxy(x, y + 8);  printf("■  ■    ■        ■    ■");
		gotoxy(x, y + 9);  printf("■  ■■■■        ■    ■");
		gotoxy(x, y + 10); printf("■                        ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자128
	if (a == 128)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■                        ■");
		gotoxy(x, y + 4);  printf("■  ■  ■■■  ■■■    ■");
		gotoxy(x, y + 5);  printf("■  ■      ■  ■  ■    ■");
		gotoxy(x, y + 6);  printf("■  ■  ■■■  ■■■    ■");
		gotoxy(x, y + 7);  printf("■  ■  ■      ■  ■    ■");
		gotoxy(x, y + 8);  printf("■  ■  ■■■  ■■■    ■");
		gotoxy(x, y + 9);  printf("■                        ■");
		gotoxy(x, y + 10); printf("■                        ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자256
	if (a == 256)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■                        ■");
		gotoxy(x, y + 4);  printf("■  ■■■ ■■■ ■■■  ■");
		gotoxy(x, y + 5);  printf("■      ■ ■     ■      ■");
		gotoxy(x, y + 6);  printf("■  ■■■ ■■■ ■■■  ■");
		gotoxy(x, y + 7);  printf("■  ■         ■ ■  ■  ■");
		gotoxy(x, y + 8);  printf("■  ■■■ ■■■ ■■■  ■");
		gotoxy(x, y + 9);  printf("■                        ■");
		gotoxy(x, y + 10); printf("■                        ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자512
	if (a == 512)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■                        ■");
		gotoxy(x, y + 3);  printf("■                        ■");
		gotoxy(x, y + 4);  printf("■  ■■■   ■   ■■■  ■");
		gotoxy(x, y + 5);  printf("■  ■       ■       ■  ■");
		gotoxy(x, y + 6);  printf("■  ■■■   ■   ■■■  ■");
		gotoxy(x, y + 7);  printf("■      ■   ■   ■      ■");
		gotoxy(x, y + 8);  printf("■  ■■■   ■   ■■■  ■");
		gotoxy(x, y + 9);  printf("■                        ■");
		gotoxy(x, y + 10); printf("■                        ■");
		gotoxy(x, y + 11); printf("■                        ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자1024
	if (a == 1024)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■       □    □□□□   ■");
		gotoxy(x, y + 3);  printf("■       □    □    □   ■");
		gotoxy(x, y + 4);  printf("■       □    □    □   ■");
		gotoxy(x, y + 5);  printf("■       □    □    □   ■");
		gotoxy(x, y + 6);  printf("■       □    □□□□   ■");
		gotoxy(x, y + 7);  printf("■   ■■■■  ■    ■   ■");
		gotoxy(x, y + 8);  printf("■         ■  ■    ■   ■");
		gotoxy(x, y + 9);  printf("■   ■■■■  ■■■■   ■");
		gotoxy(x, y + 10); printf("■   ■              ■   ■");
		gotoxy(x, y + 11); printf("■   ■■■■        ■   ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
#pragma region 숫자2048
	if (a == 2048)
	{
		gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
		gotoxy(x, y + 1);  printf("■                        ■");
		gotoxy(x, y + 2);  printf("■  □□□□  □□□□    ■");
		gotoxy(x, y + 3);  printf("■        □  □    □    ■");
		gotoxy(x, y + 4);  printf("■  □□□□  □    □    ■");
		gotoxy(x, y + 5);  printf("■  □        □    □    ■");
		gotoxy(x, y + 6);  printf("■  □□□□  □□□□    ■");
		gotoxy(x, y + 7);  printf("■  ■    ■  ■■■■    ■");
		gotoxy(x, y + 8);  printf("■  ■    ■  ■    ■    ■");
		gotoxy(x, y + 9);  printf("■  ■■■■  ■■■■    ■");
		gotoxy(x, y + 10); printf("■        ■  ■    ■    ■");
		gotoxy(x, y + 11); printf("■        ■  ■■■■    ■");
		gotoxy(x, y + 12); printf("■                        ■");
		gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	}
#pragma endregion
}
void Move()//입력과 움직임 처리
{
#pragma region 입력
	char Kbi;//입력받은 값을 저장하는 변수
	char StartCheck = 'Z';//검사를 시작할 부분을 판단하는 변수
	Kbi = _getch();
	gotoxy(10, 53); printf("%d  ", Kbi);
	switch (Kbi) {
	case UP: gotoxy(2, 53); printf("UP   "); StartCheck = 'U'; break;
	case DOWN: gotoxy(2, 53); printf("DOWN "); StartCheck = 'D'; break;
	case LEFT: gotoxy(2, 53); printf("LEFT "); StartCheck = 'L'; break;
	case RIGHT: gotoxy(2, 53); printf("RIGHT"); StartCheck = 'R'; break;
	case _W: gotoxy(2, 53); printf("UP   "); StartCheck = 'U'; break;
	case _S: gotoxy(2, 53); printf("DOWN "); StartCheck = 'D'; break;
	case _A: gotoxy(2, 53); printf("LEFT "); StartCheck = 'L'; break;
	case _D: gotoxy(2, 53); printf("RIGHT"); StartCheck = 'R'; break;
	}
#pragma endregion
#pragma region 검사
	ifmove = false;
	int nx = 5;
	int ny = 5;
	if (StartCheck == 'U') {
		for (int i = 1; i < 4; i++)/* y */{
			for (int j = 0; j < 4; j++)/* x */{
				if (arr2048[j][i] != 0)//현재 검사하는 칸이 비어있지 않다면
				{
					int Cy = i;
					while (1)
					{
						if (arr2048[j][Cy - 1] == 0)//현재 검사하는칸보다 한칸 위에 있는 칸이 비어있으면
						{
							ifmove = true;
							arr2048[j][Cy - 1] = arr2048[j][Cy];//현재 검사하는칸보다 한 칸 위에 있는 칸의 값을 현재 칸으로지정
							Show(j, Cy - 1, arr2048[j][Cy]);//업데이트
							arr2048[j][Cy] = 0;
							Show(j, Cy, 0);//업데이트
							Cy--;
							if (Cy == 0)
							{
								break;
							}
						}
						else if (arr2048[j][Cy - 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0 && j != nx && Cy != ny)//현재 검사하는칸보다 한칸 위에 있는 칸이 자신의 숫자와 같으면
						{
							ifmove = true;
							Score += (arr2048[j][Cy] * 2);
							//gotoxy(15, 54); printf("(%d,%d) = %d", j, Cy - 1, arr2048[j][Cy - 1]);
							arr2048[j][Cy - 1] = arr2048[j][Cy] * 2;//현재 검사하는칸보다 한 칸 위에 있는 칸의 값을 (현재 칸 * 2)로지정
							Show(j, Cy - 1, arr2048[j][Cy] * 2);//업데이트
							arr2048[j][Cy] = 0;//현재 검사하는칸을 0으로
							Show(j, Cy, 0);//업데이트
							nx = j; ny = Cy - 1;
							Cy--;//검사 y값을 한칸 위로했으므로 한칸 빼주기
							if (Cy == 0) { break; }
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		if (ifmove == true)
		{
			AddRandom();
		}
	}
	if (StartCheck == 'D') {
		for (int i =2; i >= 0; i--)/* y */ {
			for (int j = 0; j < 4; j++)/* x */ {
				if (arr2048[j][i] != 0)//현재 검사하는 칸이 비어있지 않다면
				{
					int Cy = i;
					while (1)
					{
						if (arr2048[j][Cy + 1] == 0)//현재 검사하는칸보다 한칸 위에 아래 칸이 비어있으면
						{
							ifmove = true;
							arr2048[j][Cy + 1] = arr2048[j][Cy];//현재 검사하는칸보다 한 칸 아래 있는 칸의 값을 현재 칸으로지정
							Show(j, Cy + 1, arr2048[j][Cy]);//업데이트
							arr2048[j][Cy] = 0;
							Show(j, Cy, 0);//업데이트
							Cy++;
							if (Cy == 3)
							{
								break;
							}
						}
						else if (arr2048[j][Cy + 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0 && j != nx && Cy != ny)//현재 검사하는칸보다 한칸 위에 있는 칸이 자신의 숫자와 같으면
						{
							ifmove = true;
							Score += (arr2048[j][Cy] * 2);
							arr2048[j][Cy + 1] = arr2048[j][Cy] * 2;//현재 검사하는칸보다 한 칸 위에 있는 칸의 값을 (현재 칸 * 2)로지정
							Show(j, Cy + 1, arr2048[j][Cy] * 2);//업데이트
							arr2048[j][Cy] = 0;//현재 검사하는칸을 0으로
							Show(j, Cy, 0);//업데이트
							nx = j; ny = Cy + 1;
							Cy++;//검사 y값을 한칸 위로했으므로 한칸 빼주기
							if (Cy == 3) { break; }
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		if (ifmove == true)
		{
			AddRandom();
		}
	}
	if (StartCheck == 'L') {
		for (int i = 1; i < 4; i++)/* x */ {
			for (int j = 0; j < 4; j++)/* y */ {
				if (arr2048[i][j] != 0)//현재 검사하는 칸이 비어있지 않다면
				{
					int Cx = i;
					while (1)
					{
						if (arr2048[Cx-1][j] == 0)//현재 검사하는칸보다 한칸 왼쪽 칸이 비어있으면
						{
							ifmove = true;
							arr2048[Cx-1][j] = arr2048[Cx][j];//현재 검사하는칸보다 한 칸 왼쪽 칸의 값을 현재 칸으로지정
							Show(Cx-1,j, arr2048[Cx][j]);//업데이트
							arr2048[Cx][j] = 0;
							Show(Cx, j, 0);//업데이트
							Cx--;
							if (Cx == 0)
							{
								break;
							}
						}
						else if (arr2048[Cx-1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0 && Cx != nx && j != ny)//현재 검사하는칸보다 한칸 왼쪽 칸이 자신의 숫자와 같으면
						{
							ifmove = true;
							Score += (arr2048[Cx][j] * 2);
							arr2048[Cx-1][j] = arr2048[Cx][j] * 2;//현재 검사하는칸보다 한 칸 왼쪽 칸의 값을 (현재 칸 * 2)로지정
							Show(Cx-1,j, arr2048[Cx][j] * 2);//업데이트
							arr2048[Cx][j] = 0;//현재 검사하는칸을 0으로
							Show(Cx, j, 0);//업데이트
							nx = Cx-1; ny = j;
							Cx--;//검사 y값을 한칸 위로했으므로 한칸 빼주기
							if (Cx == 0) { break; }
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		if (ifmove == true)
		{
			AddRandom();
		}
	}
	if (StartCheck == 'R') {
		for (int i = 2; i >=0; i--)/* x */ {
			for (int j = 0; j < 4; j++)/* y */ {
				if (arr2048[i][j] != 0)//현재 검사하는 칸이 비어있지 않다면
				{
					int Cx = i;
					while (1)
					{
						if (arr2048[Cx + 1][j] == 0)//현재 검사하는칸보다 한칸 오른쪽 칸이 비어있으면
						{
							ifmove = true;
							arr2048[Cx + 1][j] = arr2048[Cx][j];//현재 검사하는칸보다 한 칸 오른쪽 칸의 값을 현재 칸으로지정
							Show(Cx + 1, j, arr2048[Cx][j]);//업데이트
							arr2048[Cx][j] = 0;
							Show(Cx, j, 0);//업데이트
							Cx++;
							if (Cx == 3)
							{
								break;
							}
						}
						else if (arr2048[Cx + 1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0 && Cx != nx && j != ny)//현재 검사하는칸보다 한칸 오른쪽 칸이 자신의 숫자와 같으면
						{
							ifmove = true;
							Score += (arr2048[Cx][j] * 2);
							//gotoxy(15, 54); printf("(%d,%d) = %d", j, Cy - 1, arr2048[j][Cy - 1]);
							arr2048[Cx + 1][j] = arr2048[Cx][j] * 2;//현재 검사하는칸보다 한 칸 왼쪽 칸의 값을 (현재 칸 * 2)로지정
							Show(Cx + 1, j, arr2048[Cx][j] * 2);//업데이트
							arr2048[Cx][j] = 0;//현재 검사하는칸을 0으로
							Show(Cx, j, 0);//업데이트
							nx = Cx + 1; ny = j;
							Cx++;//검사 y값을 한칸 위로했으므로 한칸 빼주기
							if (Cx == 3) { break; }
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		if (ifmove == true)
		{
			AddRandom();
		}
	}
#pragma endregion
}
bool GameOver() {//게임오버 판별
#pragma region 배열에 빈칸이 있는지
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arr2048[j][i] == 0)
			{
				return false;
			}
		}
	}
#pragma endregion
	for (int i = 1; i < 4; i++)/* y */ {
		for (int j = 0; j < 4; j++)/* x */ {
			if (arr2048[j][i] != 0)//현재 검사하는 칸이 비어있지 않다면
			{
				int Cy = i;
				while (1)
				{
					if (arr2048[j][Cy - 1] == 0)//현재 검사하는칸보다 한칸 위에 있는 칸이 비어있으면
					{
						return false;
					}
					else if (arr2048[j][Cy - 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0)//현재 검사하는칸보다 한칸 위에 있는 칸이 자신의 숫자와 같으면
					{
						return false;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	for (int i = 2; i >= 0; i--)/* y */ {
		for (int j = 0; j < 4; j++)/* x */ {
			if (arr2048[j][i] != 0)//현재 검사하는 칸이 비어있지 않다면
			{
				int Cy = i;
				while (1)
				{
					if (arr2048[j][Cy + 1] == 0)//현재 검사하는칸보다 한칸 위에 아래 칸이 비어있으면
					{
						return false;
					}
					else if (arr2048[j][Cy + 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0)//현재 검사하는칸보다 한칸 위에 있는 칸이 자신의 숫자와 같으면
					{
						return false;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	for (int i = 1; i < 4; i++)/* x */ {
		for (int j = 0; j < 4; j++)/* y */ {
			if (arr2048[i][j] != 0)//현재 검사하는 칸이 비어있지 않다면
			{
				int Cx = i;
				while (1)
				{
					if (arr2048[Cx - 1][j] == 0)//현재 검사하는칸보다 한칸 왼쪽 칸이 비어있으면
					{
						return false;
					}
					else if (arr2048[Cx - 1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0)//현재 검사하는칸보다 한칸 왼쪽 칸이 자신의 숫자와 같으면
					{
						return false;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	for (int i = 2; i >= 0; i--)/* x */ {
		for (int j = 0; j < 4; j++)/* y */ {
			if (arr2048[i][j] != 0)//현재 검사하는 칸이 비어있지 않다면
			{
				int Cx = i;
				while (1)
				{
					if (arr2048[Cx + 1][j] == 0)//현재 검사하는칸보다 한칸 오른쪽 칸이 비어있으면
					{
						return false;
					}
					else if (arr2048[Cx + 1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0)//현재 검사하는칸보다 한칸 오른쪽 칸이 자신의 숫자와 같으면
					{
						return false;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
#pragma region 모든 조건을 만족시키지 않으면 게임 오버
	EndGame();
#pragma endregion

}
void EndGame()//게임오버 메시지 출력
{
#pragma region GAME
	int y = 13;
	int x = 0;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■  □□□□□□□□□□  ■");
	gotoxy(x, y + 3);  printf("■  □                    ■");
	gotoxy(x, y + 4);  printf("■  □                    ■");
	gotoxy(x, y + 5);  printf("■  □                    ■");
	gotoxy(x, y + 6);  printf("■  □                    ■");
	gotoxy(x, y + 7);  printf("■  □        □□□□□  ■");
	gotoxy(x, y + 8);  printf("■  □                □  ■");
	gotoxy(x, y + 9);  printf("■  □                □  ■");
	gotoxy(x, y + 10); printf("■  □                □  ■");
	gotoxy(x, y + 11); printf("■  □□□□□□□□□□  ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	x = 26;
	y = 13;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■  □□□□□□□□□□  ■");
	gotoxy(x, y + 3);  printf("■  □                □  ■");
	gotoxy(x, y + 4);  printf("■  □                □  ■");
	gotoxy(x, y + 5);  printf("■  □                □  ■");
	gotoxy(x, y + 6);  printf("■  □                □  ■");
	gotoxy(x, y + 7);  printf("■  □□□□□□□□□□  ■");
	gotoxy(x, y + 8);  printf("■  □                □  ■");
	gotoxy(x, y + 9);  printf("■  □                □  ■");
	gotoxy(x, y + 10); printf("■  □                □  ■");
	gotoxy(x, y + 11); printf("■  □                □  ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	x = 52;
	y = 13;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 3);  printf("■   □      □      □   ■");
	gotoxy(x, y + 4);  printf("■   □      □      □   ■");
	gotoxy(x, y + 5);  printf("■   □      □      □   ■");
	gotoxy(x, y + 6);  printf("■   □      □      □   ■");
	gotoxy(x, y + 7);  printf("■   □      □      □   ■");
	gotoxy(x, y + 8);  printf("■   □      □      □   ■");
	gotoxy(x, y + 9);  printf("■   □      □      □   ■");
	gotoxy(x, y + 10); printf("■   □      □      □   ■");
	gotoxy(x, y + 11); printf("■   □      □      □   ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	x = 78;
	y = 13;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 3);  printf("■   □                   ■");
	gotoxy(x, y + 4);  printf("■   □                   ■");
	gotoxy(x, y + 5);  printf("■   □                   ■");
	gotoxy(x, y + 6);  printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 7);  printf("■   □                   ■");
	gotoxy(x, y + 8);  printf("■   □                   ■");
	gotoxy(x, y + 9);  printf("■   □                   ■");
	gotoxy(x, y + 10); printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 11); printf("■                        ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
#pragma endregion
#pragma region OVER
	x = 0;
	y = 26;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■  □□□□□□□□□□  ■");
	gotoxy(x, y + 3);  printf("■  □                □  ■");
	gotoxy(x, y + 4);  printf("■  □                □  ■");
	gotoxy(x, y + 5);  printf("■  □                □  ■");
	gotoxy(x, y + 6);  printf("■  □                □  ■");
	gotoxy(x, y + 7);  printf("■  □                □  ■");
	gotoxy(x, y + 8);  printf("■  □                □  ■");
	gotoxy(x, y + 9);  printf("■  □                □  ■");
	gotoxy(x, y + 10); printf("■  □                □  ■");
	gotoxy(x, y + 11); printf("■  □□□□□□□□□□  ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	x = 26;
	y = 26;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■  □                □  ■");
	gotoxy(x, y + 3);  printf("■  □                □  ■");
	gotoxy(x, y + 4);  printf("■  □                □  ■");
	gotoxy(x, y + 5);  printf("■  □                □  ■");
	gotoxy(x, y + 6);  printf("■  □                □  ■");
	gotoxy(x, y + 7);  printf("■    □            □    ■");
	gotoxy(x, y + 8);  printf("■    □            □    ■");
	gotoxy(x, y + 9);  printf("■      □        □      ■");
	gotoxy(x, y + 10); printf("■        □    □        ■");
	gotoxy(x, y + 11); printf("■          □□          ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	x = 52;
	y = 26;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 3);  printf("■   □                   ■");
	gotoxy(x, y + 4);  printf("■   □                   ■");
	gotoxy(x, y + 5);  printf("■   □                   ■");
	gotoxy(x, y + 6);  printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 7);  printf("■   □                   ■");
	gotoxy(x, y + 8);  printf("■   □                   ■");
	gotoxy(x, y + 9);  printf("■   □                   ■");
	gotoxy(x, y + 10); printf("■   □□□□□□□□□   ■");
	gotoxy(x, y + 11); printf("■                        ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	x = 78;
	y = 26;
	gotoxy(x, y + 0);  printf("■■■■■■■■■■■■■■");
	gotoxy(x, y + 1);  printf("■                        ■");
	gotoxy(x, y + 2);  printf("■   □□□□□□□□     ■");
	gotoxy(x, y + 3);  printf("■   □              □   ■");
	gotoxy(x, y + 4);  printf("■   □              □   ■");
	gotoxy(x, y + 5);  printf("■   □              □   ■");
	gotoxy(x, y + 6);  printf("■   □□□□□□□□     ■");
	gotoxy(x, y + 7);  printf("■   □ □□              ■");
	gotoxy(x, y + 8);  printf("■   □    □□           ■");
	gotoxy(x, y + 9);  printf("■   □       □□        ■");
	gotoxy(x, y + 10); printf("■   □          □□     ■");
	gotoxy(x, y + 11); printf("■   □             □□  ■");
	gotoxy(x, y + 12); printf("■                        ■");
	gotoxy(x, y + 13); printf("■■■■■■■■■■■■■■");
	
#pragma endregion
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr2048[j][i] = 0;
		}
	}
	Sleep(10000);
	main();
}

