#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <stdlib.h>

using namespace std;

//#define FOR(a,b) for (int i=a; i<=b; i++);

static HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
static HANDLE inpHandle = GetStdHandle(STD_INPUT_HANDLE);

const int OutRandom[3] = { 2,2,4 };

short ColorBackground[10000];
bool WantExit, Over, Checking; 
int broad[4][4]; int add[4][4];
int NumItemMenu = 3; int Score = 0; int Best;
int SelectionMenuItem;
const string NameMenuItem[3] = { "Play", "Credit", "Exit" };

int readKey()
{
	fflush(stdin);
	char c = _getch();
	if ((int)c == -32)
	{
		c = _getch();
		return -((int)c);
	}
	else
		return (int)c;
}

void resizeConsole(int width, int height)
{
	_COORD coord;
	coord.X = width;
	coord.Y = height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	SetConsoleScreenBufferSize(outHandle, coord);
	SetConsoleWindowInfo(outHandle, TRUE, &Rect);
}

void gotoxy(SHORT x, SHORT y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(outHandle, c);
}

void setColor(int colorText, int colorBackground)
{
	SetConsoleTextAttribute(outHandle, colorText + 16 * colorBackground);
}

void printxy(long n, int x, int y, int colorText, int colorBackground)
{
	setColor(colorText, colorBackground);
	gotoxy(x, y);
	cout << n;
}

void printxy(string s, int x, int y, int colorText, int colorBackground)
{
	setColor(colorText, colorBackground);
	gotoxy(x, y);
	cout << s;
}

void showHelpFinal(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy(" /\\", 29, 24, 12 * kind, 0);
	printxy("<||>", 29, 25, 14 * kind, 0);
	printxy("\\/", 30, 26, 11 * kind, 0);
	printxy("Use your ", 19, 25, 7 * kind, 0);
	printxy("on your keyboard to move the tiles.", 35, 25, 7 * kind, 0);
	printxy("Share with friends :)", 85, 14, 8 * kind, 0);
}

void showMenu(bool status) {
	int kind = 0;
	if (status) kind = 1;
	for (int i=0; i<NumItemMenu; i++) {
		printxy("  ", 53, 12 + i * 3, 0, 0);
		printxy(NameMenuItem[i], 55, 12+i*3, 15 * kind, 0);
	}
}

void showGameName(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy(" ___   ____     _   ____  ", 45, 4, 6 * kind, 0);
	printxy("    | |    |   /   |    | ", 45, 5, 6 * kind, 0);
	printxy(" ___| |    |  /    |____| ", 45, 6, 6 * kind, 0);
	printxy("|     |    | /___| |    | ", 45, 7, 6 * kind, 0);
	printxy("|___/ |____|     | |____| ", 45, 8, 6 * kind, 0);
	printxy("Version 1.0", 74, 8, 14 * kind, 8 * kind);
}

void showSelection(bool status) {
	int kind = 0;
	if (status) kind = 1;
	if (SelectionMenuItem == 0) {
		printxy("       ", 55, 12, 0, 0);
		printxy(NameMenuItem[0], 53, 12, 11 * kind, 0);
	}
	else if (SelectionMenuItem == 1) {
		printxy("       ", 55, 12+3 , 0, 0);
		printxy(NameMenuItem[1], 53, 12+3, 11 * kind, 0);
	}
	else if (SelectionMenuItem == 2) {
		printxy("       ", 55, 12 + 6, 0, 0);
		printxy(NameMenuItem[2], 53, 12 + 6, 11*kind, 0);
	}
}

void showIcon(bool status) {
	int kind = 0;
	if (status) kind = 1;
	for (int i = 0; i < 10; i++) {
		printxy("X", i * 2, 20 + i, 23 * kind, 16 * kind);
		printxy("X", 100 + i * 2, i, 23 * kind, 16 * kind);
	}
}

