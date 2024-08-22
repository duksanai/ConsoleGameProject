#pragma once
#include <iostream>
#include <functional>
#include <random>
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
	Joker(const std::string& name, const std::string& toolTip, const int jokerGrade);
public:
	std::function<void(PlayingCard* card)> PassiveAbility = [](PlayingCard* card) {};
	std::function<void(PlayingCard* card)> AtTrigger = [](PlayingCard* card) {};
	std::function<void(PlayingCard* card)> AfterTrigger = [](PlayingCard* card) {};
	void PrintJoker()const;

	std::string getName()const;
	std::string getToolTip()const;
	int getJokerGrade()const;
	void addChips(int chip);

	void setPassiveAbility(std::function<void(PlayingCard* card)> function);
	void setAtTrigger(std::function<void(PlayingCard* card)> function);
	void setAfterTrigger(std::function<void(PlayingCard* card)> function);


private:
	std::string name;
	std::string toolTip;
	int jokerGrade;
	int chip;
	int multiple;
};