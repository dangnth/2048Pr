#include <ctime>
#include <fstream>
#include <string.h>

using namespace std;

struct User { int score; string name; };

User Player[5];
int broad[4][4]; int add[4][4];
const int OutRandom[3] = { 2,2,4 };
short ColorBackground[10000];
int Best;

int countNum(int x) {
	int countN = 0;
	do {
		countN++;
		x /= 10;
	} while (x != 0);
	return countN;
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

void OutRand() {
	time_t t;
	srand((unsigned)time(&t));
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

void GetBest() {
	fstream HighScore;
	HighScore.open("highscore.txt", ios::in);
	for (int i = 0; i <= 4; i++) {
		HighScore >> Player[i].name >> Player[i].score;
	}
	HighScore >> Best;
	HighScore.close();
}

void UpBest() {
	fstream HighScore;
	HighScore.open("highscore.txt", ios::out);
	for (int i = 0; i <= 4; i++) {
		HighScore << Player[i].name << " " << Player[i].score << endl;
	}
	HighScore << Best;
	HighScore.close();
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
