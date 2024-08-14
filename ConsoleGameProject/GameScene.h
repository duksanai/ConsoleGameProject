#pragma once

#include "Deck.h"
#include "PlayerStatus.h"
#include "Hand.h"
#include "StageInfo.h"

class GameScene
{
public:
	void GameInit(Deck deck);
	void GameStart();
	void StartBlind();
	void Cursor();
private:
	PlayerStatus* status;
	StageInfo* stageInfo;
	Deck deck;
	Hand hand;
	std::vector<PlayingCard*> selectedCard;
};

