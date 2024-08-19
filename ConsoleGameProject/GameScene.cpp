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
	std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "���");
	std::vector<std::string>::iterator rankingEnd = ranking.end();

	PushJoker("��Ŀ", "+4�� ����� ȹ��", "afterTrigger", [pMul](PlayingCard* card)
		{
			*pMul += 4;
		});

	PushJoker("�λ��� ��Ŀ", "���̾Ƹ�� ���� ī�带 �÷����� ������ +3�� ��� ȹ��", "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "��")
			{
				*pMul += 3;
			}

		});

	PushJoker("��Ȱ�� ��Ŀ", "�÷����� �ڵ忡 ��� ���� �� +50���� Ĩ�� ȹ��", "afterTrigger", [findPair, rankingEnd, pChip](PlayingCard* card)
		{
			if (findPair != rankingEnd)
			{
				*pChip += 50;
			}
		});
#pragma endregion
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
	int hand;
	int handCount;
	int discardCount;
	while (true)
	{
		deck.Shuffle();

		hand = status->getHand();
		handCount = status->getHandCount();
		discardCount = status->getDiscardCount();

		// �п� ī�� �߰�
		for (int i = 0; i < hand; i++)
		{
			handList->AddCard(deck.PopCard());
		}

		// ���� ī��Ʈ ��ŭ Ȥ�� ��������� �ѱ� �� ���� ī�带 �����ϰ� �����ϴ� �κ�
		while (true)
		{
			system("cls");
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
	cout << "Ĩ X ���\t" << chip << " X " << multiple << " = " << chip * multiple << endl;
	cout << "������ ��Ŀ" << endl;
	for (auto joker : myJokers)
	{
		cout << joker->getName() << "\t" << joker->getToolTip() << endl;
	}
	cout << endl;
	if (!selectedCard.empty())
	{
		cout << ranking[0];
	}
	cout << endl;
	cout << "���õ� ī��" << endl;
	for (auto card : selectedCard)
	{
		card->PrintCard();
		cout << "\t";
	}
	cout << endl;
	handList->PrintHand();
	cout << endl;

	cout << "Ŀ�� �̵�: ��, ��" << endl;
	cout << "z - ����, x - �׸� ����, c - ���� ����" << endl;
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
		cout << "Ŀ��: " << index + 1 << "�� ī��" << endl;
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
				if (index < handList->getHandSize())
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
				if (!selectedCard.empty())
				{
					// ī�� �ϳ��� Ʈ����
					PlayingCard* nullCard = nullptr;
					Trigger();
					// ��� ī�� Ʈ���� �� ��Ŀ Ʈ���� �ֱ�
					for (auto& joker : myJokers)
					{
						joker->AfterTrigger(nullCard);
					}
					delete nullCard;
					return;
				}
			}
			// ���� ��ư - z
			else if (key == 90 || key == 122)
			{
				// �̹� ������ ī�� ���� ���
				if (FindCard(handList->getCard(index)))
				{
					selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), handList->getCard(index)), selectedCard.end());
				}
				// ī�� ����, ���� ī�尡 5�庸�� ���� ����
				else if (selectedCard.size() < 5)
				{
					selectedCard.push_back(handList->getCard(index));
				}
				// ���� �˻� �Լ�
				CheckRanking();
			}

			// �׸� ���� - x
			else if (key == 88 || key == 120)
			{
				handList->SortShape();
			}

			// ���� ���� - c
			else if (key == 67 || key == 99)
			{
				handList->SortNum();
			}
		}
		system("cls");
		PrintGame();
	}
}

void GameScene::Trigger()
{
	// ȭ�� ����
	PrintGame();
	// �ֻ��� ���� ��������
	chip = status->getHandRanking(ranking[0]).getChip();
	multiple = status->getHandRanking(ranking[0]).getMultiple();
	// Ʈ���� �ϱ�
	for (auto& card : selectedCard)
	{
		// ������ ī�� Ĩ ���ϱ�
		chip += card->getChip();
		// ��Ŀ ī�� �˻� -> ��Ŀ �ɷ� Ʈ����
		for (auto& joker : myJokers)
		{
			joker->AtTrigger(card);
		}
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
	int cardCount = sortedCards.size();

	for (auto& card : sortedCards) {
		numberCount[card->getCardType().number]++;
		shapeCount[card->getCardType().shape]++;
	}

	bool isFourCard = false, isStraight = true, isFlush = false, isTriple = false, isPair = false;

	// �� ī�� üũ��
	for (auto& pair : numberCount)
	{
		if (pair.second == 4)
		{
			isFourCard = true;
		}
	}

	// ��Ʈ����Ʈ üũ��
	if (cardCount == 5)
	{
		for (int i = 0; i < sortedCards.size() - 1; i++)
		{
			if (sortedCards[i]->getCardType().number + 1 != sortedCards[i + 1]->getCardType().number)
			{
				isStraight = false;
			}
		}
	}
	else
	{
		isStraight = false;
	}

	// �÷��� üũ��
	if (shapeCount.size() == 1 && cardCount == 5)
	{
		isFlush = true;
	}

	// Ʈ���� üũ��

	for (auto& pair : numberCount)
	{
		if (pair.second == 3)
		{
			isTriple = true;
		}
	}

	// ��� üũ��
	int countPair = 0;
	for (auto& pair : numberCount)
	{
		if (pair.second == 2)
		{
			isPair = true;
			countPair++;
		}
	}

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
	if ((numberCount.size() == 1 && shapeCount.size() == 1) && cardCount == 5)
	{
		ranking.push_back("�÷��� ���̺�");
	}

	// �÷��� �Ͽ콺
	if ((cardCount == 5 && shapeCount.size() == 1) && (isTriple && isPair))
	{
		ranking.push_back("�÷��� �Ͽ콺");
	}

	// ���̺� ī��
	if (cardCount == 5 && numberCount.size() == 1)
	{
		ranking.push_back("���̺� ī��");
	}

	// ��Ʈ����Ʈ �÷���
	if (isStraight && (shapeCount.size() == 1))
	{
		ranking.push_back("��Ʈ����Ʈ �÷���");
	}

	// �� ī��
	if (isFourCard)
	{
		ranking.push_back("�� ī��");
	}

	// Ǯ�Ͽ콺
	if (isTriple && isPair)
	{
		ranking.push_back("Ǯ�Ͽ콺");
	}

	// �÷���
	if (isFlush)
	{
		ranking.push_back("�÷���");
	}

	// ��Ʈ����Ʈ
	if (isStraight)
	{
		ranking.push_back("��Ʈ����Ʈ");
	}

	// Ʈ����
	if (isTriple)
	{
		ranking.push_back("Ʈ����");
	}

	// �� ���
	if (countPair == 2)
	{
		ranking.push_back("�� ���");
	}

	// �� ���
	if (isPair)
	{
		ranking.push_back("�� ���");
	}

	if (sortedCards.size() > 0)
	{
		ranking.push_back("����");
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
