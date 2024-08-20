#include "Util.h"

void gotoxy(int x, int y)
{
    COORD pos = { x,y }; //x, y 좌표 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커서 설정
}

void PrintCardFrame(int x, int y)
{
    int cardHeigth = 10;
    int cardWidth = 8;
    for (int i = 0; i < cardHeigth; i++)
    {
        gotoxy(x, y + i);
        TextColor(BLACK, WHITE);
        for (int j = 0; j < cardWidth; j++)
        {
            cout << "　";
        }
        TextColor(WHITE, BLACK);
        cout << "　";
    }
}

void PrintBackground()
{
    TextColor(WHITE, DARKGREEN);
}

void TextColor(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}