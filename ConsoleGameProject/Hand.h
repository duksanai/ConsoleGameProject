#pragma once
#include <vector>
#include "PlayingCard.h"

class Hand
{
public:
	void SortNum();
	void SortShape();
	void AddCard(PlayingCard* card);
	void Discard(std::vector<PlayingCard*> cards);
	int getHandSize();
private:
	std::vector<PlayingCard*> handList;
	std::vector<PlayingCard*>::iterator iter;
};

