#include "ConsoleFuncs.h"
#include <Windows.h>
#include <iostream>
using namespace std;

void ResizeConsole(int column, int row)
{
	int width = column * 8 + 33, height = row * 16 + 39;
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void FixedSizeWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void SetCenterWindow(int column, int row)
{
	int cw = column * 8 + 33;	//console width
	int ch = row * 16 + 39;		//console height

	RECT r;
	GetWindowRect(GetDesktopWindow(), &r);
	int dw = r.right;			//desktop width
	int dh = r.bottom;			//desktop height

	int x = (dw - cw) / 2;		//console position x
	int y = (dh - ch) / 2;		//console position y

	SetWindowPos(GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}
void ShowCursor(bool show)
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = show;			//state = false: ẩn con trỏ chuột
	Info.dwSize = 15;				//kích thước con trỏ chuột
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void ClearScreen()
{
	ColorXY(0, 0, 240);
	for (int j = 0; j < 25; j++)
		cout << "                                                                                ";
	GotoXY(0, 0);
}

void GotoXY(int x, int y)
{
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void ColorXY(int x, int y, int c)
{
	GotoXY(x, y);
	Color(c);
}