void Loading(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy("Loading...", 55, 21, 11*kind, 0);
	for (int i = 0; i <= 30; i++) {
		printxy("| ", 45 + i, 23, 7*kind , 0);
	}
	for (int i = 0; i <= 30; i++) {
		printxy("| ", 45 + i, 23, 0, 10*kind);
		Sleep(25);
	}
	kind = 0;
	printxy("Loading...", 55, 21, 11 * kind, 0);
	for (int i = 0; i <= 30; i++) {
		printxy("| ", 45 + i, 23, 7 * kind, 0);
	}
	for (int i = 0; i <= 30; i++) {
		printxy("| ", 45 + i, 23, 0, 10 * kind);
		//Sleep(25);
	}
}

void showHelp(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy("|", 30, 24, 12 * kind, 0);
	printxy("_   _", 28, 25, 14 * kind, 0);
	printxy("|", 30, 26, 11 * kind, 0);
}

void Menu() {
	showMenu(true);
	showGameName(true);
	showHelpFinal(false);
	showHelp(true);
	SelectionMenuItem = 0;
	showIcon(true);
	int key = 0;
	do {
		showSelection(true);
		key = readKey();
		if (key == -72) {
			SelectionMenuItem = max(0, SelectionMenuItem - 1);
		}
		else if (key == -80) {
			SelectionMenuItem = min(NumItemMenu - 1, SelectionMenuItem + 1);
		}
		showSelection(false);
		showMenu(true);
	} while (key != 13);
	Loading(true);
	showMenu(false);
	showGameName(false);
	//showIcon(false);
	//Loading(false);
}

void showGamePlay(bool status) {
	int kind = 0;
	if (status) kind = 1;
	for (int i = 47; i < 67; i += 6) {
		printxy("_____", i+1, 9, 6 * kind, 0);
		for (int j = 10; j < 21; j += 3) {
			printxy("|     |", i, j, 6 * kind, 0);
			printxy("|     |", i, j + 1, 6 * kind, 0);
			printxy("|_____|", i, j + 2, 6 * kind, 0);
		}
	}
}

void showItem(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy(" __  __  .. __ ", 47, 3, 8 * kind, 0);
	printxy(" __||  |/_||__|  ", 47, 4, 8 * kind, 0);
	printxy("|__ |__|  ||__|  ", 47, 5, 8 * kind, 0);
	printxy("Join the number ", 47, 7, 7 * kind, 0);
	printxy("and get to the 2048 tile!", 47, 8, 7 * kind, 0);
}

int countNum(int x) {
	int countN = 0;
	do {
		countN++;
		x /= 10;
	} while (x != 0);
	return countN;
}

void showScore(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy("  Score  ", 64, 4, 15 * kind, 6 * kind);
	printxy("         ", 64, 5, 15 * kind, 6 * kind);
	printxy(Score, 68-countNum(Score)/2, 5, 15 * kind, 6 * kind);
}

void showBest(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy("  Best   ", 64, 6, 15 * kind, 8 * kind);
	printxy("         ", 64, 7, 15 * kind, 8 * kind);
	printxy(Best, 68 - countNum(Best)/2, 7, 15 * kind, 8 * kind);
}

void IntRand() {
	int num = 2; int x, y, value;
	do {
		x = rand() % 4 + 0;
		y = rand() % 4 + 0;
		value = rand() % 2 + 0;
		if (broad[x][y] == 0) {
			broad[x][y] = OutRandom[value];
			num--;
		}
	} while (num != 0); 
	//broad[1][2] = 2; broad[0][0] = 4;
}

void Start() {
	showHelp(false);
	showHelpFinal(true);
	showGamePlay(true);
	showItem(true);
	showScore(true);
	showBest(true);
	IntRand();
}

void OutRand() {
	int num = 1; int x, y, value;
	do {
		x = rand() % 4 + 0;
		y = rand() % 4 + 0;
		value = rand() % 3 + 0;
		if (broad[x][y] == 0) {
			broad[x][y] = OutRandom[value];
			num--;
		}
	} while (num != 0);
}

