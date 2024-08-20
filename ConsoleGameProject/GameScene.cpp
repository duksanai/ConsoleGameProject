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
	isEnter = false;
	

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

	PushJoker("조커", "+4의 배수를 획득", "afterTrigger", [pMul](PlayingCard* card)
		{
			*pMul += 4;
			Sleep(500);
		});

	PushJoker("인색한 조커", "다이아몬드 문양 카드를 플레이할 때마다 +3의 배수 획득", "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "◆")
			{
				*pMul += 3;
				Sleep(500);
			}

		});

	PushJoker("교활한 조커", "플레이한 핸드에 페어 포함 시 +50개의 칩을 획득", "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "원 페어");
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

		// 앤티 정보 출력
		cout << "<<앤티: " << antie << ">>" << endl << endl;

		for (int i = 0; i < 3; i++)
		{
			stageInfo[i]->PrintStageInfo();
		}
		cout << "현재 블라인드: " << stageInfo[currentBlind]->getBlind() << endl;
		cout << endl;
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
				StartBlind(currentBlind);
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

	// 제출 카운트 만큼 혹은 데드라인을 넘길 때 까지 카드를 선택하고 제출하는 부분
	while (true)
	{
		// 패에 카드 추가
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
		// 점수 넘겼으면
		if (score >= stageInfo[currentBlind]->getScoreDeadLine())
		{
			cout << "블라인드 클리어!" << endl;
			stageInfo[currentBlind]->setClear(true);
			deck.RestoreDeck();
			Sleep(1000);
			break;
		}
		// 제출 횟수 전부 소모
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
	cout << "목표 점수: " << stageInfo[currentBlind]->getScoreDeadLine() << endl;
	cout << "칩 X 배수: ";
	if (isEnter)
	{
		cout << chip << " X " << multiple;
	}
	else if (ranking.size() != 0)
	{
		cout << status->getHandRanking(ranking.back()).getChip() << " X " << status->getHandRanking(ranking.back()).getMultiple();
	}
	cout << endl;
	cout << "<스코어>" << endl;
	cout << score << endl;

	cout << endl;
	cout << "<보유한 조커>" << endl;
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
	cout << "선택된 카드" << endl;

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
	cout << "▲" << endl;

	cout << endl;
	cout << "핸드: " << handCount << "\t버리기: " << discardCount << endl;
	cout << endl;

	cout << "z - 선택, x - 버리기, c - 그림 정렬, v - 숫자 정렬, d - 덱 조회" << endl;
	cout << "Enter - 제출" << endl;
	cout << endl;
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
	cursorIndex = 0;
	std::vector<PlayingCard*>::iterator iter;
	iter = selectedCard.begin();
	while (true)
	{
		cout << "커서: " << cursorIndex + 1 << "번 카드" << endl;
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			// 왼쪽
			case 75:
				if (cursorIndex > 0)
				{
					cursorIndex--;
				}
				break;
			//오른쪽
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
			// 엔터키 - 제출 버튼
			if (key == 13)
			{
				if (!selectedCard.empty())
				{
					// 카드, 조커 트리거
					isEnter = true;
					Trigger();
					handCount--;
					isEnter = false;
					// 선택한 카드들을 묘지에 추가
					deck.UsedCards(selectedCard);
					// 패에서 선택한 카드 제거
					handList->Discard(selectedCard);
					std::vector<PlayingCard*>().swap(selectedCard);
					return;
				}
			}
			// 선택 버튼 - z
			else if (key == 90 || key == 122)
			{
				// 이미 선택한 카드 선택 취소
				if (FindCard(handList->getCard(cursorIndex)))
				{
					selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), handList->getCard(cursorIndex)), selectedCard.end());
				}
				// 카드 선택, 선택 카드가 5장보다 적을 때만
				else if (selectedCard.size() < 5)
				{
					selectedCard.push_back(handList->getCard(cursorIndex));
				}
				// 족보 검사 함수
				CheckRanking();
			}

			// 버리기 - x
			else if (key == 88 || key == 120)
			{
				if (discardCount > 0)
				{
					// 선택한 카드들을 묘지에 추가
					deck.UsedCards(selectedCard);
					// 패에서 선택한 카드 제거
					handList->Discard(selectedCard);
					std::vector<PlayingCard*>().swap(selectedCard);
					discardCount--;
					return;
				}
			}

			// 숫자 정렬 - c
			else if (key == 67 || key == 99)
			{
				handList->SortNum();
			}

			// 그림 정렬 - v
			else if (key == 86 || key == 118)
			{
				handList->SortShape();
			}

			// 덱 조회 - d
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
	// 화면 갱신
	RefreshScreen(0);
	// 최상위 족보 가져오기
	chip = status->getHandRanking(ranking.back()).getChip();
	multiple = status->getHandRanking(ranking.back()).getMultiple();
	// 트리거 하기
	for (auto& card : bestHand)
	{
		// 족보에 카드 칩 더하기
		chip += card->getChip();

		RefreshScreen(500);

		// 트리거할 때 조커 어빌리티
		for (auto& joker : myJokers)
		{
			joker->AtTrigger(card);
			RefreshScreen(0);
		}
	}

	// 트리거 후 조커 어빌리티
	for (auto& joker : myJokers)
	{
		joker->AfterTrigger(nullptr);
		RefreshScreen(0);
	}

	score += chip * multiple;
	RefreshScreen(500);
}

