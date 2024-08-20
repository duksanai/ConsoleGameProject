#include "PlayingCard.h"

PlayingCard::PlayingCard(const std::string& shape, const int number, const int chip, const int uniqueNum)
	:shape(shape), number(number), chip(chip), uniqueNum(uniqueNum)
{
	isSelected = false;
}

//bool PlayingCard::operator<(const PlayingCard& other) const
//{
//	if (shape == other.shape)
//	{
//		return number < other.number;
//	}
//	return shape < other.shape;
//}

// 숫자
bool PlayingCard::operator<(const PlayingCard& other) const
{
	if (number == other.number)
	{
		return shape > other.shape;
	}
	return number > other.number;
}

// 모양
bool PlayingCard::operator>(const PlayingCard& other) const
{

	if (shape == other.shape)
	{
		return number > other.number;
	}
	return shape > other.shape;
}

CardType PlayingCard::getCardType()
{
	return CardType(shape, number);
}

void PlayingCard::PrintCard(const int x, const int y)const
{
	PrintCardFrame(x, y);
	// 모양 출력 - 도트 맵 필요

	// 숫자 출력 - 도트 맵 필요

	/*std::cout << shape;
	switch (number)
	{
	case 1:
		std::cout << "A";
		break;
	case 11:
		std::cout << "J";
		break;
	case 12:
		std::cout << "Q";
		break;
	case 13:
		std::cout << "K";
		break;
	default:
		std::cout << number;
		break;
	}*/
}

std::string PlayingCard::getShape()
{
	return shape;
}

int PlayingCard::getChip()
{
	return chip;
}

bool CardType::operator<(const CardType& rhs) const
{
	if (shape != rhs.shape)
	{
		return shape < rhs.shape;
	}
	return number < rhs.number;
}