void showBroad(bool status) {
	int kind = 0; 
	if (status) kind = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (broad[i][j] != 0) {
				printxy("     ", 50 + j * 6-2, 10 + i * 3, ColorBackground[broad[i][j]] * kind, ColorBackground[broad[i][j]] * kind);
				printxy("     ", 50 + j * 6-2, 10 + i * 3 + 1, 0, ColorBackground[broad[i][j]] * kind);
				//printxy("   ", 50 + j * 6 - 2, 10 + i * 3 + 2, 0, ColorBackground[broad[i][j]] * kind);
				printxy(broad[i][j], 50 + j * 6-countNum(broad[i][j]) / 2, 10 + i * 3+1, 0, ColorBackground[broad[i][j]]*kind);
			}
		}
	}
}

void Calculation(int status) {
	int x, y;
	switch (status)
	{
	case 0:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (broad[i][j] != 0) {
					y = j; x = i;
					while ( x - 1 >= 0 ) {
						if (broad[x - 1][y] == 0) {
							swap(broad[x - 1][y], broad[x][y]);
							--x; Checking = true;
						}
						else if (broad[x - 1][y] == broad[x][y] && add[x - 1][y] == 0) {
							add[x - 1][y] = 1;
							broad[x][y] = 0; Checking = true;
							break;
						}
						else break;
					}
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i < 4; i++) {
			for (int j = 3; j >=0; j--) {
				if (broad[i][j] != 0) {
					x = i; y = j;
					while (y + 1 <= 3) {
						if (broad[x][y + 1] == 0) {
							swap(broad[x][y + 1], broad[x][y]);
							++y; Checking = true;
						}
						else if (broad[x][y + 1] == broad[x][y] && add[x][y + 1] == 0) {
							add[x][y + 1] = 1;
							broad[x][y] = 0; Checking = true;
							break;
						}
						else break;
					}
				}
			}
		}
		break;
	case 2:
		for (int i = 3; i >= 0; i--) {
			for (int j = 3; j >= 0; j--) {
				if (broad[i][j] != 0) {
					x = i; y = j;
					while (x + 1 <= 3) {
						if (broad[x + 1][y] == 0) {
							swap(broad[x + 1][y], broad[x][y]);
							++x; Checking = true;
						}
						else if (broad[x + 1][y] == broad[x][y] && add[x + 1][y] == 0) {
							add[x + 1][y] = 1;
							broad[x][y] = 0; Checking = true;
							break;
						}
						else break;
					}
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j <= 3; ++j) {
				if (broad[i][j] != 0) {
					x = i; y = j;
					while (y - 1 >= 0) {
						if (broad[x][y - 1] == 0) {
							swap(broad[x][y - 1], broad[x][y]);
							--y; Checking = true;
						}
						else if (broad[x][y - 1] == broad[x][y] && add[x][y - 1] == 0) {
							add[x][y - 1] = 1; 
							broad[x][y] = 0; Checking = true;
							break;
						}
						else break;
					}
				}
			}
		}
		break;
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (add[i][j] != 0)
			{
				broad[i][j] *= 2;
				Score += broad[i][j];
				add[i][j] = 0;
			}
		}
	}
}

void CheckOver() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (broad[i][j]==0)
			{
				return;
			}
			else if ((i - 1 >= 0 && broad[i][j] == broad[i - 1][j]) || (i + 1 <= 3 && broad[i][j] == broad[i + 1][j]) ||
				(j - 1 >= 0 && broad[i][j] == broad[i][j - 1]) || (j + 1 <= 3 && broad[i][j] == broad[i][j + 1])) {
				return;
			}
		}
	}
	Over = true;
}

void Playing() {
	int key = 0;
	do {
		showBroad(true); Checking = false;
		showScore(true); showBest(true);
		key = readKey();
		if (key == -72) {
			showBroad(false);
			Calculation(0);
			if (Checking) {
				OutRand();
			}
			showBroad(true);
			key = 0;
		}
		if ( key == -77 ) {
			showBroad(false);
			Calculation(1);
			if (Checking)
			{
				OutRand();
			}
			showBroad(true);
			key = 0;
		}
		if (key == -80) {
			showBroad(false);
			Calculation(2);
			if (Checking) {
				OutRand();
			}
			showBroad(true);
			key = 0;
		}
		if (key==-75) {
			showBroad(false);
			Calculation(3);
			if (Checking) {
				OutRand();
			}
			showBroad(true);
			key = 0;
		}
		CheckOver();
		//showScore(false); showBest(false);
	} while (!Over);
}

