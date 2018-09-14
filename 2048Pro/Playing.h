bool Over;

void CheckOver() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (broad[i][j] == 0)
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
			CheckCanMove = false;
			Calculation(0);
			if (Checking) {
				OutRand();
				showBroad(true);
			}
			key = 0;
		}
		if (key == -77) {
			showBroad(false);
			CheckCanMove = false;
			Calculation(1);
			if (Checking)
			{
				OutRand();
				showBroad(true);
			}
			key = 0;
		}
		if (key == -80) {
			showBroad(false);
			CheckCanMove = false;
			Calculation(2);
			if (Checking) {
				OutRand();
				showBroad(true);
			}
			key = 0;
		}
		if (key == -75) {
			showBroad(false);
			CheckCanMove = false;
			Calculation(3);
			if (Checking) {
				OutRand();
				showBroad(true);
			}
			key = 0;
		}
		CheckOver();
		//showScore(false); showBest(false);
	} while (!Over);
}
