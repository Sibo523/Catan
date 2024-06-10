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
    std::cout<<"*******************************"<<std::endl;
    gameManager.get(1,0);
    gameManager.get(1,1);
    gameManager.get(1,2);
    gameManager.get(1,3);

    return 0;
}
