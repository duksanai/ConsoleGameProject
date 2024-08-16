#pragma once

#include <conio.h>

#include "Deck.h"
#include "PlayerStatus.h"
#include "Hand.h"
#include "StageInfo.h"

using std::cout;
using std::cin;
using std::endl;

class GameScene
{
public:
	void GameInit(Deck deck);
private:
	void GameStart();
	void StartBlind();
	void PrintGame()const;
	void PrintResult()const;
	void SkipBlind();
	void MakeAntie();
	void PickCards();

	PlayerStatus* status;
	StageInfo* stageInfo[3];
	Deck deck;
	Hand hand;
	std::vector<PlayingCard*> selectedCard;
	int deadLine[9];
	int currentBlind;
	int round;
	int antie;
	int chip;
	int multiple;
	int score;
};

