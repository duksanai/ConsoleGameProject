#include "Hand.h"

void Hand::PrintHand(int x, int y)const
{
	gotoxy(x, y - 3);
	cout << "<패>" << endl;
	for (auto card : handList)
	{
		card->PrintCard(x, y);
		std::cout << "\t";
		x += 22;
	}
	std::cout << std::endl;
}

// 숫자 순서대로 정렬
void Hand::SortNum()
{
	// 숫자가 큰 카드부터 정렬
	// 그 다음, 같은 그림끼리 정렬?
	// 같은 그림부터 정렬 후 숫자로 정렬? -> 이게 맞다

	std::sort(handList.begin(), handList.end(), [](const PlayingCard* a, const PlayingCard* b)
		{
			return *a > *b;
		});
}

// 그림 순서대로 정렬
void Hand::SortShape()
{
	// 숫자로 먼저 정렬한 후 그림 순서로 정렬해야함. 
	std::sort(handList.begin(), handList.end(), [](const PlayingCard* a, const PlayingCard* b)
		{
			return *a < *b;
		});
}

void Hand::AddCard(PlayingCard* card)
{
	handList.push_back(card);
}

PlayingCard* Hand::getCard(int index)const
{
	return handList[index];
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

int Hand::getHandSize()const
{
	return handList.size();
}

bool Hand::FindCard(PlayingCard* card)
{
	if (find(handList.begin(), handList.end(), card) == handList.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}
