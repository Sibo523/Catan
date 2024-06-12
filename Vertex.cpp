#include "Vertex.h"
Vertex::Vertex(int owner, int numberToken) : owner(owner), numberToken(numberToken), flag(false) {}
Vertex::~Vertex() {}

std::string Vertex::getOwner()
{
    return std::to_string(owner);
}
int Vertex::getOwnerint()
{
    return owner;
}
// cannot unsettle
void Vertex::settle(Settlement *s)
{
    set = s;
    flag = true;
}
Player Vertex::getOwnerPlayer()
{
    if (set == nullptr)
    {
        throw std::invalid_argument("No settlement");
    }
    return set->getOwner();
}
bool Vertex::isSettled()
{
    return flag;
}

Settlement Vertex::getSettlement(){
    return *set;
}
Settlement* Vertex::getSettlementPtr(){
    return set;
}
bool Vertex::operator==(const Vertex& other) const{
    return owner == other.owner && numberToken == other.numberToken;
}
