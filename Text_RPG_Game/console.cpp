#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <string>

#include "console.h"
#include "Character.h"

#define GAME_WIDTH 100
#define GAME_HEIGHT 30

using namespace std;

Character player;
Cursor cursor;

enum Sences
{
	GAME_TITLE,
	SAVE_FILE,
	MAKE_CHARACTER,
	MAIN_MENU,
	MAP,
	PLAYER_INFO,
	VILIGE,
	STORE,
	LODGE,
	DUNGENS,
	FIGHT_SENCE, 
	GAME_EXIT
};

CONSOLE_CURSOR_INFO cursorInfo;

/*Cursor Class*/
Cursor::Cursor() {}
Cursor::Cursor(int _x, int _y)	{ x = _x; y = _y; }
int Cursor::GetPosX() { return x; }
int Cursor::GetPosY() { return y; }
const char* Cursor::print() { return shape; }
void Cursor::SetPos(int _x, int _y) { x = _x;  y = _y; }

void SetGameOption()
{
	system("mode con:cols=100 lines=30 | title TextRPG");
	std::wcout.imbue(std::locale("Kor"));
}

void CursorSetting()
{
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void moveCursor(int x, int y)	//콘솔 내 입력커서 이동
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);	//콘솔 헨들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);	//가져온 헨들(커서)을 해당 좌표로 이동
}

/*타이틀 화면*/
Sences GameTitle()
{
	DrawGameTitle();
	cursor.SetPos(37, 20);
	moveCursor(cursor.GetPosX(), cursor.GetPosY());
	cout << cursor.print();

	while (1)
	{
		if (_kbhit() != 0)
		{
			switch (_getch())
			{
			case 'w':
			case 'W':
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << "   ";
				if (cursor.GetPosY() == 20)
					cursor.SetPos(cursor.GetPosX(), 2 + cursor.GetPosY());
				else
					cursor.SetPos(cursor.GetPosX(), -1 + cursor.GetPosY());
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << cursor.print();
				break;
			case 's':
			case 'S':
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << "   ";
				if (cursor.GetPosY() == 22)
					cursor.SetPos(cursor.GetPosX(), -2 + cursor.GetPosY());
				else
					cursor.SetPos(cursor.GetPosX(), 1 + cursor.GetPosY());
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << cursor.print();
				break;
			case ' ':
				switch (cursor.GetPosY())
				{
				case 20:
					return MAKE_CHARACTER;
					break;
				case 21:
					if (0/*세이브 파일이 있다면*/)
						return SAVE_FILE;
					break;
				case 22:
					return GAME_EXIT;
					break;
				}
				break;
			default:
				break;
			}
			Sleep(20);
		}
	}
}

/*캐릭터 생성 화면*/
Sences MakeCharacter()
{
	int answerInt;
	char answerName[20];
	while (1)
	{
		system("cls");
		DrawTextInterfaceFrame();
		moveCursor(3, 4);
		cout << "◆ 원하는 직업을 골라주세요" << endl;
		moveCursor(3, 5); 	cout << "1. 전사";
		moveCursor(3, 6);	cout << "2. 마법사";
		moveCursor(3, 7);	cout << "3. 궁수";
		moveCursor(3, 8);	cout << "4. 격투가";
		moveCursor(3, 9);	cout << "5. 도적";
		moveCursor(3, 11);	cout << " └─> ";
		answerInt = -1;
		while (true)
		{
			cin >> answerInt;
			if (1 <= answerInt && answerInt <= 5)
				player.SetPlayerJob(answerInt);
			break;
		}

		moveCursor(3, 14);
		cout << "◆ 당신의 이름을 알려주세요";
		moveCursor(3, 15);	cout << " └─> ";
		cin >> answerName;
		player.SetName(answerName);

		system("cls");
		DrawTextInterfaceFrame();
		DrawPlayerStatus(3, 4);
		cout << "◆ 이걸로 결정하시겠습니까? : ";
		moveCursor(6, 17);	cout << "Yes";
		moveCursor(6, 18);	cout << "No";
		Cursor cursor(3, 17);
		moveCursor(cursor.GetPosX(), cursor.GetPosY());
		cout << cursor.print();
		char getChar = NULL;
		while (1)
		{
			if (_kbhit() != 0)
			{
				getChar = _getch();
				switch (getChar)
				{
				case 'w':
				case 'W':
					moveCursor(cursor.GetPosX(), cursor.GetPosY());
					cout << "   ";
					if (cursor.GetPosY() == 17)
						cursor.SetPos(cursor.GetPosX(), 18);
					else
						cursor.SetPos(cursor.GetPosX(), -1 + cursor.GetPosY());
					moveCursor(cursor.GetPosX(), cursor.GetPosY());
					cout << cursor.print();
					break;
				case 's':
				case 'S':
					moveCursor(cursor.GetPosX(), cursor.GetPosY());
					cout << "   ";
					if (cursor.GetPosY() == 18)
						cursor.SetPos(cursor.GetPosX(), 17);
					else
						cursor.SetPos(cursor.GetPosX(), 1 + cursor.GetPosY());
					moveCursor(cursor.GetPosX(), cursor.GetPosY());
					cout << cursor.print();
					break;
				case ' ':
					break;
				}
				Sleep(20);
			}
			if (getChar == ' ')
				break;
		}
		switch (cursor.GetPosY())
		{
		case 17:
			return MAP;
			break;
		case 18:
			continue;
		}
	}
}

/*인게임 내 메인메뉴*/
Sences MainMenu()
{
	return MAP;
}

