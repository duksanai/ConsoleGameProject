#include "HandRanking.h"

HandRanking::HandRanking(const int chip, const int multiple, const int level)
	:chip(chip), multiple(multiple), level(level)
{
}

void HandRanking::LevelUp(int level, int chip, int multiple)
{
	this->level += level;
	this->chip += chip;
	this->multiple += multiple;
}

void HandRanking::LevelDown(int level, int chip, int multiple)
{
	if (level > 1)
	{
		this->level -= level;
		this->chip -= chip;
		this->multiple -= multiple;
	}
}

int HandRanking::getChip()const
{
	return chip;
}

int HandRanking::getMultiple()const
{
	return multiple;
}

int HandRanking::getLevel()const
{
	return level;
}
