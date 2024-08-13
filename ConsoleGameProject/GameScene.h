#pragma once
#include <list>

#include "Deck.h"
#include "PlayerStatus.h"
#include "Hand.h"
#include "StageInfo.h"

class GameScene
{
public:
	void GameInit(Deck deck);
	void Start();
	void Cursor();
private:
	PlayerStatus status;
	Deck deck;
	Hand hand;
	StageInfo stageInfo;
	std::list<PlayingCard*> selectedCard;
};

