#pragma once

#include "Windows.h"

void MainSM(int CC, int RC);
void PlayGameSM();
void ResetDataSM();

void ThreadFuncSM();
void EatFood1SM();
void EatFood2SM();
void InsertPointSnake(POINT*& snake, int size, POINT head);		//Tăng độ dài thân rắn sau khi ăn
void ProcessDeadSM(int code);		//code: 0 (cả 2 cùng chết), 1 (rắn 1 chết), 2 (rắn 2 chết), 3 (hết giờ)

void PrintScores();		//In hai SCORE của 2 người chơi (special mode)
void PrintTimer();		//In thời gian còn lại của game (special mode)
void DrawSnakeSM(POINT*& snake, int size, int ps);

bool isValidSM(int x, int y);
void GenerateFoodSM();

void MoveRight1SM();
void MoveLeft1SM();
void MoveUp1SM();
void MoveDown1SM();

void MoveRight2SM();
void MoveLeft2SM();
void MoveUp2SM();
void MoveDown2SM();