#include "GameScene.h"

// 게임 생성 부분 좀 더 구상할 것
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
	

	// 조커 테스트용
	InitJoker();

	GameStart();
}

void GameScene::InitJoker()
{
	int* pMul = &multiple;
	int* pChip = &chip;
#pragma region 일반 조커
	// 16개
	PushJoker("조커", "+4의 배수를 획득", 0, "afterTrigger", [=](PlayingCard* card)
		{
			*pMul += 4;
			Sleep(300);
		});

	PushJoker("인색한 조커", "다이아몬드 문양 카드를 플레이할 때마다 +3의 배수 획득", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "◆")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("음욕 조커", "하트 문양 카드를 플레이할 때마다 +3의 배수 획득", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "♥")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("분노하는 조커", "스페이드 문양 카드를 플레이해 득점할 때마다 +3 배수를 획득합니다.", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "♠")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("탐욕스러운 조커", "클럽 문양 카드를 플레이할 때마다 +3의 배수 획득", 0, "atTrigger", [pMul](PlayingCard* card)
		{
			if (card->getShape() == "♣")
			{
				*pMul += 3;
				Sleep(300);
			}
		});

	PushJoker("엉뚱한 조커", "플레이한 핸드에 트리플 포함 시 +12 배수를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "트리플");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 12;
				Sleep(300);
			}
		});

	PushJoker("미친 조커", "플레이한 핸드에 포카드 포함 시 +20 배수를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "포 카드");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 20;
				Sleep(300);
			}
		});

	PushJoker("정신나간 조커", "플레이한 핸드에 스트레이트 포함 시 +12 배수를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "스트레이트");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 12;
				Sleep(300);
			}
		});

	PushJoker("괴짜 조커", "플레이한 핸드에 플러시 포함 시 +10 배수를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "플러시");
			if (findPair == ranking.end())
			{
				
			}
			else
			{
				*pMul += 10;
				Sleep(300);
			}
		});

	PushJoker("교활한 조커", "플레이한 핸드에 페어 포함 시 +50개의 칩을 획득", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "원 페어");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 50;
				Sleep(300);
			}
		});

	PushJoker("악랄한 조커", "플레이한 핸드에 트리플 포함 시 칩 +100개를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "트리플");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 100;
				Sleep(300);
			}
		});

	PushJoker("영리한 조커", "플레이한 핸드에 포카드 포함 시 칩 +150개를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "포카드");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 150;
				Sleep(300);
			}
		});

	PushJoker("기만적인 조커", "플레이한 핸드에 스트레이트 포함 시 칩 +100개를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "스트레이트");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 100;
				Sleep(300);
			}
		});

	PushJoker("간교한 조커", "플레이한 핸드에 플러시 포함 시 칩 +80개를 획득합니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::vector<std::string>::iterator findPair = find(ranking.begin(), ranking.end(), "플러시");
			if (findPair == ranking.end())
			{

			}
			else
			{
				*pChip += 80;
				Sleep(300);
			}
		});

	PushJoker("인쇄 오류", "+?? 배수", 0, "afterTrigger", [pMul](PlayingCard* card)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(1, 23);

			*pMul += dist(gen);
			Sleep(300);
		});

	PushJoker("캐번디시", "X3 배수를 획득합니다. 라운드 종료 시 1/1000 확률로 이 카드가 파괴됩니다.", 0, "afterTrigger", [=](PlayingCard* card)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 999);
			*pMul *= 3;
			if (dist(gen) == 999)
			{ 
				for (Joker* joker : myJokers)
				{
					if (joker->getName() == "캐번디시")
					{
						myJokers.erase(remove(myJokers.begin(), myJokers.end(), joker), myJokers.end());
					}
				}
			}
			Sleep(300);
		});
