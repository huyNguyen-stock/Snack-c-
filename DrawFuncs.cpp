#include "DrawFuncs.h"
#include "ConsoleFuncs.h"
#include "Logo.h"
#include "FileFuncs.h"
#include <iostream>
#include <conio.h>
using namespace std;

void DrawWelcomeScreen(int maxColumn, int maxRow)
{
	ClearScreen();
	DrawLogoTeam(maxColumn, maxRow);
	Sleep(500);
	ColorXY((maxColumn - 28) / 2, maxRow - 2, 240); cout << "Press 'Space' to continue...";
	while (_getch() != ' ') { }
}

int DrawHomeScreen(int maxColumn, int maxRow, bool haveLoadGame)
{
	const char* option1[4] = { "    NEW GAME    ", "  SPECIAL MODE  ", "      SCORE     ", "      QUIT      " };
	const char* option2[5] = { "    NEW GAME    ", "  SPECIAL MODE  ", "    LOADGAME    ", "      SCORE     ", "      QUIT      " };
	char c1 = (char)175, c2 = (char)174;			//c1 = » , c2 = «

	Color(240);
	DrawLogoSnake((maxColumn - getLSw()) / 2, 2);		//Vẽ logo snake ở giữa hàng 1
	int x = (maxColumn - 16) / 2, y = getLSh() + 2;
	int choice = 0, optionNumber = 4;					//Hiện tại choice = 0 (tạm thời là NEW GAME)
	if (haveLoadGame) optionNumber = 5;					//Nếu có LoadGame thì số lượng lựa chọn là 4, ngược lại là 3
	char key;

	ColorXY(x, y + 2, 252); cout << option1[0];			//In dòng NEW GAME màu đỏ
	GotoXY(x, y + 2); cout << c1;						//In kí tự » vào bên trái NEW GAME
	GotoXY(x + 15, y + 2); cout << c2;					//In kí tự « vào bên phải NEW GAME
	if (!haveLoadGame)
	{
		ColorXY(x, y + 4, 240); cout << option1[1];		//In dòng 1vs1 GAME MODE màu trắng
		ColorXY(x, y + 6, 240); cout << option1[2];		//In dòng SCORE màu trắng
		ColorXY(x, y + 8, 240); cout << option1[3];		//In dòng QUIT màu trắng
	}
	else
	{
		ColorXY(x, y + 4, 240); cout << option2[1];		//In dòng 1vs1 GAME MODE màu trắng
		ColorXY(x, y + 6, 240); cout << option2[2];		//In dòng LOADGAME màu trắng
		ColorXY(x, y + 8, 240); cout << option2[3];		//In dòng SCORE màu trắng
		ColorXY(x, y + 10, 240); cout << option2[4];	//In dòng QUIT màu trắng
	}
	
	while (true)
	{
		key = toupper(_getch());						//Detect phím
		if (key == 'W' or key == 'S')
		{
			ColorXY(x, y + 2 + 2 * choice, 240);			//Reset màu và xóa » « của lựa chọn cũ
			if (!haveLoadGame) cout << option1[choice];	//
			else cout << option2[choice];				//
		}
		if (key == 'W') choice = (choice + optionNumber - 1) % optionNumber;	//Lên
		if (key == 'S') choice = (choice + 1) % optionNumber;					//Xuống	
		if (key == 'W' or key == 'S')
		{
			ColorXY(x, y + 2 + 2 * choice, 252);			//In dòng lựa chọn tiếp theo màu đỏ
			if (!haveLoadGame) cout << option1[choice];	//
			else cout << option2[choice];				//
			GotoXY(x, y + 2 + 2 * choice); cout << c1;				//In kí tự »
			GotoXY(x + 15, y + 2 + 2 * choice); cout << c2;			//In kí tự «
		}
		if (key == 13)									//Ấn Enter
		{
			ClearScreen();
			switch (choice)
			{
				//Điều chỉnh lại giá trị trả về: 0 là NEW GAME, 1 là 1vs1, 2 là SCORE, 3 là QUIT, 4 là LOADGAME
				case 0: return 0;
				case 1: return 1;
				case 2: if (!haveLoadGame) return 2; else return 4;
				case 3: if (!haveLoadGame) return 3; else return 2;
				case 4: return 3;
			}
		}
	}
	return -1;


	//»   NEW GAME   «
	//
	//» SPECIAL MODE «
	//
	//»   LOADGAME   «
	//
	//»     SCORE    «
	//
	//»     QUIT     «
}

