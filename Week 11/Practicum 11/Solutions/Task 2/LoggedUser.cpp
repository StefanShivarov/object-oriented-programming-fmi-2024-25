#include "LoggedUser.h"

LoggedUser::LoggedUser(const char* pw)
{
	if (strlen(pw) > 8) {
		throw std::exception("incorent length must be lower than 9");
	}
	strcpy(password, pw);
}

void LoggedUser::makeMission()
{
}
