#include "Gameplay.h"
#include "ConsoleFuncs.h"
#include "DrawFuncs.h"
#include "FileFuncs.h"
#include <iostream>
#include <thread>
#include <ctime>
#include <conio.h>
using namespace std;

#define MAX_FOOD_LEVEL 6

int nCol = 0, nRow = 0;

const char headSnakeSymbol = (char)254;				//Kí tự đầu rắn
const char foodSymbol = '@';						//Kí tự thức ăn
const char gateSymbol = (char)219;					//Kí tự cổng
const int cSpeed[6] = { 110, 85, 70, 60, 50, 40 };	//Hằng số tốc độ của rắn mỗi level
const char snakeSymbols[32] = { '1', '9', '1', '2', '0', '5', '3', '0',
								'1', '9', '1', '2', '0', '5', '4', '3',
								'1', '9', '1', '2', '0', '5', '9', '1',
								'1', '9', '1', '2', '0', '6', '0', '2' };
const int scoreFood = 10;			//Số điểm đạt được sau khi ăn 1 food
const int scoreGateIn = 20;			//Số điểm đạt được sau khi qua cổng IN 

POINT snakeHEAD;					//Tọa độ đầu rắn
POINT* SNAKE = NULL;				//Mảng tọa độ thân rắn
POINT FOOD;							//Tọa độ thức ăn
POINT* GATE_IN = NULL;				//Mảng 9 tọa độ	của cổng IN
POINT* GATE_OUT = NULL;				//Mảng 9 tọa độ	của cổng OUT

char currName[MAX_NAME_LENGTH];		//Tên người chơi hiện tại (từ LOADGAME)
int currSlotPos = -1;				//Vị trí slot người chơi hiện tại (từ LOADGAME)
bool hadPlayer = false;				//Đã có người chơi chưa (từ LOADGAME)
HANDLE hp;							//handle play

int SIZE_SNAKE;		//Độ dài rắn
int INDEX;			//Độ dài rắn khi vào/ra cổng
int countFOOD;		//Đếm số FOOD đã ăn của mỗi màn
int SCORE;			//Điểm số
int LEVEL;			//Cấp độ
char MOVING;		//Hướng đang di chuyển
char CHAR_LOCK;		//Không được đi hướng này
bool STATE;			//Trạng thái rắn sống/chết
int SPEED;			//Tốc độ rắn
int COUNT;
bool GateFlag;		//true nếu được cho phép vẽ cổng
bool MoveFlag;
bool CountFlag_IN;
bool CountFlag_OUT;
bool showingFood = false;		//true nếu đang có FOOD trên màn hình
bool showingGateIn = false;		//true nếu đang có GATE_IN trên màn hình
bool showingGateOut = false;	//true nếu đang có GATE_OUT trên màn hình

