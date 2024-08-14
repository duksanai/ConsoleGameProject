#pragma once
#include <vector>
#include <map>
#include <random>
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
private:
	std::vector<PlayingCard*> deck;
	std::vector<PlayingCard*>::iterator iter;
	std::vector<PlayingCard*> usedCards;
	std::map<CardType, int> cardStock;
	std::map<CardType, int> cardStockTemp;
	std::string deckName;
};

