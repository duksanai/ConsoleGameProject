#pragma once
#include <vector>
#include "PlayingCard.h"

class Deck
{
public:
	void PrintDeck()const;
	void AddCard(PlayingCard* card);
	void DestroyCard(PlayingCard* card);
	void ChangeCard(PlayingCard* oldCard, PlayingCard* newCard);
	void Shuffle();
private:
	std::vector<PlayingCard*> deck;
	std::vector<PlayingCard*>::iterator iter;
	std::string deckName;
};

