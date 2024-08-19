#pragma once

#include <conio.h>
#include <algorithm>

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
	void StartBlind();
	void PrintGame()const;
	void PrintResult()const;
	void SkipBlind();
	void MakeAntie();
	void PickCards();
	void Trigger();
	void CheckRanking();
	void PushJoker(const std::string& name, const std::string& toolTip, const std::string& abilityType, std::function<void(PlayingCard* card)> function);
	bool FindCard(PlayingCard* card);

	PlayerStatus* status;
	std::vector<std::string> ranking;
	StageInfo* stageInfo[3];
	Deck deck;
	Hand* handList;
	std::vector<Joker*> myJokers;
	std::vector<PlayingCard*> selectedCard;
	int deadLine[9];
	int currentBlind;
	int round;
	int antie;
	int chip;
	int multiple;
	int score;
};

