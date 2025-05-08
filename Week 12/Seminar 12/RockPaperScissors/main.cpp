#include <iostream>
#include <fstream>
#include "RPSGame.h"
#include "RPSPlayerFactory.h"

int main() {
    // from text file
    {
        std::ifstream ifs("players.txt");
        if (!ifs.is_open())
        {
            std::cout << "Error opening file!";
            return -1;
        }

        size_t playersCount;
        ifs >> playersCount;
        RPSGame game(playersCount);

        for (size_t i = 0; i < playersCount; i++)
        {
            game.addPlayer(RPSPlayerFactory::createPlayer(ifs));
        }
        std::cout << game.simulateTournament();
    }

    // from console
    {
        size_t playersCount;
        std::cin >> playersCount;
        RPSGame game(playersCount);

        for (size_t i = 0; i < playersCount; i++)
        {
            game.addPlayer(RPSPlayerFactory::createPlayer(std::cin));
        }
        std::cout << game.simulateTournament();
    }
}
