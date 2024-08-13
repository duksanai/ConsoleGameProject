#pragma once
#include <conio.h>
#include "DeckSelectScene.h"


class MainMenuScene
{
public:
	void SelectMode();
private:
	int select;
	DeckSelectScene deckSelectScene;
};

