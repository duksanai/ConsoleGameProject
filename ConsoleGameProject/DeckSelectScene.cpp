#include "DeckSelectScene.h"

Deck DeckSelectScene::DeckInit()
{
	// new �ؼ� �⺻ ��, �ϴ� ī�� �� �����ڷ� ����
	// �� �߰��Ǹ� if������ selectDeck �Է°��� ���� �� �ٸ��ɷ� �Ҵ�
	int chip;
	std::string shape[4] = { "��, ��, ��, ��" };

	int key;
	key = _getch();
	switch (key)
	{
	case 49: // �⺻ ��
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (j == 0)
				{
					chip = 11;
				}
				else if (j >= 10)
				{
					chip = 10;
				}
				else
				{
					chip = j + 1;
				}
				deck.AddCard(new PlayingCard(shape[i], j + 1, chip));
			}
		}
		break;
	case 50: // üũ���� ��
		int checkShape[4] = { 0, 0, 3, 3 };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (j == 0)
				{
					chip = 11;
				}
				else if (j >= 10)
				{
					chip = 10;
				}
				else
				{
					chip = j + 1;
				}
				deck.AddCard(new PlayingCard(shape[checkShape[i]], j + 1, chip));
			}
		}
		break;
	}
	return deck;
}

void DeckSelectScene::SelectDeck()
{
	PrintDeckSelect();
	DeckInit();
	game.GameInit(deck);
}

void DeckSelectScene::PrintDeckSelect()const
{
	std::cout << "�� ����\n1. �⺻ ��\n2. üũ���� �� - �����̵�� ��Ʈ�θ� ���� �����Ǿ� �ֽ��ϴ�. " << std::endl;
}
