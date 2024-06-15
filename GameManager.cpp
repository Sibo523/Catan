#include "GameManager.h"
#include <iostream>
#include <vector>
#include <map>
GameManager::GameManager(std::vector<Player> gamePlayers)
    : players(gamePlayers), currentTurn(0), gameState("not started") {}

// GameManager::GameManager() :currentTurn(0), gameState("not started") {}
GameManager::~GameManager()
{
}
void GameManager::startGame()
{
    gameState = "started";
    board.printBoard();
    firstRound();
}

void GameManager::endGame()
{
    gameState = "ended";
    // Additional logic to end the game
}
void GameManager::play()
{

    std::cout << RED << "Player " << players[currentTurn].getName() << "'s turn" << std::endl
              << RESET_TEXT;
    int dice = rand() % 6 + 1 + rand() % 6 + 1;
    std::cout << "Dice rolled: " << dice << std::endl;
    board.generateResources(dice);
    int choice;
    do
    {
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Build Settlement\n";           // did
        std::cout << "2. Buy Development Card\n";       // need to do
        std::cout << "3. Build Road\n";                 // did
        std::cout << "4. Upgrade Settlement to City\n"; // did
        std::cout << "5. Trade with Other Players\n";   // did
        std::cout << "6. next turn\n";                  // did
        std::cout << "7. print board\n";                // did but I want to change something related the set and city
        std::cout << "8. show resources\n";             // dids
        std::cout << "Enter your choice (1-8): \n";
        std::cin >> choice;
        int x, y, z;

        int player = 0, wood_r = 0, brick_r = 0, sheep_r = 0, wheat_r = 0, ore_r = 0;
        int wood_g = 0, brick_g = 0, sheep_g = 0, wheat_g = 0, ore_g = 0;

        std::map<std::string, int> give;
        std::map<std::string, int> get;
        std::string input;
        switch (choice)
        {
        case 1:

            std::cout << "Building a settlement give me x,y for tile and the vertex z" << std::endl;
            std::cin >> x >> y >> z;
            std::cout << (BuildSettlement(x, y, z, getPlayer()) ? "Settlement built successfully" : "Settlement build failed") << std::endl;
            getSettlmets(x, y);

            break;
        case 2:
            // getPlayer().buyDevelopmentCard();
            break;
        case 3:
            std::cin >> x >> y >> z;
            std::cout << (buildRoad(x, y, z,getPlayer()) ? "Road built successfully" : "Road build failed") << std::endl;
            showRoads(x, y);
            break;
        case 4:
            std::cout << "upgrading the settlment in x,y,z , z is between 1 to 6" << std::endl;
            std::cin >> x >> y >> z;
            std::cout << (upgradeToCity(x, y, z) ? "City upgraded successfully" : "City upgrade failed") << std::endl;
            getSettlmets(x, y);
            break;
        case 5: // need to check why I can intilize things in switch case :()
            std::cout << "Trading!\n";
            std::cout << "who do you want to trade with? ";
            std::cin >> player;
            std::cout << "what do you want to give? \n wood brick sheep wheat ore\n";
            std::cin >> wood_g >> brick_g >> sheep_g >> wheat_g >> ore_g;
            give["wood"] = wood_g;
            give["brick"] = brick_g;
            give["sheep"] = sheep_g;
            give["wheat"] = wheat_g;
            give["ore"] = ore_g;
            std::cout << "what do you want to get? \n wood brick sheep wheat ore\n";
            std::cin >> wood_r >> brick_r >> sheep_r >> wheat_r >> ore_r;
            get["wood"] = wood_r;
            get["brick"] = brick_r;
            get["sheep"] = sheep_r;
            get["wheat"] = wheat_r;
            get["ore"] = ore_r;
            std::cout << "second player needs to confirm the trade(y)\n"; // get means request :)
            if (std::cin >> input && input == "y")
            {
                std::cout << (tradeWithOtherPlayers(player, give, get) ? "Trade successful" : "Trade failed") << std::endl;
            }
            break;
        case 6:
            nextTurn();
            break;
        case 7:
            printBoard();
            break;
        case 8:
            std::cout << getPlayer()->showResources();
            break;
        default:
            std::cout << "Invalid choice. Please enter a number from 1 to 6." <<choice<< std::endl;
        }

    } while (choice != 6); // I get 6 next to the next player and finish the while loop
}

void GameManager::nextTurn()
{
    currentTurn = (currentTurn + 1) % players.size();
}
void GameManager::get(size_t row, size_t col)
{
    board.getTile(row, col);
}
void GameManager::getSettlmets(int x, int y)
{
    board.printTileSet(x, y);
}
Player *GameManager::getPlayer()
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
bool GameManager::buildRoad(int x, int y, int z, Player *player)
{
    return board.buildRoad(x, y, z, player);
}
void GameManager::printBoard()
{
    board.printBoard();
}
void GameManager::showRoads(int x, int y)
{
    board.showRoads(x, y);
}
bool GameManager::tradeWithOtherPlayers(size_t other, std::map<std::string, int> give, std::map<std::string, int> get)
{
    return board.tradeResources(*getPlayer(), players[other], give, get);
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
void GameManager::firstRound()
{
    std::cout<<"\nFirst round\n";
    for (size_t i = 0; i < players.size(); i++)
    {
        bool choice = false,choice2 = false;
        while (!choice)
        {
            std::cout << "Player " << players[i].getName() << "'s turn" << std::endl;
            int x, y, z;
            std::cout << "Building a settlement give me x,y for tile and the vertex z" << std::endl;
            std::cin >> x >> y >> z;
            choice = BuildSettlement(x, y, z, &players[i]) ? true : (std::cout << "Settlement build failed" << std::endl, false); // hope it works
            choice2 =! choice;
            while (!choice2)
            { // if it's true then I want to build a road
                std::cout << "Building a road give me x,y for tile and the vertex z" << std::endl;
                std::cin >> x >> y >> z;
                choice2 = buildRoad(x, y, z,&players[i]) ? (std::cout << "Built a road\n", true) : false; //I want it false to end the turn
            }
        }
        std::cout<<players[i].showResources();
    }
    std::cout<<"\nSecond round\n";
for (size_t i = players.size() - 1; i != static_cast<size_t>(-1); --i)
    {
        //need to give resources don't forget
        bool choice = false,choice2 = false;
        while (!choice)
        {
            std::cout << "Player " << players[i].getName() << "'s turn" << std::endl;
            int x, y, z;
            std::cout << "Building a settlement give me x,y for tile and the vertex z" << std::endl;
            std::cin >> x >> y >> z;
            choice = BuildSettlement(x, y, z, &players[i]) ? true : (std::cout << "Settlement build failed" << std::endl, false); // hope it works
            choice2 =! choice;
            while (!choice2)
            { // if it's true then I want to build a road
                std::cout << "Building a road give me x,y for tile and the vertex z" << std::endl;
                std::cin >> x >> y >> z;
                choice2 = buildRoad(x, y, z,&players[i]) ? (std::cout << "Built a road\n", true) : false; //I want it false to end the turn
            }
        }
        std::cout<<players[i].showResources();
    }

}