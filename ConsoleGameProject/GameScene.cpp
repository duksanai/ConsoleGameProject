#include "GameScene.h"

// ���� ���� �κ� �� �� ������ ��
void GameScene::GameInit(Deck deck)
{
	this->deck = deck;
	handList = new Hand();
	status = new PlayerStatus(4, 4, 8, 5);

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
	isEnter = false;
	jokerIndex = -1;
	

	// ��Ŀ �׽�Ʈ��
	InitJoker();

	GameStart();
}

void GameScene::InitJoker()
{
	int* pMul = &multiple;
	int* pChip = &chip;
#pragma region �Ϲ� ��Ŀ
	// 16��
	PushJoker("��Ŀ", "+4�� ����� ȹ��", 0, "afterTrigger", [=](PlayingCard* card)
		{
			*pMul += 4;
			Sleep(300);
		});

	PushJoker("�λ��� ��Ŀ", "���̾Ƹ�� ���� ī�带 �÷����� ������ +3�� ��� ȹ��", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "��")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("���� ��Ŀ", "��Ʈ ���� ī�带 �÷����� ������ +3�� ��� ȹ��", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "��")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("�г��ϴ� ��Ŀ", "�����̵� ���� ī�带 �÷����� ������ ������ +3 ����� ȹ���մϴ�.", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "��")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("Ž�彺���� ��Ŀ", "Ŭ�� ���� ī�带 �÷����� ������ +3�� ��� ȹ��", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "��")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("������ ��Ŀ", "�÷����� �ڵ忡 Ʈ���� ���� �� +12 ����� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "Ʈ����");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 12;
				Sleep(300);
			}
		});

	PushJoker("��ģ ��Ŀ", "�÷����� �ڵ忡 ��ī�� ���� �� +20 ����� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "�� ī��");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 20;
				Sleep(300);
			}
		});

	PushJoker("���ų��� ��Ŀ", "�÷����� �ڵ忡 ��Ʈ����Ʈ ���� �� +12 ����� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "��Ʈ����Ʈ");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 12;
				Sleep(300);
			}
		});

	PushJoker("��¥ ��Ŀ", "�÷����� �ڵ忡 �÷��� ���� �� +10 ����� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "�÷���");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 10;
				Sleep(300);
			}
		});

	PushJoker("��Ȱ�� ��Ŀ", "�÷����� �ڵ忡 ��� ���� �� +50���� Ĩ�� ȹ��", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "�� ���");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 50;
				Sleep(300);
			}
		});

	PushJoker("�Ƕ��� ��Ŀ", "�÷����� �ڵ忡 Ʈ���� ���� �� Ĩ +100���� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "Ʈ����");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 100;
				Sleep(300);
			}
		});

	PushJoker("������ ��Ŀ", "�÷����� �ڵ忡 ��ī�� ���� �� Ĩ +150���� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "��ī��");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 150;
				Sleep(300);
			}
		});

	PushJoker("�⸸���� ��Ŀ", "�÷����� �ڵ忡 ��Ʈ����Ʈ ���� �� Ĩ +100���� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "��Ʈ����Ʈ");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 100;
				Sleep(300);
			}
		});

	PushJoker("������ ��Ŀ", "�÷����� �ڵ忡 �÷��� ���� �� Ĩ +80���� ȹ���մϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "�÷���");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 80;
				Sleep(300);
			}
		});

	PushJoker("�μ� ����", "+?? ���", 0, "afterTrigger", [pMul](PlayingCard* card)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(1, 23);

			*pMul += dist(gen);
			Sleep(300);
		});

	PushJoker("ĳ�����", "X3 ����� ȹ���մϴ�. ���� ���� �� 1/1000 Ȯ���� �� ī�尡 �ı��˴ϴ�.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 999);
			*pMul *= 3;
			if (dist(gen) == 999)
			{ 
				for (Joker* joker : myJokers)
				{
					if (joker->getName() == "ĳ�����")
					{
						myJokers.erase(remove(myJokers.begin(), myJokers.end(), joker), myJokers.end());
					}
				}
			}
			Sleep(300);
		});
