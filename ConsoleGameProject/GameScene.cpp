#include "GameScene.h"

// 게임 생성 부분 좀 더 구상할 것
void GameScene::GameInit(Deck deck)
{
	this->deck = deck;
	status = new PlayerStatus(4, 4, 8);
	stageInfo = new StageInfo("스몰 블라인드", 1, 1, 300);
	GameStart();
}

void GameScene::GameStart()
{

}

void GameScene::StartBlind()
{

}

