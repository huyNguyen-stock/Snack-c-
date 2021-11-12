#pragma once

#include "Windows.h"
#define MAX_PLAYERS_NUMBER 5
#define MAX_NAME_LENGTH 23

struct PLAYER
{
	bool used;
	char namePlayer[MAX_NAME_LENGTH];
	POINT headSnake;
	POINT* snake;
	int length;
	int level;
	int score;
	int countFood;
	int INDEX;
	bool GateFlag;
	bool MoveFlag;
	bool CountFlag_IN;
	bool CountFlag_OUT;
	char direction;
	bool haveFood;
	bool haveGateIn;
	bool haveGateOut;
	POINT food, gateIn, gateOut;
};

struct TOP_PLAYER
{
	char namePlayer[MAX_NAME_LENGTH];
	int score;
};

const char fileNamePlayer[] = "Player.txt";
const char fileNameTP[] = "TopPlayer.txt";

int readFile(PLAYER*& arrPlayer);	//Nhập dữ liệu từ file vào mảng arrPlayer và đếm số lượng slot đã dùng, trả về hàm có mở và đọc file thành công không
void writeFile(PLAYER*& arrPlayer);		//Xuất dữ liệu từ mảng arrPlayer vào file, trả về hàm có mở và xuất file thành công không 
void addData(PLAYER*& arrPlayer, int i, PLAYER newPlayer);	//Ghì đè (thay thế) newPlayer vào slot thứ i của mảng arrPlayer
void deleteData(int i);		//Xóa dữ liệu slot thứ i của mảng arrPlayer

void sortScore(TOP_PLAYER*& arrTP, int number);		//Sắp xếp mảng arrTP theo score
int readFile(TOP_PLAYER*& arrTP);		//Nhập dữ liệu từ file vào mảng arrTP và đếm số lượng người chơi đã trong top, trả về hàm có mở và đọc file thành công
void writeFile(TOP_PLAYER*& arrTP, int n);	    //Xuất dữ liệu từ mảng arrTP vào file, trả về hàm có mở và xuất file thành công không 
bool enoughScore(int newScore);			// Kiểm tra newPlayer có đạt top không
void addData(TOP_PLAYER newPlayer);				//Thêm (thay thế) nguời chơi mới vào file