#pragma endregion
#pragma region ��� ��Ŀ
	// 5��
	PushJoker("��Ŀ ���Ľ�", "�� ��Ŀ ���Ը��� X1 ����� ȹ���մϴ�. ��Ŀ ���ٽ��� �� �������� ����", 1, "afterTrigger", [=](PlayingCard* card)
		{
			int multi;
			multi = status->getJokerSlot() - myJokers.size() + 1;
			*pMul *= multi;
			Sleep(300);
		});
	PushJoker("�Ǻ���ġ", "���̽�, 2, 3, 5, 8�� �÷����� ������ ������ +8 ����� ȹ���մϴ�.", 1, "atTrigger", [=](PlayingCard* card)
		{
			if (card->getCardType().number == 1 ||
				card->getCardType().number == 2 ||
				card->getCardType().number == 3 ||
				card->getCardType().number == 5 ||
				card->getCardType().number == 8)
			{
				*pMul += 8;
				Sleep(300);
			}
		});
	PushJoker("���� ������", "�÷����� ������ ī�忡 Ĩ +4���� ���������� �߰��մϴ�.", 1, "atTrigger", [=](PlayingCard* card)
		{
			card->AddChips(4);
			Sleep(300);
		});
	PushJoker("���", "������ ������ �ڵ��� ��� X3 ����� ȹ���մϴ�.", 1, "afterTrigger", [=](PlayingCard* card)
		{
			if (handCount == 0)
			{
				*pMul *= 3;
			}
		});
	PushJoker("����", "��Ʈ ī�带 �÷��� ���� ��� ī�帶�� 1/3 Ȯ���� X2 ����� ȹ���մϴ�.", 1, "atTrigger", [=](PlayingCard* card)
		{
			if (card->getCardType().shape == "��")
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dist(0, 2);

				int gatcha = dist(gen);
				if (gatcha == 2)
				{
					*pMul *= 2;
					Sleep(300);
				}
			}
		});
#pragma endregion
#pragma region ���� ��Ŀ
	// 1��
	PushJoker("�߱� ī��", "�� ��� ��Ŀ���� X2 ����� ȹ���մϴ�.", 2, "afterTrigger", [=](PlayingCard* card)
		{
			for (Joker* joker : myJokers)
			{
				if (joker->getJokerGrade() == 1)
				{
					*pMul *= 2;
					Sleep(300);
				}
			}
		});
#pragma endregion

}

void GameScene::GameStart()
{
	MakeAntie();
	while (true)
	{
		system("cls");

		// ��Ƽ ���� ���
		cout << "<<��Ƽ: " << antie << ">>" << endl << endl;

		for (int i = 0; i < 3; i++)
		{
			stageInfo[i]->PrintStageInfo();
		}
		cout << "���� ����ε�: " << stageInfo[currentBlind]->getBlind() << endl;
		cout << endl;
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
				StartBlind(currentBlind);
				out = true;
				break;
			case 50:
				// ����ε� �ǳʶٱ�
				if (currentBlind != 2)
				{
					SkipBlind();
					out = true;
				}
				else
				{
					cout << "���� ����ε�� ��ŵ�� �Ұ����մϴ�!" << endl;
				}
				break;
			default:
				cout << "�ٽ� �Է��ϼ���. " << endl;
				break;
			}
		}
		
		if (currentBlind >= 2)
		{
			currentBlind = 0;
			antie++;
			MakeAntie();
		}
		else
		{
			currentBlind++;
		}

		// Ŭ���� ��Ƽ ���� ����
		if (antie > 8)
		{
			cout << "�����մϴ�! ��� ���带 Ŭ�����߽��ϴ�." << endl;
			break;
		}
	}
}

