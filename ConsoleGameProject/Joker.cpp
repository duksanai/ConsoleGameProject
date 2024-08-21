#include "Joker.h"

Joker::Joker(const std::string& name, const std::string& toolTip)
	:name(name), toolTip(toolTip)
{
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

std::string Joker::getName()
{
	return name;
}

std::string Joker::getToolTip()
{
	return toolTip;
}