void DrawGameBorder(int maxColumn, int maxRow)
{
	ClearScreen();
	Color(249);
	char c1 = (char)219, c2 = (char)220, c3 = (char)223;		//c1 = █ , c2 = ▄ , c3 = ▀
	int i;
	int j = maxRow - 4;
	int k = maxColumn - 2;
	for (i = 1; i < maxRow - 3; i++) 
	{
		Sleep(4);
		GotoXY(1, j--);
		cout << c1;
		GotoXY(maxColumn - 2, i);
		cout << c1;
	}
	for (i = 1; i < maxColumn - 1; i++) 
	{
		Sleep(4);
		GotoXY(i, 0);
		cout << c2;
		GotoXY(k--, maxRow - 3);
		cout << c3;
	}
}

void drawInfoPlayers(int maxColumn, int maxRow, PLAYER*& arr, int choice)
{
	int width = 46, height = 6 + 2 * MAX_PLAYERS_NUMBER;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;
	int k = 0;
	for (int i = 0; i < MAX_PLAYERS_NUMBER; i++)
	{
		if (arr[i].used == false)
		{
			ColorXY(x + 5, y + 6 + k, 248);
			cout << "Empty slot!";
		}
		else
		{
			if (i == choice) Color(252);
			else Color(240);
			GotoXY(x + 5, y + 6 + k); cout << arr[i].namePlayer;
			GotoXY(x + 30, y + 6 + k); cout << arr[i].score;
			GotoXY(x + 39, y + 6 + k); cout << arr[i].level;
		}
		k += 2;
	}
}
void drawChoiceBorder(int x, int y)
{
	char c1 = (char)218, c2 = (char)196, c3 = (char)191,	//218 = ┌  ,  196 = ─  ,  191 = ┐
		 c4 = (char)192, c5 = (char)179, c6 = (char)217;	//192 = └  ,  179 = │  ,  217 = ┘
	int width = 40, height = 3;

	Color(252);
	GotoXY(x, y + 0); cout << c1; for (int i = 0; i < width - 2; i++) cout << c2; cout << c3;	// ┌──────┐
	GotoXY(x, y + 1); cout << c5; GotoXY(x + width - 1, y + 1); cout << c5;						// │      │
	GotoXY(x, y + 2); cout << c4; for (int i = 0; i < width - 2; i++) cout << c2; cout << c6;	// └──────┘
}
void clearChoiceBorder(int x, int y)
{
	int width = 40, height = 3;

	Color(240);
	GotoXY(x, y + 0); for (int i = 0; i < width; i++) cout << ' ';
	GotoXY(x, y + 1); cout << ' '; GotoXY(x + width - 1, y + 1); cout << ' ';
	GotoXY(x, y + 2); for (int i = 0; i < width; i++) cout << ' ';
}

