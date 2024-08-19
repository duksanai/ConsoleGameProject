#include "PlayingCard.h"

PlayingCard::PlayingCard(const std::string& shape, const int number, const int chip)
	:shape(shape), number(number), chip(chip)
{
	isSelected = false;
}

bool PlayingCard::operator<(const PlayingCard& other) const
{
	if (shape == other.shape)
	{
		return number < other.number;
	}
	return shape < other.shape;
}

CardType PlayingCard::getCardType()
{
	return CardType(shape, number);
}

void PlayingCard::PrintCard()
{
	std::cout << shape;
	switch (number)
	{
	case 1:
		std::cout << "A";
		break;
	case 11:
		std::cout << "J";
		break;
	case 12:
		std::cout << "Q";
		break;
	case 13:
		std::cout << "K";
		break;
	default:
		std::cout << number;
		break;
	}
}

std::string PlayingCard::getShape()
{
	return shape;
}

int PlayingCard::getChip()
{
	return chip;
}

bool CardType::operator<(const CardType& rhs) const
{
	if (shape != rhs.shape)
	{
		return shape < rhs.shape;
	}
	return number < rhs.number;
}