void MainGP(int CC, int RC, bool newGame)
{
	nCol = CC; nRow = RC;

	if (newGame) ResetData();
	else if (LoadData() == false) return;

	PlayGame();
}
void PlayGame() {
	ClearScreen();
	DrawGameBorder(nCol, nRow);
	if (showingFood) DrawFood(FOOD, foodSymbol);
	if (showingGateIn) DrawGate(GATE_IN);
	if (showingGateOut) DrawGate(GATE_OUT);
	DrawSnake();
	DrawHeadSnake(snakeHEAD, headSnakeSymbol, 252);
	PrintScoreLevel();

	thread play = thread(ThreadFunc);
	hp = play.native_handle();

	int key = 0;
	while (true)
	{
		if (STATE == 1)
		{
			key = toupper(_getch());
			if (STATE == 0) //Sau khi chết/win game, key vẫn chờ để nhận phím nên ấn phím space để ra khỏi if (STATE == 1)
			{
				while (key != ' ') key = toupper(_getch());
				continue;
			}
			if (key != CHAR_LOCK && (key == 'W' || key == 'A' || key == 'D' || key == 'S'))
			{
				if (key == 'W') CHAR_LOCK = 'S';
				if (key == 'A') CHAR_LOCK = 'D';
				if (key == 'D') CHAR_LOCK = 'A';
				if (key == 'S') CHAR_LOCK = 'W';
				MOVING = key;
			}
			if ((key == 'P' || key == 27))	//PAUSE GAME
			{
				SuspendThread(hp);
			Pause_Label:
				int tmp = DrawPauseBox(nCol, nRow);
				if (tmp == 0) //Resume
				{
					ResumeThread(hp);
					if (showingFood) DrawFood(FOOD, foodSymbol);
					if (showingGateIn) DrawGate(GATE_IN);
					if (showingGateOut) DrawGate(GATE_IN);
					PrintScoreLevel();
				}
				if (tmp == 1) //Replay
				{
					ResetData();
					DrawGameBorder(nCol, nRow);
					GenerateFood();
					PrintScoreLevel();
					DrawFood(FOOD, foodSymbol);
					showingFood = true;

					ResumeThread(hp);
				}
				if (tmp == 2) //Home và save
				{
					PLAYER* arrPlayer = NULL;
					int nPlayer = readFile(arrPlayer);
					char title1[] = " Do you want to save this game? ";
					int tmp2 = DrawAskBox(nCol, nRow - 2, title1, true);
					if (tmp2 == -1) goto Pause_Label;	//Tắt SaveAskBox
					if (tmp2 == 1)	//Yes = Mở màn hình chọn slot để save
						ExportData(arrPlayer);
					if (arrPlayer != NULL) delete[] arrPlayer;
					STATE = 0;
					ResumeThread(hp);
					play.join();
					if (SNAKE != NULL) { delete[] SNAKE; SNAKE = NULL; }
					if (GATE_IN != NULL) { delete[] GATE_IN; GATE_IN = NULL; }
					if (GATE_OUT != NULL) { delete[] GATE_OUT; GATE_OUT = NULL; }
					return;
				}
			}
		}
		else
		{	//Xử lý sau khi chết
			if (enoughScore(SCORE))		//Đủ điểm đạt top, 0 điểm = false
			{
				TOP_PLAYER newTP;
				newTP.score = SCORE;
				if (hadPlayer)
				{
					DrawScoreDoneNoti(nCol, nRow - 2);
					stringCopy(currName, newTP.namePlayer);
				}
				else DrawEnterNameScoreBox(nCol, nRow - 2, newTP.namePlayer);
				addData(newTP);
			}
			if (hadPlayer)
			{
				hadPlayer = false;
				deleteData(currSlotPos);
			}
			char title2[] = "   Do you want to play again?   ";
			int tmp4 = DrawAskBox(nCol, nRow - 2, title2, true);
			if (tmp4 == 1)	//Yes = Replay
			{
				ResetData();
				DrawGameBorder(nCol, nRow);
				GenerateFood();
				PrintScoreLevel();
				DrawFood(FOOD, foodSymbol);
				showingFood = true;

				ResumeThread(hp);
			}
			if (tmp4 == 0)	//No = về Home
			{
				STATE = 0;
				ResumeThread(hp);
				play.join();
				if (SNAKE != NULL) { delete[] SNAKE; SNAKE = NULL; }
				if (GATE_IN != NULL) { delete[] GATE_IN; GATE_IN = NULL; }
				if (GATE_OUT != NULL) { delete[] GATE_OUT; GATE_OUT = NULL; }
				return;
			}
		}
	}
}
void ResetData() {
	STATE = 1;
	SIZE_SNAKE = 5;
	countFOOD = 0;
	SCORE = 0;
	LEVEL = 1;
	COUNT = 0;
	MOVING = 'D';
	CHAR_LOCK = 'A';
	SPEED = cSpeed[LEVEL - 1];
	GateFlag = 0;
	CountFlag_IN = 0;
	CountFlag_OUT = 0;
	MoveFlag = 1;
	if (SNAKE != NULL) { delete[] SNAKE; SNAKE = NULL; }
	if (GATE_IN != NULL) { delete[] GATE_IN; GATE_IN = NULL; }
	if (GATE_OUT != NULL) { delete[] GATE_OUT; GATE_OUT = NULL; }
	snakeHEAD = { 35, 15 };
	SNAKE = new POINT[4];
	SNAKE[0] = { 31, 15 };
	SNAKE[1] = { 32, 15 };
	SNAKE[2] = { 33, 15 };
	SNAKE[3] = { 34, 15 };
	GenerateFood();
	showingFood = true;
	showingGateIn = false;
	showingGateOut = false;
}
bool LoadData()
{
	PLAYER* arrPlayer = NULL;
	int nPlayer = readFile(arrPlayer);
	int tmp = DrawLoadGameScreen(nCol, nRow, arrPlayer);

	PLAYER player = arrPlayer[tmp];
	if (arrPlayer != NULL) delete[] arrPlayer;
	if (tmp == -1) return false;

	hadPlayer = true;
	stringCopy(player.namePlayer, currName);
	currSlotPos = tmp;

	ImportData(player);

	return true;
}
void ImportData(PLAYER currPlayer)
{
	STATE = 1;
	SIZE_SNAKE = currPlayer.length;
	snakeHEAD = currPlayer.headSnake;
	if (SNAKE != NULL) delete[] SNAKE;
	SNAKE = new POINT[SIZE_SNAKE - 1];
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
		SNAKE[i] = currPlayer.snake[i];
	SCORE = currPlayer.score;
	LEVEL = currPlayer.level;
	SPEED = cSpeed[LEVEL - 1];
	countFOOD = currPlayer.countFood;
	MOVING = currPlayer.direction;
	if (MOVING == 'W') CHAR_LOCK = 'S';
	if (MOVING == 'S') CHAR_LOCK = 'W';
	if (MOVING == 'A') CHAR_LOCK = 'D';
	if (MOVING == 'D') CHAR_LOCK = 'A';
	showingFood = currPlayer.haveFood;
	showingGateIn = currPlayer.haveGateIn;
	showingGateOut = currPlayer.haveGateOut;
	if (currPlayer.haveFood) FOOD = currPlayer.food;
	if (currPlayer.haveGateIn || currPlayer.haveGateOut)
	{
		if (GATE_IN == NULL) GATE_IN = new POINT[9];
		setGateIn(currPlayer.gateIn.x, currPlayer.gateIn.y);
		if (GATE_OUT == NULL) GATE_OUT = new POINT[9];
		setGateOut(currPlayer.gateOut.x, currPlayer.gateOut.y);
	}
	INDEX = currPlayer.INDEX;
	GateFlag = currPlayer.GateFlag;
	MoveFlag = currPlayer.MoveFlag;
	CountFlag_IN = currPlayer.CountFlag_IN;
	CountFlag_OUT = currPlayer.CountFlag_OUT;
}
void ExportData(PLAYER*& arrPlayer)
{
	PLAYER savePlayer;
	savePlayer.used = true;
	savePlayer.headSnake = snakeHEAD;
	savePlayer.snake = SNAKE;
	savePlayer.length = SIZE_SNAKE;
	savePlayer.score = SCORE;
	savePlayer.level = LEVEL;
	savePlayer.countFood = countFOOD;
	savePlayer.direction = MOVING;
	savePlayer.INDEX = INDEX;
	savePlayer.GateFlag = GateFlag;
	savePlayer.MoveFlag = MoveFlag;
	savePlayer.CountFlag_IN = CountFlag_IN;
	savePlayer.CountFlag_OUT = CountFlag_OUT;
	savePlayer.haveFood = showingFood;
	savePlayer.haveGateIn = showingGateIn;
	savePlayer.haveGateOut = showingGateOut;
	if (showingFood) savePlayer.food = FOOD;
	if (showingGateIn || showingGateOut)
	{
		savePlayer.gateIn = GATE_IN[2];
		savePlayer.gateOut = GATE_OUT[2];
	}
	if (hadPlayer)		//Nếu đã có sẵn tên người chơi (từ LOADGAME)
	{
		stringCopy(currName, savePlayer.namePlayer);
		addData(arrPlayer, currSlotPos, savePlayer);
		hadPlayer = false;
	}
	else
	{
		int tmp3 = DrawSaveBox(nCol, nRow - 2, arrPlayer, savePlayer.namePlayer);
		addData(arrPlayer, tmp3, savePlayer);
	}
	DrawSaveDoneNoti(nCol, nRow - 2);
}

