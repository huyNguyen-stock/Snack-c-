#include "SpecialMode.h"
#include "ConsoleFuncs.h"
#include "DrawFuncs.h"
#include <iostream>
#include <thread>
#include <ctime>
#include <conio.h>
using namespace std;

#define UP_ARROW 72 
#define LEFT_ARROW 75 
#define RIGHT_ARROW 77 
#define DOWN_ARROW 80 

int nColSM = 0, nRowSM = 0;

const char headSnakeSymbol = (char)254;				//Kí tự đầu rắn
const char foodSymbol = '@';						//Kí tự thức ăn
const char snakeSymbols[32] = { '1', '9', '1', '2', '0', '5', '3', '0',
								'1', '9', '1', '2', '0', '5', '4', '3',
								'1', '9', '1', '2', '0', '5', '9', '1',
								'1', '9', '1', '2', '0', '6', '0', '2' };
const int scoreFood = 10;			//Số điểm đạt được sau khi ăn 1 food

POINT snakeHead1, snakeHead2;			//Tọa độ đầu rắn
POINT *snake1 = NULL, *snake2 = NULL;	//Mảng tọa độ thân rắn
POINT food;
int ps1, ps2;				//player symbol: Mảng MSSV cho thân rắn của 2 người chơi
int sizeSnake1, sizeSnake2;	//Độ dài rắn
int score1, score2;			//Điểm số
char moving1, moving2;		//Hướng đang di chuyển
char charLock1, charLock2;	//Không được đi hướng này
bool stateSM;				//Trạng thái rắn sống/chết
int speed;					//Tốc độ chung của 2 rắn
int originalTime = 0;		//Mốc thời gian ban đầu
int timeRemaining = 0;		//Thời gian còn lại
int totalTime = 120;		//Tổng thời gian
bool snake1_isDead;	//được bật true khi rắn 1 chết (chạm thân/tường) và chờ xem rắn 2 có chết cùng lúc không (vì trong ThreadFuncSM, rắn 2 xử lý sau rắn 1)
HANDLE hpSM;				//handle play

