#include "ConsoleFuncs.h"
#include "DrawFuncs.h"
#include "FileFuncs.h"
#include "Gameplay.h"
#include "SpecialMode.h"
#include <conio.h>
using namespace std;

#define COLUMN_CONSOLE 80
#define ROW_CONSOLE 25

//----------------------------------

int main()
{
	FixedSizeWindow();
	ResizeConsole(COLUMN_CONSOLE, ROW_CONSOLE);
	SetCenterWindow(COLUMN_CONSOLE, ROW_CONSOLE);
	ShowCursor(false);
	
	DrawWelcomeScreen(COLUMN_CONSOLE, ROW_CONSOLE);

	while (true)
	{
		ClearScreen();
		PLAYER* arrPlayer = NULL;
		int nPlayer = readFile(arrPlayer);
		int select = DrawHomeScreen(COLUMN_CONSOLE, ROW_CONSOLE, nPlayer > 0);
		if (arrPlayer != NULL) delete[] arrPlayer;

		switch (select)
		{
			case 0: MainGP(COLUMN_CONSOLE, ROW_CONSOLE, true); break;	//NEW GAME
			case 1: MainSM(COLUMN_CONSOLE, ROW_CONSOLE); break;			//SPECIAL MODE
			case 2:														//SCORE
			{
				TOP_PLAYER* arrTP = NULL;
				int nTP = readFile(arrTP);
				DrawScoreScreen(COLUMN_CONSOLE, ROW_CONSOLE - 2, arrTP, nTP);
				if (arrTP != NULL) delete[] arrTP;
				while (_getch() != 27) {}
				break;
			}
			case 3: return 0;											//QUIT
			case 4: MainGP(COLUMN_CONSOLE, ROW_CONSOLE, false);	break;	//LOADGAME
			default: break;
		}
	}

	return 0;
}