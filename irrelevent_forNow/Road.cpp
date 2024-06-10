#include "Road.h"

Road::Road(Player& ownerPlayer, std::pair<int, int> startLoc, std::pair<int, int> endLoc) 
    : owner(ownerPlayer), startLocation(startLoc), endLocation(endLoc) {}