void showGameOver(bool status) {
	showHelpFinal(false);
	int kind = 0;
	if (status) kind = 1;
	showGamePlay(false);
	if (Score > Best) {
		printxy("New best score !", 52, 16, kind * 10, 0);
		printxy(Score, 55 + countNum(Score) / 2, 18, 14 * kind, 0);
	}
	printxy("  Game Over!  ", 52, 14, 12 * kind, 8 * kind);
	printxy("Press Enter to return Menu", 45, 20, 6 * kind, 0);
}

void UnStart() {
	showGamePlay(false);
	showItem(false);
	showScore(false);
	showBest(false);
	showGameOver(false);
}

void ScreenCredit(bool x) {
	int kind = 0;
	if (x) kind = 1;
	for (int i = 0; i < 10; i++) {
		printxy("><", i * 2, 20 + i, 15 * kind, 16 * kind);
		printxy("><", 100 + i * 2, i, 15 * kind, 16 * kind);
	}
	printxy("CREDIT:", 15, 7, 11 * kind, 0);
	printxy("Coder:", 20, 9, 11 * kind, 0);
	printxy("#Nguyen Tran Huu Dang", 23, 11, 11 * kind, 0);
	printxy("-KTPM_K13. UIT", 23, 12, 11 * kind, 0);
	printxy("-Practice Smarter-", 23, 13, 11 * kind, 0);
	printxy("Contact:", 65, 7, 10 * kind, 0);
	printxy("-pogback1f4@gmail.com", 70, 8, 10 * kind, 0);
	printxy("-github.com/dangnth", 70, 9, 10 * kind, 0);
	printxy("-01686968950", 70, 10, 10 * kind, 0);
	printxy("THANK   YOU!", 65, 25, 13 * kind, 0);
	printxy("9-10-2018.", 65, 26, 13 * kind, 0);
	printxy("Enter", 25, 27, 9 * kind, 11 * kind);
	printxy("to return Menu", 31, 27, 15 * kind, 0);

}

void Solve() {
	Menu(); int key = 0;
	switch (SelectionMenuItem)
	{
	case 0 :
		WantExit = false;
		showGameName(false);
		showMenu(false);
		Start();
		Playing();
		if (Over) {
			Sleep(1500);
			showGameOver(true);
			do
			{
				key = readKey();
			} while (key != 13);
		}
		UnStart();
		key = 0;
		break;
	case 1: 
		WantExit = false;
		showGameName(false);
		ScreenCredit(true);
		while (key != 13) {
			key = readKey();
		}
		key = 0;
		ScreenCredit(false);
		break;
	default:
		WantExit = true;
		break;
	}
}

void BuildColorBackground() {
	ColorBackground[2] = 6;
	ColorBackground[4] = 14;
	ColorBackground[8] = 10;
	ColorBackground[16] = 11;
	ColorBackground[32] = 9;
	ColorBackground[64] = 3;
	ColorBackground[128] = 2;
	ColorBackground[256] = 8;
	ColorBackground[512] = 12;
	ColorBackground[1024] = 5;
	ColorBackground[2048] = 13;
}

void GetBest() {
	fstream HighScore;
	HighScore.open("highscore.txt", ios::in);
	HighScore >> Best;
	HighScore.close();
}

void UpBest() {
	fstream HighScore;
	HighScore.open("highscore.txt", ios::out);
	HighScore << Score;
	HighScore.close();
}

void Game() {
	resizeConsole(100, 100);
	WantExit = false;
	time_t t;
	srand((unsigned) time(&t));
	BuildColorBackground();
	do {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				broad[i][j] = 0;
				add[i][j] = 0;
			}
		}
		Solve();
		if (Score > Best) {
			UpBest();
		}
		Score = 0;
		GetBest();
		Over = false;
	} while (!WantExit);
}

int main() {
	Game();
	return 0;
}