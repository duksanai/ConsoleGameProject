#pragma once
#include <vector>
#include "PlayingCard.h"

class Hand
{
public:
	void SortNum();
	void SortShape();
	void AddCard(std::vector<PlayingCard*> cards);
	void Discard(std::vector<PlayingCard*> cards);
private:
	std::vector<PlayingCard*> handList;
	std::vector<PlayingCard*>::iterator iter;
};

