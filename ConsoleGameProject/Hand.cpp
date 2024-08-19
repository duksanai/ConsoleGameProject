#include "Hand.h"

void Hand::PrintHand()const
{
	for (auto card : handList)
	{
		card->PrintCard();
		std::cout << "\t";
	}
	std::cout << std::endl;
}

// �� �ִ� ����..
// ���� ������� ����
void Hand::SortNum()
{
	// ���ڰ� ū ī����� ����
	// �� ����, ���� �׸����� ����?
	// ���� �׸����� ���� �� ���ڷ� ����? -> �̰� �´�

	// ���� �׸����� ������

}

// �׸� ������� ����
void Hand::SortShape()
{
	// ���ڷ� ���� ������ �� �׸� ������ �����ؾ���. 
	
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
