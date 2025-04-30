#pragma once
#include <iostream>
#pragma warning(disable: 4996)
enum class Starts:short {
	OneStar = 1<<8,
	TwoStar = 1<<9,
	ThreeStar = 1 << 10,
	FourStar = 1 << 11,
	FiveStar = 1 << 12
};
class Player
{
private:
	static int idCounter;
	
	void free();
	void copyFrom(const Player& other);
	void moveFrom(Player&& other);

protected:
	char** subjects = nullptr;
	int subjectCount = 0;

	const int ID;
	int points=0;
	Starts star=Starts::OneStar;
public:
	Player();
	Player(const char* const* subject,int count);

	Player(const Player& other);
	Player(Player&& other);

	Player& operator=(const Player& other);
	Player& operator=(Player&& other);



	void setPoints(int _points);
	void setSubject(const char* const* sub,int count);
	
	int getID() const;

	int getStar() const;
	virtual bool levelUp();

	virtual void makeMission()= 0;

	virtual ~Player();
protected:
	bool levelHelper(int twoStarPoints, int threeStarPoints, int fourStarPoints, int fiveStarPoints);
};

