#include "DeckSelectScene.h"

Deck DeckSelectScene::DeckInit(int inputNum)
{
	// new �ؼ� �⺻ ��, �ϴ� ī�� �� �����ڷ� ����
	// �� �߰��Ǹ� if������ selectDeck �Է°��� ���� �� �ٸ��ɷ� �Ҵ�
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
