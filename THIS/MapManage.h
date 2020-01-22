#pragma once
#include"Console.h"

struct CMap
{
	char strName[32];
	char Mirror[5][80];
	COORD MapSize;



	bool Init(const char* Line)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int k = 0; k < 80; k++)
			{
				Mirror[i][k] = ' ';
			}
		}


		FILE* pFile = nullptr;
		fopen_s(&pFile, Line, "rt");
		if (!pFile)
			return false;

		strcpy_s(strName, Line);
		int Length = strlen(strName);

		for (int i = Length - 1; i >= 0; --i)
		{
			if (strName[i] == '.')
			{
				memset(&strName[i], 0, Length - i);
				break;
			}
		}

		char sLine[80] = {};
		fgets(sLine, 80, pFile);  // 해당 적들의 위치의 크기들을 알려주는 81, 5 크기가 첫줄에 있다.
		char* pContext = nullptr;
		char* pTok = strtok_s(sLine, ",", &pContext);// , 기준으로 나눈다.
		MapSize.X = atoi(pTok);
		MapSize.Y = atoi(pContext);

		for (int i = 4; i < MapSize.Y; i++)
		{
			fgets(sLine, 80, pFile);

			for (int k = 0; k < MapSize.X; k++)
			{
				if(sLine[k] == '1')
					Mirror[i][k] = 'X';
			}
		}	
		fclose(pFile);
		return true;
	}

	void Map_Render() //적들이 맨처음 등장할떄 한칸씩 천천히 자기위치로 가는 액션.....
	{
		for (int k = 0; k < MapSize.X; k++)
		{
			if (Mirror[4][k] == 'X')
			{
				MainBuffer[4][k] = Mirror[4][k];
			}
		}
	}
};


struct MapManager
{
	vector<struct CMap*> vec_Map;

	bool Init()
	{
		FILE* pFile = nullptr;
		fopen_s(&pFile, "MapList.txt", "rt");

		if (!pFile)
			return false;

		int MapCount = 0;
		char Line[64] = {};

		fgets(Line, 64, pFile);			//pFile로 부터 문자열을 가져오는 함수.
		MapCount = atoi(Line);         //숫자로된 문자를 정수형으로 바꿔준다.

		for (int i = 0; i < MapCount ; i++)
		{
			fgets(Line, 64, pFile);

			int Length = strlen(Line);
			Line[Length - 1] = 0;
			CMap* pMap = new CMap;
			pMap->Init(Line);
			vec_Map.push_back(pMap);
		}
		fclose(pFile);

		return true;
	}

	CMap* GetMap(int idx)
	{
		return vec_Map[idx];
	}

	void Delete_MapList()
	{
		for (size_t  i = 0; i < vec_Map.size(); i++)
		{
			delete vec_Map[i];
		}
	}
};