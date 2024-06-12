#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility> // for std::pair
#include <iostream>
#include <iomanip>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_set>
#include "Tile.h"
// #include "Settlement.h"

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

class Board {
public:
    Board();
    ~Board();

    void placeRobber(int x, int y); // not implmented yet but it enters into the tile and turn off the flag tha allows me to get resources
    void moveRobber(int x, int y); //undo the tiles so it can get resources and do the same thing as place robber
    void generateResources(int diceRoll); //give the resources to the playres assigned to that tile according to the settelments
    void setupBoard();
    void printBoard();
    void getTile(size_t x, size_t y);
    std::vector<std::vector<Tile>> getTiles();
    bool buildSet(int x, int y, int z,Player* player);
    void printTileSet(int x, int y);
    bool upgradeToCity(int x, int y, int z,Player* player);
    Vertex* getVertex(int x, int y, int z);
    // friend std::ostream& operator<<(std::ostream& os,Board& b);//print the graph

private:
    std::vector<std::vector<Tile>> tiles;

    // helper function
    bool checkValidTile(size_t x, size_t y);
    void ReleventTiles(int, std::vector<std::pair<Tile,int>> &tiles);
    //for the vertices
    void put3254(int x, int y,Vertex* v1, Vertex* v2);
    void fourToOne(int x, int y);
    void sixToTwo(int x, int y);
    //for the hexagons
    void initializeVertices();
    void initializeTiles();
    //didn't do yet
    std::vector<std::pair<int, int>> ports;
    std::pair<int, int> robberPosition;
    //to create the tiles
    int generate_number_token(std::vector<std::pair<int,int>> &numberTokens );
    std::string generate_resource(    std::vector<std::pair<std::string,int>>& numberTokens);
};

#endif // BOARD_H
