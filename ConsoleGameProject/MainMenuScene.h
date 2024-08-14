#pragma once
#include <conio.h>
#include "DeckSelectScene.h"


class MainMenuScene
{
public:
	void SelectMode();
private:
	void PrintMainMenu()const;
private:
	DeckSelectScene deckSelectScene;
};

