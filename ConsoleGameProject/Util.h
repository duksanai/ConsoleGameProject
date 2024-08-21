#pragma once
#include <iostream>
#include <Windows.h>
#include <map>
#include <functional>

using std::cout;
using std::endl;

enum Color{
	BLACK,
	BLUE,
	DARKGREEN,
	LIGHTBLUE,
	RED,
	PURPLE,
	YELLOW,
	LIGHTGRAY,
	DARKGRAY,
	SKYBLUE,
	GREEN,
	CYAN,
	PINK,
	SWEETPOTATO,
	LIGHTYELLOW,
	WHITE
};

void gotoxy(int x, int y);
void TextColor(int font, int backGround);