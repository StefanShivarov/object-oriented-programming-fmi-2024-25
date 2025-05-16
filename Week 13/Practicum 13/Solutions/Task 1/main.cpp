#include "Battleground.h"

int main(int argc, const char * argv[]) {
    Beast* beast1 = new Minotaur();
    Beast* beast2 = new Centaur();
    Beast* beast3 = new Sphinx();
    Beast* beast4 = new Minotaur();
    Beast* beast5 = new Minotaur();
    Beast* beast6 = new Sphinx();
    Beast* beast7 = new Sphinx();
    
    const Beast* beasts[7] = {beast1,beast2,beast3,beast4,beast5,beast6,beast7};
    BattleGround game(beasts, 7);
    Beast* player = game.getBeastOnIndex(1);
    
    size_t battlesWon = game.beastsBeatenByMonster(player);
    std::cout<<battlesWon<<std::endl;

    delete beast1;
    delete beast2;
    delete beast3;
    delete beast4;
    delete beast5;
    delete beast6;
    delete beast7;
    delete player;
}
