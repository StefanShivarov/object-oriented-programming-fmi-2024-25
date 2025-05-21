#include "HeterogeneousContainer.hpp"
#include "Item.h"
#include "Player.h"
#include "Tank.h"
#include "Mage.h"
#include "HealthPotion.h"
#include "ManaPotion.h"

int main() {
    HeterogeneousContainer<Player> players;
    HeterogeneousContainer<Item> items;

    players.addObject(new Tank("stefo", 1000));
    players.addObject(new Mage("mage", 550, 1200));

    items.addObject(new HealthPotion());
    items.addObject(new ManaPotion());

    players[0]->printStats();
    players[0]->accept(items[0]);
    players[0]->printStats();
    players[0]->accept(items[1]);
    players[0]->printStats();

    players[1]->printStats();

    players[1]->accept(items[0]);
    players[1]->printStats();
    players[1]->accept(items[1]);
    players[1]->printStats();
}