int DrawLoadGameScreen(int maxColumn, int maxRow, PLAYER*& arrPlayer)
{
	ClearScreen();

	char c1 = (char)219, c2 = (char)220, c3 = (char)223;	//c1 = █ , c2 = ▄ , c3 = ▀
	char d1 = (char)201, d2 = (char)205, d3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 d4 = (char)200, d5 = (char)186, d6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝
	int width = 46, height = 6 + 2 * MAX_PLAYERS_NUMBER;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;		// 17 - 4

	Color(240);
	GotoXY(x, y);
	for (int i = 0; i < width; i++) cout << c2;
	for (int j = y + 1; j < y + height; j++)
	{
		GotoXY(x, j); cout << c1;
		GotoXY(x + width - 1, j); cout << c1;
	}
	GotoXY(x, y + height);
	for (int i = 0; i < width; i++) cout << c3;

	GotoXY(x - 6, y + 3);
	cout << c2 << c2 << c2 << c2 << c2 << c2;
	GotoXY(x + width, y + 3);
	cout << c2 << c2 << c2 << c2 << c2 << c2;
	GotoXY(x - 6, y + height - 4);
	cout << c3 << c3 << c3 << c3 << c3 << c3;
	GotoXY(x + width, y + height - 4);
	cout << c3 << c3 << c3 << c3 << c3 << c3;
	for (int i = y + 4; i <= y + height - 5; i++)
	{
		GotoXY(x - 6, i); cout << c1;
		GotoXY(x + width + 5, i); cout << c1;
	}
	GotoXY((maxColumn - 14) / 2, y + 1);
	cout << d1 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d3;
	GotoXY((maxColumn - 14) / 2, y + 3);
	cout << d4 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d2 << d6;

	GotoXY((maxColumn - 8) / 2, y + 2); cout << "LOADGAME";
	GotoXY(x + 10, y + 4); cout << "NAME";
	GotoXY(x + 28, y + 4); cout << "SCORE";
	GotoXY(x + 37, y + 4); cout << "LEVEL";

	int choice = 0;
	int key = 0;
	
	while (arrPlayer[choice].used == false) choice++;
	
	while (true)
	{
		drawInfoPlayers(maxColumn, maxRow, arrPlayer, choice);
		drawChoiceBorder(x + 3, y + 5 + 2 * choice);
		key = toupper(_getch());
		clearChoiceBorder(x + 3, y + 5 + 2 * choice);
		if (key == 'S')
			do
			{
				if (choice < MAX_PLAYERS_NUMBER - 1)
					choice++;
				else choice = 0;
			} while (arrPlayer[choice].used == false);
		if (key == 'W')
			do
			{
				if (choice > 0)
					choice--;
				else choice = MAX_PLAYERS_NUMBER - 1;
			} while (arrPlayer[choice].used == false);
		if (key == 13) return choice;
		if (key == 27) return -1;
	}
	return -1;

	//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
	//█               ╔══╩══════╩══╗               █
	//█               ║  LOADGAME  ║               █
	//█               ╚════════════╝               █
	//█         NAME              SCORE    LEVEL   █
	//█  ┌──────────────────────────────────────┐  █
	//█  │ Dang Phuong Nam          12       2  │  █
	//█  └──────────────────────────────────────┘  █
	//█    Hoang Anh Tu             9        1     █
	//█                                            █
	//█    Empty slot!                             █
	//█                                            █
	//█    Empty slot!                             █
	//█                                            █
	//█    Phan Le Xuan Manh        20       3     █
	//█                                            █
	//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
}

void DrawScoreScreen(int maxColumn, int maxRow, TOP_PLAYER*& arrTP, int number)
{
	char c1 = (char)219, c2 = (char)220, c3 = (char)223, c4 = (char)240;		//c1 = █ , c2 = ▄ , c3 = ▀ , c4 = ≡
	int width = 46, height = 17;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;		//x = 17, y = 3

	GotoXY(x, y);	
	for (int i = 0; i < width; i++) cout << c2;
	for (int j = y + 1; j < y + height; j++)
	{
		GotoXY(x, j); cout << c1;
		GotoXY(x + width - 1, j); cout << c1;
	}
	GotoXY(x, y + height);
	for (int i = 0; i < width; i++) cout << c3;

	GotoXY((maxColumn - 2) / 2, y + height);
	cout << c1 << c1;
	GotoXY((maxColumn - 2) / 2, y + height + 1);
	cout << c1 << c1;
	GotoXY((maxColumn - 8) / 2, y + height + 2);
	cout << c3 << c3 << c3 << c3 << c3 << c3 << c3 << c3;
	
	GotoXY((maxColumn - 16) / 2, y + 2); 
	cout << c4 << " BEST PLAYERS " << c4;
	GotoXY(x + 1, y + 4);
	cout << "     NO.          NAME            SCORE     ";
	for (int i = 0; i < number; i++)
	{
		GotoXY(x + 7, y + 6 + 2 * i);
		cout << i + 1;
		GotoXY(x + 21 - (strlen(arrTP[i].namePlayer) / 2), y + 6 + 2 * i);
		cout << arrTP[i].namePlayer;
		if (arrTP[i].score < 100)
			GotoXY(x + 37, y + 6 + 2 * i);
		else GotoXY(x + 36, y + 6 + 2 * i);
		cout << arrTP[i].score;
	}

	//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
	//█                                            █
	//█                BEST PLAYERS                █
	//█                                            █
	//█     NO.          NAME            SCORE     █
	//█                                            █
	//█      1    Dang Phuong Nam         100      █
	//█                                            █
	//█      2    Hoang Anh Tu             60      █
	//█                                            █
	//█      3    Phan Le Xuan Manh        20      █
	//█                                            █
	//█                                            █
	//█                                            █
	//█                                            █
	//█                                            █
	//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

}
void DrawWinGame(int maxColumn, int maxRow) 
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 50, height = 7;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 1; i < (width - 12) / 2; i++) cout << c2;
	cout << "< WIN GAME >";
	for (int i = 1; i < (width - 12) / 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	for (int i = 0; i < 26; i++) 
	{
		Sleep(50);
		int c = rand() % 15 + 240;
		ColorXY(x + 4, y + 3, c);
		cout << "CONGRATULATIONS, YOU HAVE WON THE GAME !!!";
	}
	Sleep(500);
	ColorXY((maxColumn - 28) / 2, y + 5, 240); cout << "Press 'Space' to continue...";

	//		╔══════════════════< WIN GAME >══════════════════╗
	//		║                                                ║
	//		║                                                ║
	//		║   CONGRATULATIONS, YOU HAVE WON THE GAME !!!   ║
	//		║                                                ║
	//		║          Press 'Space' to continue...          ║
	//		╚════════════════════════════════════════════════╝
}

