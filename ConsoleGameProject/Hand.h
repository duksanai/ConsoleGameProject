#pragma once
#include <vector>
#include <algorithm>
#include "PlayingCard.h"

class Hand
{
public:
	Hand() { iter = handList.begin(); }
public:
	void PrintHand(int x, int y)const;
	void SortNum();
	void SortShape();
	void AddCard(PlayingCard* card);
	PlayingCard* getCard(int index)const;
	void Discard(std::vector<PlayingCard*> cards);
	int getHandSize()const;
	bool FindCard(PlayingCard* card);
private:
	std::vector<PlayingCard*> handList;
	std::vector<PlayingCard*>::iterator iter;
};

