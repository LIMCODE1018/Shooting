#include"Console.h"
#include"MapManage.h"
#define Bullet_Max 6
#define _CRT_SECURE_NO_WARNINGS

COORD Player_Pos = { 40, 20 };
typedef struct
{
	int pos_iX = 0;
	int pos_iY = 0;
	char image = 'i';
}Bullet;
Bullet * p_Bullet[Bullet_Max];
//총알이 M바로앞이 아니고 좀 떨어져서 발사되고
//미사일이 Max값에 적게 나온다.   →   해결..... 중첩if때문이었던거 같다.
//단발로 나오게할려면?

MapManager Map;

void Start();
void CreateBullet();
void Move_Bullet();
void ScreenFlipping();
void ScreenClear();
void DrawBuffer();
void KeyInput(const char Shape);
void ScreenRelease();
void Render();

void RR()
{
	for (int y = 0; y < dfSCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < dfSCREEN_WIDTH - 1; x++)
		{
			MainBuffer[y][x] = ' ';
		}
		MainBuffer[y][dfSCREEN_WIDTH - 1] = '\0';
	}
	MainBuffer[20][40] = 'M';//시작위치
}

int main()
{
	system(" mode  con lines=24   cols=81 ");
	RR();

	for (int i = 0; i < Bullet_Max; i++)
	{
		p_Bullet[i] = nullptr;	
	}
	if (!Map.Init())

	{
		cout << "이상하네....." << endl;
		return 0;
	}
	
	cs_Initial();
	Start();
	while (1)
	{
		Render();
	}
	ScreenRelease();
}

void Render()
{
	ScreenClear();
	//if (- _kbhit())
	//{
	//	KeyInput('M');
	//}
	//Map.vec_Map[1]->Map_Render();
	KeyInput('M');
	Move_Bullet();
	DrawBuffer();
	ScreenFlipping();
	Sleep(33);
}

void CreateBullet()
{
	if (Player_Pos.Y == 0)
		return;

	int index = -1;
	for (int i =0; i < Bullet_Max; i++)
	{
		if (p_Bullet[i] == nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
		return;

	p_Bullet[index] = new Bullet;
	
	p_Bullet[index]->pos_iX = Player_Pos.X;
	p_Bullet[index]->pos_iY = Player_Pos.Y - 1;
	MainBuffer[p_Bullet[index]->pos_iY][p_Bullet[index]->pos_iX] = 'i';
}

void Move_Bullet()
{
	for (int i = 0; i < Bullet_Max; i++)
	{
		if (p_Bullet[i] != nullptr)
		{
			if (p_Bullet[i]->pos_iY == 0)
			{
				MainBuffer[p_Bullet[i]->pos_iY][p_Bullet[i]->pos_iX] = ' ';
				delete p_Bullet[i];
				p_Bullet[i] = nullptr;
			}
			else
			{
				MainBuffer[p_Bullet[i]->pos_iY][p_Bullet[i]->pos_iX] = ' ';
				p_Bullet[i]->pos_iY--;
				MainBuffer[p_Bullet[i]->pos_iY][p_Bullet[i]->pos_iX] = p_Bullet[i]->image;
			}
		}
	}
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(WScreen[Index]);
	Index = !Index;
}

void ScreenClear()
{
	cs_ClearScreen(Index);
}

void DrawBuffer()
{
	DWORD dw;
	int Iy = 0;

	while (Iy < dfSCREEN_HEIGHT)
	{
		cs_MoveCursor(0, Iy, Index);
		WriteFile(WScreen[Index], MainBuffer[Iy], dfSCREEN_WIDTH - 1, &dw, NULL);
		Iy++;
	}
}

void KeyInput(const char Shape)
{
	static bool SpaceFlag = true;

	//=======================================================================
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && Player_Pos.X > 0)
	{
		MainBuffer[Player_Pos.Y][Player_Pos.X] = ' ';
		Player_Pos.X--;
	}
	//=======================================================================
	 if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && Player_Pos.X < dfSCREEN_WIDTH - 2)
	{
		MainBuffer[Player_Pos.Y][Player_Pos.X] = ' ';
		Player_Pos.X++;
	}
	//=======================================================================
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && Player_Pos.Y > 0)
	{
		MainBuffer[Player_Pos.Y][Player_Pos.X] = ' ';
		Player_Pos.Y--;
	}
	//=======================================================================
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && Player_Pos.Y < dfSCREEN_HEIGHT - 1)
	{
		MainBuffer[Player_Pos.Y][Player_Pos.X] = ' ';
		Player_Pos.Y++;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 )
	{
		CreateBullet();
	}
	//=======================================================================
	MainBuffer[Player_Pos.Y][Player_Pos.X] = Shape;
}
// if문 안에 동시에 2개이상의 GetAsyncKeyState적용이 불가한것 같다.
//그리고 if문안에 또다른 방향의 if문을 쓸필요없이 
//그냥 else if을 썼던것이 착오였던것 같다.

void ScreenRelease()
{
	CloseHandle(WScreen[0]);
	CloseHandle(WScreen[1]);
}

void Start()
{
	cout << endl;
	cout << "===================================" << endl;
	cout << endl;
	cout << '\t' << "게임 시작" << endl;
	cout << endl;
	cout << "===================================" << endl;
	cout << "아무키나 누르세요....." << endl;
	system("pause");
}

