#pragma once
#include <iostream>

struct CardType
{
	CardType(const std::string& shape, const int number) :shape(shape), number(number) {}
	bool operator<(const CardType& rhs) const;
	std::string shape;
	int number;
};

class PlayingCard
{
public:
	PlayingCard(const std::string& shape, const int number, const int chip);
	CardType getCardType();

private:
	std::string shape;
	int number;
	int chip;
	// std::string upgradeType;
};

