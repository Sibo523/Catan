#include "GameManager.h"

GameManager::GameManager(std::vector<Player> gamePlayers)
    : players(gamePlayers), currentTurn(0), gameState("not started") {}

// GameManager::GameManager() :currentTurn(0), gameState("not started") {}
GameManager::~GameManager(){
    
}
void GameManager::startGame()
{
    gameState = "started";
    board.printBoard();
}

void GameManager::endGame()
{
    gameState = "ended";
    // Additional logic to end the game
}
void GameManager::play()
{

    std::cout <<RED<< "Player " << players[currentTurn].getName() << "'s turn" << std::endl<<RESET_TEXT;
    int dice = rand() % 6 + 1 + rand() % 6 + 1;
    std::cout << "Dice rolled: " << dice << std::endl;
    board.generateResources(dice);
    int choice;
    do
    {
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Build Settlement\n";
        std::cout << "2. Buy Development Card\n";
        std::cout << "3. Build Road\n";
        std::cout << "4. Upgrade Settlement to City\n";
        std::cout << "5. Trade with Other Players\n";
        std::cout << "6. next turn\n";
        std::cout << "7. print board\n";
        std::cout << "8. show resources\n";
        std::cout << "Enter your choice (1-8): ";
        std::cin >> choice;
        int x,y,z;
        switch (choice)
        {
        case 1:
            
            std::cout << "Building a settlement give me x,y for tile and the vertex z" << std::endl;
            std::cin>>x>>y>>z;
            std::cout<< (BuildSettlement(x,y,z,getPlayer())? "Settlement built successfully" : "Settlement build failed")<<std::endl;
            getSettlmets(x,y);

            break;
        case 2:
            // getPlayer().buyDevelopmentCard();
            break;
        case 3:
            std::cin>>x>>y>>z;
           // buildRoad();
           std::cout<<( buildRoad(x,y,z)? "Road built successfully" : "Road build failed")<<std::endl;
            showRoads(x,y);
            break;
        case 4:
            std::cout << "upgrading the settlment in x,y,z , z is between 1 to 6" << std::endl;
            std::cin>>x>>y>>z;
            std::cout<<(upgradeToCity(x,y,z) ? "City upgraded successfully" : "City upgrade failed")<<std::endl;
            getSettlmets(x,y);
            break;
        case 5:
            // tradeWithOtherPlayers();
            break;
        case 6:
            nextTurn();
            break;
        case 7:
            printBoard();
            break;
        case 8:
            std::cout<<getPlayer()->showResources();
            break;
        default:
            std::cout << "Invalid choice. Please enter a number from 1 to 6." << std::endl;
        }

    } while (choice != 6);
}

void GameManager::nextTurn()
{
    currentTurn = (currentTurn + 1) % players.size();
    // Additional logic to handle turn transition
}
void GameManager::get(size_t row, size_t col)
{
    board.getTile(row, col);
}
void GameManager::getSettlmets(int x, int y)
{
    board.printTileSet(x, y);
}
Player* GameManager::getPlayer()
{
    return &players[currentTurn];
}
bool GameManager::BuildSettlement(size_t row, size_t col, int z, Player *player)
{
    return board.buildSet(row, col, z, player);
}
bool GameManager::upgradeToCity(int x, int y, int z)
{
    return board.upgradeToCity(x, y, z, getPlayer());
}
bool GameManager::buildRoad(int x, int y, int z)
{
    return board.buildRoad(x, y, z, getPlayer());
}
void GameManager::printBoard()
{
    board.printBoard();
}
void GameManager::showRoads(int x, int y)
{
    board.showRoads(x, y);
}

bool GameManager::checkWinCondition()
{
    // Logic to check if a player has won the game
    for (Player player : players)
    {
        if (player.getVictoryPoints() >= 10)
        {
            return true;
        }
    }
    return false;
}
