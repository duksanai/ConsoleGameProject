#pragma once
#include <conio.h>
#include "Deck.h"
#include "GameScene.h"

class DeckSelectScene
{
public:
	Deck DeckInit(int inputNum);
	void SelectDeck();

private:
	Deck deck;
	GameScene game;
	int select;
};

