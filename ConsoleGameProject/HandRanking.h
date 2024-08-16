#pragma once
class HandRanking
{
public:
	HandRanking() { chip = 0; multiple = 0; level = 0; }
	HandRanking(const int chip, const int multiple, const int level);
public:
	void LevelUp(int level, int chip, int multiple);
	void LevelDown(int level, int chip, int multiple);
	int getChip()const;
	int getMultiple()const;
	int getLevel()const;
private:
	int chip;
	int multiple;
	int level;
};

