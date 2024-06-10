#include <iostream>
#include "Board.h"
#include "GameManager.h"
// #include "Player.h"

int main() {
    // Initialize the game manager
    GameManager gameManager;
    gameManager.startGame();
    gameManager.get(0,0);
    gameManager.get(0,1);
    gameManager.get(0,2);

    return 0;
}
