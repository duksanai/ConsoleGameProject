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
			// 왼쪽
			case 75:
				if (index > 0)
				{
					// 실행
					index--;
				}
				break;
			//오른쪽
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
			// 엔터키 - 제출 버튼
			if (key == 13)
			{
				Trigger();

				return;
			}
			// 선택 버튼 - z
			else if (key == 90 || key == 122)
			{
				// 만약 선택된 카드가 5장보다 적으면 
				if (selectedCard.size() < 5)
				{
					// 이미 선택한 카드 선택 취소
					if (hand.FindCard(hand.getCard(index)))
					{
						selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), iter[index]), selectedCard.end());
					}
					// 카드 선택
					else
					{
						selectedCard.push_back(hand.getCard(index));
					}
				}
				// 족보 검사 함수
				CheckRanking();
			}
		}
		PrintGame();
	}
}

void GameScene::Trigger()
{
	// 화면 갱신
	PrintGame();
	// 트리거 하기
	for (auto& card : selectedCard)
	{
		// 족보에 카드 칩 더하기


		// 조커 카드 검사 -> 조커 능력 트리거

	}
}

// 족보를 체크하는 함수
void GameScene::CheckRanking()
{
	// 족보 벡터를 먼저 비우자
	std::vector<std::string>().swap(ranking);

	// 선택된 카드 벡터를 복사해주자. 스트레이트를 검사하려면 숫자 순으로 정렬해야 한다. 
	std::vector<PlayingCard*> sortedCards = selectedCard;
	std::sort(sortedCards.begin(), sortedCards.end(), [](const PlayingCard* a, const PlayingCard* b)
		{
			return *a < *b;
		});

	std::map<int, int> numberCount;
	std::map<std::string, int> shapeCount;

	// if문으로 제일 우선순위가 높은 족보부터 순서대로 넣음
	/*
	족보 규칙
	하이 카드 :			숫자가 높은 단일 카드. 5×1
	페어 :				같은 숫자 1쌍. 10×2
	투 페어 :			같은 숫자 2쌍. 20×2
	트리플 :				같은 숫자 3개의 묶음. 30×3
	스트레이트 :			연속된 숫자 5장. K-A-2를 포함하는 랩 어라운드 스트레이트는 인정하지 않는다. 30×4
	플러시 :				같은 문양 5장. 35×4
	풀하우스 :			같은 숫자 3개의 묶음과 같은 숫자 1쌍으로 이루어진 5장. 40×4
	포 카드 :			같은 숫자 4개의 묶음.60×7
	스트레이트 플러시 :	문양이 같은 연속된 숫자 5장. 100×8
	파이브 카드 :		랭크가 동일한 카드 5개. 120*12
	플러시 하우스 :		풀하우스와 플러시를 동시에 만족. 140*14
	플러시 파이브 :		동일 문양과 랭크로 된 파이브 카드. 200*16
	*/
	// 플러시 파이브
	// 너무 안떠올라서 다음 것 부터..
	
}

void GameScene::PrintResult() const
{
}

void GameScene::SkipBlind()
{
}

