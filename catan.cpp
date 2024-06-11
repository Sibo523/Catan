#include <iostream>
#include "Board.h"
#include "GameManager.h"
// #include "Player.h"

int main() {
    // Initialize the game manager
    GameManager gameManager;
    gameManager.startGame();
    // gameManager.get(0,0);
    // gameManager.get(0,1);
    // gameManager.get(0,2);
    // std::cout<<"*******************************"<<std::endl;
    // gameManager.get(1,1);
    // gameManager.get(1,2);
    // gameManager.get(1,3);
    // bool man = gameManager.BuildSettlement(0,0,1,"player1");
    // std::cout<<"\n\n\n"<<man<<"\n\n\n";
    // gameManager.printBoard();
    
    bool man;
    man = gameManager.BuildSettlement(0,0,3,"player1");
    man = gameManager.BuildSettlement(0,1,4,"player1");
    // man = gameManager.BuildSettlement(0,0,5,"player1");
    // man = gameManager.BuildSettlement(0,0,6,"player1");
    
    gameManager.getSettlmets(0,0);

    gameManager.getSettlmets(0,1);
    return 0;
}
