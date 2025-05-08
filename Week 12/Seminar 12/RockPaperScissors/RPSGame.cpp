#include "RPSGame.h"

void RPSGame::free() {
    for (size_t i = 0; i < capacity; i++) {
        delete players[i];
    }
    delete[] players;
    players = nullptr;
    size = capacity = 0;
}

void RPSGame::copyFrom(const RPSGame& other) {
    players = new Player* [other.capacity];
    for (size_t i = 0; i < other.size; i++) {
        players[i] = other.players[i]->clone();
    }
    size = other.size;
    capacity = other.capacity;
}

void RPSGame::moveFrom(RPSGame&& other) noexcept {
    players = other.players;
    other.players = nullptr;
    size = other.size;
    capacity = other.capacity;
    other.size = other.capacity = 0;
}

RPSGame::RPSGame(size_t playersCount) : capacity(playersCount) {
    players = new Player* [playersCount];
}

void RPSGame::addPlayer(Player* player) {
    if (player == nullptr) {
        throw std::invalid_argument("Player is null");
    }

    if (size >= capacity) {
        throw std::runtime_error("Maximum players count already reached!");
    }

    players[size++] = player;
}

RPSGame::RPSGame(const RPSGame& other) {
    copyFrom(other);
}

RPSGame::RPSGame(RPSGame&& other) noexcept {
    moveFrom(std::move(other));
}

RPSGame& RPSGame::operator=(const RPSGame& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

RPSGame& RPSGame::operator=(RPSGame&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

RPSGame::~RPSGame() {
    free();
}

size_t RPSGame::getPlayersCount() const {
    return capacity;
}

bool RPSGame::isValidIndex(size_t index) const {
    return index < size;
}

size_t RPSGame::simulateDuel(size_t firstPlayerIndex, size_t secondPlayerIndex) const {
    if (!isValidIndex(firstPlayerIndex) || !isValidIndex(secondPlayerIndex)) {
        throw std::invalid_argument("Invalid player index!");
    }

    if (firstPlayerIndex == secondPlayerIndex) {
        return 0;
    }

    return players[firstPlayerIndex]->playAgainst(players[secondPlayerIndex]);
}

size_t RPSGame::simulateTournament() const {
    int maxResult = INT_MIN;
    size_t winnerIndex = 0;
    for (size_t i = 0; i < size; i++) {
        int currentResult = 0;
        for (size_t j = 0; j < size; j++) {
            currentResult += simulateDuel(i, j);
        }

        if (currentResult > maxResult) {
            winnerIndex = i;
            maxResult = currentResult;
        }
    }
    return winnerIndex;
}
