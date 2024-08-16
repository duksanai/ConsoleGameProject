#include "GameScene.h"

// 게임 생성 부분 좀 더 구상할 것
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

		// 앤티 정보 출력
		cout << "<<앤티: " << antie << ">>" << endl << endl;

		for (int i = 0; i < 3; i++)
		{
			stageInfo[i]->PrintStageInfo();
		}

		// 블라인드 시작, 건너뛰기 선택
		int key;
		bool out = false;
		while (!out)
		{
			cout << "1. 입장" << endl;
			cout << "2. 건너뛰기" << endl;

			key = _getch();
			switch (key)
			{
			case 49:
				// 시작
				StartBlind();
				out = true;
				break;
			case 50:
				// 블라인드 건너뛰기
				SkipBlind();
				out = true;
				break;
			default:
				cout << "다시 입력하세요. " << endl;
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

		// 패에 카드 추가
		for (int i = 0; i < handCount; i++)
		{
			hand.AddCard(deck.PopCard());
		}

		// 제출 카운트 만큼 혹은 데드라인을 넘길 때 까지 카드를 선택하고 제출하는 부분
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
	cout << "목표 점수: " << stageInfo[currentBlind]->getScoreDeadLine() << endl;
}

void GameScene::MakeAntie()
{
	stageInfo[0] = new StageInfo("스몰 블라인드", antie, deadLine[antie]);
	stageInfo[1] = new StageInfo("빅 블라인드", antie, deadLine[antie] * 1.5);
	stageInfo[2] = new StageInfo("보스 블라인드", antie, deadLine[antie] * 2);
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
			// 왼쪽
			case 75:
				if (index > 0)
				{
					// 실행
				}
				break;
			//오른쪽
			case 77:

				break;
			}
		}
		else
		{
			// 엔터키
			if (key == 13)
			{

			}
			// 선택 버튼 - z
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