void ThreadFunc() {
	while (STATE == 1) {
		CountFunc();
		DrawHeadSnake(snakeHEAD, headSnakeSymbol, 252);
		ClearSnake(SNAKE[0]);
		switch (MOVING)
		{
		case 'W': MoveUp(); break;
		case 'S': MoveDown(); break;
		case 'D': MoveRight(); break;
		case 'A': MoveLeft(); break;
		}
		if (STATE == 1) {
			if (CountFlag_IN != 1)
				DrawHeadSnake(snakeHEAD, headSnakeSymbol, 252);
			DrawSnake();
		}
		FixSnakeSpeed();
	}
}
void EatFood() {
	SIZE_SNAKE++;
	INDEX = SIZE_SNAKE;
	countFOOD++;
	SCORE += scoreFood;
	InsertPointSnake();
	//DrawFood(FOOD, ' ');
	showingFood = false;
	snakeHEAD = FOOD;
	if (countFOOD < MAX_FOOD_LEVEL) {
		GenerateFood();
		DrawFood(FOOD, foodSymbol);
		showingFood = true;
	}
	else {
		GateFlag = 1;
	}
	PrintScoreLevel();
}
void InsertPointSnake()
{
	POINT* tmp = NULL;
	do {
		tmp = new POINT[SIZE_SNAKE - 1];
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
			tmp[i] = SNAKE[i];
		if (SNAKE != NULL) delete[] SNAKE;
		SNAKE = tmp;
	} while (tmp == NULL);
	SNAKE[SIZE_SNAKE - 2] = snakeHEAD;
}
void ProcessDead() {
	for (int i = 0; i < 20; i++) {
		Sleep(30);
		int j = 0;
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			int c = rand() % 15 + 240;
			ColorXY(SNAKE[i].x, SNAKE[i].y, c);
			cout << snakeSymbols[j++];
			if (j == 32) {
				j = 0;
			}
			GotoXY(snakeHEAD.x, snakeHEAD.y);
			cout << headSnakeSymbol;
		}
	}
	DrawGameOverBox(nCol, nRow - 2, SCORE);
	STATE = 0;
	SuspendThread(hp);
}

