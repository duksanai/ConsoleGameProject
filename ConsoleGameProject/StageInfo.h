#pragma once
#include <iostream>

class StageInfo
{
public:
	StageInfo(const std::string& blind, const int antie, const int scoreDeadLine);
public:
	void PrintStageInfo()const;
	int getAntie()const;
	std::string getBlind()const;
	int getScoreDeadLine()const;
	void setClear(bool result);
private:
	std::string blind;
	int antie;
	int scoreDeadLine;
	bool isClear;
};

