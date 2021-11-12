#include "Logo.h"
#include "ConsoleFuncs.h"
#include <iostream>
#include <Windows.h>
#define LOGO_SNAKE_WIDTH 36
#define LOGO_SNAKE_HEIGHT 9
using namespace std;

void DrawLogoTeam(int maxColumn, int maxRow)
{
	char c1 = (char)201, c2 = (char)200, c3 = (char)186, c4 = (char)187, c5 = (char)188, c6 = (char)205;
	int width = 53, height = 16;
	int x = (maxColumn - width) / 2, y = (maxRow - height) / 2, z = (maxColumn - 20) / 2;
	int t = 15;

	Color(8);
	GotoXY(5, 30); cout << " HCMUS - 19CTT3 - Nhom 13";
	GotoXY(5, 31); cout << "Nguyen Tan Huy   - 19120530";
	GotoXY(5, 32); cout << "Hoang Manh Khiem - 19120543";
	GotoXY(5, 33); cout << "Dang Phuong Nam  - 19120591";
	GotoXY(5, 34); cout << "Ho Huu Ngoc      - 19120602";
	GotoXY(0, 0);

	Color(240);

	GotoXY(x, y + 0); cout << " __" << endl;
	GotoXY(x, y + 1); cout << "| " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " ____" << endl;
	GotoXY(x, y + 1); cout << "|  " << endl;
	GotoXY(x, y + 2); cout << "|" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " ______" << endl;
	GotoXY(x, y + 1); cout << "|  _ " << endl;
	GotoXY(x, y + 2); cout << "|_/" << endl;
	GotoXY(x, y + 3); cout << " " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " ________" << endl;
	GotoXY(x, y + 1); cout << "|  _   " << endl;
	GotoXY(x, y + 2); cout << "|_/ |" << endl;
	GotoXY(x, y + 3); cout << "   " << endl;
	GotoXY(x, y + 4); cout << " " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _ " << endl;
	GotoXY(x, y + 2); cout << "|_/ | |" << endl;
	GotoXY(x, y + 3); cout << "    |" << endl;
	GotoXY(x, y + 4); cout << "   " << endl;
	GotoXY(x, y + 5); cout << " " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  |" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\" << endl;
	GotoXY(x, y + 3); cout << "    | |" << endl;
	GotoXY(x, y + 4); cout << "   _|" << endl;
	GotoXY(x, y + 5); cout << "  |" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   __" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|" << endl;
	GotoXY(x, y + 3); cout << "    | |  " << endl;
	GotoXY(x, y + 4); cout << "   _| |" << endl;
	GotoXY(x, y + 5); cout << "  |__" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   ____" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_ " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|  " << endl;
	GotoXY(x, y + 3); cout << "    | |    " << endl;
	GotoXY(x, y + 4); cout << "   _| |_ " << endl;
	GotoXY(x, y + 5); cout << "  |____" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   ______" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   |" << endl;
	GotoXY(x, y + 3); cout << "    | |      " << endl;
	GotoXY(x, y + 4); cout << "   _| |_   " << endl;
	GotoXY(x, y + 5); cout << "  |_____|" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   ________" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   __" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |" << endl;
	GotoXY(x, y + 3); cout << "    | |       |" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     " << endl;
	GotoXY(x, y + 5); cout << "  |_____|  " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___ " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_ " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _|" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________   " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\" << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |__" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________     " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |  " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|" << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |__" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |____" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________       " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |    " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|  " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _ " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |______" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        _" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|    " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _   " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |________" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      / " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     /" << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________|" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __   " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /" << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __     " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\  " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /_" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |__" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __       " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\    " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\ " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /  " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        _" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\   " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____| " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ___" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\     " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_  " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\    " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |__" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____   " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       | " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_  " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    _" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| " << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ___" << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  / " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/" << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |_" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  /   " << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/  " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| |_" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |___" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  /   _|" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/   |" << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\  /|" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| |_\\/" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |_____" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  /   _|" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/   |  " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\  /| |" << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| |_\\/_|" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |_____||" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  /   _|" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/   |  " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\  /| |  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| |_\\/_| |" << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |_____||__" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  /   _|" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/   |  " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\  /| |  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| |_\\/_| |_ " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |_____||____" << endl;
	Sleep(t);

	GotoXY(x, y + 0); cout << " _________   _________        __        ____    ____ " << endl;
	GotoXY(x, y + 1); cout << "|  _   _  | |_   ___  |      /  \\      |_   \\  /   _|" << endl;
	GotoXY(x, y + 2); cout << "|_/ | | \\_|   | |_  \\_|     / /\\ \\       |   \\/   |  " << endl;
	GotoXY(x, y + 3); cout << "    | |       |  _|  _     / /__\\ \\      | |\\  /| |  " << endl;
	GotoXY(x, y + 4); cout << "   _| |_     _| |___/ |  _/ /    \\ \\_   _| |_\\/_| |_ " << endl;
	GotoXY(x, y + 5); cout << "  |_____|   |_________| |____|  |____| |_____||_____|" << endl;
	Sleep(t);
	
	//GotoXY(z, y +  8); cout << "    ___   ______    ";
	//GotoXY(z, y +  9); cout << "   |   | |___   |   ";
	//GotoXY(z, y + 10); cout << "    |  |  ___|  |   ";
	//GotoXY(z, y + 11); cout << "    |  | |___   |   ";
	//GotoXY(z, y + 12); cout << "    |  |  ___|  |   ";
	//GotoXY(z, y + 13); cout << "    |__| |______|   ";

	Color(128);
	GotoXY(z + 4, y + 9); cout << "   "; GotoXY(z + 10, y + 9); cout <<  "      ";
	GotoXY(z + 5, y + 10); cout << "  "; GotoXY(z + 14, y + 10); cout << "  ";
	GotoXY(z + 5, y + 11); cout << "  "; GotoXY(z + 10, y + 11); cout << "      ";
	GotoXY(z + 5, y + 12); cout << "  "; GotoXY(z + 14, y + 12); cout << "  ";
	GotoXY(z + 5, y + 13); cout << "  "; GotoXY(z + 10, y + 13); cout << "      ";
	Sleep(t);

	Color(240);
	GotoXY(z, y + 7); cout << c1; GotoXY(z + 20, y + 7); cout << c4;
	GotoXY(z, y + 15); cout << c2; GotoXY(z + 20, y + 15); cout << c5;
	Sleep(t + 40);

	GotoXY(z + 1, y + 7); cout << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 4, y + 7); cout << c6 << c6 << c6 << c6;
	GotoXY(z + 1, y + 15); cout << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 4, y + 15); cout << c6 << c6 << c6 << c6;
	GotoXY(z, y + 8); cout << c3; GotoXY(z + 20, y + 8); cout << c3;
	GotoXY(z, y + 14); cout << c3; GotoXY(z + 20, y + 14); cout << c3;
	Sleep(t + 40);

	GotoXY(z + 5, y + 7); cout << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 8, y + 7); cout << c6 << c6 << c6 << c6;
	GotoXY(z + 5, y + 15); cout << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 8, y + 15); cout << c6 << c6 << c6 << c6;
	GotoXY(z, y + 9); cout << c3; GotoXY(z + 20, y + 9); cout << c3;
	GotoXY(z, y + 13); cout << c3; GotoXY(z + 20, y + 13); cout << c3;
	Sleep(t + 40);

	GotoXY(z + 9, y + 7); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 13, y + 7); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z + 9, y + 15); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 13, y + 15); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z, y + 10); cout << c3; GotoXY(z + 20, y + 10); cout << c3;
	GotoXY(z, y + 12); cout << c3; GotoXY(z + 20, y + 12); cout << c3;
	Sleep(t + 40);

	GotoXY(z + 14, y + 7); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 18, y + 7); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z + 14, y + 15); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z + 20 - 18, y + 15); cout << c6 << c6 << c6 << c6 << c6;
	GotoXY(z, y + 11); cout << c3; GotoXY(z + 20, y + 11); cout << c3;
	Sleep(t + 40);
}
int getLSw() { return LOGO_SNAKE_WIDTH; }
int getLSh() { return LOGO_SNAKE_HEIGHT; }

void DrawLogoSnake(int x, int y)
{
	Color(240);
	GotoXY(x, y); cout << "                       _            ";		y++;
	GotoXY(x, y); cout << "                      | |           ";		y++;
	GotoXY(x, y); cout << " __    ___ _ __   __ _| | _____     ";		y++;
	GotoXY(x, y); cout << "{OO}  / __| '_ \\ / _` | |/ / _ \\    ";		y++;
	GotoXY(x, y); cout << "\\__/  \\__ \\ | | | (_| |   <  __/    ";	y++;
	GotoXY(x, y); cout << " |^|  |___/_| |_|\\__,_|_|\\_\\___|  /\\";	y++;
	GotoXY(x, y); cout << " | |_____________________________/ /";		y++;
	GotoXY(x, y); cout << " \\________________________________/ ";
}