#include "DeckSelectScene.h"

Deck DeckSelectScene::DeckInit()
{
	deck.InitCardMap();

	// new 해서 기본 덱, 일단 카드 덱 생성자로 생성
	// 덱 추가되면 if문으로 selectDeck 입력값에 따라 덱 다른걸로 할당
	int chip;
	int count = 0;
	out = false;
	std::string shape[4] = { "♠", "◆", "♣", "♥" };
	int secondDeckShape[4] = { 0, 0, 3, 3 };

	int key;
	key = _getch();
	switch (key)
	{
	case 49: // 기본 덱
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (j == 0)
				{
					chip = 14;
				}
				else
				{
					chip = j + 1;
				}
				deck.AddCard(new PlayingCard(shape[i], j + 1, chip, j + (i * 13)));
				count++;
			}
		}
		break;
	case 50: // 체크무늬 덱
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (j == 0)
				{
					chip = 14;
				}
				else
				{
					chip = j + 1;
				}
				deck.AddCard(new PlayingCard(shape[secondDeckShape[i]], j + 1, chip, j + (i * 13)));
				count++;
			}
		}
		break;
	case 51:
		// 나가기
		out = true;
		break;
	}
	deck.setLastNum(count);
	return deck;
}

void DeckSelectScene::SelectDeck()
{
	PrintDeckSelect();
	DeckInit();
	if (out) return;
	game.GameInit(deck);
}

void DeckSelectScene::PrintDeckSelect()const
{
	std::cout << "<덱 선택>" << std::endl;
	std::cout << "1. 기본 덱" << std::endl;
	std::cout << "2. 체크무늬 덱 - 스페이드와 하트로만 덱이 구성되어 있습니다. " << std::endl;
	std::cout << "3. 나가기";
}
