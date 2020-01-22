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
//�Ѿ��� M�ٷξ��� �ƴϰ� �� �������� �߻�ǰ�
//�̻����� Max���� ���� ���´�.   ��   �ذ�..... ��øif�����̾����� ����.
//�ܹ߷� �������ҷ���?

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
	MainBuffer[20][40] = 'M';//������ġ
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
		cout << "�̻��ϳ�....." << endl;
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
// if�� �ȿ� ���ÿ� 2���̻��� GetAsyncKeyState������ �Ұ��Ѱ� ����.
//�׸��� if���ȿ� �Ǵٸ� ������ if���� ���ʿ���� 
//�׳� else if�� ������� ���������� ����.

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
	cout << '\t' << "���� ����" << endl;
	cout << endl;
	cout << "===================================" << endl;
	cout << "�ƹ�Ű�� ��������....." << endl;
	system("pause");
}

