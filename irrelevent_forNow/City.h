#ifndef CITY_H
#define CITY_H

#include "Settlement.h"
#include "Tile.h"
class City : public Settlement {
public:
    City(Player& owner, Tile tl,std::pair<int, int> location);
};

#endif // CITY_H
