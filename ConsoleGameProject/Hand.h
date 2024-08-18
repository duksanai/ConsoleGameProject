#pragma once
#include <vector>
#include <algorithm>
#include "PlayingCard.h"

class Hand
{
public:
	Hand() { iter = handList.begin(); }
public:
	void SortNum();
	void SortShape();
	void AddCard(PlayingCard* card);
	PlayingCard* getCard(int index);
	void Discard(std::vector<PlayingCard*> cards);
	int getHandSize();
	bool FindCard(PlayingCard* card);
private:
	std::vector<PlayingCard*> handList;
	std::vector<PlayingCard*>::iterator iter;
};

