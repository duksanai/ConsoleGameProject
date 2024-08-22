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

enum Keys {
	SPECIAL_KEY = 224,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_ENTER = 13
};

void gotoxy(int x, int y);
void TextColor(int font, int backGround);