void DrawBorderSwitchLevel(int maxColumn, int maxRow) {
	int i;
	int j = ((maxColumn - 2) / 2) + 1;
	int k = maxColumn - 2;
	Color(249);
	for (i = (maxColumn - 2) / 2; i >= 1; i--) {
		Sleep(8);
		GotoXY(j++, 0); cout << (char)220;
		GotoXY(i, 0); cout << (char)220;
	}
	for (i = 1; i < maxRow - 3; i++) {
		Sleep(8);
		GotoXY(maxColumn - 2, i); cout << (char)219;
		GotoXY(1, i); cout << (char)219;
	}
	for (i = 1; i < ((maxColumn - 2) / 2) + 1; i++) {
		Sleep(8);
		GotoXY(k--, maxRow - 3); cout << (char)223;
		GotoXY(i, maxRow - 3); cout << (char)223;
	}
}
void ClearBorderSwitchLevel(int maxColumn, int maxRow) {
	int i;
	int j = ((maxColumn - 2) / 2) + 1;
	int k = maxColumn - 2;
	for (i = (maxColumn - 2) / 2; i >= 1; i--) {
		Sleep(5);
		GotoXY(j++, maxRow - 3);
		cout << ' ';
		GotoXY(i, maxRow - 3);
		cout << ' ';
	}
	for (i = maxRow - 4; i >= 1; i--) {
		Sleep(5);
		GotoXY(maxColumn - 2, i);
		cout << ' ';
		GotoXY(1, i);
		cout << ' ';
	}
	for (i = 1; i < ((maxColumn - 2) / 2) + 1; i++) {
		Sleep(5);
		GotoXY(k--, 0);
		cout << ' ';
		GotoXY(i, 0);
		cout << ' ';
	}
}

int DrawPauseBox(int maxColumn, int maxRow)
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝
		 
	int width = 36, height = 6;
	int x = (maxColumn - width) / 2, y = (maxRow - 1 - height) / 2;
	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 1; i < (width - 14) / 2; i++) cout << c2;
	cout << "< PAUSE GAME >";
	for (int i = 1; i < (width - 14) / 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	int choice = 0;
	int key = 0;
	while (true)
	{
		if (choice == 0)
		{
			Color(252);
			drawResumeButton(x + 2, y + 2);
			Color(240);
			drawReplayButton(x + 13, y + 2);
			drawHomeButton(x + 24, y + 2);
		}
		if (choice == 1)
		{
			Color(240);
			drawResumeButton(x + 2, y + 2);
			Color(252);
			drawReplayButton(x + 13, y + 2);
			Color(240);
			drawHomeButton(x + 24, y + 2);
		}
		if (choice == 2)
		{
			Color(240);
			drawResumeButton(x + 2, y + 2);
			drawReplayButton(x + 13, y + 2);
			Color(252);
			drawHomeButton(x + 24, y + 2);
		}
		key = toupper(_getch());
		if (key == 13 || key == 27 || key == 'P') { clearPauseBox(maxColumn, maxRow); return choice; }
		if (key == 'A' || key == 'W') choice--;
		if (key == 'D' || key == 'S' || key == '\t') choice++;
		if (choice == -1) choice = 2;
		if (choice == 3) choice = 0;
	}
	return -1;

	//		╔══════════< PAUSE GAME >══════════╗
	//		║                                  ║
	//		║ ┌────────┐ ┌────────┐ ┌────────┐ ║
	//		║ │ Resume │ │ Replay │ │  Home  │ ║
	//		║ └────────┘ └────────┘ └────────┘ ║
	//		╚══════════════════════════════════╝
}
void drawResumeButton(int x, int y)
{
	char c1 = (char)218, c2 = (char)196, c3 = (char)191,	//218 = ┌  ,  196 = ─  ,  191 = ┐
		 c4 = (char)192, c5 = (char)179, c6 = (char)217;	//192 = └  ,  179 = │  ,  217 = ┘
	GotoXY(x, y + 0); cout << c1 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c3;
	GotoXY(x, y + 1); cout << c5 << " Resume " << c5;
	GotoXY(x, y + 2); cout << c4 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c6;
}
void drawReplayButton(int x, int y)
{
	char c1 = (char)218, c2 = (char)196, c3 = (char)191,	//218 = ┌  ,  196 = ─  ,  191 = ┐
		 c4 = (char)192, c5 = (char)179, c6 = (char)217;	//192 = └  ,  179 = │  ,  217 = ┘
	GotoXY(x, y + 0); cout << c1 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c3;
	GotoXY(x, y + 1); cout << c5 << " Replay " << c5;
	GotoXY(x, y + 2); cout << c4 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c6;
}
void drawHomeButton(int x, int y)
{
	char c1 = (char)218, c2 = (char)196, c3 = (char)191,	//218 = ┌  ,  196 = ─  ,  191 = ┐
		 c4 = (char)192, c5 = (char)179, c6 = (char)217;	//192 = └  ,  179 = │  ,  217 = ┘
	GotoXY(x, y + 0); cout << c1 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c3;
	GotoXY(x, y + 1); cout << c5 << "  Home  " << c5;
	GotoXY(x, y + 2); cout << c4 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c6;
}
void clearPauseBox(int maxColumn, int maxRow)
{
	int width = 36, height = 6;
	int x = (maxColumn - width) / 2, y = (maxRow - 1 - height) / 2;
	for (int j = y; j < y + height; j++)
	{
		GotoXY(x, j);
		for (int i = 0; i < width; i++)
			cout << " ";
	}
}