void GameScene::StartBlind(const int currentBlind)
{
	score = 0;
	cursorIndex = 0;
	rewardIndex = 0;
	jokerIndex = -1;
	deck.Shuffle();

	hand = status->getHand();
	handCount = status->getHandCount();
	discardCount = status->getDiscardCount();

	std::vector<int>().swap(rewardJokersIndex);
	RandomPickJoker();

	// ���� ī��Ʈ ��ŭ Ȥ�� ��������� �ѱ� �� ���� ī�带 �����ϰ� �����ϴ� �κ�
	while (true)
	{
		std::vector<PlayingCard*>().swap(selectedCard);
		std::vector<std::string>().swap(ranking);
		std::vector<PlayingCard*>().swap(bestHand);

		// �п� ī�� �߰�
		for (int i = handList->getHandSize(); i < hand; i++)
		{
			RefreshScreen(70);
			handList->AddCard(deck.PopCard());
		}

		chip = 0;
		multiple = 0;

		RefreshScreen(0);
		PickCards();
		// ���� �Ѱ�����
		if (score >= stageInfo[currentBlind]->getScoreDeadLine())
		{
			cout << "����ε� Ŭ����!" << endl;
			stageInfo[currentBlind]->setClear(true);
			deck.RestoreDeck();
			deck.ClearSelected();
			Sleep(1000);
			Reward();
			break;
		}
		// ���� Ƚ�� ���� �Ҹ�
		else if (handCount == 0)
		{
			system("cls");
			cout << "�й��߽��ϴ�..." << endl;
			break;
		}
	}
}

void GameScene::PrintGame() const
{
	cout << "<" << stageInfo[currentBlind]->getBlind() << ">" << endl;
	cout << "��ǥ ����: " << stageInfo[currentBlind]->getScoreDeadLine() << endl;
	cout << "Ĩ X ���: ";
	if (isEnter)
	{
		cout << chip << " X " << multiple;
	}
	else if (ranking.size() != 0)
	{
		cout << status->getHandRanking(ranking.back()).getChip() << " X " << status->getHandRanking(ranking.back()).getMultiple();
	}
	cout << endl;
	cout << score << endl;
	cout << "��ȿ ����: ";
	if (!selectedCard.empty())
	{
		cout << ranking.back();
	}
	cout << endl;
	cout << "<������ ��Ŀ> - " << status->getJokerSlot() << "����" << endl;
	if (myJokers.size() != 0)
	{
		for (int i = 0; i < myJokers.size(); i++)
		{
			if (i == jokerIndex)
			{
				cout << "�� ";
			}
			myJokers[i]->PrintJoker();
		}
	}
	for (int i = 0; i < status->getJokerSlot() - myJokers.size(); i++)
	{
		cout << endl;
	}

	cout << "<���� ī��>" << endl;
	int sCardX = 2;
	for (PlayingCard* card : bestHand)
	{
		card->PrintCard(sCardX, 16);
		sCardX += 22;
	}
	cout << endl;

	handList->PrintHand(2, 32);

	// Ŀ��
	gotoxy(cursorIndex * 22 + 11, 47);
	if (jokerIndex == -1)
	{
		cout << "��" << endl;
	}

	cout << endl;
	cout << "�ڵ�: " << handCount << "\t������: " << discardCount << endl;
	cout << endl;

	cout << "z - ����, x - ������" << endl;
	cout << "c - �׸� ����, v - ���� ����, d - �� ��ȸ" << endl;
	cout << "Enter - ����" << endl;
	cout << endl;
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
	cursorIndex = 0;
	std::vector<PlayingCard*>::iterator iter;
	iter = selectedCard.begin();
	while (true)
	{
		key = _getch();
		if (key == SPECIAL_KEY)
		{
			key = _getch();
			switch (key)
			{
			// ����
			case KEY_LEFT:
				if (cursorIndex > 0)
				{
					cursorIndex--;
				}
				break;
			//������
			case KEY_RIGHT:
				if (cursorIndex < handList->getHandSize() - 1)
				{
					cursorIndex++;
				}
				break;
			//����
			case KEY_UP:
				jokerIndex = 0;
				JokerPick();
				break;
			}
		}
		else
		{
			// ����Ű - ���� ��ư
			if (key == KEY_ENTER)
			{
				if (!selectedCard.empty())
				{
					// ī��, ��Ŀ Ʈ����
					isEnter = true;
					handCount--;
					Trigger();
					isEnter = false;
					// ������ ī����� ������ �߰�
					deck.UsedCards(selectedCard);
					// �п��� ������ ī�� ����
					handList->Discard(selectedCard);
					Sleep(1000);
					return;
				}
			}
			// ���� ��ư - z
			else if (key == 90 || key == 122)
			{
				// �̹� ������ ī�� ���� ���
				if (FindCard(handList->getCard(cursorIndex)))
				{
					handList->getCard(cursorIndex)->Select(false);
					selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), handList->getCard(cursorIndex)), selectedCard.end());
				}
				// ī�� ����, ���� ī�尡 5�庸�� ���� ����
				else if (selectedCard.size() < 5)
				{
					handList->getCard(cursorIndex)->Select(true);
					selectedCard.push_back(handList->getCard(cursorIndex));
				}
				// ���� �˻� �Լ�
				CheckRanking();
			}

			// ������ - x
			else if (key == 88 || key == 120)
			{
				if (discardCount > 0)
				{
					// ������ ī����� ������ �߰�
					deck.UsedCards(selectedCard);
					// �п��� ������ ī�� ����
					handList->Discard(selectedCard);
					discardCount--;
					return;
				}
			}

			// ���� ���� - c
			else if (key == 67 || key == 99)
			{
				handList->SortNum();
			}

			// �׸� ���� - v
			else if (key == 86 || key == 118)
			{
				handList->SortShape();
			}

			// �� ��ȸ - d
			else if (key == 68 || key == 100)
			{
				deck.CountCards();
				deck.PrintDeck();
			}
		}
		RefreshScreen(0);
	}
}

