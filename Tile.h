#ifndef TILE_H
#define TILE_H

#include <vector>
#include <utility> // for std::pair
#include <string>
#include <array>
#include <stdexcept>
#include <iostream>

#include "Vertex.h"
#include "Road.h"

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

class Tile {
public:
    Tile(std::string type, int numberToken);
    std::string getResource() const;
    int getNumberToken() const;
    std::string toString() const;
    void addVertex(Vertex* v,size_t index);
    void print();
    Vertex getVertex(size_t index);
    Vertex* getVertexPointer(size_t index);
    bool neighborSet(size_t index);
    void printSettelments();
    void printRoads();
    //Road related functions 
    void addRoad(Road *r, size_t index);
    Road* getRoadPtr(size_t index);
private:
    //needs to contains a settelment if it's null then we good
    bool hasting(int x);
    std::string type; // e.g., "wood", "brick", "sheep", "wheat", "ore", "desert"
    int numberToken;
    std::vector<Vertex*> adjacentVertices; // coordinates of vertices run on adjacent to check for settlements
    std::vector<Road*> adjacentRoads; // coordinates of vertices run on adjacent to check for settlements

    // std::vector<std::pair<int, int>> players; // coordinates of edges
};

#endif // TILE_H

