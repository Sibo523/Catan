#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility> // for std::pair
#include "Tile.h"
#include <iostream>
class Board {
public:
    Board();
    void placeRobber(int x, int y);
    void moveRobber(int x, int y);
    void generateResources(int diceRoll);
    void setupBoard();
    void printBoard();
    void getTile(size_t x, size_t y);
    std::vector<std::vector<Tile>> getTiles();
    std::vector<std::vector<Tile>> tiles;

    // friend std::ostream& operator<<(std::ostream& os,Board& b);//print the graph

private:
    // helper function
    bool checkValidTile(int x, int y);

    //for the vertices
    void put3254(int x, int y,Vertex v1, Vertex v2);
    void fourToOne(int x, int y);
    void sixToTwo(int x, int y);
    //for the hexagons
    void initializeVertices();
    //didn't do yet
    std::vector<std::pair<int, int>> ports;
    std::pair<int, int> robberPosition;
    int generate_number_token(std::vector<std::pair<int,int>> &numberTokens );
    std::string generate_resource(    std::vector<std::pair<std::string,int>>& numberTokens);
};

#endif // BOARD_H
