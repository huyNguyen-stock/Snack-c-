#pragma once

void ResizeConsole(int column, int row);	//Đổi kích thước màn hình theo số cột và hàng
void FixedSizeWindow();						//Cố định kích thước màn hình
void SetCenterWindow(int column, int row);	//Đặt màn hình ở trung tâm desktop
void ShowCursor(bool show);					//Hiện ẩn con trỏ chuột
void ClearScreen();							//Xóa màn hình

void GotoXY(int x, int y);					//Đưa con trỏ chuột đến cột x, hàng y
void Color(int c);							//Đổi màu
void ColorXY(int x, int y, int c);			//Đổi màu và đưa con trỏ chuột đến cột x, hàng y