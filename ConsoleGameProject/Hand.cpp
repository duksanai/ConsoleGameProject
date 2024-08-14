#include "Hand.h"

void Hand::SortNum()
{
}

void Hand::SortShape()
{
}

void Hand::AddCard(std::vector<PlayingCard*> cards)
{
	for (auto& card : cards)
	{
		handList.push_back(card);
	}
}

void Hand::Discard(std::vector<PlayingCard*> cards)
{
	for (auto& card : cards)
	{
		iter = find(handList.begin(), handList.end(), card);
		if (iter != handList.end())
		{
			handList.erase(remove(handList.begin(), handList.end(), *iter));
		}
	}
}
