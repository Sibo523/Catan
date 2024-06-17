#include <iostream>
#include "Board.h"
#include "GameManager.h"

#define GREEN_TEXT "\033[1;32m"
#define lm_TEXT "\033[1;39m"
int main()
{
    // Initialize the game manager
    Player *player1 = new Player("player1", GREEN_TEXT);
    Player *player2 = new Player("player2", CYAN);
    std::map<std::string, int> resources = {{"wood", 6}, {"brick", 6}, {"sheep", 6}, {"wheat", 6}, {"ore", 6}};
    player1->addResources(resources);
    player2->addResources(resources);
    GameManager gameManager({*player1, *player2});
    gameManager.startGame();
    std::cout << "\n";
    int counter = 0;
    while (!gameManager.checkWinCondition())
    {
        counter++;
        gameManager.play();
        if (counter == 2) // just go throw 2 rounds
        {
            break;
        }
    }
    delete player1;
    delete player2;
    return 0;
}
/*
    more usage of functions!
*/

// gameManager.get(0,0);
// gameManager.get(0,1);
// gameManager.get(0,2);
// std::cout<<"*******************************"<<std::endl;
//   gameManager.get(0,0);
// gameManager.get(0,1);
// gameManager.get(0,2);
// bool man = gameManager.BuildSettlement(0,0,1,"player1");
// std::cout<<"\n\n\n"<<man<<"\n\n\n";
// gameManager.printBoard();

// bool man;
// man = gameManager.BuildSettlement(0,1,4,"player1");
// man = gameManager.BuildSettlement(0,0,5,"player1");
// man = gameManager.BumakeildSettlement(0,0,2,"player1");
// gameManager.get
// gameManager.getSettlmets(0,0);
// gameManager.BuildSettlement(0,0,5,"player1");
// gameManager.getSettlmets(0,0);
// gameManager.getSettlmets(0,1);
// gameManager.getSettlmets(1,0);
// gameManager.getSettlmets(1,1);
// gameManager.getSettlmets(0,2);

// gameManager.printBoard();
//  gameManager.getSettlmets(0,2);