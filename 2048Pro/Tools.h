using namespace std;

static HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
static HANDLE inpHandle = GetStdHandle(STD_INPUT_HANDLE);

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
