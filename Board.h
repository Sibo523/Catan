#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility> // for std::pair
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_set>
#include "Tile.h"
#include "Card.h"
#include <memory>
#include <algorithm>

// #include "Settlement.h"

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

class Board
{
public:
    Board();
    ~Board();

    void placeRobber(int x, int y);       // I have not been asked to implment this, but technically it's just a flag on the tile
    void moveRobber(int x, int y);        // undo the tiles so it can get resources and do the same thing as place robber
    void generateResources(int diceRoll); // give the resources to the playres assigned to that tile according to the settelments

    void printBoard();                // print
    void getTile(size_t x, size_t y); // print
    void printTileSet(int x, int y);  // print
    void showRoads(int x, int y);     // print

    // building things
    bool buildRoad(int x, int y, int z, Player *player);
    bool buildSet(int x, int y, int z, Player *player, bool); //
    bool upgradeToCity(int x, int y, int z, Player *player);

    // trade
    bool tradeResources(Player &me, Player &other, std::map<std::string, int> offer, std::map<std::string, int> request);
    // buy development card
    bool BuyDevelopmentCard(Player *player);
    // called only in the first round that everyone puts the second settlement
    void giveFirstRoundResources(Player *player, int x);
    // get the pointer to the Vertex
    Vertex *getVertex(int x, int y, int z);
    // std::vector<std::vector<Tile>> getTiles(); //not used

private:
    // initilize
    void setupBoard(); // init
    void setupCards(); // init
    // feilds of the board
    std::vector<std::vector<Tile>> tiles;
    std::vector<Card *> cards;
    // defult player for the initilization of the roads
    Player *player = new Player("", "");
    // helper function
    bool checkValidTile(size_t x, size_t y);
    void ReleventTiles(int, std::vector<std::pair<Tile, int>> &tiles);
    // for connecting vertices
    void put3254(int x, int y, Vertex *v1, Vertex *v2);
    void fourToOne(int x, int y);
    void sixToTwo(int x, int y);
    // for connectiong roads
    void connect5to2(int x, int y, Road *r1);
    void connect1to4(int x, int y, Road *r1);
    void connect6to3(int x, int y, Road *r1);
    // for entire map called buy setupBoard
    void initializeVertices();
    void initializeTiles();
    void initializeRoads();

    // to create the tiles
    int generate_number_token(std::vector<std::pair<int, int>> &numberTokens);
    std::string generate_resource(std::vector<std::pair<std::string, int>> &numberTokens);
    // for the roads to check if I can build there
    bool switchy(int x, int y, int z, Player *player);
    bool rightSet(int x, int y, int z, Player *player);
    bool switchRoad(int x, int y, int z, Player *player);
    bool checkforRoad(int x, int y, int z, Player *player);
    bool switchRoadforSettlment(int x, int y, int z, Player *player);

    // didn't do maybe in the future
    std::vector<std::pair<int, int>> ports;
    std::pair<int, int> robberPosition;
};

#endif // BOARD_H
