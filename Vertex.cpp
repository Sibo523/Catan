#include "Vertex.h"
Vertex::Vertex(int owner, int numberToken) : owner(owner), numberToken(numberToken) {}

std::string Vertex::getOwner()
{
    return std::to_string(owner);
}