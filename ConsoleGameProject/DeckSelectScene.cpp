#include "DeckSelectScene.h"

Deck DeckSelectScene::DeckInit()
{
	deck.InitCardMap();

	// new �ؼ� �⺻ ��, �ϴ� ī�� �� �����ڷ� ����
	// �� �߰��Ǹ� if������ selectDeck �Է°��� ���� �� �ٸ��ɷ� �Ҵ�
	int chip;
	int count = 0;
	out = false;
	std::string shape[4] = { "��", "��", "��", "��" };
	int secondDeckShape[4] = { 0, 0, 3, 3 };

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
	case 50: // üũ���� ��
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
		// ������
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
	std::cout << "<�� ����>" << std::endl;
	std::cout << "1. �⺻ ��" << std::endl;
	std::cout << "2. üũ���� �� - �����̵�� ��Ʈ�θ� ���� �����Ǿ� �ֽ��ϴ�. " << std::endl;
	std::cout << "3. ������";
}
