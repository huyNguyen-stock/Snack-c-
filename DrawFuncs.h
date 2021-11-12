#pragma once

#include "FileFuncs.h"

void DrawWelcomeScreen(int maxColumn, int maxRow);
int DrawHomeScreen(int maxColumn, int maxRow, bool haveLoadGame);	//Vẽ giao diện trang chủ, trả về 0 là NEW GAME, 1 là SCORE, 2 là QUIT và 3 là LOADGAME
void DrawGameBorder(int maxColumn, int maxRow);		//Vẽ khung viền gameplay
int DrawLoadGameScreen(int maxColumn, int maxRow, PLAYER*& arrPlayer);	//Vẽ giao diện LoadGame
void DrawScoreScreen(int maxColumn, int maxRow, TOP_PLAYER*& arrTP, int number);	//Vẽ giao diện Score (top người chơi)
void DrawWinGame(int maxColumn, int maxRow);

void DrawBorderSwitchLevel(int maxColumn, int maxRow);
void ClearBorderSwitchLevel(int maxColumn, int maxRow);

int DrawPauseBox(int maxColumn, int maxRow);		//Vẽ hộp thoại Pause Game
void drawResumeButton(int x, int y);				//trả về 0
void drawReplayButton(int x, int y);				//trả về 1
void drawHomeButton(int x, int y);					//trả về 2
void clearPauseBox(int maxColumn, int maxRow);		//Tắt hộp thoại Pause Game

int DrawAskBox(int maxColumn, int maxRow, char title[], bool firstYes);		//Vẽ hộp thoại hỏi người chơi Yes/No
void drawYesButton(int x, int y);					//trả về 1
void drawNoButton(int x, int y);					//trả về 0   ;   //ESC: trả về -1
void clearAskBox(int maxColumn, int maxRow);		//Tắt hộp thoại Yes/No
													
int DrawSaveBox(int maxColumn, int maxRow, PLAYER*& arrPlayer, char getNamePlayer[]);	//Vẽ hộp thoại Save: chọn slot để lưu
void printPlayersList(PLAYER*& arrPlayer, int x, int y);	//In danh sách các player
void DrawSaveDoneNoti(int maxColumn, int maxRow);		//Vẽ hộp thoại thông báo save thành công

void DrawGameOverBox(int maxColumn, int maxRow, int score);		//Vẽ hộp thoại thông báo gameover
void DrawEnterNameScoreBox(int maxColumn, int maxRow, char getNamePlayer[]);	//Vẽ hộp thoại yêu cầu người chơi nhập tên, trả về false nếu ấn ESC
void DrawScoreDoneNoti(int maxColumn, int maxRow);		//Vẽ hộp thoại thông báo điểm đã được lưu

void DrawNameValidNoti(int maxColumn, int maxRow);
bool isValidChar(char c);
bool nameHandling(char input[], char output[]);

void DrawHeadSnake(POINT head, char ch, int cl);	//Vẽ đầu rắn
void ClearSnake(POINT tail);						//Xóa đuôi rắn cũ
void DrawFood(POINT FOOD, char ch);					//Vẽ FOOD

void DrawEndGameBox(int maxColumn, int maxRow, int code, int score1, int score2);	//Vẽ hộp thoại thông báo gameover (special mode)