void SwitchGameLevel() {
	if (snakeHEAD.x == GATE_IN[2].x && snakeHEAD.y + 1 == GATE_IN[2].y) {
		CountFlag_IN = 1;
		MoveFlag = 0;
		MOVING = 'S';
		CHAR_LOCK = 'W';
		for (int i = 0; i < SIZE_SNAKE - 2; i++)
			SNAKE[i] = SNAKE[i + 1];
		SNAKE[SIZE_SNAKE - 2] = snakeHEAD;
		ClearSnake(SNAKE[0]);
		snakeHEAD.x = 0;
		snakeHEAD.y = 0;
	}
}
void NewGameLevel() {
	if (CountFlag_IN == 1 && COUNT == SIZE_SNAKE - 1) {
		ClearGate(GATE_IN);
		showingGateIn = false;
		SCORE += scoreGateIn;
		LEVEL++;
		if (LEVEL == 7)
		{
			STATE = 0;
			DrawWinGame(nCol, nRow - 2);
			return;
		}
		ClearBorderSwitchLevel(nCol, nRow);
		Sleep(500);
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			SNAKE[i].x = GATE_OUT[2].x;
			SNAKE[i].y = GATE_OUT[2].y + 1;
		}
		snakeHEAD.x = GATE_OUT[2].x;
		snakeHEAD.y = GATE_OUT[2].y + 1;
		DrawBorderSwitchLevel(nCol, nRow);
		PrintScoreLevel();
		DrawGate(GATE_OUT);
		showingGateOut = true;
		CountFlag_IN = 0;
		COUNT = 0;
		CountFlag_OUT = 1;
		SPEED = cSpeed[LEVEL - 1];
		MoveFlag = 1;
	}
	if (CountFlag_OUT == 1 && COUNT == SIZE_SNAKE + 1) {
		ClearGate(GATE_OUT);
		showingGateOut = false;
		COUNT = 0;
		CountFlag_OUT = 0;
		countFOOD = 0;
		GenerateFood();
		DrawFood(FOOD, foodSymbol);
		showingFood = true;
	}
}
void CountFunc()
{
	if (CountFlag_IN == 1) {
		MOVING = 'S';
		CHAR_LOCK = 'W';
		if (COUNT != SIZE_SNAKE - 1) {
			COUNT++;
		}
	}
	if (CountFlag_OUT == 1) {
		if (COUNT != SIZE_SNAKE + 1) {
			COUNT++;
		}
	}
}

