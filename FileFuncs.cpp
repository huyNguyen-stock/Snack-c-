#include "FileFuncs.h"
#include "Support.h"
#include <fstream>
using namespace std;

// Cấu trúc file Player.txt (1/5 player)
//	used
//	namePlayer
//	length
//	headSnake.x headSnake.y
//	snake[i].x snake[i].y						(với i chạy từ 0 đến length - 2)
//	level
//	score
//	countFood
//	direction
//	MoveFlag CountFlag_IN CountFlag_OUT
//	haveFood haveGateIn haveGateOut
//	food.x food.y								(nếu haveFood = true)
//	gateIn.x gateIn.y gateOut.x gateOut.y		(nếu haveGateIn = true hoặc haveGateOut = true)
//	INDEX

int readFile(PLAYER*& arrPlayer)
{
	int n = 0;
	PLAYER* arr = new PLAYER[MAX_PLAYERS_NUMBER];
	ifstream ifs(fileNamePlayer);
	if (ifs.fail())
	{
		for (int i = 0; i < MAX_PLAYERS_NUMBER; i++)
			arr[i].used = false;
		arrPlayer = arr;
		ifs.close();
		return 0;
	}
	for (int i = 0; i < MAX_PLAYERS_NUMBER; i++) {
		PLAYER member;
		ifs >> member.used;
		if (member.used == true)		//Nếu slot còn trống thì không nhập các dữ liệu còn lại
		{
			ifs.ignore();
			ifs.getline(member.namePlayer, MAX_NAME_LENGTH);	//Lấy tên
			ifs >> member.length;		//Lấy độ dài (số lượng tọa độ)
			member.snake = NULL;
			ifs >> member.headSnake.x >> member.headSnake.y;
			for (int j = 0; j < member.length - 1; j++)
			{
				int m = j;
				POINT pos;
				ifs >> pos.x >> pos.y;
				addLast(member.snake, m, pos);	//Lấy mảng tọa độ
			}
			ifs >> member.level;				//Lấy level
			ifs >> member.score;				//Lấy score
			ifs >> member.countFood;		
			ifs >> member.direction;
			ifs >> member.GateFlag >> member.MoveFlag >> member.CountFlag_IN >> member.CountFlag_OUT;
			ifs >> member.haveFood >> member.haveGateIn >> member.haveGateOut;
			if (member.haveFood) 
				ifs >> member.food.x >> member.food.y;
			if (member.haveGateIn || member.haveGateOut)
				ifs >> member.gateIn.x >> member.gateIn.y >> member.gateOut.x >> member.gateOut.y;
			ifs >> member.INDEX;
			n++;
		}
		arr[i] = member;
	}
	arrPlayer = arr;
	ifs.close();
	return n;
}
void writeFile(PLAYER*& arrPlayer) {
	ofstream ofs(fileNamePlayer);
	if (ofs.fail()) return;
	for (int i = 0; i < MAX_PLAYERS_NUMBER; i++) {
		ofs << arrPlayer[i].used;
		if (arrPlayer[i].used == false) {	//Nếu slot còn trống thì không in các dữ liệu còn lại
			if (i < MAX_PLAYERS_NUMBER - 1) ofs << endl;
			continue;
		}
		ofs << endl;
		ofs << arrPlayer[i].namePlayer << endl;
		ofs << arrPlayer[i].length << endl;
		ofs << arrPlayer[i].headSnake.x << " " << arrPlayer[i].headSnake.y << endl;
		for (int j = 0; j < arrPlayer[i].length - 1; j++)
			ofs << (arrPlayer[i].snake)[j].x << " " << (arrPlayer[i].snake)[j].y << endl;
		ofs << arrPlayer[i].level << endl;
		ofs << arrPlayer[i].score << endl;
		ofs << arrPlayer[i].countFood << endl;
		ofs << arrPlayer[i].direction << endl;
		ofs << arrPlayer[i].GateFlag << " " << arrPlayer[i].MoveFlag << " " << arrPlayer[i].CountFlag_IN << " " << arrPlayer[i].CountFlag_OUT << endl;
		ofs << arrPlayer[i].haveFood << " " << arrPlayer[i].haveGateIn << " " << arrPlayer[i].haveGateOut << endl;
		if (arrPlayer[i].haveFood) ofs << arrPlayer[i].food.x << " " << arrPlayer[i].food.y << endl;
		if (arrPlayer[i].haveGateIn || arrPlayer[i].haveGateOut) ofs << arrPlayer[i].gateIn.x << " " << arrPlayer[i].gateIn.y << " " << arrPlayer[i].gateOut.x << " " << arrPlayer[i].gateOut.y << endl;
		ofs << arrPlayer[i].INDEX;		//dòng nay chưa endl
		if (i < MAX_PLAYERS_NUMBER - 1) ofs << endl;
	}
	ofs.close();
}

void addData(PLAYER*& arrPlayer, int i, PLAYER newPlayer) {
	arrPlayer[i] = newPlayer;
	arrPlayer[i].used = true;
	writeFile(arrPlayer);
}

void deleteData(int i)
{
	PLAYER* arr;
	int n = readFile(arr);
	PLAYER none;
	none.used = false;
	arr[i] = none;
	writeFile(arr);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Cấu trúc file TopPlayer.txt (1/5 player)
//	score namePlayer

void sortScore(TOP_PLAYER*& arrTP, int number)
{
	for (int i = 0; i < number - 1; i++)
		for (int j = i + 1; j < number; j++)
			if (arrTP[i].score < arrTP[j].score)
			{
				TOP_PLAYER tmp = arrTP[i];
				arrTP[i] = arrTP[j];
				arrTP[j] = tmp;
			}
}

int readFile(TOP_PLAYER*& arrTP) {
	ifstream ifs(fileNameTP);
	if (ifs.fail()) return 0;
	int n = 0;
	TOP_PLAYER* arr = NULL;
	while (!ifs.eof())
	{
		TOP_PLAYER member;
		ifs >> member.score;
		ifs.ignore();
		ifs.getline(member.namePlayer, MAX_NAME_LENGTH);
		addLast(arrTP, n, member);
	}
	ifs.close();
	return n;
}

void writeFile(TOP_PLAYER*& arrTP, int number)
{
	ofstream ofs(fileNameTP);
	if (ofs.fail()) return;
	for (int i = 0; i < number - 1; i++)
		ofs << arrTP[i].score << " " << arrTP[i].namePlayer << endl;
	if (number >= 1) 
		ofs << arrTP[number - 1].score << " " << arrTP[number - 1].namePlayer;
	ofs.close();
}

bool enoughScore(int newScore)
{
	if (newScore == 0) return false;
	TOP_PLAYER* arr = NULL;
	int n = readFile(arr);
	if (n < MAX_PLAYERS_NUMBER) return true;
	for (int i = n - 1; i >= 0; i--)
		if (arr[i].score < newScore)
			return true;
	return false;
}

void addData(TOP_PLAYER newPlayer)
{
	TOP_PLAYER* arr = NULL;
	int n = readFile(arr);
	addLast(arr, n, newPlayer);
	sortScore(arr, n);
	if (n > MAX_PLAYERS_NUMBER)
		removeLast(arr, n);
	writeFile(arr, n);
}
