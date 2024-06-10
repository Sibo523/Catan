#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <utility> // for std::pair
#include "Player.h"

class Settlement {
public:
    Settlement(Player& owner, std::pair<int, int> location);
    void upgradeToCity();

private:
    Player& owner;
    std::pair<int, int> location;
};

#endif // SETTLEMENT_H