int DrawAskBox(int maxColumn, int maxRow, char title[], bool firstYes)
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 36, height = 7;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;
	ColorXY(x, y, 248);
	cout << c1;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i); 
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;
	ColorXY(x + 2, y + 2, 240); cout << title;

	int choice = 1;
	if (!firstYes) choice = 0;
	int key = 0;
	while (true)
	{
		if (choice == 1)
		{
			Color(252);
			drawYesButton(x + 6, y + 3);
			Color(240);
			drawNoButton(x + 22, y + 3);
		}
		if (choice == 0)
		{
			Color(240);
			drawYesButton(x + 6, y + 3);
			Color(252);
			drawNoButton(x + 22, y + 3);
		}
		key = toupper(_getch());
		if (key == 13) return choice;
		if (key == 27) return -1;
		if (key == 'A' || key == 'W' || key == 'D' || key == 'S' || key == '\t') choice = 1 - choice;
	}
	return -1;
	//		╔══════════════════════════════════╗
	//		║  Do you want to save this game?  ║
	//		║                                  ║
	//		║     ┌───────┐       ┌──────┐     ║
	//		║     │  Yes  │       │  No  │     ║
	//		║     └───────┘       └──────┘     ║
	//		╚══════════════════════════════════╝

	//		╔══════════════════════════════════╗
	//		║    Do you want to play again?    ║
	//		║                                  ║
	//		║     ┌───────┐       ┌──────┐     ║
	//		║     │  Yes  │       │  No  │     ║
	//		║     └───────┘       └──────┘     ║
	//		╚══════════════════════════════════╝
}
void drawYesButton(int x, int y)
{
	char c1 = (char)218, c2 = (char)196, c3 = (char)191,	//218 = ┌  ,  196 = ─  ,  191 = ┐
		 c4 = (char)192, c5 = (char)179, c6 = (char)217;	//192 = └  ,  179 = │  ,  217 = ┘
	GotoXY(x, y + 0); cout << c1 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c3;
	GotoXY(x, y + 1); cout << c5 << "  Yes  " << c5;
	GotoXY(x, y + 2); cout << c4 << c2 << c2 << c2 << c2 << c2 << c2 << c2 << c6;
}
void drawNoButton(int x, int y)
{
	char c1 = (char)218, c2 = (char)196, c3 = (char)191,	//218 = ┌  ,  196 = ─  ,  191 = ┐
		 c4 = (char)192, c5 = (char)179, c6 = (char)217;	//192 = └  ,  179 = │  ,  217 = ┘
	GotoXY(x, y + 0); cout << c1 << c2 << c2 << c2 << c2 << c2 << c2 << c3;
	GotoXY(x, y + 1); cout << c5 << "  No  " << c5;
	GotoXY(x, y + 2); cout << c4 << c2 << c2 << c2 << c2 << c2 << c2 << c6;
}
void clearAskBox(int maxColumn, int maxRow)
{
	int width = 36, height = 7;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;
	for (int j = y; j < y + height; j++)
	{
		GotoXY(x, j);
		for (int i = 0; i < width; i++)
			cout << " ";
	}
}

