#include "Settlement.h"

Settlement::Settlement(Player& ownerPlayer ) 
    : owner(ownerPlayer),amount(1){} // this initializes works

Player Settlement::getOwner() const {
    return owner;
}
void Settlement::upgradeToCity() {
    amount = 2;    
}
int Settlement::getAmount() const {
    return amount;
}