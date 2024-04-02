enum Sences;

class Cursor
{
private:
	const char* shape = "¢º";
	int x;
	int y;

public:
	Cursor();
	Cursor(int _x, int _y);
	int GetPosX();
	int GetPosY();
	const char* print();

	void SetPos(int _x, int _y);
};

void SetGameOption();
void CursorSetting();
void moveCursor(int x, int y);

Sences GameTitle();
Sences MakeCharacter();
Sences MainMenu();
Sences MapInterface();
Sences PlayerInformation();
Sences Vilige();
Sences Store();
Sences Lodge();
Sences Dungens();
Sences FightInterface();

void DrawGameTitle();
void DrawTextInterfaceFrame();
void DrawPlayerStatus(int x, int y);

void ChangeGameSences(Sences num);