void MainSM(int CC, int RC)
{
	nColSM = CC; nRowSM = RC;
	ResetDataSM();
	PlayGameSM();
}
void PlayGameSM()
{
	ClearScreen();
	DrawGameBorder(nColSM, nRowSM);
	DrawHeadSnake(snakeHead1, headSnakeSymbol, 252); DrawSnakeSM(snake1, sizeSnake1, ps1);
	DrawHeadSnake(snakeHead2, headSnakeSymbol, 253); DrawSnakeSM(snake2, sizeSnake2, ps2);
	GenerateFoodSM();
	PrintScores();
	DrawFood(food, foodSymbol);
	originalTime = (int)time(NULL);

	thread play = thread(ThreadFuncSM);
	hpSM = play.native_handle();

	int key = 0;
	while (true)
	{
		if (stateSM == true)
		{
			key = toupper(_getch());
			if (stateSM == false) //Sau khi end game, key vẫn chờ để nhận phím nên ấn phím space để ra khỏi if (stateSM)
			{
				while (key != ' ') key = _getch();
				continue;
			}
			if (key != charLock1 && (key == 'W' || key == 'A' || key == 'D' || key == 'S'))
			{
				if (key == 'W') charLock1 = 'S';
				if (key == 'A') charLock1 = 'D';
				if (key == 'D') charLock1 = 'A';
				if (key == 'S') charLock1 = 'W';
				moving1 = key;
			}
			if (key != charLock2 && (key == UP_ARROW || key == LEFT_ARROW || key == RIGHT_ARROW || key == DOWN_ARROW))
			{
				if (key == UP_ARROW)	charLock2 = DOWN_ARROW;
				if (key == LEFT_ARROW)	charLock2 = RIGHT_ARROW;
				if (key == RIGHT_ARROW)	charLock2 = LEFT_ARROW;
				if (key == DOWN_ARROW)	charLock2 = UP_ARROW;
				moving2 = key;
			}
			if (key == '=' && speed > 50) speed -= 10;
			if (key == '-' && speed < 1000) speed += 10;
			if (key == 27)	//EXIT
			{
				SuspendThread(hpSM);
				char title1[] = " Do you want to exit this game? ";
				int tmp2 = DrawAskBox(nColSM, nRowSM - 2, title1, false);
				if (tmp2 == 1)		//Yes = về Home
				{
					stateSM = false;
					ResumeThread(hpSM);
					play.join();
					if (snake1 != NULL) { delete[] snake1; snake1 = NULL; }
					if (snake2 != NULL) { delete[] snake2; snake2 = NULL; }
					return;
				}
				if (tmp2 == 0)		//No = Resume
				{
					clearAskBox(nColSM, nRowSM - 2);
					DrawFood(food, foodSymbol);
					ResumeThread(hpSM);
				}
			}
		}
		else
		{
			char title2[] = "   Do you want to play again?   ";
			int tmp3 = DrawAskBox(nColSM, nRowSM - 2, title2, true);
			if (tmp3 == 1)	//Yes = Replay
			{
				ResetDataSM();
				DrawGameBorder(nColSM, nRowSM);
				GenerateFoodSM();
				PrintScores();
				DrawFood(food, foodSymbol);
				originalTime = (int)time(NULL);
				
				ResumeThread(hpSM);
			}
			if (tmp3 == 0)	//No = về Home
			{		
				stateSM = false;
				ResumeThread(hpSM);
				play.join();
				if (snake1 != NULL) { delete[] snake1; snake1 = NULL; }
				if (snake2 != NULL) { delete[] snake2; snake2 = NULL; }
				return;
			}
		}
	}
}
void ResetDataSM()
{
	stateSM = true;
	srand((int)time(NULL));
	ps1 = rand() % 4;
	do { ps2 = rand() % 4; } while (ps1 == ps2);
	sizeSnake1 = 5;		sizeSnake2 = 5;
	score1 = 0;			score2 = 0;
	moving1 = 'D';		moving2 = LEFT_ARROW;
	charLock1 = 'A';	charLock2 = RIGHT_ARROW;
	speed = 140;
	food = { 0, 0 };
	snake1_isDead = false;
	if (snake1 != NULL) { delete[] snake1; snake1 = NULL; }
	if (snake2 != NULL) { delete[] snake2; snake2 = NULL; }
	snakeHead1 = { 32, 7 };		snakeHead2 = { 47, 15 };
	snake1 = new POINT[4];		snake2 = new POINT[4];
	snake1[0] = { 28, 7 };		snake2[0] = { 51, 15 };
	snake1[1] = { 29, 7 };		snake2[1] = { 50, 15 };
	snake1[2] = { 30, 7 };		snake2[2] = { 49, 15 };
	snake1[3] = { 31, 7 };		snake2[3] = { 48, 15 };
}

void ThreadFuncSM()
{
	while (stateSM)
	{
		timeRemaining = originalTime + totalTime - (int)time(NULL);
		PrintTimer();
		if (timeRemaining == 0) ProcessDeadSM(3);	//Nếu hết thời gian
		POINT oldTail1 = snake1[0], oldTail2 = snake2[0];
		switch (moving1)
		{
		case 'W': MoveUp1SM(); break;
		case 'S': MoveDown1SM(); break;
		case 'D': MoveRight1SM(); break;
		case 'A': MoveLeft1SM(); break;
		}
		switch (moving2)
		{
		case UP_ARROW:    MoveUp2SM(); break;
		case DOWN_ARROW:  MoveDown2SM(); break;
		case RIGHT_ARROW: MoveRight2SM(); break;
		case LEFT_ARROW:  MoveLeft2SM(); break;
		}
		if (stateSM == true && snake1_isDead) ProcessDeadSM(1);
		if (stateSM == true)
		{
			ClearSnake(oldTail1);
			ClearSnake(oldTail2);
			DrawHeadSnake(snakeHead1, headSnakeSymbol, 252); DrawSnakeSM(snake1, sizeSnake1, ps1);
			DrawHeadSnake(snakeHead2, headSnakeSymbol, 253); DrawSnakeSM(snake2, sizeSnake2, ps2);
			Sleep(speed);
		}
	}
}
void EatFood1SM()
{
	sizeSnake1++;
	score1 += scoreFood;
	InsertPointSnake(snake1, sizeSnake1, snakeHead1);
	snakeHead1 = food;

	GenerateFoodSM();
	DrawFood(food, foodSymbol);
	PrintScores();
}

