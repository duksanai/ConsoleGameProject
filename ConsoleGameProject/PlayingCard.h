#pragma once
#include <iostream>
#include "Util.h"

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
	PlayingCard(const std::string& shape, const int number, const int chip, const int uniqueNum);
	bool operator<(const PlayingCard& other)const;
	bool operator>(const PlayingCard& other)const;
	CardType getCardType();
	void PrintCard(const int x, const int y)const;
	std::string getShape();
	int getChip();

private:
	std::string shape;
	int number;
	int chip;
	int uniqueNum;
	bool isSelected;
	// std::string upgradeType;
};