void GameScene::JokerPick()
{
	std::vector<int> pickedJokerIndex;

	int key;
	while (true)
	{
		RefreshScreen(0);
		key = _getch();
		if (key == SPECIAL_KEY)
		{
			key = _getch();
			switch (key)
			{
			case KEY_UP:
				if (jokerIndex > 0)
				{
					jokerIndex -= 1;
				}
				break;
			case KEY_DOWN:
				jokerIndex += 1;
				if (jokerIndex > myJokers.size() - 1)
				{
					jokerIndex = -1;
					return;
				}
				break;
			}
		}
		else
		{
			// z - ��Ŀ ����
			if (key == 90 || key == 122)
			{
				pickedJokerIndex.push_back(jokerIndex);
				if (pickedJokerIndex.size() == 2)
				{
					std::swap(myJokers[pickedJokerIndex[0]], myJokers[pickedJokerIndex[1]]);
				}
			}
		}
	}
	
}

void GameScene::Trigger()
{
	// ȭ�� ����
	RefreshScreen(0);
	// �ֻ��� ���� ��������
	chip = status->getHandRanking(ranking.back()).getChip();
	multiple = status->getHandRanking(ranking.back()).getMultiple();
	
	// Ʈ���� �ϱ�
	for (PlayingCard*& card : bestHand)
	{
		// ������ ī�� Ĩ ���ϱ�
		chip += card->getChip();

		RefreshScreen(300);

		// Ʈ������ �� ��Ŀ �����Ƽ
		for (Joker*& joker : myJokers)
		{
			joker->AtTrigger(card);
			RefreshScreen(0);
		}
	}

	// Ʈ���� �� ��Ŀ �����Ƽ
	for (Joker*& joker : myJokers)
	{
		joker->AfterTrigger(nullptr);
		RefreshScreen(0);
	}

	score += chip * multiple;
	RefreshScreen(300);
}

