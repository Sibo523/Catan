#include "Tile.h"
Tile::Tile(std::string tileType, int token)
    : type(tileType), numberToken(token)
{
    for (size_t i = 0; i < 6; i++)
    {
        adjacentVertices.push_back(NULL);
        adjacentRoads.push_back(NULL);
    }
}

std::string Tile::getResource() const
{
    return type;
}
int Tile::getNumberToken() const
{
    return numberToken;
}
std::string Tile::toString() const
{
    return type + "-" + std::to_string(numberToken);
}
void Tile::print()
{
    std::cout << "         " + adjacentVertices[0]->getOwner() << "-1" << std::endl; // 1
    std::cout << "   " + adjacentVertices[1]->getOwner() << "-2" << "     ";         // 2
    std::cout << "   " + adjacentVertices[2]->getOwner() << "-3" << std::endl;       // 3
    std::cout << "      " + type + "-" + std::to_string(numberToken) << std::endl;
    std::cout << "   " + adjacentVertices[3]->getOwner() << "-4" << "     ";         // 4
    std::cout << "   " + adjacentVertices[4]->getOwner() << "-5" << std::endl;       // 5
    std::cout << "         " + adjacentVertices[5]->getOwner() << "-6" << std::endl; // 6
}
void printWithColor(bool isSettled, const std::string &playerName, std::string color, Vertex *v)
{
    if (isSettled)
    {
        std::cout << color << playerName << "-" << v->getSettlement().getAmount() << RESET_TEXT;
    }
    else
    {
        std::cout << RED_TEXT << "Not" << RESET_TEXT;
    }
}
void Tile::printSettelments()
{

    std::cout << "         ";
    printWithColor(adjacentVertices[0]->isSettled(), adjacentVertices[0]->isSettled() ? adjacentVertices[0]->getOwnerPlayer().getName() : "", adjacentVertices[0]->isSettled() ? adjacentVertices[0]->getOwnerPlayer().getColor() : "",
                   adjacentVertices[0]);
    std::cout << "-1" << std::endl; // 1

    std::cout << "   ";
    printWithColor(adjacentVertices[1]->isSettled(), adjacentVertices[1]->isSettled() ? adjacentVertices[1]->getOwnerPlayer().getName() : "", adjacentVertices[1]->isSettled() ? adjacentVertices[1]->getOwnerPlayer().getColor() : "", adjacentVertices[1]);
    std::cout << "-2     "; // 2

    std::cout << "   ";
    printWithColor(adjacentVertices[2]->isSettled(), adjacentVertices[2]->isSettled() ? adjacentVertices[2]->getOwnerPlayer().getName() : "", adjacentVertices[2]->isSettled() ? adjacentVertices[2]->getOwnerPlayer().getColor() : "", adjacentVertices[2]);
    std::cout << "-3" << std::endl; // 3

    std::cout << "         " << type + "-" + std::to_string(numberToken) << std::endl;

    std::cout << "   ";
    printWithColor(adjacentVertices[3]->isSettled(), adjacentVertices[3]->isSettled() ? adjacentVertices[3]->getOwnerPlayer().getName() : "", adjacentVertices[3]->isSettled() ? adjacentVertices[3]->getOwnerPlayer().getColor() : "", adjacentVertices[3]);
    std::cout << "-4     "; // 4

    std::cout << "   ";
    printWithColor(adjacentVertices[4]->isSettled(), adjacentVertices[4]->isSettled() ? adjacentVertices[4]->getOwnerPlayer().getName() : "", adjacentVertices[4]->isSettled() ? adjacentVertices[4]->getOwnerPlayer().getColor() : "", adjacentVertices[4]);
    std::cout << "-5" << std::endl; // 5

    std::cout << "         ";
    printWithColor(adjacentVertices[5]->isSettled(), adjacentVertices[5]->isSettled() ? adjacentVertices[5]->getOwnerPlayer().getName() : "", adjacentVertices[5]->isSettled() ? adjacentVertices[5]->getOwnerPlayer().getColor() : "", adjacentVertices[5]);
    std::cout << "-6" << std::endl; // 6
}
// Vertex related functions
void Tile::printRoads()
{
    std::cout << "         ";
    if (adjacentRoads[0] != NULL)
    {
        adjacentRoads[0]->print();
        std::cout << "-1";
    }
    else
    {
        std::cout << "Not";
    }
    std::cout << std::endl; // 1

    std::cout << "   ";
    if (adjacentRoads[1] != NULL)
    {
        adjacentRoads[1]->print();
        std::cout << "-2";
    }
    else
    {
        std::cout << "Not";
    }
    std::cout << "     "; // 2

    std::cout << "   ";
    if (adjacentRoads[2] != NULL)
    {
        adjacentRoads[2]->print();
        std::cout << "-3";
    }
    else
    {
        std::cout << "Not";
    }
    std::cout << std::endl; // 3

    std::cout << "         " << type + "-" + std::to_string(numberToken) << std::endl;

    std::cout << "   ";
    if (adjacentRoads[3] != NULL)
    {
        adjacentRoads[3]->print();
        std::cout << "-4";
    }
    else
    {
        std::cout << "Not";
    }
    std::cout << "     "; // 4

    std::cout << "   ";
    if (adjacentRoads[4] != NULL)
    {
        adjacentRoads[4]->print();
        std::cout << "-5";
    }
    else
    {
        std::cout << "Not";
    }
    std::cout << std::endl; // 5

    std::cout << "         ";
    if (adjacentRoads[5] != NULL)
    {
        adjacentRoads[5]->print();
        std::cout << "-6";
    }
    else
    {
        std::cout << "Not";
    }
    std::cout << std::endl; // 6
}
void Tile::addVertex(Vertex *v, size_t index)
{
    if (index >= 7 || index < 1)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    adjacentVertices[index - 1] = v;
}
Vertex Tile::getVertex(size_t index)
{
    if (index >= 7 || index < 1)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    return *adjacentVertices[index - 1];
}
Vertex *Tile::getVertexPointer(size_t index)
{
    if (index >= 7 || index < 1)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    return adjacentVertices[index - 1];
}
void Tile::addRoad(Road *r, size_t index)
{
    if (index >= 7 || index < 1)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    adjacentRoads[index - 1] = r;
}
Road *Tile::getRoadPtr(size_t index)
{
    if (index >= 7 || index < 1)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    return adjacentRoads[index - 1];
}
// ting means settlement
bool Tile::hasting(int x)
{
    if (adjacentVertices[x - 1]->isSettled())
    { // sadge it has a settlement
        return true;
    }
    return false;
}
bool Tile::neighborSet(size_t index)
{ // returns true if one of the neighbors already have setllments means I can't build here
    switch (index)
    {
    case 1:
        return hasting(2) || hasting(3);
        break;

    case 2:
        return hasting(1) || hasting(4);
        break;

    case 3:
        return hasting(1) || hasting(5);
        break;

    case 4:
        return hasting(2) || hasting(6);
        break;

    case 5:
        return hasting(3) || hasting(6);
        break;

    case 6:
        return hasting(4) || hasting(5);
        break;

    default:
        std::cout << "Index out of bounds in Tile::neighborSet()";
        return false;
        break;
    }
}