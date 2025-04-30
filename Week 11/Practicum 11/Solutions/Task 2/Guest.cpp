#include "Guest.h"

void Guest::makeMission()
{

}

bool Guest::levelUp()
{
	std::cout << "You cannot level up on Guest\n";
	return false;
}

Guest::Guest(unsigned timePlayable)
	:Player(), timePlayable(timePlayable)
{
}
