#ifndef SETTLEMENT_H
#define SETTLEMENT_H

// #include <utility> // for std::pair
#include "Player.h"

class Settlement {
public:
    Settlement(Player* owner);
    ~Settlement();
    void upgradeToCity(); //will change from 1 to 2
    Player getOwner() const;
    Player* getOwnerPtr();
    int getAmount() const; // if there's two then it's a city
private:
    int amount; //or 1 or 2
    Player* owner;
};

#endif // SETTLEMENT_H
