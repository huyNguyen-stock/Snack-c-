#pragma once

#include "FileFuncs.h"

void MainGP(int CC, int RC, bool newGame);
void PlayGame();				//Chơi game
void ResetData();				//Dữ liệu mặc định
bool LoadData();				//Lấy dữ liệu từ file
void ImportData(PLAYER currPlayer);		//Nạp dữ liệu từ file vào các biến toàn cục
void ExportData(PLAYER*& arrPlayer);	//Xuất dữ liệu các biến toàn cục ra file

void ThreadFunc();				//Hàm quản lý rắn di chuyển
void EatFood();					//Rắn ăn food
void InsertPointSnake();		//Tăng độ dài thân rắn sau khi ăn
void ProcessDead();				//Xử lý rắn chết

void SwitchGameLevel();			//Xử lý khi bắt đầu vào cổng IN
void NewGameLevel();			//Xử lý sang màn mới
void CountFunc();				//Hàm đếm thân rắn khi ra/vào cổng

void PrintScoreLevel();			//In SCORE và LEVEL lên màn hình
void DrawSnake();				//Vẽ thân rắn
void DrawGate(POINT*& GATE);	//Vẽ cổng
void ClearGate(POINT*& GATE);	//Xóa cổng

bool isValid(int x, int y);		//true nếu tọa độ (x, y) không nằm trên rắn
void GenerateFood();			//Tạo tọa độ cho FOOD
void GenerateGate();			//Tạo tọa độ cho GATE_IN và GATE_OUT

void MoveRight();				//Rắn sang phải
void MoveLeft();				//Rắn sang trái
void MoveUp();					//Rắn lên trên
void MoveDown();				//Rắn xuống dưới
void FixSnakeSpeed();			//Điều chỉnh tốc rắn (dọc - ngang)

void setGateIn(int x, int y);	//Gán tọa độ cho GATE_IN
void setGateOut(int x, int y);	//Gán tọa độ cho GATE_OUT
void stringCopy(char src[], char des[]);		//Copy chuỗi thứ 1 (src) vào chuỗi thứ 2 (des)