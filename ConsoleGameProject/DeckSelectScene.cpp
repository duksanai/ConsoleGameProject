#include "DeckSelectScene.h"

Deck DeckSelectScene::DeckInit(int inputNum)
{
	// new 해서 기본 덱, 일단 카드 덱 생성자로 생성
	// 덱 추가되면 if문으로 selectDeck 입력값에 따라 덱 다른걸로 할당
}

void DeckSelectScene::SelectDeck()
{
	int key;
	key = _getch();
	switch (key)
	{
	case 49:
		game.GameInit(DeckInit(1));
		break;
	case 50:
		game.GameInit(DeckInit(2));
		break;
	}
	game.Start();
}
