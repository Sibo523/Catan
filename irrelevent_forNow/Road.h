#ifndef ROAD_H
#define ROAD_H

#include <utility> // for std::pair
#include "Player.h"

class Road {
public:
    Road(Player& owner, std::pair<int, int> startLocation, std::pair<int, int> endLocation);

private:
    Player& owner;
    std::pair<int, int> startLocation;
    std::pair<int, int> endLocation;
};

#endif // ROAD_H
