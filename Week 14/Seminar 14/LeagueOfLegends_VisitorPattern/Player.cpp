#include "Player.h"
#include <cstring>
#pragma warning(disable:4996)

void Player::free() {
    delete[] name;
    name = nullptr;
    health = 0;
}

void Player::copyFrom(const Player& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    health = other.health;
}

void Player::moveFrom(Player&& other) noexcept {
    name = other.name;
    other.name = nullptr;
    other.health = 0;
}

size_t Player::getHealth() const {
    return health;
}

const char* Player::getName() const {
    return name;
}

Player::Player(const Player& other) {
    copyFrom(other);
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Player::~Player() {
    free();
}

Player::Player(Player&& other) noexcept {
    moveFrom(std::move(other));
}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Player::Player(const char* name, size_t hp) : health(hp) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Player::printStats() const {
    std::cout << "Name: " << name << ", Health: " << health << std::endl;
}
