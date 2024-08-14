#include "PlayerStatus.h"

PlayerStatus::PlayerStatus(int handCount, int discardCount, int hand)
	:handCount(handCount), discardCount(discardCount), hand(hand)
{
	InitHandRanking();
}

void PlayerStatus::PrintHandRanking() const
{
	std::cout << "<족보>" << std::endl;
	std::cout << "이름\t\t레벨\t칩\t배수" << std::endl;
	for (auto& pair : handRankings)
	{
		std::cout << pair.first << "\t\t";
		std::cout << pair.second.getLevel() << "\t\t";
		std::cout << pair.second.getChip() << "\t\t";
		std::cout << pair.second.getMultiple() << std::endl;
	}
}

void PlayerStatus::HandLevelUp(const std::string& name, const int chip, const int multiple)
{
	handRankings[name].LevelUp(1, chip, multiple);
}

void PlayerStatus::HandLevelDown(const std::string& name, const int chip, const int multiple)
{
	if (handRankings[name].getLevel() == 1)
	{
		std::cout << "최소 레벨에 도달했습니다. " << std::endl;
	}
	else
	{
		handRankings[name].LevelDown(1, chip, multiple);
	}
}

void PlayerStatus::HandCountPlus(const int num)
{
	handCount += num;
	if (handCount <= 1)
	{
		std::cout << "더 이상 내려가지 않습니다. " << std::endl;
		handCount = 1;
	}
}

void PlayerStatus::DiscardCountPlus(const int num)
{
	discardCount += num;
	if (discardCount <= 0)
	{
		std::cout << "더 이상 내려가지 않습니다. " << std::endl;
		discardCount = 0;
	}
}

void PlayerStatus::HandPlus(const int num)
{
	hand += num;
	if (hand <= 1)
	{
		std::cout << "더 이상 내려가지 않습니다. " << std::endl;
		hand = 1;
	}
}

void PlayerStatus::InitHandRanking()
{
	handRankings.insert(std::make_pair("하이", HandRanking(1, 5, 1)));
	handRankings.insert(std::make_pair("페어", HandRanking(1, 10, 2)));
	handRankings.insert(std::make_pair("투 페어", HandRanking(1, 20, 2)));
	handRankings.insert(std::make_pair("트리플", HandRanking(1, 30, 3)));
	handRankings.insert(std::make_pair("스트레이트", HandRanking(1, 30, 4)));
	handRankings.insert(std::make_pair("플러시", HandRanking(1, 35, 4)));
	handRankings.insert(std::make_pair("풀하우스", HandRanking(1, 40, 4)));
	handRankings.insert(std::make_pair("포 카드", HandRanking(1, 60, 7)));
	handRankings.insert(std::make_pair("스트레이트", HandRanking(1, 100, 8)));
	handRankings.insert(std::make_pair("파이브 카드", HandRanking(1, 120, 12)));
	handRankings.insert(std::make_pair("플러시 하우스", HandRanking(1, 140, 14)));
	handRankings.insert(std::make_pair("플러시 파이브", HandRanking(1, 200, 16)));
}
