#ifndef TILE_H
#define TILE_H

#include <vector>
#include <utility> // for std::pair
#include <string>
#include "Vertex.h"
#include <array>
class Tile {
public:
    Tile(std::string type, int numberToken);
    std::string getResource() const;
    int getNumberToken() const;
    std::string toString() const;
    void addVertex(Vertex v,size_t index);
    void print();
    Vertex getVertex(size_t index);
    Vertex* getVertexPointer(size_t index);
    bool neighborSet(size_t index);
    void printSettelments();
private:
    //needs to contains a settelment if it's null then we good
    bool hasting(int x);
    std::string type; // e.g., "wood", "brick", "sheep", "wheat", "ore", "desert"
    int numberToken;
    std::vector<Vertex> adjacentVertices; // coordinates of vertices run on adjacent to check for settlements
    // std::vector<std::pair<int, int>> players; // coordinates of edges
};

#endif // TILE_H

