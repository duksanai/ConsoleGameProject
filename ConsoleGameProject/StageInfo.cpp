#include "StageInfo.h"

StageInfo::StageInfo(const std::string& blind, const int antie, const int round, const int scoreDeadLine)
	:blind(blind), antie(antie), round(round), scoreDeadLine(scoreDeadLine)
{
}

void StageInfo::PrintStageInfo() const
{
	std::cout << "=============================" << std::endl;
	std::cout << "<" << blind << ">" << std::endl;
	std::cout << "앤티: " << antie << std::endl;
	std::cout << "라운드: " << round << std::endl;
	std::cout << "목표 점수" << scoreDeadLine << std::endl;
	std::cout << "=============================" << std::endl;
}
