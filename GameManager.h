#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
// #include "Player.h"
#include "Board.h"

class GameManager {
public:
    // GameManager(std::vector<Player> players);
    GameManager();
    void startGame();
    void endGame();
    void nextTurn();
    bool checkWinCondition();
    void get(size_t row, size_t col);
private:
    // std::vector<Player> players;
    Board board;
    int currentTurn;
    std::string gameState;
};

#endif // GAMEMANAGER_H
