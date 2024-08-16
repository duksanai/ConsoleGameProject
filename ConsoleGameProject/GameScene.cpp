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
				}
				break;
			//������
			case 77:

				break;
			}
		}
		else
		{
			// ����Ű
			if (key == 13)
			{

			}
			// ���� ��ư - z
			else if (key == 90 || key == 122)
			{

			}
		}
	}
}

void GameScene::PrintResult() const
{
}

void GameScene::SkipBlind()
{
}

