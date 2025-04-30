#pragma once
#include "Player.h"
class PremiumPlayer:public Player
{
	char* name;
	int nameSize = 0;

	void free();
	void copyFrom(const PremiumPlayer& other);
	void moveFrom(PremiumPlayer&& other);


public:
	

	PremiumPlayer(const char* name);
	PremiumPlayer(const char* name, const char* const* sub,int subjectCount);

	PremiumPlayer(const PremiumPlayer& other);
	PremiumPlayer(PremiumPlayer&& other);

	PremiumPlayer& operator=(const PremiumPlayer& other);
	PremiumPlayer& operator=(PremiumPlayer&& other);

	void setName(const char* _name);


	bool levelUp() override;
	void makeMission() override;
	~PremiumPlayer();
};

