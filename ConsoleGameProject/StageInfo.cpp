#include "StageInfo.h"

StageInfo::StageInfo(const std::string& blind, const int antie, const int round, const int scoreDeadLine)
	:blind(blind), antie(antie), round(round), scoreDeadLine(scoreDeadLine)
{
}

void StageInfo::PrintStageInfo() const
{
	std::cout << "=============================" << std::endl;
	std::cout << "<" << blind << ">" << std::endl;
	std::cout << "��Ƽ: " << antie << std::endl;
	std::cout << "����: " << round << std::endl;
	std::cout << "��ǥ ����" << scoreDeadLine << std::endl;
	std::cout << "=============================" << std::endl;
}