int DrawSaveBox(int maxColumn, int maxRow, PLAYER*& arrPlayer, char getNamePlayer[])
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
	 	 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 44, height = 6 + MAX_PLAYERS_NUMBER;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

Hide_Error_Label:
	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 0; i < 17; i++) cout << c2;
	cout << "< SAVE >";
	for (int i = 0; i < 17; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	printPlayersList(arrPlayer, x, y);

	ColorXY(x + 2, y + 2, 240); cout << "Please enter your name: ";
	ColorXY(x + 6, y + 3, 240); cout << "> ";

	ShowCursor(true);
	char in[255];
	cin.getline(in, 255);
	if (nameHandling(in, getNamePlayer) == false)
	{
		DrawNameValidNoti(maxColumn, maxRow);
		goto Hide_Error_Label;
	}
	ShowCursor(false);

	ColorXY(x + 2, y + 2, 240); cout << "Select a save slot for your game:";
	ColorXY(x + 6, y + 3, 240); cout << "                                     " << c5;

	int choice = 0;
	int key = 0;
	while (true)
	{
		Color(252);
		if (arrPlayer[choice].used)
		{
			GotoXY(x +  4, y + 5 + choice); cout << arrPlayer[choice].namePlayer;
			if (arrPlayer[choice].score < 100)
				GotoXY(x + 28, y + 5 + choice);
			else GotoXY(x + 27, y + 5 + choice);
			cout << arrPlayer[choice].score;
			GotoXY(x + 37, y + 5 + choice); cout << arrPlayer[choice].level;
		}
		else
		{
			GotoXY(x + 4, y + 5 + choice); cout << "Empty slot!";
		}
		key = toupper(_getch());
		if (key == 'W' || key == 'S')
		{
			if (arrPlayer[choice].used)
			{
				Color(240);
				GotoXY(x +  4, y + 5 + choice); cout << arrPlayer[choice].namePlayer;
				if (arrPlayer[choice].score < 100)
					GotoXY(x + 28, y + 5 + choice);
				else GotoXY(x + 27, y + 5 + choice);
				cout << arrPlayer[choice].score;
				GotoXY(x + 37, y + 5 + choice); cout << arrPlayer[choice].level;
			}
			else
			{
				ColorXY(x + 4, y + 5 + choice, 248);
				cout << "Empty slot!";
			}
		}
		if (key == 'W') choice--;
		if (key == 'S' || key == '\t') choice++;
		if (choice == -1) choice = MAX_PLAYERS_NUMBER - 1;
		if (choice == MAX_PLAYERS_NUMBER) choice = 0;
		if (key == 13)
		{
			if (arrPlayer[choice].used)
			{
				char title[] = "You want to overwrite this slot?";
				int tmp = DrawAskBox(maxColumn, maxRow, title, false);
				if (tmp == 1) return choice;
				else
				{
					clearAskBox(maxColumn, maxRow);
					ColorXY(x + 2, y + 2, 240); cout << "Select a save slot for your game:";
					printPlayersList(arrPlayer, x, y);
				}
			}
			else return choice;
		}
	}
	return -1;

	//		╔═════════════════< SAVE >═════════════════╗
	//		║                                          ║
	//		║  Please enter your name:                 ║
	//		║     > _                                  ║
	//		║       NAME              SCORE    LEVEL   ║
	//		║   AnhTu                  250       2     ║
	//		║   Cong Tang Ton Nu Ta Ha  60       2     ║
	//		║   Empty slot!                            ║
	//		║   Empty slot!                            ║
	//		║   ADuc                    10       1     ║
	//		╚══════════════════════════════════════════╝

	//		╔═════════════════< SAVE >═════════════════╗
	//		║                                          ║
	//		║  Select a save slot for your game:       ║
	//		║                                          ║
	//		║       NAME              SCORE    LEVEL   ║
	//		║   AnhTu                  250       2     ║
	//		║   PNam                    60       2     ║
	//		║   Empty slot!                            ║
	//		║   Empty slot!                            ║
	//		║   ADuc                    10       1     ║
	//		╚══════════════════════════════════════════╝
}
void printPlayersList(PLAYER*& arrPlayer, int x, int y)
{
	ColorXY(x + 1, y + 4, 240); cout << "       NAME              SCORE    LEVEL   ";
	for (int i = 0; i < MAX_PLAYERS_NUMBER; i++)
		if (arrPlayer[i].used)
		{
			Color(240);
			GotoXY(x + 4, y + 5 + i); cout << arrPlayer[i].namePlayer;
			if (arrPlayer[i].score < 100)
				GotoXY(x + 28, y + 5 + i);
			else GotoXY(x + 27, y + 5 + i);
			cout << arrPlayer[i].score;
			GotoXY(x + 37, y + 5 + i); cout << arrPlayer[i].level;
		}
		else
		{
			ColorXY(x + 4, y + 5 + i, 248);
			cout << "Empty slot!";
		}
}

