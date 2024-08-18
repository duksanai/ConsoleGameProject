#include "GameScene.h"

// ���� ���� �κ� �� �� ������ ��
void GameScene::GameInit(Deck deck)
{
	this->deck = deck;

	status = new PlayerStatus(4, 4, 8);

	deadLine[0] = 100;
	deadLine[1] = 300;
	deadLine[2] = 800;
	deadLine[3] = 2800;
	deadLine[4] = 6000;
	deadLine[5] = 11000;
	deadLine[6] = 20000;
	deadLine[7] = 35000;
	deadLine[8] = 50000;

	currentBlind = 0;
	round = 1;
	antie = 1;
	score = 0;

	GameStart();
}

void GameScene::GameStart()
{
	while (true)
	{
		system("cls");
		MakeAntie();

		// ��Ƽ ���� ���
		cout << "<<��Ƽ: " << antie << ">>" << endl << endl;

		for (int i = 0; i < 3; i++)
		{
			stageInfo[i]->PrintStageInfo();
		}

		// ����ε� ����, �ǳʶٱ� ����
		int key;
		bool out = false;
		while (!out)
		{
			cout << "1. ����" << endl;
			cout << "2. �ǳʶٱ�" << endl;

			key = _getch();
			switch (key)
			{
			case 49:
				// ����
				StartBlind();
				out = true;
				break;
			case 50:
				// ����ε� �ǳʶٱ�
				SkipBlind();
				out = true;
				break;
			default:
				cout << "�ٽ� �Է��ϼ���. " << endl;
				break;
			}
		}
		

		if (currentBlind > 2)
		{
			currentBlind = 0;
			antie++;
		}

		if (antie > 8)
		{
			system("cls");
			PrintResult();
			break;
		}
	}
}

void GameScene::StartBlind()
{
	int handCount;
	int discardCount;
	while (true)
	{
		deck.Shuffle();

		handCount = status->getHandCount();
		discardCount = status->getDiscardCount();

		// �п� ī�� �߰�
		for (int i = 0; i < handCount; i++)
		{
			hand.AddCard(deck.PopCard());
		}

		// ���� ī��Ʈ ��ŭ Ȥ�� ��������� �ѱ� �� ���� ī�带 �����ϰ� �����ϴ� �κ�
		while (true)
		{
			PrintGame();
			PickCards();
		}




		if (handCount < 0)
		{
			break;
		}
	}
}

void GameScene::PrintGame() const
{
	cout << "<" << stageInfo[currentBlind]->getBlind() << ">" << endl;
	cout << "��ǥ ����: " << stageInfo[currentBlind]->getScoreDeadLine() << endl;
}

void GameScene::MakeAntie()
{
	stageInfo[0] = new StageInfo("���� ����ε�", antie, deadLine[antie]);
	stageInfo[1] = new StageInfo("�� ����ε�", antie, deadLine[antie] * 1.5);
	stageInfo[2] = new StageInfo("���� ����ε�", antie, deadLine[antie] * 2);
}

void GameScene::PickCards()
{
	int key;
	int index = 0;
	std::vector<PlayingCard*>::iterator iter;
	iter = selectedCard.begin();
	while (true)
	{
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			// ����
			case 75:
				if (index > 0)
				{
					// ����
					index--;
				}
				break;
			//������
			case 77:
				if (index < hand.getHandSize())
				{
					index++;
				}
				break;
			}
		}
		else
		{
			// ����Ű - ���� ��ư
			if (key == 13)
			{
				Trigger();

				return;
			}
			// ���� ��ư - z
			else if (key == 90 || key == 122)
			{
				// ���� ���õ� ī�尡 5�庸�� ������ 
				if (selectedCard.size() < 5)
				{
					// �̹� ������ ī�� ���� ���
					if (hand.FindCard(hand.getCard(index)))
					{
						selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), iter[index]), selectedCard.end());
					}
					// ī�� ����
					else
					{
						selectedCard.push_back(hand.getCard(index));
					}
				}
				// ���� �˻� �Լ�
				CheckRanking();
			}
		}
		PrintGame();
	}
}

void GameScene::Trigger()
{
	// ȭ�� ����
	PrintGame();
	// Ʈ���� �ϱ�
	for (auto& card : selectedCard)
	{
		// ������ ī�� Ĩ ���ϱ�


		// ��Ŀ ī�� �˻� -> ��Ŀ �ɷ� Ʈ����

	}
}

// ������ üũ�ϴ� �Լ�
void GameScene::CheckRanking()
{
	// ���� ���͸� ���� �����
	std::vector<std::string>().swap(ranking);

	// ���õ� ī�� ���͸� ����������. ��Ʈ����Ʈ�� �˻��Ϸ��� ���� ������ �����ؾ� �Ѵ�. 
	std::vector<PlayingCard*> sortedCards = selectedCard;
	std::sort(sortedCards.begin(), sortedCards.end(), [](const PlayingCard* a, const PlayingCard* b)
		{
			return *a < *b;
		});

	std::map<int, int> numberCount;
	std::map<std::string, int> shapeCount;

	// if������ ���� �켱������ ���� �������� ������� ����
	/*
	���� ��Ģ
	���� ī�� :			���ڰ� ���� ���� ī��. 5��1
	��� :				���� ���� 1��. 10��2
	�� ��� :			���� ���� 2��. 20��2
	Ʈ���� :				���� ���� 3���� ����. 30��3
	��Ʈ����Ʈ :			���ӵ� ���� 5��. K-A-2�� �����ϴ� �� ����� ��Ʈ����Ʈ�� �������� �ʴ´�. 30��4
	�÷��� :				���� ���� 5��. 35��4
	Ǯ�Ͽ콺 :			���� ���� 3���� ������ ���� ���� 1������ �̷���� 5��. 40��4
	�� ī�� :			���� ���� 4���� ����.60��7
	��Ʈ����Ʈ �÷��� :	������ ���� ���ӵ� ���� 5��. 100��8
	���̺� ī�� :		��ũ�� ������ ī�� 5��. 120*12
	�÷��� �Ͽ콺 :		Ǯ�Ͽ콺�� �÷��ø� ���ÿ� ����. 140*14
	�÷��� ���̺� :		���� ����� ��ũ�� �� ���̺� ī��. 200*16
	*/
	// �÷��� ���̺�
	// �ʹ� �ȶ��ö� ���� �� ����..
	
}

void GameScene::PrintResult() const
{
}

void GameScene::SkipBlind()
{
}

