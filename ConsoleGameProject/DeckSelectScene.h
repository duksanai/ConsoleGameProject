#pragma once
#include <conio.h>
#include "Deck.h"
#include "GameScene.h"

class DeckSelectScene
{
public:
	void SelectDeck();
private:
	Deck DeckInit();
	void PrintDeckSelect()const;
private:
	Deck deck;
	GameScene game;
	int select;
	bool out;
};

