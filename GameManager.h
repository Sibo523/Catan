#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
// #include "Player.h"
#include "Board.h"

class GameManager {
public:
    // GameManager(std::vector<Player> players);
    GameManager(std::vector<Player> gamePlayers);
    ~GameManager();
    void startGame();
    void endGame();
    void nextTurn();
    bool checkWinCondition();
    void get(size_t row, size_t col);
    bool BuildSettlement(size_t row, size_t col,int z, Player* name);
    void printBoard();
    void getSettlmets(int x, int y);
    bool upgradeToCity(int x, int y, int z);
    Player* getPlayer();
    void play();
    bool buildRoad(int, int ,int );
    void showRoads(int,int);
private:
    std::vector<Player> players;
    Board board;
    int currentTurn;
    std::string gameState;
};

#endif // GAMEMANAGER_H
