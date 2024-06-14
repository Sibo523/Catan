#include "Road.h"
#define RESET_TEXT "\033[0m"

Road::Road(Player* ownerPlayer) 
    : owner(ownerPlayer) {}
Player Road::getOwner() const {
    return *owner;
}
Player* Road::getOwnerPtr() {
    return owner;
}
void Road::setOwner(Player* newOwner){
    owner = newOwner;
}
void Road::print(){
    std::cout << owner->getColor()<<"Road owned by " << owner->getName()<<RESET_TEXT;
}