Sences MapInterface()
{
	system("cls");
	int answerInt;
	DrawTextInterfaceFrame();
	moveCursor(3, 4);
	cout << "◆ 가고싶은 곳을 선택해주세요" << endl;
	moveCursor(6, 5); 	cout << "1. 던전";
	moveCursor(6, 6);	cout << "2. 여관";
	moveCursor(6, 7);	cout << "3. 상점";
	cursor.SetPos(3, 5);
	moveCursor(cursor.GetPosX(), cursor.GetPosY());
	cout << cursor.print();
	while (1)
	{
		if (_kbhit() != 0)
		{
			switch (_getch())
			{
			case 'w':
			case 'W':
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << "   ";
				if (cursor.GetPosY() == 5)
					cursor.SetPos(cursor.GetPosX(), cursor.GetPosY() + 2);
				else
					cursor.SetPos(cursor.GetPosX(), cursor.GetPosY() - 1);
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << cursor.print();
				break;
			case 's':
			case 'S':
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << "   ";
				if (cursor.GetPosY() == 7)
					cursor.SetPos(cursor.GetPosX(), cursor.GetPosY() - 2);
				else
					cursor.SetPos(cursor.GetPosX(), cursor.GetPosY() + 1);
				moveCursor(cursor.GetPosX(), cursor.GetPosY());
				cout << cursor.print();
				break;
			case ' ':
				switch (cursor.GetPosY())
				{
				case 5:
					return DUNGENS;
				case 6:
					return LODGE;
				case 7:
					return STORE;
				}
			}
			Sleep(20);
		}
	}
}

Sences PlayerInformation()
{
	return MAP;
}
Sences Vilige()
{
	return MAP;
}
Sences Store()
{
	return MAP;
}
Sences Lodge()
{
	return MAP;
}
Sences Dungens()
{
	return MAP;
}
Sences FightInterface()
{
	return MAP;
}

void DrawGameTitle()
{
	cout << endl << endl << endl;
	cout << "                                          RRRRRRRRRR      PPPPPPPPP        GGGGGGG     " << endl;
	cout << "                                          RR       RR     PP      PP      GG     GG    " << endl;
	cout << "                                          RR       RR     PP      PP     GG            " << endl;
	cout << "                                          RR       RR     PP      PP     GG            " << endl;
	cout << "                                          RRRRRRRRRR      PPPPPPPPP      GG            " << endl;
	cout << "           ttttt  eee   x   x  ttttt      RR RR           PP             GG  GGGGGGG   " << endl;
	cout << "             t   e   e   x x     t        RR  RR          PP             GG       GG   " << endl;
	cout << "             t   eeeee    x      t        RR    RR        PP             GG       GG   " << endl;
	cout << "             t   e       x x     t        RR     RR       PP              GG     GG    " << endl;
	cout << "             t    eee   x   x    t        RR      RR      PP               GGGGGGG     " << endl;
	cout << endl << endl << endl;
	moveCursor(40, 20);
	printf("GAME START");
	moveCursor(40, 21);
	printf("LOAD GAME");
	moveCursor(40, 22);
	printf("EXIT");
}

/*장문 혹은 다량의 텍스트가 출력되는 모든 인터페이스에 해딩 틀 사용*/
void DrawTextInterfaceFrame()
{
	cout << "┌─────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "│                                                                                                 │" << endl;
	cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────┘" << endl;
	return;
}

void DrawPlayerStatus(int x_, int y_)
{
	moveCursor(x_, y_);
	cout << "┌─── 상태창 ──────┐";	moveCursor(x_, y_+1);
	cout << "│이름 : " << player.GetName() << "	  │";	moveCursor(x_, y_+2);
	cout << "│직업 : " << player.GetJobName() << "	  │";	moveCursor(x_, y_+3);
	cout << "│공격력 : " << player.Getattack() << " 	  │";	moveCursor(x_, y_+4);
	cout << "│체력 : " << player.GetHP() << "	  │";	moveCursor(x_, y_+5);
	cout << "│마나 : " << player.GetMP() << "	  │";	moveCursor(x_, y_+6);
	cout << "│속도 : " << player.Getspeed() << "	  │";	moveCursor(x_, y_+7);
	cout << "│소지금 : " << player.Getmoney() << "	  │";	moveCursor(x_, y_+8);
	cout << "│레벨 : " << player.Getlevel() << "	  │";	moveCursor(x_, y_+9);
	cout << "│경험치 : " << player.Getexp() << "  	  │";	moveCursor(x_, y_+10);
	cout << "└─────────────────┘";	moveCursor(x_, y_+11);
	moveCursor(x_, y_+12);
}

void ChangeGameSences(Sences _type)
{
	Sences nowSencs = _type;
	while (true)
	{
		switch (nowSencs)
		{
		case GAME_TITLE:
			nowSencs = GameTitle();
			break;
		case MAKE_CHARACTER:
			nowSencs = MakeCharacter();
			break;
		case MAIN_MENU:
			break;
		case MAP:
			nowSencs = MapInterface();
			break;
		case PLAYER_INFO:
			break;
		case VILIGE:
			break;
		case STORE:
			cout << "상점 화면 전환" << endl;
			system("pause");
			nowSencs = MAP;
			break;
		case LODGE:
			cout << "여관 화면 전환" << endl;
			system("pause");
			nowSencs = MAP;
			break;
		case DUNGENS:
			cout << "던전 입구 화면 전환" << endl;
			system("pause");
			nowSencs = MAP;
			break;
		case FIGHT_SENCE:
			break;
		case GAME_EXIT:
			return;
		default:
			break;
		}
	}
}



