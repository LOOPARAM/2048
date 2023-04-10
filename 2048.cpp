
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
#pragma region ����������

int map[53][53] = {0};//���� ���鶧 ����� �迭//���δ�53 ���δ� 53

int arr2048[4][4] = {{0,0,0,0 } ,
					 {0,0,0,0 } ,
					 {0,0,0,0 } ,
					 {0,0,0,0 } };//���� �ǿ� ��ġ�ϴ� ���ڸ� ����

int Score = 0;//���� ������ �ǹ�//������ ��ģ ������ ������ ����Ѵ�

bool ifmove = false;
#pragma endregion
#pragma region �Լ���
void gotoxy(int x, int y);//Ŀ���̵� �Լ�
void Setup();//���� ���۽� ����Ǵ� �⺻ ���� �Լ�
int AddRandom();//���� ���� �Լ�
int Show(int x, int y, int a);//�ٲ� ���� ȭ�鿡 ǥ�� �Լ�
void Move();//�̵��� ��ġ�� �Լ�
bool GameOver();//�̵� �Ұ��� �Ǻ� �Լ�
void EndGame();//���ӿ��� ó��

#pragma endregion
int main()
{
#pragma region �⺻ ����
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
void gotoxy(int x, int y)//Ŀ���̵� �Լ�
{
#pragma region Ŀ���̵�
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#pragma endregion
}
void Setup()//�ڵ尡 ����Ǹ� ���� ���� �����ϴ� �Լ�
{
#pragma region map��� ����
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
#pragma region map���
	for (int i = 0; i < 53; i++)
	{
		for (int j = 0; j < 53; j++)
		{
			gotoxy(i*2, j); printf((map[i][j] == 1) ? "��" : "  ");
		}
	}
#pragma endregion
#pragma region �õ� �ʱ�ȭ
	srand(time(NULL));//�õ� �ʱ�ȭ
#pragma endregion
#pragma region ���� �ΰ� ����
	AddRandom();
	AddRandom();
#pragma endregion
}
int AddRandom()//���� ���� �Լ�
{
#pragma region ���� ��, ���� ������ �ε��� ����

	int Choose2or4Rand = 0;//2�� 90% 4�� 10%�� �����ϰ� �������� �����ϴ� ����
	Choose2or4Rand = (rand()%100)+1;//1~100�� ������ ���� ����
	int Set2or4 = (Choose2or4Rand <= 90) ? 2 : 4;//90���ϸ�(90%) 2 �ƴϸ�(10%) 4
	int Count0Index = 0;//arr2048�� ���� 0�� �ε����� ���� ����
	for (int i = 0; i < 4; i++)//arr2048 �� 0�� �ε����� ã�� �ڵ�
	{for (int j = 0; j < 4; j++) {if (arr2048[j][i] == 0){Count0Index++;}}}
	if (Count0Index == 0) { return 0; }
	int* ArrCount0Index = (int*)malloc(sizeof(int) * (Count0Index*2));//arr2048���� 0�� �ε����� �����ϴ� �迭
	int a = 0;
	for (int i = 0; i < 4; i++)//arr2048 �� 0�� �ε����� �迭�� �����ϴ� �ڵ�
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
#pragma region �����ϰ� ���
	arr2048[ArrCount0Index[(CreatRandom * 2)]][ArrCount0Index[(CreatRandom * 2)+1]] = Set2or4;
	Show(ArrCount0Index[CreatRandom * 2], ArrCount0Index[(CreatRandom * 2) + 1], Set2or4);
	return 0;
#pragma endregion
}
int Show(int x, int y, int a)//������ ���� map�� ǥ�����ִ� �Լ�
{
//(0,0)//(26,0)//(52,0)//(78,0)
//(0,13)//(26,13)//(52,13)//(78,13)
//(0,26)//(26,26)//(52,26)//(78,26)
//(0,39)//(26,39)//(52,39)//(78,39)
#pragma region x,y�� ����
	//map���� ��ĭ�� ��� 13ĭ
	x = x * 26;
	y = y * 13;
	if (x < 0 || y < 0)
	{
		return 0;
	}
#pragma endregion
#pragma region �ʱ�ȭ
	if (a == 0)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��                        ��");
		gotoxy(x, y + 4);  printf("��                        ��");
		gotoxy(x, y + 5);  printf("��                        ��");
		gotoxy(x, y + 6);  printf("��                        ��");
		gotoxy(x, y + 7);  printf("��                        ��");
		gotoxy(x, y + 8);  printf("��                        ��");
		gotoxy(x, y + 9);  printf("��                        ��");
		gotoxy(x, y + 10); printf("��                        ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����2
	if (a == 2)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��    ���������    ��");
		gotoxy(x, y + 4);  printf("��                  ��    ��");
		gotoxy(x, y + 5);  printf("��                  ��    ��");
		gotoxy(x, y + 6);  printf("��                  ��    ��");
		gotoxy(x, y + 7);  printf("��    ���������    ��");
		gotoxy(x, y + 8);  printf("��    ��                  ��");
		gotoxy(x, y + 9);  printf("��    ��                  ��");
		gotoxy(x, y + 10); printf("��    ��                  ��");
		gotoxy(x, y + 11); printf("��    ���������    ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����4
	if (a == 4)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��     ��          ��     ��");
		gotoxy(x, y + 4);  printf("��     ��          ��     ��");
		gotoxy(x, y + 5);  printf("��     ��          ��     ��");
		gotoxy(x, y + 6);  printf("��     ��          ��     ��");
		gotoxy(x, y + 7);  printf("��     ��������     ��");
		gotoxy(x, y + 8);  printf("��                 ��     ��");
		gotoxy(x, y + 9);  printf("��                 ��     ��");
		gotoxy(x, y + 10); printf("��                 ��     ��");
		gotoxy(x, y + 11); printf("��                 ��     ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����8
	if (a == 8)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��     ��������     ��");
		gotoxy(x, y + 4);  printf("��     ��          ��     ��");
		gotoxy(x, y + 5);  printf("��     ��          ��     ��");
		gotoxy(x, y + 6);  printf("��     ��          ��     ��");
		gotoxy(x, y + 7);  printf("��     ��������     ��");
		gotoxy(x, y + 8);  printf("��     ��          ��     ��");
		gotoxy(x, y + 9);  printf("��     ��          ��     ��");
		gotoxy(x, y + 10); printf("��     ��          ��     ��");
		gotoxy(x, y + 11); printf("��     ��������     ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����16
	if (a == 16)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��                        ��");
		gotoxy(x, y + 4);  printf("��  ��    �������    ��");
		gotoxy(x, y + 5);  printf("��  ��    ��              ��");
		gotoxy(x, y + 6);  printf("��  ��    ��              ��");
		gotoxy(x, y + 7);  printf("��  ��    �������    ��");
		gotoxy(x, y + 8);  printf("��  ��    ��        ��    ��");
		gotoxy(x, y + 9);  printf("��  ��    ��        ��    ��");
		gotoxy(x, y + 10); printf("��  ��    �������    ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����32
	if (a == 32)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��  �����  ������  ��");
		gotoxy(x, y + 4);  printf("��        ��          ��  ��");
		gotoxy(x, y + 5);  printf("��        ��          ��  ��");
		gotoxy(x, y + 6);  printf("��  �����  ������  ��");
		gotoxy(x, y + 7);  printf("��        ��  ��          ��");
		gotoxy(x, y + 8);  printf("��        ��  ��          ��");
		gotoxy(x, y + 9);  printf("��  �����  ������  ��");
		gotoxy(x, y + 10); printf("��                        ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����64
	if (a == 64)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��  �����  ��    ��    ��");
		gotoxy(x, y + 4);  printf("��  ��        ��    ��    ��");
		gotoxy(x, y + 5);  printf("��  ��        ��    ��    ��");
		gotoxy(x, y + 6);  printf("��  �����  �����    ��");
		gotoxy(x, y + 7);  printf("��  ��    ��        ��    ��");
		gotoxy(x, y + 8);  printf("��  ��    ��        ��    ��");
		gotoxy(x, y + 9);  printf("��  �����        ��    ��");
		gotoxy(x, y + 10); printf("��                        ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����128
	if (a == 128)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��                        ��");
		gotoxy(x, y + 4);  printf("��  ��  ����  ����    ��");
		gotoxy(x, y + 5);  printf("��  ��      ��  ��  ��    ��");
		gotoxy(x, y + 6);  printf("��  ��  ����  ����    ��");
		gotoxy(x, y + 7);  printf("��  ��  ��      ��  ��    ��");
		gotoxy(x, y + 8);  printf("��  ��  ����  ����    ��");
		gotoxy(x, y + 9);  printf("��                        ��");
		gotoxy(x, y + 10); printf("��                        ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����256
	if (a == 256)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��                        ��");
		gotoxy(x, y + 4);  printf("��  ���� ���� ����  ��");
		gotoxy(x, y + 5);  printf("��      �� ��     ��      ��");
		gotoxy(x, y + 6);  printf("��  ���� ���� ����  ��");
		gotoxy(x, y + 7);  printf("��  ��         �� ��  ��  ��");
		gotoxy(x, y + 8);  printf("��  ���� ���� ����  ��");
		gotoxy(x, y + 9);  printf("��                        ��");
		gotoxy(x, y + 10); printf("��                        ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����512
	if (a == 512)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��                        ��");
		gotoxy(x, y + 3);  printf("��                        ��");
		gotoxy(x, y + 4);  printf("��  ����   ��   ����  ��");
		gotoxy(x, y + 5);  printf("��  ��       ��       ��  ��");
		gotoxy(x, y + 6);  printf("��  ����   ��   ����  ��");
		gotoxy(x, y + 7);  printf("��      ��   ��   ��      ��");
		gotoxy(x, y + 8);  printf("��  ����   ��   ����  ��");
		gotoxy(x, y + 9);  printf("��                        ��");
		gotoxy(x, y + 10); printf("��                        ��");
		gotoxy(x, y + 11); printf("��                        ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����1024
	if (a == 1024)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��       ��    �����   ��");
		gotoxy(x, y + 3);  printf("��       ��    ��    ��   ��");
		gotoxy(x, y + 4);  printf("��       ��    ��    ��   ��");
		gotoxy(x, y + 5);  printf("��       ��    ��    ��   ��");
		gotoxy(x, y + 6);  printf("��       ��    �����   ��");
		gotoxy(x, y + 7);  printf("��   �����  ��    ��   ��");
		gotoxy(x, y + 8);  printf("��         ��  ��    ��   ��");
		gotoxy(x, y + 9);  printf("��   �����  �����   ��");
		gotoxy(x, y + 10); printf("��   ��              ��   ��");
		gotoxy(x, y + 11); printf("��   �����        ��   ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
#pragma region ����2048
	if (a == 2048)
	{
		gotoxy(x, y + 0);  printf("���������������");
		gotoxy(x, y + 1);  printf("��                        ��");
		gotoxy(x, y + 2);  printf("��  �����  �����    ��");
		gotoxy(x, y + 3);  printf("��        ��  ��    ��    ��");
		gotoxy(x, y + 4);  printf("��  �����  ��    ��    ��");
		gotoxy(x, y + 5);  printf("��  ��        ��    ��    ��");
		gotoxy(x, y + 6);  printf("��  �����  �����    ��");
		gotoxy(x, y + 7);  printf("��  ��    ��  �����    ��");
		gotoxy(x, y + 8);  printf("��  ��    ��  ��    ��    ��");
		gotoxy(x, y + 9);  printf("��  �����  �����    ��");
		gotoxy(x, y + 10); printf("��        ��  ��    ��    ��");
		gotoxy(x, y + 11); printf("��        ��  �����    ��");
		gotoxy(x, y + 12); printf("��                        ��");
		gotoxy(x, y + 13); printf("���������������");
	}
#pragma endregion
}
void Move()//�Է°� ������ ó��
{
#pragma region �Է�
	char Kbi;//�Է¹��� ���� �����ϴ� ����
	char StartCheck = 'Z';//�˻縦 ������ �κ��� �Ǵ��ϴ� ����
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
#pragma region �˻�
	ifmove = false;
	int nx = 5;
	int ny = 5;
	if (StartCheck == 'U') {
		for (int i = 1; i < 4; i++)/* y */{
			for (int j = 0; j < 4; j++)/* x */{
				if (arr2048[j][i] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
				{
					int Cy = i;
					while (1)
					{
						if (arr2048[j][Cy - 1] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� �ִ� ĭ�� ���������
						{
							ifmove = true;
							arr2048[j][Cy - 1] = arr2048[j][Cy];//���� �˻��ϴ�ĭ���� �� ĭ ���� �ִ� ĭ�� ���� ���� ĭ��������
							Show(j, Cy - 1, arr2048[j][Cy]);//������Ʈ
							arr2048[j][Cy] = 0;
							Show(j, Cy, 0);//������Ʈ
							Cy--;
							if (Cy == 0)
							{
								break;
							}
						}
						else if (arr2048[j][Cy - 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0 && j != nx && Cy != ny)//���� �˻��ϴ�ĭ���� ��ĭ ���� �ִ� ĭ�� �ڽ��� ���ڿ� ������
						{
							ifmove = true;
							Score += (arr2048[j][Cy] * 2);
							//gotoxy(15, 54); printf("(%d,%d) = %d", j, Cy - 1, arr2048[j][Cy - 1]);
							arr2048[j][Cy - 1] = arr2048[j][Cy] * 2;//���� �˻��ϴ�ĭ���� �� ĭ ���� �ִ� ĭ�� ���� (���� ĭ * 2)������
							Show(j, Cy - 1, arr2048[j][Cy] * 2);//������Ʈ
							arr2048[j][Cy] = 0;//���� �˻��ϴ�ĭ�� 0����
							Show(j, Cy, 0);//������Ʈ
							nx = j; ny = Cy - 1;
							Cy--;//�˻� y���� ��ĭ ���������Ƿ� ��ĭ ���ֱ�
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
				if (arr2048[j][i] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
				{
					int Cy = i;
					while (1)
					{
						if (arr2048[j][Cy + 1] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� �Ʒ� ĭ�� ���������
						{
							ifmove = true;
							arr2048[j][Cy + 1] = arr2048[j][Cy];//���� �˻��ϴ�ĭ���� �� ĭ �Ʒ� �ִ� ĭ�� ���� ���� ĭ��������
							Show(j, Cy + 1, arr2048[j][Cy]);//������Ʈ
							arr2048[j][Cy] = 0;
							Show(j, Cy, 0);//������Ʈ
							Cy++;
							if (Cy == 3)
							{
								break;
							}
						}
						else if (arr2048[j][Cy + 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0 && j != nx && Cy != ny)//���� �˻��ϴ�ĭ���� ��ĭ ���� �ִ� ĭ�� �ڽ��� ���ڿ� ������
						{
							ifmove = true;
							Score += (arr2048[j][Cy] * 2);
							arr2048[j][Cy + 1] = arr2048[j][Cy] * 2;//���� �˻��ϴ�ĭ���� �� ĭ ���� �ִ� ĭ�� ���� (���� ĭ * 2)������
							Show(j, Cy + 1, arr2048[j][Cy] * 2);//������Ʈ
							arr2048[j][Cy] = 0;//���� �˻��ϴ�ĭ�� 0����
							Show(j, Cy, 0);//������Ʈ
							nx = j; ny = Cy + 1;
							Cy++;//�˻� y���� ��ĭ ���������Ƿ� ��ĭ ���ֱ�
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
				if (arr2048[i][j] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
				{
					int Cx = i;
					while (1)
					{
						if (arr2048[Cx-1][j] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� ĭ�� ���������
						{
							ifmove = true;
							arr2048[Cx-1][j] = arr2048[Cx][j];//���� �˻��ϴ�ĭ���� �� ĭ ���� ĭ�� ���� ���� ĭ��������
							Show(Cx-1,j, arr2048[Cx][j]);//������Ʈ
							arr2048[Cx][j] = 0;
							Show(Cx, j, 0);//������Ʈ
							Cx--;
							if (Cx == 0)
							{
								break;
							}
						}
						else if (arr2048[Cx-1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0 && Cx != nx && j != ny)//���� �˻��ϴ�ĭ���� ��ĭ ���� ĭ�� �ڽ��� ���ڿ� ������
						{
							ifmove = true;
							Score += (arr2048[Cx][j] * 2);
							arr2048[Cx-1][j] = arr2048[Cx][j] * 2;//���� �˻��ϴ�ĭ���� �� ĭ ���� ĭ�� ���� (���� ĭ * 2)������
							Show(Cx-1,j, arr2048[Cx][j] * 2);//������Ʈ
							arr2048[Cx][j] = 0;//���� �˻��ϴ�ĭ�� 0����
							Show(Cx, j, 0);//������Ʈ
							nx = Cx-1; ny = j;
							Cx--;//�˻� y���� ��ĭ ���������Ƿ� ��ĭ ���ֱ�
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
				if (arr2048[i][j] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
				{
					int Cx = i;
					while (1)
					{
						if (arr2048[Cx + 1][j] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ������ ĭ�� ���������
						{
							ifmove = true;
							arr2048[Cx + 1][j] = arr2048[Cx][j];//���� �˻��ϴ�ĭ���� �� ĭ ������ ĭ�� ���� ���� ĭ��������
							Show(Cx + 1, j, arr2048[Cx][j]);//������Ʈ
							arr2048[Cx][j] = 0;
							Show(Cx, j, 0);//������Ʈ
							Cx++;
							if (Cx == 3)
							{
								break;
							}
						}
						else if (arr2048[Cx + 1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0 && Cx != nx && j != ny)//���� �˻��ϴ�ĭ���� ��ĭ ������ ĭ�� �ڽ��� ���ڿ� ������
						{
							ifmove = true;
							Score += (arr2048[Cx][j] * 2);
							//gotoxy(15, 54); printf("(%d,%d) = %d", j, Cy - 1, arr2048[j][Cy - 1]);
							arr2048[Cx + 1][j] = arr2048[Cx][j] * 2;//���� �˻��ϴ�ĭ���� �� ĭ ���� ĭ�� ���� (���� ĭ * 2)������
							Show(Cx + 1, j, arr2048[Cx][j] * 2);//������Ʈ
							arr2048[Cx][j] = 0;//���� �˻��ϴ�ĭ�� 0����
							Show(Cx, j, 0);//������Ʈ
							nx = Cx + 1; ny = j;
							Cx++;//�˻� y���� ��ĭ ���������Ƿ� ��ĭ ���ֱ�
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
bool GameOver() {//���ӿ��� �Ǻ�
#pragma region �迭�� ��ĭ�� �ִ���
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
			if (arr2048[j][i] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
			{
				int Cy = i;
				while (1)
				{
					if (arr2048[j][Cy - 1] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� �ִ� ĭ�� ���������
					{
						return false;
					}
					else if (arr2048[j][Cy - 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� �ִ� ĭ�� �ڽ��� ���ڿ� ������
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
			if (arr2048[j][i] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
			{
				int Cy = i;
				while (1)
				{
					if (arr2048[j][Cy + 1] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� �Ʒ� ĭ�� ���������
					{
						return false;
					}
					else if (arr2048[j][Cy + 1] == arr2048[j][Cy] && arr2048[j][Cy] != 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� �ִ� ĭ�� �ڽ��� ���ڿ� ������
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
			if (arr2048[i][j] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
			{
				int Cx = i;
				while (1)
				{
					if (arr2048[Cx - 1][j] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� ĭ�� ���������
					{
						return false;
					}
					else if (arr2048[Cx - 1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0)//���� �˻��ϴ�ĭ���� ��ĭ ���� ĭ�� �ڽ��� ���ڿ� ������
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
			if (arr2048[i][j] != 0)//���� �˻��ϴ� ĭ�� ������� �ʴٸ�
			{
				int Cx = i;
				while (1)
				{
					if (arr2048[Cx + 1][j] == 0)//���� �˻��ϴ�ĭ���� ��ĭ ������ ĭ�� ���������
					{
						return false;
					}
					else if (arr2048[Cx + 1][j] == arr2048[Cx][j] && arr2048[Cx][j] != 0)//���� �˻��ϴ�ĭ���� ��ĭ ������ ĭ�� �ڽ��� ���ڿ� ������
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
#pragma region ��� ������ ������Ű�� ������ ���� ����
	EndGame();
#pragma endregion

}
void EndGame()//���ӿ��� �޽��� ���
{
#pragma region GAME
	int y = 13;
	int x = 0;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��  �����������  ��");
	gotoxy(x, y + 3);  printf("��  ��                    ��");
	gotoxy(x, y + 4);  printf("��  ��                    ��");
	gotoxy(x, y + 5);  printf("��  ��                    ��");
	gotoxy(x, y + 6);  printf("��  ��                    ��");
	gotoxy(x, y + 7);  printf("��  ��        ������  ��");
	gotoxy(x, y + 8);  printf("��  ��                ��  ��");
	gotoxy(x, y + 9);  printf("��  ��                ��  ��");
	gotoxy(x, y + 10); printf("��  ��                ��  ��");
	gotoxy(x, y + 11); printf("��  �����������  ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	x = 26;
	y = 13;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��  �����������  ��");
	gotoxy(x, y + 3);  printf("��  ��                ��  ��");
	gotoxy(x, y + 4);  printf("��  ��                ��  ��");
	gotoxy(x, y + 5);  printf("��  ��                ��  ��");
	gotoxy(x, y + 6);  printf("��  ��                ��  ��");
	gotoxy(x, y + 7);  printf("��  �����������  ��");
	gotoxy(x, y + 8);  printf("��  ��                ��  ��");
	gotoxy(x, y + 9);  printf("��  ��                ��  ��");
	gotoxy(x, y + 10); printf("��  ��                ��  ��");
	gotoxy(x, y + 11); printf("��  ��                ��  ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	x = 52;
	y = 13;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��   ����������   ��");
	gotoxy(x, y + 3);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 4);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 5);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 6);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 7);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 8);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 9);  printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 10); printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 11); printf("��   ��      ��      ��   ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	x = 78;
	y = 13;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��   ����������   ��");
	gotoxy(x, y + 3);  printf("��   ��                   ��");
	gotoxy(x, y + 4);  printf("��   ��                   ��");
	gotoxy(x, y + 5);  printf("��   ��                   ��");
	gotoxy(x, y + 6);  printf("��   ����������   ��");
	gotoxy(x, y + 7);  printf("��   ��                   ��");
	gotoxy(x, y + 8);  printf("��   ��                   ��");
	gotoxy(x, y + 9);  printf("��   ��                   ��");
	gotoxy(x, y + 10); printf("��   ����������   ��");
	gotoxy(x, y + 11); printf("��                        ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
#pragma endregion
#pragma region OVER
	x = 0;
	y = 26;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��  �����������  ��");
	gotoxy(x, y + 3);  printf("��  ��                ��  ��");
	gotoxy(x, y + 4);  printf("��  ��                ��  ��");
	gotoxy(x, y + 5);  printf("��  ��                ��  ��");
	gotoxy(x, y + 6);  printf("��  ��                ��  ��");
	gotoxy(x, y + 7);  printf("��  ��                ��  ��");
	gotoxy(x, y + 8);  printf("��  ��                ��  ��");
	gotoxy(x, y + 9);  printf("��  ��                ��  ��");
	gotoxy(x, y + 10); printf("��  ��                ��  ��");
	gotoxy(x, y + 11); printf("��  �����������  ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	x = 26;
	y = 26;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��  ��                ��  ��");
	gotoxy(x, y + 3);  printf("��  ��                ��  ��");
	gotoxy(x, y + 4);  printf("��  ��                ��  ��");
	gotoxy(x, y + 5);  printf("��  ��                ��  ��");
	gotoxy(x, y + 6);  printf("��  ��                ��  ��");
	gotoxy(x, y + 7);  printf("��    ��            ��    ��");
	gotoxy(x, y + 8);  printf("��    ��            ��    ��");
	gotoxy(x, y + 9);  printf("��      ��        ��      ��");
	gotoxy(x, y + 10); printf("��        ��    ��        ��");
	gotoxy(x, y + 11); printf("��          ���          ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	x = 52;
	y = 26;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��   ����������   ��");
	gotoxy(x, y + 3);  printf("��   ��                   ��");
	gotoxy(x, y + 4);  printf("��   ��                   ��");
	gotoxy(x, y + 5);  printf("��   ��                   ��");
	gotoxy(x, y + 6);  printf("��   ����������   ��");
	gotoxy(x, y + 7);  printf("��   ��                   ��");
	gotoxy(x, y + 8);  printf("��   ��                   ��");
	gotoxy(x, y + 9);  printf("��   ��                   ��");
	gotoxy(x, y + 10); printf("��   ����������   ��");
	gotoxy(x, y + 11); printf("��                        ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	x = 78;
	y = 26;
	gotoxy(x, y + 0);  printf("���������������");
	gotoxy(x, y + 1);  printf("��                        ��");
	gotoxy(x, y + 2);  printf("��   ���������     ��");
	gotoxy(x, y + 3);  printf("��   ��              ��   ��");
	gotoxy(x, y + 4);  printf("��   ��              ��   ��");
	gotoxy(x, y + 5);  printf("��   ��              ��   ��");
	gotoxy(x, y + 6);  printf("��   ���������     ��");
	gotoxy(x, y + 7);  printf("��   �� ���              ��");
	gotoxy(x, y + 8);  printf("��   ��    ���           ��");
	gotoxy(x, y + 9);  printf("��   ��       ���        ��");
	gotoxy(x, y + 10); printf("��   ��          ���     ��");
	gotoxy(x, y + 11); printf("��   ��             ���  ��");
	gotoxy(x, y + 12); printf("��                        ��");
	gotoxy(x, y + 13); printf("���������������");
	
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

