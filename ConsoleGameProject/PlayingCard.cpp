#include "PlayingCard.h"

PlayingCard::PlayingCard(const std::string& shape, const int number, const int chip)
	:shape(shape), number(number), chip(chip)
{
}

CardType PlayingCard::getCardType()
{
	return CardType(shape, number);
}
