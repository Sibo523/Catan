#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <utility> // for std::pair
#include "Player.h"

class Settlement {
public:
    Settlement(Player& owner);
    void upgradeToCity(); //will change from 1 to 2
    Player getOwner() const;
    int getAmount() const; // if there's two then it's a city
private:
    int amount; //or 1 or 2
    Player& owner;
    std::pair<int, int> location;
};

#endif // SETTLEMENT_H
