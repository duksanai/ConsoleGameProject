#pragma once
#include <map>
#include <iostream>
#include "HandRanking.h"

class PlayerStatus
{
public:
	void PrintHandRanking()const;
	void HandLevelUp(const int chip, const int multiple);
	void HandCountPlus(const int num);
	void DiscardCountPlus(const int num);
	void HandPlus(const int num);
private:
	std::map<std::string, HandRanking> handRanking;
	int handCount;
	int discardCount;
	int hand;
};

