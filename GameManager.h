#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
// #include "Player.h"
#include "Board.h"

class GameManager
{
public:
    GameManager(std::vector<Player> gamePlayers);
    ~GameManager();

    void startGame(); // start the first round

    bool checkWinCondition();                // checks if the current player have 10 victory points
    void play();                             // big switch case
    bool upgradeToCity(int x, int y, int z); // settlement to city
    Player *getPlayer();

    // build things could and should be private but here for the test
    bool BuildSettlement(size_t row, size_t col, int z, Player *name, bool flag);
    bool buildRoad(int, int, int, Player *player);

    // Print
    void get(size_t row, size_t col); // print
    void getSettlmets(int x, int y);  // print
    void printBoard();                // prnt
    void showRoads(int, int);         // print
    void endGame();                   // end the game, not used really cause no reason
private:
    // players that play the game
    std::vector<Player> players;
    // the board in which the game is played upon
    Board board;

    void firstRound();
    void nextTurn(); // switch to the next player in the list

    // use Cards
    friend void YearOfPlenty(GameManager *gameManager);
    friend void Monopoly(GameManager *gameManager);
    friend void RoadBuilding(GameManager *gameManager);
    friend void Knight(GameManager *gameManager); // technically it is a easy function I will implement in the future
    int currentTurn;
    std::string gameState;
    bool tradeWithOtherPlayers(size_t other, std::map<std::string, int> resourcesGiven, std::map<std::string, int> resourcesReceived);
    bool BuyDevelopmentCard(Player *player);
    bool useDevelopmentCard(Player *player, std::string cardType);
    void giveFirstRoundResources(Player *player, int x);
};

#endif // GAMEMANAGER_H
