#pragma once
#include<iostream>
#include<windows.h>
#include<stdbool.h>
#include<vector>
#include<conio.h>
#define dfSCREEN_WIDTH		81	// 콘솔 가로 80칸 + NULL
#define dfSCREEN_HEIGHT	24	// 콘솔 세로 24칸

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
	//다시한번 말하지만 FillConsoleOutputCharacter 이 함수는 지정 좌표에 n개의 글자를 보여주는것이다.
	//만약 81 * 24이렇게 크기를 넣는다고 해서 이것이 2차배열  처럼 처리를 하는게 절대 아니다....
	//주의하자 동현아.
}


//헤더파일을 만들고 cpp파일에 해당 함수을 구현하면 왜 이미 있다고 뜨는지? 



