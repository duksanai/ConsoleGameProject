#include "GameScene.h"

// ���� ���� �κ� �� �� ������ ��
void GameScene::GameInit(Deck deck)
{
	this->deck = deck;
	status = new PlayerStatus(4, 4, 8);
	stageInfo = new StageInfo("���� ����ε�", 1, 1, 300);
	GameStart();
}

void GameScene::GameStart()
{

}

void GameScene::StartBlind()
{

}

