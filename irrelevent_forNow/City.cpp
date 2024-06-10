#include "City.h"

City::City(Player& ownerPlayer, Tile tl,std::pair<int, int> loc) 
    : Settlement(ownerPlayer, loc) {}