// ������ üũ�ϴ� �Լ�
void GameScene::CheckRanking()
{
	// ���� ���͸� ���� �����
	std::vector<std::string>().swap(ranking);
	std::vector<PlayingCard*>().swap(bestHand);

	// ���õ� ī�� ���͸� ����������. ��Ʈ����Ʈ�� �˻��Ϸ��� ���� ������ �����ؾ� �Ѵ�. 
	std::vector<PlayingCard*> sortedCards = selectedCard;
	std::sort(sortedCards.begin(), sortedCards.end(), [](const PlayingCard* a, const PlayingCard* b)
		{
			return *a < *b;
		});

	std::map<int, std::vector<PlayingCard*>> numberCount;
	std::map<std::string, std::vector<PlayingCard*>> shapeCount;
	int cardCount = sortedCards.size();

	for (auto& card : sortedCards) {
		numberCount[card->getCardType().number].push_back(card);
		shapeCount[card->getCardType().shape].push_back(card);
	}

	bool isFourCard = false, isStraight = false, isFlush = false, isTriple = false, isPair = false;
	int straitCount = 0;

	// ���� üũ��
	if (sortedCards.size() > 0)
	{
		ranking.push_back("����");
	}

	// ��� üũ��
	int countPair = 0;
	for (auto& pair : numberCount)
	{
		if (pair.second.size() == 2)
		{
			isPair = true;
			for (int i = 0; i < pair.second.size(); i++)
			{
				bestHand.push_back(pair.second[i]);
			}
			countPair++;
		}
	}

	// Ʈ���� üũ��
	for (auto& pair : numberCount)
	{
		if (pair.second.size() == 3)
		{
			isTriple = true;
			for (int i = 0; i < pair.second.size(); i++)
			{
				bestHand.push_back(pair.second[i]);
			}
		}
	}


	// ��Ʈ����Ʈ üũ��
	if (cardCount == 5)
	{
		for (int i = 0; i < sortedCards.size() - 1; i++)
		{
			if (sortedCards[i]->getCardType().number - 1 == sortedCards[i + 1]->getCardType().number)
			{
				straitCount++;
			}
		}
		if (straitCount == 4)
		{
			bestHand = selectedCard;
			isStraight = true;
		}
	}

	// �÷��� üũ��
	if (shapeCount.size() == 1 && cardCount == 5)
	{
		bestHand = selectedCard;
		isFlush = true;
	}

	// �� ī�� üũ��
	for (auto& pair : numberCount)
	{
		if (pair.second.size() == 4)
		{
			bestHand = pair.second;
			isFourCard = true;
		}
	}

	// if������ ���� �켱������ ���� ������ �������� ����
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

	// �� ���
	if (isPair)
	{
		ranking.push_back("�� ���");
	}

	// �� ���
	if (countPair == 2)
	{
		ranking.push_back("�� ���");
	}

	// Ʈ����
	if (isTriple)
	{
		ranking.push_back("Ʈ����");
	}

	// ��Ʈ����Ʈ
	if (isStraight)
	{
		ranking.push_back("��Ʈ����Ʈ");
	}

	// �÷���
	if (isFlush)
	{
		ranking.push_back("�÷���");
	}

	// Ǯ�Ͽ콺
	if (isTriple && isPair)
	{
		bestHand = selectedCard;
		ranking.push_back("Ǯ�Ͽ콺");
	}

	// �� ī��
	if (isFourCard)
	{
		ranking.push_back("�� ī��");
	}

	// ��Ʈ����Ʈ �÷���
	if (isStraight && (shapeCount.size() == 1))
	{
		ranking.push_back("��Ʈ����Ʈ �÷���");
	}

	// ���̺� ī��
	if (cardCount == 5 && numberCount.size() == 1)
	{
		ranking.push_back("���̺� ī��");
		bestHand = selectedCard;
	}

	// �÷��� �Ͽ콺
	if ((cardCount == 5 && shapeCount.size() == 1) && (isTriple && isPair))
	{
		ranking.push_back("�÷��� �Ͽ콺");
		bestHand = selectedCard;
	}

	// �÷��� ���̺�
	if ((numberCount.size() == 1 && shapeCount.size() == 1) && cardCount == 5)
	{
		ranking.push_back("�÷��� ���̺�");
		bestHand = selectedCard;
	}

	// �ƹ��͵� �������� ������ ����ī�常 �ֱ�
	if (sortedCards.size() > 0 && !isFourCard && !isStraight && !isFlush && !isTriple && !isPair)
	{
		bestHand.push_back(sortedCards[0]);
	}
}