void PrintScoreLevel()
{
	ColorXY(6, nRow - 2, 240);
	cout << "SCORE: " << SCORE << "  ";
	ColorXY(nCol - 14, nRow - 2, 240);
	cout << "LEVEL: " << LEVEL << " ";
}
void DrawSnake() {
	Color(240);
	int j = 0;
	if (MoveFlag == 1)
	{
		j = 0;
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			GotoXY(SNAKE[i].x, SNAKE[i].y);
			cout << snakeSymbols[j++];
			if (j == 32)
				j = 0;
		}
	}
	else
	{
		j = 0;
		INDEX--;
		for (int i = 0; i < INDEX - 1; i++)
		{
			GotoXY(SNAKE[i].x, SNAKE[i].y);
			cout << snakeSymbols[j++];
			if (j == 32)
				j = 0;
		}
	}
}
void DrawGate(POINT*& GATE)
{
	Color(248);
	for (int i = 0; i < 9; i++)
	{
		GotoXY(GATE[i].x, GATE[i].y);
		cout << gateSymbol;
	}
}
void ClearGate(POINT*& GATE)
{
	for (int i = 0; i < 9; i++)
	{
		GotoXY(GATE[i].x, GATE[i].y);
		cout << ' ';
	}
	for (int i = 0; i < 9; i++)
		GATE[i] = { 0, 0 };
}

bool isValid(int x, int y) {
	if (x == snakeHEAD.x && y == snakeHEAD.y) {
		return false;
	}
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
		if (x == SNAKE[i].x && y == SNAKE[i].y) {
			return false;
		}
	return true;
}
void GenerateFood() {
	srand((int)time(NULL));

	int x = 0, y = 0;
	do {
		x = rand() % (nCol - 4) + 2;	//2 -> 77
		y = rand() % (nRow - 4) + 1;		//1 -> 21
	} while (!isValid(x, y));
	FOOD.x = x;
	FOOD.y = y;
}
void GenerateGate() {
	srand((int)time(NULL));

	int x = 0, y = 0;
	int i;
	GATE_IN = new POINT[9];
	GATE_OUT = new POINT[9];
	do {
		x = rand() % (nCol - 10) + 5;	//5 -> 74
		y = rand() % (nRow - 13) + 10;	//10 -> 21
		setGateIn(x, y);
		for (i = 0; i < 9; i++)
			if (!isValid(GATE_IN[i].x, GATE_IN[i].y))
				break;
	} while (i < 9);

	do {
		x = rand() % (nCol - 10) + 5;	//5 -> 74
		y = rand() % 11 + 2;				//2 -> 12
		setGateOut(x, y);
		for (int i = 0; i < 9; i++)
			if (!isValid(GATE_OUT[i].x, GATE_OUT[i].y))
				break;
	} while (i < 9);
}

