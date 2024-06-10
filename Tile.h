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
private:
    std::string type; // e.g., "wood", "brick", "sheep", "wheat", "ore", "desert"
    int numberToken;
    std::vector<Vertex> adjacentVertices; // coordinates of vertices run on adjacent to check for settlements
    // std::vector<std::pair<int, int>> players; // coordinates of edges
};

#endif // TILE_H

