#include "Settlement.h"

Settlement::Settlement(Player& ownerPlayer, std::pair<int, int> loc) 
    : owner(ownerPlayer), location(loc) {}

void Settlement::upgradeToCity() {
    // Logic to upgrade settlement to city
}