void MoveRight() {
	for (int i = 0; i < SIZE_SNAKE - 3; i++) {
		if (snakeHEAD.x + 1 == SNAKE[i].x && snakeHEAD.y == SNAKE[i].y) {
			ProcessDead();
			return;
		}
	}
	if (snakeHEAD.x + 1 == nCol - 2) {
		ProcessDead();
	}
	else {
		if (countFOOD == MAX_FOOD_LEVEL) {
			if (GateFlag) {
				GenerateGate();
				DrawGate(GATE_IN);
				showingGateIn = true;
				GateFlag = 0;
			}
			if (showingGateIn)
				if ((snakeHEAD.x + 1 == GATE_IN[0].x && snakeHEAD.y == GATE_IN[0].y) ||
					(snakeHEAD.x + 1 == GATE_IN[5].x && snakeHEAD.y == GATE_IN[5].y) ||
					(snakeHEAD.x + 1 == GATE_IN[7].x && snakeHEAD.y == GATE_IN[7].y)) {
					ProcessDead();
					return;
				}
			if (showingGateOut)
				if ((snakeHEAD.x + 1 == GATE_OUT[0].x && snakeHEAD.y == GATE_OUT[0].y) ||
					(snakeHEAD.x + 1 == GATE_OUT[5].x && snakeHEAD.y == GATE_OUT[5].y) ||
					(snakeHEAD.x + 1 == GATE_OUT[7].x && snakeHEAD.y == GATE_OUT[7].y)) {
					ProcessDead();
					return;
				}
			NewGameLevel();
		}
		else if (snakeHEAD.x + 1 == FOOD.x && snakeHEAD.y == FOOD.y)
			EatFood();
		if (snakeHEAD.x + 1 != nCol - 2) {
			for (int i = 0; i < SIZE_SNAKE - 2; i++)
				SNAKE[i] = SNAKE[i + 1];
			SNAKE[SIZE_SNAKE - 2] = snakeHEAD;
			snakeHEAD.x++;
		}
	}
}
void MoveLeft() {
	for (int i = 0; i < SIZE_SNAKE - 3; i++) {
		if (snakeHEAD.x - 1 == SNAKE[i].x && snakeHEAD.y == SNAKE[i].y) {
			ProcessDead();
			return;
		}
	}
	if (snakeHEAD.x - 1 == 1) {
		ProcessDead();
	}
	else {
		if (countFOOD == MAX_FOOD_LEVEL) {
			if (GateFlag) {
				GenerateGate();
				DrawGate(GATE_IN);
				showingGateIn = true;
				GateFlag = 0;
			}
			if (showingGateIn)
				if ((snakeHEAD.x - 1 == GATE_IN[4].x && snakeHEAD.y == GATE_IN[4].y) ||
					(snakeHEAD.x - 1 == GATE_IN[8].x && snakeHEAD.y == GATE_IN[8].y) ||
					(snakeHEAD.x - 1 == GATE_IN[6].x && snakeHEAD.y == GATE_IN[6].y)) {
					ProcessDead();
					return;
				}
			if (showingGateOut)
				if ((snakeHEAD.x - 1 == GATE_OUT[4].x && snakeHEAD.y == GATE_OUT[4].y) ||
					(snakeHEAD.x - 1 == GATE_OUT[8].x && snakeHEAD.y == GATE_OUT[8].y) ||
					(snakeHEAD.x - 1 == GATE_OUT[6].x && snakeHEAD.y == GATE_OUT[6].y)) {
					ProcessDead();
					return;
				}
			NewGameLevel();
		}
		else if (snakeHEAD.x - 1 == FOOD.x && snakeHEAD.y == FOOD.y)
			EatFood();
		if (snakeHEAD.x - 1 != 1) {
			for (int i = 0; i < SIZE_SNAKE - 2; i++) {
				SNAKE[i] = SNAKE[i + 1];
			}
			SNAKE[SIZE_SNAKE - 2] = snakeHEAD;
			snakeHEAD.x--;
		}
	}
}
void MoveUp() {
	for (int i = 0; i < SIZE_SNAKE - 3; i++) {
		if (snakeHEAD.x == SNAKE[i].x && snakeHEAD.y - 1 == SNAKE[i].y) {
			ProcessDead();
			return;
		}
	}
	if (snakeHEAD.y - 1 == 0) {
		ProcessDead();
	}
	else {
		if (countFOOD == MAX_FOOD_LEVEL) {
			if (GateFlag) {
				GenerateGate();
				DrawGate(GATE_IN);
				showingGateIn = true;
				GateFlag = 0;
			}
			if (showingGateIn)
				for (int i = 0; i < 5; i++) {
					if (snakeHEAD.x == GATE_IN[i].x && snakeHEAD.y - 1 == GATE_IN[i].y) {
						ProcessDead();
						return;
					}
				}
			if (showingGateOut)
				for (int i = 5; i < 9; i++) {
					if (snakeHEAD.x == GATE_OUT[i].x && snakeHEAD.y - 1 == GATE_OUT[i].y) {
						ProcessDead();
						return;
					}
				}
			NewGameLevel();
		}
		else if (snakeHEAD.x == FOOD.x && snakeHEAD.y - 1 == FOOD.y)
			EatFood();
		if (snakeHEAD.y - 1 != 0) {
			for (int i = 0; i < SIZE_SNAKE - 2; i++) {
				SNAKE[i] = SNAKE[i + 1];
			}
			SNAKE[SIZE_SNAKE - 2] = snakeHEAD;
			snakeHEAD.y--;
		}
	}
}
void MoveDown() {
	for (int i = 0; i < SIZE_SNAKE - 3; i++) {
		if (snakeHEAD.x == SNAKE[i].x && snakeHEAD.y + 1 == SNAKE[i].y) {
			ProcessDead();
			return;
		}
	}
	if (snakeHEAD.y + 1 == nRow - 3) {
		ProcessDead();
	}
	else {
		if (countFOOD == MAX_FOOD_LEVEL) {
			if (GateFlag) {
				GenerateGate();
				DrawGate(GATE_IN);
				showingGateIn = true;
				GateFlag = 0;
			}
			if (showingGateIn)
				for (int i = 5; i < 9; i++) {
					if (snakeHEAD.x == GATE_IN[i].x && snakeHEAD.y + 1 == GATE_IN[i].y) {
						ProcessDead();
						return;
					}
				}
			if (showingGateOut)
				for (int i = 0; i < 5; i++) {
					if (snakeHEAD.x == GATE_OUT[i].x && snakeHEAD.y + 1 == GATE_OUT[i].y) {
						ProcessDead();
						return;
					}
				}
			SwitchGameLevel();
			NewGameLevel();
		}
		else if (snakeHEAD.x == FOOD.x && snakeHEAD.y + 1 == FOOD.y)
			EatFood();
		if (snakeHEAD.y + 1 != nRow - 3) {
			for (int i = 0; i < SIZE_SNAKE - 2; i++) {
				SNAKE[i] = SNAKE[i + 1];
			}
			SNAKE[SIZE_SNAKE - 2] = snakeHEAD;
			if (MoveFlag == 1)
				snakeHEAD.y++;
		}
	}
}
void FixSnakeSpeed()
{
	if (MOVING == 'W' || MOVING == 'S')
		Sleep(SPEED + (SPEED / 3));
	else Sleep(SPEED);
}

