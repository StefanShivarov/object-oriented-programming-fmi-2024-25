#pragma once
#include "Player.h"
class Guest:public Player
{
	unsigned timePlayable;
	

public:
	void makeMission() override;
	bool levelUp() override;
	Guest(unsigned timePlayable);
};

