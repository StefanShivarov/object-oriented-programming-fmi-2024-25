#include "Player.h"
int Player::idCounter = 0;

void Player::free()
{
	for (int i = 0; i < subjectCount; i++)
	{
		delete[] subjects[i];
		subjects[i] == nullptr;
	}
	delete[] subjects;
	subjects = nullptr;
	subjectCount = 0;
}

void Player::copyFrom(const Player& other)
	
{
	subjectCount = other.subjectCount;
	subjects = new char* [subjectCount];
	for (int i = 0; i < subjectCount; i++)
	{
		strcpy(subjects[i], other.subjects[i]);
	}
	points = other.points;
	star = other.star;
	
}

void Player::moveFrom(Player&& other)
{
	subjectCount = other.subjectCount;
	other.subjectCount = 0;

	points = other.points;
	other.points = 0;

	subjects = other.subjects;
	other.subjects = nullptr;
}

Player::Player()
	:ID(++idCounter)
{
	
}

Player::Player(const char* const* subject,int count)
	:ID(++idCounter)
{
	setSubject(subject, count);
}

Player::Player(const Player& other)
	:ID(++idCounter)
{
	copyFrom(other);
}

Player::Player(Player&& other): ID(++idCounter)
{
	moveFrom(std::move(other));
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	// TODO: insert return statement here
}

Player& Player::operator=(Player&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
	// TODO: insert return statement here
}

void Player::setPoints(int _points)
{
	points = _points;
}

void Player::setSubject(const char* const* sub,int count)
{
	for (int i = 0; i < subjectCount; i++)
	{
		delete[] subjects[i];
	}
	delete[] subjects;
	subjectCount = count;
	subjects = new char* [count] {nullptr};
	for (int i = 0; i < count; i++)
	{
		subjects[i] = new char[strlen(sub[i])+1];
		strcpy(subjects[i], sub[i]);
	}

}

int Player::getID() const
{
	return ID;
}

int Player::getStar() const
{
	switch (star)
	{

		case Starts::OneStar: 
		{
			return 1;
		}
		case Starts::TwoStar:
		{
			return 2;
		}
		case Starts::ThreeStar:
		{
			return 3;
		}
		case Starts::FourStar:
		{
			return 4;
		}
		case Starts::FiveStar:
		{
			return 5;
		}
	}
	return 0;
}

bool Player::levelUp()
{

	return levelHelper(256, 512, 1024, 2048);	
}

Player::~Player()
{
	free();
}

bool Player::levelHelper(int twoStarPoints, int threeStarPoints, int fourStarPoints, int fiveStarPoints)
{
	switch (star)
	{

	case Starts::OneStar:
	{
		if (points >= twoStarPoints) {
			points -= twoStarPoints;
			star = Starts::TwoStar;
			return true;
		}
		break;
	}

	case Starts::TwoStar:
	{
		if (points >= threeStarPoints) {
			points -= threeStarPoints;
			star = Starts::ThreeStar;
			return true;
		}
		break;
	}
	case Starts::ThreeStar:
	{
		if (points >= fourStarPoints) {
			points -= fourStarPoints;
			star = Starts::FourStar;
			return true;
		}
		break;
	}
	case Starts::FourStar:
	{
		if (points >= fiveStarPoints) {
			points -= fiveStarPoints;
			star = Starts::FiveStar;
			return true;
		}
		break;
	}
	case Starts::FiveStar:
		break;
	default:

		break;
	}
	/*if (points >= (int)Starts::FiveStar)
	{
		return false;
	}
	if (points >= (int)star)
	{
		points -= (int)star << 1;
		star = (Starts)((int)star<<1);
		return true;
	}*/
	return false;
	
}
