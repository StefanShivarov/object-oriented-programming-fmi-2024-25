#include "PremiumPlayer.h"


void PremiumPlayer::free()
{
    delete[] name;
}

void PremiumPlayer::copyFrom(const PremiumPlayer& other)
{
    nameSize = other.nameSize;
    name = new char[nameSize + 1];
    strcpy(name, other.name);
}

void PremiumPlayer::moveFrom(PremiumPlayer&& other)
{
    nameSize = other.nameSize;
    other.nameSize = 0;

    name = other.name;
    other.name = nullptr;
}

PremiumPlayer::PremiumPlayer(const char* name)
    :Player()
{
    setName(name);
}

PremiumPlayer::PremiumPlayer(const char* _name, const char* const* sub,int subjectCount)
    :Player(sub,subjectCount)
{
    setName(_name);
}

PremiumPlayer::PremiumPlayer(const PremiumPlayer& other)
    :Player(other)
{
    copyFrom(other);
}

PremiumPlayer::PremiumPlayer(PremiumPlayer&& other)
    :Player(std::move(other))
{
    moveFrom(std::move(other));
}

PremiumPlayer& PremiumPlayer::operator=(const PremiumPlayer& other)
{
    if (this != &other)
    {
        Player::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
    // TODO: insert return statement here
}

PremiumPlayer& PremiumPlayer::operator=(PremiumPlayer&& other)
{
    if (this != &other)
    {
        Player::operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }
    return *this;
    // TODO: insert return statement here
}

void PremiumPlayer::setName(const char* _name)
{
    if (_name || &_name == &name)
    {
        return;
    }
    delete[] name;
    nameSize = strlen(_name);
    name = new char[nameSize + 1];
    strcpy(name, _name);
}

bool PremiumPlayer::levelUp()
{
    return levelHelper(256, 512, 768, 1024);
}

void PremiumPlayer::makeMission()
{
}

PremiumPlayer::~PremiumPlayer()
{
    free();
}
