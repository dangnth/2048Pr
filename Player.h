#include <iostream>
#include <stdlib.h>

using namespace std;

int Score = 0;
bool Checking, CheckCanMove;
//int broad[4][4]; int add[4][4];

void Calculation(int status) {
	int x, y;
	switch (status)
	{
	case 0:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (broad[i][j] != 0) {
					y = j; x = i;
					while (x - 1 >= 0) {
						if (broad[x - 1][y] == 0) {
							swap(broad[x - 1][y], broad[x][y]);
							--x; Checking = true; CheckCanMove = true;
						}
						else if (broad[x - 1][y] == broad[x][y] && add[x - 1][y] == 0) {
							add[x - 1][y] = 1;
							broad[x][y] = 0; Checking = true; CheckCanMove = true;
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
			for (int j = 3; j >= 0; j--) {
				if (broad[i][j] != 0) {
					x = i; y = j;
					while (y + 1 <= 3) {
						if (broad[x][y + 1] == 0) {
							swap(broad[x][y + 1], broad[x][y]);
							++y; Checking = true; CheckCanMove = true;
						}
						else if (broad[x][y + 1] == broad[x][y] && add[x][y + 1] == 0) {
							add[x][y + 1] = 1;
							broad[x][y] = 0; Checking = true; CheckCanMove = true;
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
							++x; Checking = true; CheckCanMove = true;
						}
						else if (broad[x + 1][y] == broad[x][y] && add[x + 1][y] == 0) {
							add[x + 1][y] = 1;
							broad[x][y] = 0; Checking = true; CheckCanMove = true;
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
							--y; Checking = true; CheckCanMove = true;
						}
						else if (broad[x][y - 1] == broad[x][y] && add[x][y - 1] == 0) {
							add[x][y - 1] = 1;
							broad[x][y] = 0; Checking = true; CheckCanMove = true;
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