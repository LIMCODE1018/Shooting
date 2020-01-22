#pragma once
#include<iostream>
#include<windows.h>
#include<stdbool.h>
#include<vector>
#include<conio.h>
#define dfSCREEN_WIDTH		81	// �ܼ� ���� 80ĭ + NULL
#define dfSCREEN_HEIGHT	24	// �ܼ� ���� 24ĭ

using namespace std;

enum Type
{
	SPACE,
	ENERMY,
	END
};

HANDLE WScreen[2];
char MainBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
int		Index = 0;

void cs_Initial(void)
{
	WScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	WScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(WScreen[0], &stConsoleCursor);
	SetConsoleCursorInfo(WScreen[1], &stConsoleCursor);
}

void cs_MoveCursor(int iPosX, int iPosY, int index)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	SetConsoleCursorPosition(WScreen[index], stCoord);
}


void cs_ClearScreen(int index)
{
	DWORD dw; // unsigned long 
	for (short i = 0; i < dfSCREEN_HEIGHT; i++)
	{
		FillConsoleOutputCharacter(WScreen[index], ' ', dfSCREEN_WIDTH - 1, { 0, i }, &dw);
	}
	//�ٽ��ѹ� �������� FillConsoleOutputCharacter �� �Լ��� ���� ��ǥ�� n���� ���ڸ� �����ִ°��̴�.
	//���� 81 * 24�̷��� ũ�⸦ �ִ´ٰ� �ؼ� �̰��� 2���迭  ó�� ó���� �ϴ°� ���� �ƴϴ�....
	//�������� ������.
}


//��������� ����� cpp���Ͽ� �ش� �Լ��� �����ϸ� �� �̹� �ִٰ� �ߴ���? 



