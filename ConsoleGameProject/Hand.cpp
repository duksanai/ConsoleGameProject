#include "Hand.h"

void Hand::PrintHand(int x, int y)const
{
	gotoxy(x, y - 3);
	cout << "<��>" << endl;
	for (auto card : handList)
	{
		card->PrintCard(x, y);
		std::cout << "\t";
		x += 22;
	}
	std::cout << std::endl;
}

// ���� ������� ����
void Hand::SortNum()
{
	// ���ڰ� ū ī����� ����
	// �� ����, ���� �׸����� ����?
	// ���� �׸����� ���� �� ���ڷ� ����? -> �̰� �´�

	std::sort(handList.begin(), handList.end(), [](const PlayingCard* a, const PlayingCard* b)
		{
			return *a > *b;
		});
}

// �׸� ������� ����
void Hand::SortShape()
{
	// ���ڷ� ���� ������ �� �׸� ������ �����ؾ���. 
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