void GameScene::PrintRewards()
{
	int x = 20, y = 10;
	gotoxy(x, y - 1);
	cout << "���������æ���������������������������������������������������������������������������������������������������������������������������������������������������������������������";
	for (int i = 0; i < rewardJokersIndex.size(); i++, y++)
	{
		gotoxy(x, y);
		cout << "�� ";
		if (rewardIndex == i)
		{
			cout << "�� ";
		}
		jokers[rewardJokersIndex[i]]->PrintJoker();
		gotoxy(x + 92, y);
		cout << "��";
		gotoxy(x, y + 1);
	}
	cout << "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
	y++;
	if (myJokers.size() != 0)
	{
		for (int i = 0; i < myJokers.size(); i++, y++)
		{
			gotoxy(x, y);
			cout << "�� ";
			if (jokerIndex == i)
			{
				cout << "�� ";
			}
			myJokers[i]->PrintJoker();
			gotoxy(x + 92, y);
			cout << "��";
		}
	}
	gotoxy(x, y);
	cout << "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
}

void GameScene::Reward()
{
	int key;
	while (true)
	{
		PrintRewards();
		key = _getch();
		if (key == SPECIAL_KEY)
		{
			key = _getch();
			switch (key)
			{
			// Ŀ�� �̵�
			case KEY_UP:
				if (rewardIndex > 0)
				{
					rewardIndex--;
				}
				break;
			case KEY_DOWN:
				if (rewardIndex < rewardJokersIndex.size() - 1)
				{
					rewardIndex++;
				}
				break;
			}
		}
		else
		{
			// ��Ŀ ���� - zŰ
			if (key == 90 || key == 122)
			{
				// �ִ� �������� ���� �ʾ��� ��� - �߰�
				if (myJokers.size() < status->getJokerSlot())
				{
					myJokers.push_back(jokers[rewardJokersIndex[rewardIndex]]);
				}
				// �ִ� �������� ��� - ��ü
				else
				{
					std::swap(jokers[rewardJokersIndex[rewardIndex]], myJokers[ChangeJoker()]);
				}
				return;
			}
		}
	}
}

void GameScene::RandomPickJoker()
{
	// Ŀ�� -> 70��, ��Ŀ�� -> 20��, ���� -> 10��
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 9);
	std::uniform_int_distribution<> common(0, 15);
	std::uniform_int_distribution<> uncommon(16, 20);

	int gatcha;
	for (int i = 0; i < 3; i++)
	{
		gatcha = dist(gen);

		// Ŀ��
		if (gatcha < 7)
		{
			rewardJokersIndex.push_back(common(gen));
		}
		else if (gatcha < 9)
		{
			rewardJokersIndex.push_back(uncommon(gen));
		}
		else
		{
			rewardJokersIndex.push_back(21);
		}
	}
	

}

int GameScene::ChangeJoker()
{
	jokerIndex = 0;
	int key;
	while (true)
	{
		PrintRewards();
		key = _getch();
		if (key == SPECIAL_KEY)
		{
			key = _getch();
			switch (key)
			{
				// Ŀ�� �̵�
			case KEY_UP:
				if (jokerIndex > 0)
				{
					jokerIndex--;
				}
				break;
			case KEY_DOWN:
				if (jokerIndex < myJokers.size() - 1)
				{
					jokerIndex++;
				}
				break;
			}
		}
		else
		{
			// ��Ŀ ���� - zŰ
			if (key == 90 || key == 122)
			{
				return jokerIndex;
			}
		}
	}
}

void GameScene::PushJoker(const std::string& name, const std::string& toolTip, const int grade, const std::string& abilityType, std::function<void(PlayingCard* card)> function)
{
	Joker* joker = new Joker(name, toolTip, grade);
	if (abilityType == "passive")
	{
		joker->PassiveAbility = function;
	}
	else if (abilityType == "atTrigger")
	{
		joker->AtTrigger = function;
	}
	else if (abilityType == "afterTrigger")
	{
		joker->AfterTrigger = function;
	}
	jokers.push_back(joker);
}

void GameScene::PrintResult() const
{
}

void GameScene::SkipBlind()
{
	
}

bool GameScene::FindCard(PlayingCard* card)
{
	if (find(selectedCard.begin(), selectedCard.end(), card) == selectedCard.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameScene::RefreshScreen(int sleep)
{
	system("cls");
	PrintGame();
	Sleep(sleep);
}
