#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "Build.h"
#include "Tools.h"
#include "Player.h"
#include "Screen.h"
#include "Playing.h"

using namespace std;

bool WantExit;
int row, colum;

void Start() {
	showHelp(false);
	showHelpFinal(true);
	showGamePlay(true);
	showItem(true);
	showScore(true);
	showBest(true);
	IntRand();
}

void UnStart() {
	showGamePlay(false);
	showItem(false);
	showScore(false);
	showBest(false);
	showGameOver(false);
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
			showGameOver(false);
		}
		UnStart();
		key = 0;
		break;
	case 1: 
		WantExit = false;
		showGameName(false);
		ScreenRanking(true);
		while (key != 13) {
			key = readKey();
		}
		key = 0;
		break;
	case 2:
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

void Game() {
	row = 100; colum = 100;
	resizeConsole(colum,row);
	WantExit = false;
	BuildColorBackground();
	GetBest();
	do {
		system("cls");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				broad[i][j] = 0;
				add[i][j] = 0;
			}
		}
		Solve();
		Over = false;
	} while (!WantExit);
}

int main() {
	Game();
	return 0;
}