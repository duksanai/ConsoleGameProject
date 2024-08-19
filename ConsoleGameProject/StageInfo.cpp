#include "StageInfo.h"

StageInfo::StageInfo(const std::string& blind, const int antie, const int scoreDeadLine)
	:blind(blind), antie(antie), scoreDeadLine(scoreDeadLine)
{
	isClear = false;
}

void StageInfo::PrintStageInfo() const
{
	std::cout << "<" << blind << ">";
	if (isClear)
	{
		std::cout << " - Ŭ����";
	}
	std::cout << std::endl;
	std::cout << "��ǥ ����: " << scoreDeadLine << std::endl;
	std::cout << "=============================" << std::endl;
}

int StageInfo::getAntie() const
{
	return antie;
}

std::string StageInfo::getBlind() const
{
	return blind;
}

int StageInfo::getScoreDeadLine() const
{
	return scoreDeadLine;
}

void StageInfo::setClear(bool result)
{
	isClear = result;
}
