const string NameMenuItem[4] = { "Play","Ranking", "Credit", "Exit" };

int SelectionMenuItem;
int NumItemMenu = 4;
string NamePlayer;

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
	for (int i = 0; i < NumItemMenu; i++) {
		printxy("  ", 53, 12 + i * 3, 0, 0);
		printxy(NameMenuItem[i], 55, 12 + i * 3, 15 * kind, 0);
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
		printxy("       ", 55, 12 + 3, 0, 0);
		printxy(NameMenuItem[1], 53, 12 + 3, 11 * kind, 0);
	}
	else if (SelectionMenuItem == 2) {
		printxy("       ", 55, 12 + 6, 0, 0);
		printxy(NameMenuItem[2], 53, 12 + 6, 11 * kind, 0);
	}
	else if (SelectionMenuItem == 3) {
		printxy("       ", 55, 12 + 9, 0, 0);
		printxy(NameMenuItem[3], 53, 12 + 9, 11 * kind, 0);
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
	printxy("Loading...", 55, 21, 11 * kind, 0);
	for (int i = 0; i <= 30; i++) {
		printxy("| ", 45 + i, 23, 7 * kind, 0);
	}
	for (int i = 0; i <= 30; i++) {
		printxy("| ", 45 + i, 23, 0, 10 * kind);
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
}

void showGamePlay(bool status) {
	int kind = 0;
	if (status) kind = 1;
	for (int i = 47; i < 67; i += 6) {
		printxy("_____", i + 1, 9, 6 * kind, 0);
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

void showScore(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy("  Score  ", 64, 4, 15 * kind, 6 * kind);
	printxy("         ", 64, 5, 15 * kind, 6 * kind);
	printxy(Score, 68 - countNum(Score) / 2, 5, 15 * kind, 6 * kind);
}

void showBest(bool status) {
	int kind = 0;
	if (status) kind = 1;
	printxy("  Best   ", 64, 6, 15 * kind, 8 * kind);
	printxy("         ", 64, 7, 15 * kind, 8 * kind);
	printxy(Best, 68 - countNum(Best) / 2, 7, 15 * kind, 8 * kind);
}

void showBroad(bool status) {
	int kind = 0;
	if (status) kind = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (broad[i][j] != 0) {
				printxy("     ", 50 + j * 6 - 2, 10 + i * 3, ColorBackground[broad[i][j]] * kind, ColorBackground[broad[i][j]] * kind);
				printxy("     ", 50 + j * 6 - 2, 10 + i * 3 + 1, 0, ColorBackground[broad[i][j]] * kind);
				printxy(broad[i][j], 50 + j * 6 - countNum(broad[i][j]) / 2, 10 + i * 3 + 1, 0, ColorBackground[broad[i][j]] * kind);
			}
		}
	}
}

void showGameOver(bool status) {
	showHelpFinal(false);
	int kind = 0;
	if (status) kind = 1;
	showGamePlay(false);
	printxy("  Game Over!  ", 52, 14, 12 * kind, 8 * kind);
	if (Score > Best) {
		printxy("New best score !", 52, 16, kind * 10, 0);
		printxy(Score, 55 + countNum(Score) / 2, 18, 14 * kind, 0);
		printxy("Please Enter Your Name: ", 45, 20, 7 * kind, 0);
		cin >> NamePlayer;
		Best = Score;
		GetBest();
		for (int i = 0; i <= 4; i++) {
			if (Best > Player[i].score) {
				Player[i].score = Best;
				Player[i].name = NamePlayer;
				break;
			}
		}
		Score = 0;
		UpBest();
	}
	printxy("Press Enter to return Menu", 45, 22, 6 * kind, 0);
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

void ScreenRanking(bool status) {
	int kind = 0;
	if (status) kind = 1;
	for (int i = 0; i <= 4; i++) {
		printxy(Player[i].name, 50, 10 + i * 2, 7 * kind, 0);
		printxy(Player[i].score, 70, 10 + i * 2, 7 * kind, 0);
	}
	printxy("Enter", 25, 27, 9 * kind, 11 * kind);
	printxy("to return Menu", 31, 27, 15 * kind, 0);
}