#pragma endregion
#pragma region 희귀 조커
	// 5개
	PushJoker("조커 스탠실", "빈 조커 슬롯마다 X1 배수를 획득합니다. 조커 스텐실은 빈 슬롯으로 간주", 1, "afterTrigger", [=](PlayingCard* card)
		{
			int multi;
			multi = status->getJokerSlot() - myJokers.size() + 1;
			*pMul *= multi;
			Sleep(300);
		});
	PushJoker("피보나치", "에이스, 2, 3, 5, 8을 플레이해 득점할 때마다 +8 배수를 획득합니다.", 1, "atTrigger", [=](PlayingCard* card)
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
	PushJoker("도보 여행자", "플레이해 득점한 카드에 칩 +4개를 영구적으로 추가합니다.", 1, "atTrigger", [=](PlayingCard* card)
		{
			card->AddChips(4);
			Sleep(300);
		});
	PushJoker("곡예사", "라운드의 마지막 핸드일 경우 X3 배수를 획득합니다.", 1, "afterTrigger", [=](PlayingCard* card)
		{
			if (handCount == 0)
			{
				*pMul *= 3;
			}
		});
	PushJoker("혈석", "하트 카드를 플레이 했을 경우 카드마다 1/3 확률로 X2 배수를 획득합니다.", 1, "atTrigger", [=](PlayingCard* card)
		{
			if (card->getCardType().shape == "♥")
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
#pragma region 영웅 조커
	// 1개
	PushJoker("야구 카드", "각 희귀 조커마다 X2 배수를 획득합니다.", 2, "afterTrigger", [=](PlayingCard* card)
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
				if (currentBlind != 2)
				{
					SkipBlind();
					out = true;
				}
				else
				{
					cout << "보스 블라인드는 스킵이 불가능합니다!" << endl;
				}
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

		// 클리어 앤티 기준 변경
		if (antie > 8)
		{
			cout << "축하합니다! 모든 라운드를 클리어했습니다." << endl;
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

	// 제출 카운트 만큼 혹은 데드라인을 넘길 때 까지 카드를 선택하고 제출하는 부분
	while (true)
	{
		std::vector<PlayingCard*>().swap(selectedCard);
		std::vector<std::string>().swap(ranking);
		std::vector<PlayingCard*>().swap(bestHand);

		// 패에 카드 추가
		for (int i = handList->getHandSize(); i < hand; i++)
		{
			RefreshScreen(70);
			handList->AddCard(deck.PopCard());
		}

		chip = 0;
		multiple = 0;

		RefreshScreen(0);
		PickCards();
		// 점수 넘겼으면
		if (score >= stageInfo[currentBlind]->getScoreDeadLine())
		{
			cout << "블라인드 클리어!" << endl;
			stageInfo[currentBlind]->setClear(true);
			deck.RestoreDeck();
			deck.ClearSelected();
			Sleep(1000);
			Reward();
			break;
		}
		// 제출 횟수 전부 소모
		else if (handCount == 0)
		{
			system("cls");
			cout << "패배했습니다..." << endl;
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
	cout << score << endl;
	cout << "유효 족보: ";
	if (!selectedCard.empty())
	{
		cout << ranking.back();
	}
	cout << endl;
	cout << "<보유한 조커> - " << status->getJokerSlot() << "슬롯" << endl;
	if (myJokers.size() != 0)
	{
		for (int i = 0; i < myJokers.size(); i++)
		{
			if (i == jokerIndex)
			{
				cout << "▶ ";
			}
			myJokers[i]->PrintJoker();
		}
	}
	for (int i = 0; i < status->getJokerSlot() - myJokers.size(); i++)
	{
		cout << endl;
	}

	cout << "<적용 카드>" << endl;
	int sCardX = 2;
	for (PlayingCard* card : bestHand)
	{
		card->PrintCard(sCardX, 16);
		sCardX += 22;
	}
	cout << endl;

	handList->PrintHand(2, 32);

	// 커서
	gotoxy(cursorIndex * 22 + 11, 47);
	if (jokerIndex == -1)
	{
		cout << "▲" << endl;
	}

	cout << endl;
	cout << "핸드: " << handCount << "\t버리기: " << discardCount << endl;
	cout << endl;

	cout << "z - 선택, x - 버리기" << endl;
	cout << "c - 그림 정렬, v - 숫자 정렬, d - 덱 조회" << endl;
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
		key = _getch();
		if (key == SPECIAL_KEY)
		{
			key = _getch();
			switch (key)
			{
			// 왼쪽
			case KEY_LEFT:
				if (cursorIndex > 0)
				{
					cursorIndex--;
				}
				break;
			//오른쪽
			case KEY_RIGHT:
				if (cursorIndex < handList->getHandSize() - 1)
				{
					cursorIndex++;
				}
				break;
			//위쪽
			case KEY_UP:
				jokerIndex = 0;
				JokerPick();
				break;
			}
		}
		else
		{
			// 엔터키 - 제출 버튼
			if (key == KEY_ENTER)
			{
				if (!selectedCard.empty())
				{
					// 카드, 조커 트리거
					isEnter = true;
					handCount--;
					Trigger();
					isEnter = false;
					// 선택한 카드들을 묘지에 추가
					deck.UsedCards(selectedCard);
					// 패에서 선택한 카드 제거
					handList->Discard(selectedCard);
					Sleep(1000);
					return;
				}
			}
			// 선택 버튼 - z
			else if (key == 90 || key == 122)
			{
				// 이미 선택한 카드 선택 취소
				if (FindCard(handList->getCard(cursorIndex)))
				{
					handList->getCard(cursorIndex)->Select(false);
					selectedCard.erase(remove(selectedCard.begin(), selectedCard.end(), handList->getCard(cursorIndex)), selectedCard.end());
				}
				// 카드 선택, 선택 카드가 5장보다 적을 때만
				else if (selectedCard.size() < 5)
				{
					handList->getCard(cursorIndex)->Select(true);
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
			// z - 조커 선택
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
	// 화면 갱신
	RefreshScreen(0);
	// 최상위 족보 가져오기
	chip = status->getHandRanking(ranking.back()).getChip();
	multiple = status->getHandRanking(ranking.back()).getMultiple();
	
	// 트리거 하기
	for (PlayingCard*& card : bestHand)
	{
		// 족보에 카드 칩 더하기
		chip += card->getChip();

		RefreshScreen(300);

		// 트리거할 때 조커 어빌리티
		for (Joker*& joker : myJokers)
		{
			joker->AtTrigger(card);
			RefreshScreen(0);
		}
	}

	// 트리거 후 조커 어빌리티
	for (Joker*& joker : myJokers)
	{
		joker->AfterTrigger(nullptr);
		RefreshScreen(0);
	}

	score += chip * multiple;
	RefreshScreen(300);
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
		bestHand.push_back(sortedCards[0]);
	}
}

void GameScene::PrintRewards()
{
	int x = 20, y = 10;
	gotoxy(x, y - 1);
	cout << "┌─보상선택──────────────────────────────────────────────────────────────────────────────────┐";
	for (int i = 0; i < rewardJokersIndex.size(); i++, y++)
	{
		gotoxy(x, y);
		cout << "│ ";
		if (rewardIndex == i)
		{
			cout << "▶ ";
		}
		jokers[rewardJokersIndex[i]]->PrintJoker();
		gotoxy(x + 92, y);
		cout << "│";
		gotoxy(x, y + 1);
	}
	cout << "├───────────────────────────────────────────────────────────────────────────────────────────┤";
	y++;
	if (myJokers.size() != 0)
	{
		for (int i = 0; i < myJokers.size(); i++, y++)
		{
			gotoxy(x, y);
			cout << "│ ";
			if (jokerIndex == i)
			{
				cout << "▶ ";
			}
			myJokers[i]->PrintJoker();
			gotoxy(x + 92, y);
			cout << "│";
		}
	}
	gotoxy(x, y);
	cout << "└───────────────────────────────────────────────────────────────────────────────────────────┘";
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
			// 커서 이동
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
			// 조커 선택 - z키
			if (key == 90 || key == 122)
			{
				// 최대 보유량을 넘지 않았을 경우 - 추가
				if (myJokers.size() < status->getJokerSlot())
				{
					myJokers.push_back(jokers[rewardJokersIndex[rewardIndex]]);
				}
				// 최대 보유량일 경우 - 교체
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
	// 커먼 -> 70퍼, 언커먼 -> 20퍼, 레어 -> 10퍼
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 9);
	std::uniform_int_distribution<> common(0, 15);
	std::uniform_int_distribution<> uncommon(16, 20);

	int gatcha;
	for (int i = 0; i < 3; i++)
	{
		gatcha = dist(gen);

		// 커먼
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
				// 커서 이동
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
			// 조커 선택 - z키
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