void DrawSaveDoneNoti(int maxColumn, int maxRow)
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		c4 = (char)200, c5 = (char)186, c6 = (char)188;		//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 28, height = 5;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	ColorXY(x + 5, y + 2, 240); cout << "Saved successfully!";
	Sleep(500);

	//		╔══════════════════════════╗
	//		║                          ║
	//		║    Saved successfully!   ║
	//		║                          ║
	//		╚══════════════════════════╝
}

void DrawGameOverBox(int maxColumn, int maxRow, int score)
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 34, height = 7;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 1; i < (width - 12) / 2; i++) cout << c2;
	cout << "< GAMEOVER >";
	for (int i = 1; i < (width - 12) / 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	GotoXY((maxColumn - 22) / 2, y + 2); cout << "Your final score is " << score;
	Sleep(500);
	GotoXY((maxColumn - 28) / 2, y + 4); cout << "Press 'Space' to continue...";

	//		╔══════════< GAMEOVER >══════════╗
	//		║                                ║
	//	    ║     Your final score is 33     ║
	//		║                                ║
	//		║  Press 'Space' to continue...  ║
	//		║                                ║
	//		╚════════════════════════════════╝
}

void DrawEnterNameScoreBox(int maxColumn, int maxRow, char getNamePlayer[])
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 38, height = 9;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	Hide_Error_Label:
	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	GotoXY(x + 5, y + 2); cout << "Your result will be exported";
	GotoXY(x + 9, y + 3); cout << "to the BEST PLAYERS!";
	GotoXY(x + 2, y + 5); cout << "Please enter your name:";
	GotoXY(x + 2, y + 6); cout << "  > ";
	ShowCursor(true);
	char in[255];
	cin.getline(in, 255);
	if (nameHandling(in, getNamePlayer) == false)
	{
		DrawNameValidNoti(maxColumn, maxRow);
		goto Hide_Error_Label;
	}
	ShowCursor(false);

	//		╔════════════════════════════════════╗
	//		║                                    ║
	//		║    Your result will be exported    ║
	//	    ║        to the BEST PLAYERS!        ║
	//		║                                    ║
	//		║ Please enter your name:            ║
	//		║   > asdcs_                         ║
	//		║                                    ║
	//		╚════════════════════════════════════╝
}
void DrawScoreDoneNoti(int maxColumn, int maxRow)
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 38, height = 7;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	GotoXY(x + 4, y + 2); cout << "Your result have been exported";
	GotoXY(x + 9, y + 3); cout << "to the BEST PLAYERS!";
	Sleep(500);
	GotoXY(x + 5, y + 5); cout << "Press 'Space' to continue...";
	
	while (_getch() != ' ') { }

	//		╔════════════════════════════════════╗
	//		║                                    ║
	//		║   Your result have been exported   ║
	//	    ║        to the BEST PLAYERS!        ║
	//		║                                    ║
	//		║    Press 'Space' to continue...    ║
	//		╚════════════════════════════════════╝
}

