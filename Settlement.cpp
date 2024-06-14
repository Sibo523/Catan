#include "Settlement.h"

Settlement::Settlement(Player* ownerPlayer ) 
    : owner(ownerPlayer),amount(1){} // this initializes works
Settlement::~Settlement() {
}
Player Settlement::getOwner() const {
    return *owner;
}
Player* Settlement::getOwnerPtr() {
    return owner;
}
void Settlement::upgradeToCity() {
    amount = 2;    
}
int Settlement::getAmount() const {
    return amount;
}