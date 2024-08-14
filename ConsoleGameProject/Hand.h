#pragma once

class Hand
{
public:
	void SortNum();
	void SortShape();
	void AddCard(PlayingCard* card);
private:
	std::list<PlayingCard*> handList;
};

