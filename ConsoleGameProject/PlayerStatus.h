#pragma once
#include <map>
#include <iostream>
#include "HandRanking.h"

class PlayerStatus
{
public:
	PlayerStatus();
	PlayerStatus(int handCount, int discardCount, int hand);
public:
	void PrintHandRanking()const;
	HandRanking getHandRanking(const std::string& rank)const;
	void HandLevelUp(const std::string& name, const int chip, const int multiple);
	void HandLevelDown(const std::string& name, const int chip, const int multiple);
	void HandCountPlus(const int num);
	void DiscardCountPlus(const int num);
	void HandPlus(const int num);
	void InitHandRanking();
	int getHand()const;
	int getHandCount()const;
	int getDiscardCount()const;
private:
	std::map<std::string, HandRanking> handRankings;
	int handCount;
	int discardCount;
	int hand;
};