void DrawNameValidNoti(int maxColumn, int maxRow)
{
	ShowCursor(false);

	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		c4 = (char)200, c5 = (char)186, c6 = (char)188;		//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 30, height = 6;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 1; i < (width - 10) / 2; i++) cout << c2;
	cout << "< ERROR >";
	for (int i = 1; i < (width - 10) / 2 + 1; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	GotoXY(x + 9, y + 2); cout << "Invalid name!";
	GotoXY(x + 2, y + 3); cout << "Please enter another name.";

	Sleep(1000);

	ShowCursor(true);
	//		╔═════════< ERROR >══════════╗
	//		║                            ║
	//		║        Invalid name!       ║
	//	    ║ Please enter another name. ║
	//	    ║                            ║
	//		╚════════════════════════════╝

}
bool isValidChar(char c)
{
	if ('A' <= toupper(c) && toupper(c) <= 'Z') return true;
	if ('0' <= c && c <= '9') return true;
	if (c == ' ') return true;
	if (c == '_') return true;
	if (c == '-') return true;
	if (c == '(') return true;
	if (c == ')') return true;
	return false;
}

//Hàm xử lý tên: kiểm tra + chuẩn hóa
bool nameHandling(char input[], char output[])	//Trả về: 0 (tên không hợp lệ), 1 (tên hợp lệ)
{
	int b = 0;		//begin
	while (input[b] == ' ') b++;
	if (input[b] == '\0') return false;		//Tên toàn khoảng trắng
	if (toupper(input[b]) < 'A' || 'Z' < toupper(input[b])) return false;
	int e = b + 1;		//end
	while (input[e] != '\0')
	{
		if (isValidChar(input[e]) == false)
			return false;
		e++;
	}
	while (input[e - 1] == ' ') e--;
	int i = b, j = 0;
	while (i < e)
	{
		if (input[i] != ' ')
		{
			if (j == MAX_NAME_LENGTH - 1) break;
			output[j] = input[i];
			j++;
			if (input[i + 1] == ' ' && i + 1 < e)
			{
				output[j] = ' ';
				j++;
			}
		}
		i++;
	}
	output[j] = '\0';
	if (i < e)	//Tên quá dài
	{
		output[j - 2] = '*';
		output[j - 1] = '*';
	}
	return true;
}

void DrawHeadSnake(POINT head, char ch, int cl)
{
	if (head.x == 0 && head.y == 0) return;
	ColorXY(head.x, head.y, cl);
	cout << ch;
}
void ClearSnake(POINT tail) 
{
	GotoXY(tail.x, tail.y);
	cout << ' ';
}
void DrawFood(POINT FOOD, char ch) 
{
	ColorXY(FOOD.x, FOOD.y, 242);
	cout << ch;
}

//----------------------------------

void DrawEndGameBox(int maxColumn, int maxRow, int code, int score1, int score2)
{
	char c1 = (char)201, c2 = (char)205, c3 = (char)187,	//201 = ╔  ,  205 = ═  ,  187 = ╗
		 c4 = (char)200, c5 = (char)186, c6 = (char)188;	//200 = ╚  ,  186 = ║  ,  188 = ╝

	int width = 34, height = 7;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2;

	ColorXY(x, y, 240);
	cout << c1;
	for (int i = 1; i < (width - 12) / 2; i++) cout << c2;
	if (code == 3) cout << "< TIME OUT >";
	else cout << "< END GAME >";
	for (int i = 1; i < (width - 12) / 2; i++) cout << c2;
	cout << c3;
	for (int i = 1; i < height - 1; i++)
	{
		GotoXY(x, y + i);
		cout << c5;
		for (int j = 0; j < width - 2; j++) cout << " ";
		cout << c5;
	}
	GotoXY(x, y + height - 1);
	cout << c4;
	for (int i = 0; i < width - 2; i++) cout << c2;
	cout << c6;

	GotoXY(x + 9, y + 3);
	if (code == 0 || (code == 3 && score1 == score2)) cout << "TWO PLAYERS DREW";
	if (code == 1 || (code == 3 && score1  < score2)) cout << "  PLAYER 2 WON  ";
	if (code == 2 || (code == 3 && score1  > score2)) cout << "  PLAYER 1 WON  ";
	
	Sleep(500);
	GotoXY((maxColumn - 28) / 2, y + 5); cout << "Press 'Space' to continue...";

	//		╔══════════< END GAME >══════════╗
	//		║                                ║
	//		║                                ║
	//	    ║          PLAYER 1 WON          ║
	//		║                                ║
	//		║  Press 'Space' to continue...  ║
	//		╚════════════════════════════════╝

	//		╔══════════< END GAME >══════════╗
	//		║                                ║
	//		║                                ║
	//	    ║        TWO PLAYERS DREW        ║
	//		║                                ║
	//		║  Press 'Space' to continue...  ║
	//		╚════════════════════════════════╝
}