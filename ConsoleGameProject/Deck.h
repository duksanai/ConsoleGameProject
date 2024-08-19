#pragma once
#include <vector>
#include <map>
#include <utility>
#include <random>
#include <conio.h>

#include "PlayingCard.h"
#include "Hand.h"

class Deck
{
public:
	void PrintDeck()const;
	void AddCard(PlayingCard* card);
	void DestroyCard(PlayingCard* card);
	void ChangeCard(PlayingCard* oldCard, PlayingCard* newCard);
	void UsedCards(std::vector<PlayingCard*> usedCards);
	void RestoreDeck();
	void Shuffle();
	void InitCardMap();
	void CountCards();
	PlayingCard* PopCard();

private:
	std::vector<PlayingCard*> cards;
	std::vector<PlayingCard*>::iterator iter;
	std::vector<PlayingCard*> usedCards;
	std::map<CardType, int> cardStock;
	std::map<CardType, int> cardStockTemp;
	std::string deckName;
};

