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
    void initializeVertices();
    std::vector<std::pair<int, int>> ports;
    std::pair<int, int> robberPosition;
    int generate_number_token(std::vector<std::pair<int,int>> &numberTokens );
    std::string generate_resource(    std::vector<std::pair<std::string,int>>& numberTokens);
    bool checkValidTile(int x, int y);
};

#endif // BOARD_H
