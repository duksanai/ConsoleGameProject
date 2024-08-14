#include "PlayerStatus.h"

PlayerStatus::PlayerStatus(int handCount, int discardCount, int hand)
	:handCount(handCount), discardCount(discardCount), hand(hand)
{
	InitHandRanking();
}

void PlayerStatus::PrintHandRanking() const
{
	std::cout << "<����>" << std::endl;
	std::cout << "�̸�\t\t����\tĨ\t���" << std::endl;
	for (auto& pair : handRankings)
	{
		std::cout << pair.first << "\t\t";
		std::cout << pair.second.getLevel() << "\t\t";
		std::cout << pair.second.getChip() << "\t\t";
		std::cout << pair.second.getMultiple() << std::endl;
	}
}

void PlayerStatus::HandLevelUp(const std::string& name, const int chip, const int multiple)
{
	handRankings[name].LevelUp(1, chip, multiple);
}

void PlayerStatus::HandLevelDown(const std::string& name, const int chip, const int multiple)
{
	if (handRankings[name].getLevel() == 1)
	{
		std::cout << "�ּ� ������ �����߽��ϴ�. " << std::endl;
	}
	else
	{
		handRankings[name].LevelDown(1, chip, multiple);
	}
}

void PlayerStatus::HandCountPlus(const int num)
{
	handCount += num;
	if (handCount <= 1)
	{
		std::cout << "�� �̻� �������� �ʽ��ϴ�. " << std::endl;
		handCount = 1;
	}
}

void PlayerStatus::DiscardCountPlus(const int num)
{
	discardCount += num;
	if (discardCount <= 0)
	{
		std::cout << "�� �̻� �������� �ʽ��ϴ�. " << std::endl;
		discardCount = 0;
	}
}

void PlayerStatus::HandPlus(const int num)
{
	hand += num;
	if (hand <= 1)
	{
		std::cout << "�� �̻� �������� �ʽ��ϴ�. " << std::endl;
		hand = 1;
	}
}

void PlayerStatus::InitHandRanking()
{
	handRankings.insert(std::make_pair("����", HandRanking(1, 5, 1)));
	handRankings.insert(std::make_pair("���", HandRanking(1, 10, 2)));
	handRankings.insert(std::make_pair("�� ���", HandRanking(1, 20, 2)));
	handRankings.insert(std::make_pair("Ʈ����", HandRanking(1, 30, 3)));
	handRankings.insert(std::make_pair("��Ʈ����Ʈ", HandRanking(1, 30, 4)));
	handRankings.insert(std::make_pair("�÷���", HandRanking(1, 35, 4)));
	handRankings.insert(std::make_pair("Ǯ�Ͽ콺", HandRanking(1, 40, 4)));
	handRankings.insert(std::make_pair("�� ī��", HandRanking(1, 60, 7)));
	handRankings.insert(std::make_pair("��Ʈ����Ʈ", HandRanking(1, 100, 8)));
	handRankings.insert(std::make_pair("���̺� ī��", HandRanking(1, 120, 12)));
	handRankings.insert(std::make_pair("�÷��� �Ͽ콺", HandRanking(1, 140, 14)));
	handRankings.insert(std::make_pair("�÷��� ���̺�", HandRanking(1, 200, 16)));
}
