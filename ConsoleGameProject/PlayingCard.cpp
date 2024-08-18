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

bool CardType::operator<(const CardType& rhs) const
{
	if (shape != rhs.shape)
	{
		return shape < rhs.shape;
	}
	return number < rhs.number;
}
