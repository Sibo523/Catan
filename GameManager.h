#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
// #include "Player.h"
#include "Board.h"

class GameManager
{
public:
    // GameManager(std::vector<Player> players);
    GameManager(std::vector<Player> gamePlayers);
    ~GameManager();
    void startGame();
    void endGame();
    void nextTurn();
    bool checkWinCondition();
    void get(size_t row, size_t col);
    bool BuildSettlement(size_t row, size_t col, int z, Player *name, bool flag);
    void printBoard();
    void getSettlmets(int x, int y);
    bool upgradeToCity(int x, int y, int z);
    Player *getPlayer();
    void play();
    bool buildRoad(int, int, int, Player *player);
    void showRoads(int, int);

private:
    void firstRound();
    friend void YearOfPlenty(GameManager *gameManager);
    friend void Monopoly(GameManager *gameManager);
    friend void RoadBuilding(GameManager *gameManager);
    friend void Knight(GameManager *gameManager);
    std::vector<Player> players;
    Board board;
    int currentTurn;
    std::string gameState;
    bool tradeWithOtherPlayers(size_t other, std::map<std::string, int> resourcesGiven, std::map<std::string, int> resourcesReceived);
    bool BuyDevelopmentCard(Player *player);
    bool useDevelopmentCard(Player *player, std::string cardType);
};

#endif // GAMEMANAGER_H
