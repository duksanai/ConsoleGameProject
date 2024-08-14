#pragma once
#include <iostream>

class StageInfo
{
public:
	StageInfo(const std::string& blind, const int antie, const int round, const int scoreDeadLine);
public:
	void PrintStageInfo()const;
private:
	std::string blind;
	int antie;
	int round;
	int scoreDeadLine;
};

