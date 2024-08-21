#pragma once

#include <conio.h>
#include <algorithm>
#include <Windows.h>

#include "Deck.h"
#include "PlayerStatus.h"
#include "Hand.h"
#include "StageInfo.h"
#include "Joker.h"

using std::cout;
using std::cin;
using std::endl;

class GameScene
{
public:
	//~GameScene();
	void GameInit(Deck deck);
private:
	void InitJoker();
	void GameStart();
	void StartBlind(const int currentBlind);
	void PrintGame()const;
	void PrintResult()const;
	void SkipBlind();
	void MakeAntie();
	void PickCards();
	void Trigger();
	void CheckRanking();
	void PushJoker(const std::string& name, const std::string& toolTip, const int grade, const std::string& abilityType, std::function<void(PlayingCard* card)> function);
	bool FindCard(PlayingCard* card);

	void RefreshScreen(int sleep);

	PlayerStatus* status;
	std::vector<std::string> ranking;
	StageInfo* stageInfo[3];
	Deck deck;
	Hand* handList;
	std::vector<Joker*> jokers;
	std::vector<Joker*> myJokers;
	std::vector<PlayingCard*> selectedCard;
	std::vector<PlayingCard*> bestHand;
	int deadLine[9];
	int currentBlind;
	int round;
	int antie;
	int chip;
	int multiple;
	int score;
	int hand;
	int handCount;
	int discardCount;
	int cursorIndex;
	bool isEnter;
};

