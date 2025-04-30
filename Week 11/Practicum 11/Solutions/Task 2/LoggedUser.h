#pragma once
#include "Player.h"
class LoggedUser :public Player
{
private:
	char password[8 + 1];
public:
	LoggedUser(const char* pw);
	void makeMission() override;
};