void EatFood2SM()
{
	sizeSnake2++;
	score2 += scoreFood;
	InsertPointSnake(snake2, sizeSnake2, snakeHead2);
	snakeHead2 = food;

	GenerateFoodSM();
	DrawFood(food, foodSymbol);
	PrintScores();
}
void InsertPointSnake(POINT*& snake, int size, POINT head)
{
	POINT* tmp = NULL;
	do {
		tmp = new POINT[size - 1];
		for (int i = 0; i < size - 1; i++)
			tmp[i] = snake[i];
		if (snake != NULL) delete[] snake;
		snake = tmp;
	} while (tmp == NULL);
	snake[size - 2] = head;
}
void ProcessDeadSM(int code)
{
	for (int i = 0; i < 20; i++)
	{
		Sleep(30);
		if (code != 2)
		{
			int j = ps1 * 8;
			for (int i = 0; i < sizeSnake1 - 1; i++)
			{
				int c = rand() % 15 + 240;
				ColorXY(snake1[i].x, snake1[i].y, c);
				cout << snakeSymbols[j++];
				if (j == (ps1 + 1) * 8)
					j = ps1 * 8;
				GotoXY(snakeHead1.x, snakeHead1.y);
				cout << headSnakeSymbol;
			}
		}
		if (code != 1)
		{
			int j = ps1 * 8;
			for (int i = 0; i < sizeSnake2 - 1; i++)
			{
				int c = rand() % 15 + 240;
				ColorXY(snake2[i].x, snake2[i].y, c);
				cout << snakeSymbols[j++];
				if (j == (ps1 + 1) * 8)
					j = ps1 * 8;
				GotoXY(snakeHead2.x, snakeHead2.y);
				cout << headSnakeSymbol;
			}
		}
	}
	DrawEndGameBox(nColSM, nRowSM - 2, code, score1, score2);
	stateSM = false;
	SuspendThread(hpSM);
}

void PrintScores()
{
	ColorXY(6, nRowSM - 2, 240);
	cout << "PLAYER 1: " << score1 << "  ";
	ColorXY(nColSM - 18, nRowSM - 2, 240);
	cout << "PLAYER 2: " << score2 << " ";
}
void PrintTimer()
{
	if (timeRemaining >= 100) GotoXY((nColSM - 3) / 2, nRowSM - 2);
	else if (timeRemaining >= 10) GotoXY((nColSM - 2) / 2, nRowSM - 2);
	else GotoXY((nColSM - 1) / 2, nRowSM - 2);

	if (timeRemaining >= 10) Color(240);
	else Color(244);

	cout << " " << timeRemaining << "  ";
}
void DrawSnakeSM(POINT*& snake, int size, int ps)
{
	Color(240);
	int j = ps * 8;
	for (int i = 0; i < size - 1; i++)
	{
		GotoXY(snake[i].x, snake[i].y);
		cout << snakeSymbols[j++];
		if (j == (ps + 1) * 8)
			j = ps * 8;
	}
}

bool isValidSM(int x, int y)
{
	if (x == snakeHead1.x && y == snakeHead1.y) return false;
	if (x == snakeHead2.x && y == snakeHead2.y) return false;
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (x == snake1[i].x && y == snake1[i].y)
			return false;
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (x == snake2[i].x && y == snake2[i].y)
			return false;
	return true;
}
void GenerateFoodSM()
{
	srand((int)time(NULL));

	int x = 0, y = 0;
	do {
		x = rand() % (nColSM - 4) + 2;	//2 -> 77
		y = rand() % (nRowSM - 4) + 1;		//1 -> 21
	} while (!isValidSM(x, y));
	food.x = x;
	food.y = y;
}

