#ifndef ROAD_H
#define ROAD_H

#include <utility> // for std::pair
#include "Player.h"

class Road {
public:
    Road(Player* owner);
    Player getOwner() const;
    Player* getOwnerPtr();
    void print();
    void setOwner(Player* newOwner);
private:
    Player* owner;
};

#endif // ROAD_H
