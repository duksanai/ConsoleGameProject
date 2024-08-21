#include "PlayingCard.h"

PlayingCard::PlayingCard(const std::string& shape, const int number, const int chip, const int uniqueNum)
	:shape(shape), number(number), chip(chip), uniqueNum(uniqueNum)
{
	isSelected = false;
}

//bool PlayingCard::operator<(const PlayingCard& other) const
//{
//	if (shape == other.shape)
//	{
//		return number < other.number;
//	}
//	return shape < other.shape;
//}

// 収切
bool PlayingCard::operator<(const PlayingCard& other) const
{
	if (number == other.number)
	{
		return shape > other.shape;
	}
	return number > other.number;
}

// 乞丞
bool PlayingCard::operator>(const PlayingCard& other) const
{

	if (shape == other.shape)
	{
		return number > other.number;
	}
	return shape > other.shape;
}

CardType PlayingCard::getCardType()
{
	return CardType(shape, number);
}

void PlayingCard::PrintCard(const int x, int y)const
{
	if (isSelected)
	{
		y -= 2;
	}
	PrintCardFrame(x, y);
	PrintSuit(shape, x, y);
	PrintRank(number, x + 10, y + 7);
	TextColor(WHITE, BLACK);
}

std::string PlayingCard::getShape()
{
	return shape;
}

int PlayingCard::getChip()
{
	return chip;
}

void PlayingCard::Select(bool isSelected)
{
	this->isSelected = isSelected;
}

bool CardType::operator<(const CardType& rhs) const
{
	if (shape != rhs.shape)
	{
		return shape < rhs.shape;
	}
	return number < rhs.number;
}

void PlayingCard::PrintCardFrame(int x, int y)const
{
	int cardHeigth = 14;
	int cardWidth = 10;
	for (int i = 0; i < cardHeigth; i++)
	{
		gotoxy(x, y + i);
		TextColor(BLACK, WHITE);
		for (int j = 0; j < cardWidth; j++)
		{
			cout << "　";
		}
		TextColor(WHITE, BLACK);
		cout << "　";
	}
}

void PlayingCard::PrintSuit(const std::string suit, int x, int y)const
{
	gotoxy(x, y);
	if (suit == "⊆")
	{
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";
	}
	else if (suit == "×")
	{
		TextColor(WHITE,WHITE);
		cout << "　　"; 
		TextColor(WHITE, RED);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, RED);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, RED);
		cout << "　　　　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, RED);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		
		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, RED);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
	}
	else if (suit == "⊂")
	{
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, RED);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, RED);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, RED);
		cout << "　　　　　";

		gotoxy(x, y + 2);
		TextColor(WHITE, RED);
		cout << "　　　　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, RED);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, RED);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, RED);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
	}
	else if (suit == "∪")
	{
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";
	}
	TextColor(WHITE, BLACK);
}

void PlayingCard::PrintRank(const int rank, int x, int y)const
{
	gotoxy(x, y);
	switch (rank)
	{
	case 1:
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		break;
	case 2:
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";
		break;
	case 3:
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";
		break;
	case 4:
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		break;
	case 5:
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";
		break;
	case 6:
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";
		break;
	case 7:
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		break;
	case 8:
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";
		break;
	case 9:
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, WHITE);
		cout << "　　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";
		break;
	case 10:
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		break;
	case 11:
		TextColor(WHITE, DARKGRAY);
		cout << "　　　　　";

		gotoxy(x, y + 1);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　　";
		break;
	case 12:
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		break;
	case 13:
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";

		gotoxy(x, y + 1);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 2);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 3);
		TextColor(WHITE, DARKGRAY);
		cout << "　　";
		TextColor(WHITE, WHITE);
		cout << "　　　";

		gotoxy(x, y + 4);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";

		gotoxy(x, y + 5);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　";

		gotoxy(x, y + 6);
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		TextColor(WHITE, WHITE);
		cout << "　　　";
		TextColor(WHITE, DARKGRAY);
		cout << "　";
		break;
	}
}