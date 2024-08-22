#pragma once
#include <iostream>
#include <map>
#include <functional>
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
	void PrintCard(const int x, int y)const;
	std::string getShape();
	int getChip();
	void Select(bool isSelected);
	void AddChips(int chips);

private:
	void PrintCardFrame(int x, int y)const;
	void PrintSuit(std::string suit, int x, int y)const;
	void PrintRank(int rank, int x, int y)const;

private:
	std::string shape;
	int number;
	int chip;
	int uniqueNum;
	bool isSelected;

	// std::string upgradeType;
};

