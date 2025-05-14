#pragma once
#include <iostream>
#include "Player.h"

class RPSGame {
public:
    explicit RPSGame(size_t playersCount);

    RPSGame(const RPSGame& other);
    RPSGame(RPSGame&& other) noexcept;
    RPSGame& operator=(const RPSGame& other);
    RPSGame& operator=(RPSGame&& other) noexcept;
    ~RPSGame();

    void addPlayer(Player* player);

    size_t getPlayersCount() const;
    size_t simulateTournament() const;
private:
    Player** players = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void free();
    void copyFrom(const RPSGame& other);
    void moveFrom(RPSGame&& other) noexcept;

    bool isValidIndex(size_t index) const;
    size_t simulateDuel(size_t firstPlayerIndex, size_t secondPlayerIndex) const;
};
