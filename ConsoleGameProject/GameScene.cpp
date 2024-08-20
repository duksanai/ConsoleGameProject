#include "GameScene.h"

// ���� ���� �κ� �� �� ������ ��
void GameScene::GameInit(Deck deck)
{
	this->deck = deck;
	handList = new Hand();
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
	isEnter = false;
	

	// ��Ŀ �׽�Ʈ��
	InitJoker();
	

	GameStart();
}

void GameScene::InitJoker()
{
#pragma region ��Ŀ ����
	// �ӽ÷� ��Ŀ 3�� �ֱ�
	// 1. ��Ŀ - Ʈ���� �Ϸ� �� - +4�� ����� ȹ��
	// 2. �λ��� ��Ŀ - Ʈ���� �� - ���̾Ƹ�� ���� ī�带 �÷����� ������ +3�� ��� ȹ��
	// 3. ��Ȱ�� ��Ŀ - Ʈ���� �Ϸ� �� - �÷����� �ڵ忡 ��� ���� �� +50���� Ĩ�� ȹ��

	int* pMul = &multiple;
	int* pChip = &chip;

	PushJoker("��Ŀ", "+4�� ����� ȹ��", "afterTrigger", [pMul](PlayingCard* card)
		{
			*pMul += 4;
			Sleep(500);
		});

	PushJoker("�λ��� ��Ŀ", "���̾Ƹ�� ���� ī�带 �÷����� ������ +3�� ��� ȹ��", "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "��")
			{
				*pMul += 3;
				Sleep(500);
			}

		});

	PushJoker("��Ȱ�� ��Ŀ", "�÷����� �ڵ忡 ��� ���� �� +50���� Ĩ�� ȹ��", "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "�� ���");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pChip += 50;
				Sleep(500);
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
				SkipBlind();
				out = true;
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

		if (antie > 8)
		{
			PrintResult();
			break;
		}
	}
}

void GameScene::StartBlind(const int currentBlind)
{
	score = 0;
	deck.Shuffle();

	hand = status->getHand();
	handCount = status->getHandCount();
	discardCount = status->getDiscardCount();

	// ���� ī��Ʈ ��ŭ Ȥ�� ��������� �ѱ� �� ���� ī�带 �����ϰ� �����ϴ� �κ�
	while (true)
	{
		// �п� ī�� �߰�
		for (int i = handList->getHandSize(); i < hand; i++)
		{
			handList->AddCard(deck.PopCard());
		}

		std::vector<PlayingCard*>().swap(selectedCard);
		std::vector<std::string>().swap(ranking);

		chip = 0;
		multiple = 0;

		RefreshScreen(500);
		PickCards();
		// ���� �Ѱ�����
		if (score >= stageInfo[currentBlind]->getScoreDeadLine())
		{
			cout << "����ε� Ŭ����!" << endl;
			stageInfo[currentBlind]->setClear(true);
			deck.RestoreDeck();
			Sleep(1000);
			break;
		}
		// ���� Ƚ�� ���� �Ҹ�
		else if (handCount == 0)
		{
			PrintResult();
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
	cout << "<���ھ�>" << endl;
	cout << score << endl;

	cout << endl;
	cout << "<������ ��Ŀ>" << endl;
	for (auto joker : myJokers)
	{
		cout << joker->getName() << ": " << joker->getToolTip() << endl;
	}
	cout << endl;
	if (!selectedCard.empty())
	{
		cout << ranking.back();
	}
	cout << endl;
	cout << "���õ� ī��" << endl;

	int sCardX = 1;
	for (auto card : selectedCard)
	{
		card->PrintCard(sCardX, 10);
		sCardX += 10;
		cout << "\t";
	}
	cout << endl;

	handList->PrintHand(1, 20);

	for (int i = 0; i < cursorIndex; i++)
	{
		cout << "\t";
	}
	cout << "��" << endl;

	cout << endl;
	cout << "�ڵ�: " << handCount << "\t������: " << discardCount << endl;
	cout << endl;

	cout << "z - ����, x - ������, c - �׸� ����, v - ���� ����, d - �� ��ȸ" << endl;
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
		cout << "Ŀ��: " << cursorIndex + 1 << "�� ī��" << endl;
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			// ����
			case 75:
				if (cursorIndex > 0)
				{
					cursorIndex--;
				}
				break;
			//������
			case 77:
				if (cursorIndex < handList->getHandSize() - 1)
				{
					cursorIndex++;
				}
				break;
			}
		}
		else
		{
			// ����Ű - ���� ��ư
			if (key == 13)
			{
				if (!selectedCard.empty())
				{
					// ī��, ��Ŀ Ʈ����
					isEnter = true;
					Trigger();
					handCount--;
					isEnter = false;
					// ������ ī����� ������ �߰�
					deck.UsedCards(selectedCard);
					// �п��� ������ ī�� ����
					handList->Discard(selectedCard);
					std::vector<PlayingCard*>().swap(selectedCard);
					return;
				}
			}
			// ���� ��ư - z
			else if (key == 90 || key == 122)
			{
				// �̹� ������ ī�� ���� ���
				if (FindCard(handList->getCard(cursorIndex)))
				{
					selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), handList->getCard(cursorIndex)), selectedCard.end());
				}
				// ī�� ����, ���� ī�尡 5�庸�� ���� ����
				else if (selectedCard.size() < 5)
				{
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
					std::vector<PlayingCard*>().swap(selectedCard);
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

void GameScene::Trigger()
{
	// ȭ�� ����
	RefreshScreen(0);
	// �ֻ��� ���� ��������
	chip = status->getHandRanking(ranking.back()).getChip();
	multiple = status->getHandRanking(ranking.back()).getMultiple();
	// Ʈ���� �ϱ�
	for (auto& card : bestHand)
	{
		// ������ ī�� Ĩ ���ϱ�
		chip += card->getChip();

		RefreshScreen(500);

		// Ʈ������ �� ��Ŀ �����Ƽ
		for (auto& joker : myJokers)
		{
			joker->AtTrigger(card);
			RefreshScreen(0);
		}
	}

	// Ʈ���� �� ��Ŀ �����Ƽ
	for (auto& joker : myJokers)
	{
		joker->AfterTrigger(nullptr);
		RefreshScreen(0);
	}

	score += chip * multiple;
	RefreshScreen(500);
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
		bestHand.push_back(sortedCards.back());
	}
}

void GameScene::PushJoker(const std::string& name, const std::string& toolTip, const std::string& abilityType, std::function<void(PlayingCard* card)> function)
{
	Joker* joker = new Joker(name, toolTip);
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
	myJokers.push_back(joker);
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
