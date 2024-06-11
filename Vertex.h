#ifndef Vertex_H
#define Vertex_H

#include <vector>
#include <utility> // for std::pair
#include <string>
// #include "Settlement.h"

class Vertex
{

public:
    Vertex(int owner, int numberToken); // no need for owner I think
    std::string getOwner();
    bool isSettled();
    void settle();
    int getOwnerint();
private:
    bool flag = false;
    int owner; // e.g., "wood", "brick", "sheep", "wheat", "ore", "desert"
    int numberToken;
};

#endif // Vertex_H