// 족보를 체크하는 함수
void GameScene::CheckRanking()
{
	// 족보 벡터를 먼저 비우자
	std::vector<std::string>().swap(ranking);
	std::vector<PlayingCard*>().swap(bestHand);

	// 선택된 카드 벡터를 복사해주자. 스트레이트를 검사하려면 숫자 순으로 정렬해야 한다. 
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

	// 하이 체크만
	if (sortedCards.size() > 0)
	{
		ranking.push_back("하이");
	}

	// 페어 체크만
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

	// 트리플 체크만
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


	// 스트레이트 체크만
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

	// 플러시 체크만
	if (shapeCount.size() == 1 && cardCount == 5)
	{
		bestHand = selectedCard;
		isFlush = true;
	}

	// 포 카드 체크만
	for (auto& pair : numberCount)
	{
		if (pair.second.size() == 4)
		{
			bestHand = pair.second;
			isFourCard = true;
		}
	}

	// if문으로 제일 우선순위가 높은 족보를 마지막에 넣음
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

	// 원 페어
	if (isPair)
	{
		ranking.push_back("원 페어");
	}

	// 투 페어
	if (countPair == 2)
	{
		ranking.push_back("투 페어");
	}

	// 트리플
	if (isTriple)
	{
		ranking.push_back("트리플");
	}

	// 스트레이트
	if (isStraight)
	{
		ranking.push_back("스트레이트");
	}

	// 플러시
	if (isFlush)
	{
		ranking.push_back("플러시");
	}

	// 풀하우스
	if (isTriple && isPair)
	{
		bestHand = selectedCard;
		ranking.push_back("풀하우스");
	}

	// 포 카드
	if (isFourCard)
	{
		ranking.push_back("포 카드");
	}

	// 스트레이트 플러시
	if (isStraight && (shapeCount.size() == 1))
	{
		ranking.push_back("스트레이트 플러시");
	}

	// 파이브 카드
	if (cardCount == 5 && numberCount.size() == 1)
	{
		ranking.push_back("파이브 카드");
		bestHand = selectedCard;
	}

	// 플러시 하우스
	if ((cardCount == 5 && shapeCount.size() == 1) && (isTriple && isPair))
	{
		ranking.push_back("플러시 하우스");
		bestHand = selectedCard;
	}

	// 플러시 파이브
	if ((numberCount.size() == 1 && shapeCount.size() == 1) && cardCount == 5)
	{
		ranking.push_back("플러시 파이브");
		bestHand = selectedCard;
	}

	// 아무것도 만족하지 않으면 하이카드만 넣기
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