void MoveRight1SM()
{
	if (snakeHead1.x + 1 == snakeHead2.x && snakeHead1.y == snakeHead2.y)
	{
		if (moving2 == LEFT_ARROW) ProcessDeadSM(0);
		else ProcessDeadSM(1);
		return;
	}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead1.x + 1 == snake1[i].x && snakeHead1.y == snake1[i].y)
		{
			snake1_isDead = true;
			return;
		}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead1.x + 1 == snake2[i].x && snakeHead1.y == snake2[i].y)
		{
			snake1_isDead = true;
			return;
		}
	if (snakeHead1.x + 1 == nColSM - 2)
	{
		snake1_isDead = true;
		return;
	}
	if (snakeHead1.x + 1 == food.x && snakeHead1.y == food.y)
		EatFood1SM();
	if (snakeHead1.x + 1 != nColSM - 2)
	{
		for (int i = 0; i < sizeSnake1 - 2; i++)
			snake1[i] = snake1[i + 1];
		snake1[sizeSnake1 - 2] = snakeHead1;
		snakeHead1.x++;
	}
}
void MoveLeft1SM()
{
	if (snakeHead1.x - 1 == snakeHead2.x && snakeHead1.y == snakeHead2.y)
	{
		if (moving2 == RIGHT_ARROW) ProcessDeadSM(0);
		else ProcessDeadSM(1);
		return;
	}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead1.x - 1 == snake1[i].x && snakeHead1.y == snake1[i].y)
		{
			snake1_isDead = true;
			return;
		}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead1.x - 1 == snake2[i].x && snakeHead1.y == snake2[i].y)
		{
			snake1_isDead = true;
			return;
		}
	if (snakeHead1.x - 1 == 1)
	{
		snake1_isDead = true;
		return;
	}
	if (snakeHead1.x - 1 == food.x && snakeHead1.y == food.y)
		EatFood1SM();
	if (snakeHead1.x - 1 != 1)
	{
		for (int i = 0; i < sizeSnake1 - 2; i++)
			snake1[i] = snake1[i + 1];
		snake1[sizeSnake1 - 2] = snakeHead1;
		snakeHead1.x--;
	}
}
void MoveUp1SM()
{
	if (snakeHead1.x == snakeHead2.x && snakeHead1.y - 1 == snakeHead2.y)
	{
		if (moving2 == DOWN_ARROW) ProcessDeadSM(0);
		else ProcessDeadSM(1);
		return;
	}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead1.x == snake1[i].x && snakeHead1.y - 1 == snake1[i].y)
		{
			snake1_isDead = true;
			return;
		}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead1.x == snake2[i].x && snakeHead1.y - 1 == snake2[i].y)
		{
			snake1_isDead = true;
			return;
		}
	if (snakeHead1.y - 1 == 0)
	{
		snake1_isDead = true;
		return;
	}
	if (snakeHead1.x == food.x && snakeHead1.y - 1 == food.y)
		EatFood1SM();
	if (snakeHead1.y - 1 != 0)
	{
		for (int i = 0; i < sizeSnake1 - 2; i++)
			snake1[i] = snake1[i + 1];
		snake1[sizeSnake1 - 2] = snakeHead1;
		snakeHead1.y--;
	}
}
void MoveDown1SM()
{
	if (snakeHead1.x == snakeHead2.x && snakeHead1.y + 1 == snakeHead2.y)
	{
		if (moving2 == UP_ARROW) ProcessDeadSM(0);
		else ProcessDeadSM(1);
		return;
	}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead1.x == snake1[i].x && snakeHead1.y + 1 == snake1[i].y)
		{
			snake1_isDead = true;
			return;
		}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead1.x == snake2[i].x && snakeHead1.y + 1 == snake2[i].y)
		{
			snake1_isDead = true;
			return;
		}
	if (snakeHead1.y + 1 == nRowSM - 3)
	{
		snake1_isDead = true;
		return;
	}
	if (snakeHead1.x == food.x && snakeHead1.y + 1 == food.y)
		EatFood1SM();
	if (snakeHead1.y + 1 != nRowSM - 3)
	{
		for (int i = 0; i < sizeSnake1 - 2; i++)
			snake1[i] = snake1[i + 1];
		snake1[sizeSnake1 - 2] = snakeHead1;
		snakeHead1.y++;
	}
}

