#include "GameScene.h"

// 게임 생성 부분 좀 더 구상할 것
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
	

	// 조커 테스트용
	InitJoker();
	

	GameStart();
}

void GameScene::InitJoker()
{
#pragma region 조커 생성
	// 임시로 조커 3개 넣기
	// 1. 조커 - 트리거 완료 후 - +4의 배수를 획득
	// 2. 인색한 조커 - 트리거 시 - 다이아몬드 문양 카드를 플레이할 때마다 +3의 배수 획득
	// 3. 교활한 조커 - 트리거 완료 후 - 플레이한 핸드에 페어 포함 시 +50개의 칩을 획득

	int* pMul = &multiple;
	int* pChip = &chip;
	std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "페어");
	std::vector<std::string>::iterator rankingEnd = ranking.end();

	PushJoker("조커", "+4의 배수를 획득", "afterTrigger", [pMul](PlayingCard* card)
		{
			*pMul += 4;
		});

	PushJoker("인색한 조커", "다이아몬드 문양 카드를 플레이할 때마다 +3의 배수 획득", "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "◆")
			{
				*pMul += 3;
			}

		});

	PushJoker("교활한 조커", "플레이한 핸드에 페어 포함 시 +50개의 칩을 획득", "afterTrigger", [findPair, rankingEnd, pChip](PlayingCard* card)
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
	int hand;
	int handCount;
	int discardCount;
	while (true)
	{
		deck.Shuffle();

		hand = status->getHand();
		handCount = status->getHandCount();
		discardCount = status->getDiscardCount();

		// 패에 카드 추가
		for (int i = 0; i < hand; i++)
		{
			handList->AddCard(deck.PopCard());
		}

		// 제출 카운트 만큼 혹은 데드라인을 넘길 때 까지 카드를 선택하고 제출하는 부분
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
	cout << "목표 점수: " << stageInfo[currentBlind]->getScoreDeadLine() << endl;
	cout << "칩 X 배수\t" << chip << " X " << multiple << " = " << chip * multiple << endl;
	cout << "보유한 조커" << endl;
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
	cout << "선택된 카드" << endl;
	for (auto card : selectedCard)
	{
		card->PrintCard();
		cout << "\t";
	}
	cout << endl;
	handList->PrintHand();
	cout << endl;

	cout << "커서 이동: ←, →" << endl;
	cout << "z - 선택, x - 그림 정렬, c - 숫자 정렬" << endl;
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
		cout << "커서: " << index + 1 << "번 카드" << endl;
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
				if (index < handList->getHandSize())
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
				if (!selectedCard.empty())
				{
					// 카드 하나씩 트리거
					PlayingCard* nullCard = nullptr;
					Trigger();
					// 모든 카드 트리거 후 조커 트리거 넣기
					for (auto& joker : myJokers)
					{
						joker->AfterTrigger(nullCard);
					}
					delete nullCard;
					return;
				}
			}
			// 선택 버튼 - z
			else if (key == 90 || key == 122)
			{
				// 이미 선택한 카드 선택 취소
				if (FindCard(handList->getCard(index)))
				{
					selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), handList->getCard(index)), selectedCard.end());
				}
				// 카드 선택, 선택 카드가 5장보다 적을 때만
				else if (selectedCard.size() < 5)
				{
					selectedCard.push_back(handList->getCard(index));
				}
				// 족보 검사 함수
				CheckRanking();
			}

			// 그림 정렬 - x
			else if (key == 88 || key == 120)
			{
				handList->SortShape();
			}

			// 숫자 정렬 - c
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
	// 화면 갱신
	PrintGame();
	// 최상위 족보 가져오기
	chip = status->getHandRanking(ranking[0]).getChip();
	multiple = status->getHandRanking(ranking[0]).getMultiple();
	// 트리거 하기
	for (auto& card : selectedCard)
	{
		// 족보에 카드 칩 더하기
		chip += card->getChip();
		// 조커 카드 검사 -> 조커 능력 트리거
		for (auto& joker : myJokers)
		{
			joker->AtTrigger(card);
		}
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
	int cardCount = sortedCards.size();

	for (auto& card : sortedCards) {
		numberCount[card->getCardType().number]++;
		shapeCount[card->getCardType().shape]++;
	}

	bool isFourCard = false, isStraight = true, isFlush = false, isTriple = false, isPair = false;

	// 포 카드 체크만
	for (auto& pair : numberCount)
	{
		if (pair.second == 4)
		{
			isFourCard = true;
		}
	}

	// 스트레이트 체크만
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

	// 플러시 체크만
	if (shapeCount.size() == 1 && cardCount == 5)
	{
		isFlush = true;
	}

	// 트리플 체크만

	for (auto& pair : numberCount)
	{
		if (pair.second == 3)
		{
			isTriple = true;
		}
	}

	// 페어 체크만
	int countPair = 0;
	for (auto& pair : numberCount)
	{
		if (pair.second == 2)
		{
			isPair = true;
			countPair++;
		}
	}

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
	if ((numberCount.size() == 1 && shapeCount.size() == 1) && cardCount == 5)
	{
		ranking.push_back("플러시 파이브");
	}

	// 플러시 하우스
	if ((cardCount == 5 && shapeCount.size() == 1) && (isTriple && isPair))
	{
		ranking.push_back("플러시 하우스");
	}

	// 파이브 카드
	if (cardCount == 5 && numberCount.size() == 1)
	{
		ranking.push_back("파이브 카드");
	}

	// 스트레이트 플러시
	if (isStraight && (shapeCount.size() == 1))
	{
		ranking.push_back("스트레이트 플러시");
	}

	// 포 카드
	if (isFourCard)
	{
		ranking.push_back("포 카드");
	}

	// 풀하우스
	if (isTriple && isPair)
	{
		ranking.push_back("풀하우스");
	}

	// 플러시
	if (isFlush)
	{
		ranking.push_back("플러시");
	}

	// 스트레이트
	if (isStraight)
	{
		ranking.push_back("스트레이트");
	}

	// 트리플
	if (isTriple)
	{
		ranking.push_back("트리플");
	}

	// 투 페어
	if (countPair == 2)
	{
		ranking.push_back("투 페어");
	}

	// 원 페어
	if (isPair)
	{
		ranking.push_back("원 페어");
	}

	if (sortedCards.size() > 0)
	{
		ranking.push_back("하이");
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
