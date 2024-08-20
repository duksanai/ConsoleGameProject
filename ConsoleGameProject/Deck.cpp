#include "Deck.h"

// GameScene에서 덱 조회를 선택하면 나올 화면
// 
void Deck::PrintDeck() const
{
	system("cls");
	std::string shape[4] = { "♠", "◆", "♥", "♣" };
	int i = 0;
	std::cout << "\tA\t2\t3\t4\t5\t6\t7\t8\t9\t10\tJ\tQ\tK" << std::endl;
	for (auto& count : cardStockTemp)
	{
		if (count.first.number == 1)
		{
			std::cout << shape[i];
			i++;
		}
		std::cout << "\t" << count.second;
		if (count.first.number == 13)
		{
			std::cout << std::endl;
		}
	}
	std::cout << "나가기 - x";
	int key;
	key = _getch();
	if (key == 88 || key == 120)
	{
		return;
	}
}

void Deck::AddCard(PlayingCard* card)
{
	cards.push_back(card);
}

void Deck::DestroyCard(PlayingCard* card)
{
}

void Deck::ChangeCard(PlayingCard* oldCard, PlayingCard* newCard)
{
}

void Deck::UsedCards(std::vector<PlayingCard*> usedCards)
{
	for (auto& card : usedCards)
	{
		this->usedCards.push_back(card);
	}
}

void Deck::RestoreDeck()
{
	for (auto& card : usedCards)
	{
		cards.push_back(card);
	}
	std::vector<PlayingCard*>().swap(usedCards);
}

void Deck::Shuffle()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, static_cast<int>(cards.size() - 1));

	int dest, sour;
	PlayingCard* temp;


	iter = cards.begin();

	for (int i = 0; i < cards.size() * cards.size(); i++)
	{
		dest = dist(gen);
		sour = dist(gen);

		temp = iter[sour];
		iter[sour] = iter[dest];
		iter[dest] = temp;
	}
}

void Deck::InitCardMap()
{
	std::string shape[4] = { "♠", "◆", "♥", "♣" };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cardStock.insert(std::make_pair(CardType(shape[i], j + 1), 0));
		}
	}
}

void Deck::CountCards()
{
	cardStockTemp = cardStock;
	for (auto& card : cards)
	{
		cardStockTemp[card->getCardType()]++;
	}
}

PlayingCard* Deck::PopCard()
{
	PlayingCard* temp;
	temp = cards.back();
	cards.pop_back();
	return temp;
}

void Deck::setLastNum(int num)
{
	lastNum = num;
}


