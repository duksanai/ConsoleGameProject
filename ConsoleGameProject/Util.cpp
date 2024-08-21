#include "Util.h"

void gotoxy(int x, int y)
{
    COORD pos = { x,y }; //x, y ��ǥ ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //Ŀ�� ����
}

void TextColor(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}