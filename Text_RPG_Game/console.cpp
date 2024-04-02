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
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void moveCursor(int x, int y)	//�ܼ� �� �Է�Ŀ�� �̵�
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);	//�ܼ� ��� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);	//������ ���(Ŀ��)�� �ش� ��ǥ�� �̵�
}

/*Ÿ��Ʋ ȭ��*/
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
					if (0/*���̺� ������ �ִٸ�*/)
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

/*ĳ���� ���� ȭ��*/
Sences MakeCharacter()
{
	int answerInt;
	char answerName[20];
	while (1)
	{
		system("cls");
		DrawTextInterfaceFrame();
		moveCursor(3, 4);
		cout << "�� ���ϴ� ������ ����ּ���" << endl;
		moveCursor(3, 5); 	cout << "1. ����";
		moveCursor(3, 6);	cout << "2. ������";
		moveCursor(3, 7);	cout << "3. �ü�";
		moveCursor(3, 8);	cout << "4. ������";
		moveCursor(3, 9);	cout << "5. ����";
		moveCursor(3, 11);	cout << " ����> ";
		answerInt = -1;
		while (true)
		{
			cin >> answerInt;
			if (1 <= answerInt && answerInt <= 5)
				player.SetPlayerJob(answerInt);
			break;
		}

		moveCursor(3, 14);
		cout << "�� ����� �̸��� �˷��ּ���";
		moveCursor(3, 15);	cout << " ����> ";
		cin >> answerName;
		player.SetName(answerName);

		system("cls");
		DrawTextInterfaceFrame();
		DrawPlayerStatus(3, 4);
		cout << "�� �̰ɷ� �����Ͻðڽ��ϱ�? : ";
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

/*�ΰ��� �� ���θ޴�*/
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
	cout << "�� ������� ���� �������ּ���" << endl;
	moveCursor(6, 5); 	cout << "1. ����";
	moveCursor(6, 6);	cout << "2. ����";
	moveCursor(6, 7);	cout << "3. ����";
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

/*�幮 Ȥ�� �ٷ��� �ؽ�Ʈ�� ��µǴ� ��� �������̽��� �ص� Ʋ ���*/
void DrawTextInterfaceFrame()
{
	cout << "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "��                                                                                                 ��" << endl;
	cout << "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
	return;
}

void DrawPlayerStatus(int x_, int y_)
{
	moveCursor(x_, y_);
	cout << "�������� ����â ��������������";	moveCursor(x_, y_+1);
	cout << "���̸� : " << player.GetName() << "	  ��";	moveCursor(x_, y_+2);
	cout << "������ : " << player.GetJobName() << "	  ��";	moveCursor(x_, y_+3);
	cout << "�����ݷ� : " << player.Getattack() << " 	  ��";	moveCursor(x_, y_+4);
	cout << "��ü�� : " << player.GetHP() << "	  ��";	moveCursor(x_, y_+5);
	cout << "������ : " << player.GetMP() << "	  ��";	moveCursor(x_, y_+6);
	cout << "���ӵ� : " << player.Getspeed() << "	  ��";	moveCursor(x_, y_+7);
	cout << "�������� : " << player.Getmoney() << "	  ��";	moveCursor(x_, y_+8);
	cout << "������ : " << player.Getlevel() << "	  ��";	moveCursor(x_, y_+9);
	cout << "������ġ : " << player.Getexp() << "  	  ��";	moveCursor(x_, y_+10);
	cout << "��������������������������������������";	moveCursor(x_, y_+11);
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
			cout << "���� ȭ�� ��ȯ" << endl;
			system("pause");
			nowSencs = MAP;
			break;
		case LODGE:
			cout << "���� ȭ�� ��ȯ" << endl;
			system("pause");
			nowSencs = MAP;
			break;
		case DUNGENS:
			cout << "���� �Ա� ȭ�� ��ȯ" << endl;
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