void setGateIn(int x, int y)
{
	GATE_IN[0] = { x - 2, y };
	GATE_IN[1] = { x - 1, y };
	GATE_IN[2] = { x, y };
	GATE_IN[3] = { x + 1, y };		// 56 78
	GATE_IN[4] = { x + 2, y };		// 01234
	GATE_IN[5] = { x - 2, y - 1 };
	GATE_IN[6] = { x - 1, y - 1 };
	GATE_IN[7] = { x + 1, y - 1 };
	GATE_IN[8] = { x + 2, y - 1 };
}
void setGateOut(int x, int y)
{
	GATE_OUT[0] = { x - 2, y };
	GATE_OUT[1] = { x - 1, y };
	GATE_OUT[2] = { x, y };
	GATE_OUT[3] = { x + 1, y };		//01234
	GATE_OUT[4] = { x + 2, y };		//56 78
	GATE_OUT[5] = { x - 2, y + 1 };
	GATE_OUT[6] = { x - 1, y + 1 };
	GATE_OUT[7] = { x + 1, y + 1 };
	GATE_OUT[8] = { x + 2, y + 1 };
}
void stringCopy(char src[], char des[])		//Copy chuỗi thứ 1 (src) vào chuỗi thứ 2 (des)
{
	int i;
	for (i = 0; src[i] != '\0'; i++)
		des[i] = src[i];
	des[i] = '\0';
}