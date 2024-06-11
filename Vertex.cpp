#include "Vertex.h"
Vertex::Vertex(int owner, int numberToken) : owner(owner), numberToken(numberToken) {}


std::string Vertex::getOwner()
{
    return std::to_string(owner);
}
int Vertex::getOwnerint()
{
    return owner;
}
//cannot unsettle
void Vertex::settle()
{
    flag = true;
}
bool Vertex::isSettled()
{
    return flag;
}