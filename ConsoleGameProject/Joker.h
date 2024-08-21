#pragma once
#include <iostream>
#include <functional>
#include "PlayingCard.h"
#include "Util.h"

enum class grade {
	COMMON,
	UNCOMMON,
	RARE
};

class Joker
{
public:
	Joker(const std::string& name, const std::string& toolTip);
public:
	std::function<void(PlayingCard* card)> PassiveAbility = [](PlayingCard* card) {};
	std::function<void(PlayingCard* card)> AtTrigger = [](PlayingCard* card) {};
	std::function<void(PlayingCard* card)> AfterTrigger = [](PlayingCard* card) {};
	void PrintJoker()const;

	std::string getName();
	std::string getToolTip();

private:
	std::string name;
	std::string toolTip;
	int jokerGrade;
};