void MoveRight2SM()
{
	if (snakeHead2.x + 1 == snakeHead1.x && snakeHead2.y == snakeHead1.y)
	{
		if (moving1 == 'A') ProcessDeadSM(0);
		else ProcessDeadSM(2);
		return;
	}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead2.x + 1 == snake2[i].x && snakeHead2.y == snake2[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead2.x + 1 == snake1[i].x && snakeHead2.y == snake1[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	if (snakeHead2.x + 1 == nColSM - 2)
	{
		if (snake1_isDead)
		{
			snake1_isDead = false;
			ProcessDeadSM(0);
		}
		else ProcessDeadSM(2);
		return;
	}
	if (snakeHead2.x + 1 == food.x && snakeHead2.y == food.y)
		EatFood2SM();
	if (snakeHead2.x + 1 != nColSM - 2)
	{
		for (int i = 0; i < sizeSnake2 - 2; i++)
			snake2[i] = snake2[i + 1];
		snake2[sizeSnake2 - 2] = snakeHead2;
		snakeHead2.x++;
	}
}
void MoveLeft2SM()
{
	if (snakeHead2.x - 1 == snakeHead1.x && snakeHead2.y == snakeHead1.y)
	{
		if (moving1 == 'D') ProcessDeadSM(0);
		else ProcessDeadSM(2);
		return;
	}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead2.x - 1 == snake2[i].x && snakeHead2.y == snake2[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead2.x - 1 == snake1[i].x && snakeHead2.y == snake1[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	if (snakeHead2.x - 1 == 1)
	{
		if (snake1_isDead)
		{
			snake1_isDead = false;
			ProcessDeadSM(0);
		}
		else ProcessDeadSM(2);
		return;
	}
	if (snakeHead2.x - 1 == food.x && snakeHead2.y == food.y)
		EatFood2SM();
	if (snakeHead2.x - 1 != 1)
	{
		for (int i = 0; i < sizeSnake2 - 2; i++)
			snake2[i] = snake2[i + 1];
		snake2[sizeSnake2 - 2] = snakeHead2;
		snakeHead2.x--;
	}
}
void MoveUp2SM()
{
	if (snakeHead2.x == snakeHead1.x && snakeHead2.y - 1 == snakeHead1.y)
	{
		if (moving1 == 'S') ProcessDeadSM(0);
		ProcessDeadSM(2);
		return;
	}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead2.x == snake2[i].x && snakeHead2.y - 1 == snake2[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead2.x == snake1[i].x && snakeHead2.y - 1 == snake1[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	if (snakeHead2.y - 1 == 0)
	{
		if (snake1_isDead)
		{
			snake1_isDead = false;
			ProcessDeadSM(0);
		}
		else ProcessDeadSM(2);
		return;
	}
	if (snakeHead2.x == food.x && snakeHead2.y - 1 == food.y)
		EatFood2SM();
	if (snakeHead2.y - 1 != 0)
	{
		for (int i = 0; i < sizeSnake2 - 2; i++)
			snake2[i] = snake2[i + 1];
		snake2[sizeSnake2 - 2] = snakeHead2;
		snakeHead2.y--;
	}
}
void MoveDown2SM()
{
	if (snakeHead2.x == snakeHead1.x && snakeHead2.y + 1 == snakeHead1.y)
	{
		if (moving1 == 'W') ProcessDeadSM(0);
		ProcessDeadSM(2);
		return;
	}
	for (int i = 0; i < sizeSnake2 - 1; i++)
		if (snakeHead2.x == snake2[i].x && snakeHead2.y + 1 == snake2[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	for (int i = 0; i < sizeSnake1 - 1; i++)
		if (snakeHead2.x == snake1[i].x && snakeHead2.y + 1 == snake1[i].y)
		{
			if (snake1_isDead)
			{
				snake1_isDead = false;
				ProcessDeadSM(0);
			}
			else ProcessDeadSM(2);
			return;
		}
	if (snakeHead2.y + 1 == nRowSM - 3)
	{
		if (snake1_isDead)
		{
			snake1_isDead = false;
			ProcessDeadSM(0);
		}
		else ProcessDeadSM(2);
		return;
	}
	if (snakeHead2.x == food.x && snakeHead2.y + 1 == food.y)
		EatFood2SM();
	if (snakeHead2.y + 1 != nRowSM - 3)
	{
		for (int i = 0; i < sizeSnake2 - 2; i++)
			snake2[i] = snake2[i + 1];
		snake2[sizeSnake2 - 2] = snakeHead2;
		snakeHead2.y++;
	}
}