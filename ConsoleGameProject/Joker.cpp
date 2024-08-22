#include "Joker.h"

Joker::Joker(const std::string& name, const std::string& toolTip, const int jokerGrade)
	:name(name), toolTip(toolTip), jokerGrade(jokerGrade)
{
	chip = 0;
	multiple = 0;
}

void Joker::PrintJoker() const
{
	if (jokerGrade == static_cast<int>(grade::UNCOMMON))
	{
		TextColor(GREEN, BLACK);
	}
	else if (jokerGrade == static_cast<int>(grade::RARE))
	{
		TextColor(LIGHTBLUE, BLACK);
	}
	cout << name << ": " << toolTip << endl;
	TextColor(WHITE, BLACK);
}

std::string Joker::getName()const
{
	return name;
}

std::string Joker::getToolTip()const
{
	return toolTip;
}

int Joker::getJokerGrade() const
{
	return jokerGrade;
}

void Joker::addChips(int chip)
{
	this->chip += chip;
}

void Joker::setPassiveAbility(std::function<void(PlayingCard* card)> function)
{
	PassiveAbility = function;
}

void Joker::setAtTrigger(std::function<void(PlayingCard* card)> function)
{
	AtTrigger = function;
}

void Joker::setAfterTrigger(std::function<void(PlayingCard* card)> function)
{
	AfterTrigger = function;
}


