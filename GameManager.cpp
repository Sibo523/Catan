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
        std::cout << "2. Buy Development Card\n";       // doing
        std::cout << "3. Build Road\n";                 // did
        std::cout << "4. Upgrade Settlement to City\n"; // did
        std::cout << "5. Trade with Other Players\n";   // did
        std::cout << "6. next turn\n";                  // did
        std::cout << "7. print board\n";                // did but I want to change something related the set and city
        std::cout << "8. show resources\n";             // dids
        std::cout << "9. use development card\n";       // need to do
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
            std::cout << (BuildSettlement(x, y, z, getPlayer(), true) ? "Settlement built successfully" : "Settlement build failed") << std::endl;
            getSettlmets(x, y);
            showRoads(x, y);
            break;
        case 2:
            std::cout << (BuyDevelopmentCard(getPlayer()) ? "Development card bought successfully" : "Development card buy failed") << std::endl;
            break;
        case 3:
            std::cin >> x >> y >> z;
            std::cout << (buildRoad(x, y, z, getPlayer()) ? "Road built successfully" : "Road build failed") << std::endl;
            showRoads(x, y);
            break;
        case 4:
            std::cout << "upgrading the settlment in x,y,z , z is between 1 to 6" << std::endl;
            std::cin >> x >> y >> z;
            std::cout << (upgradeToCity(x, y, z) ? "City upgraded successfully" : "City upgrade failed") << std::endl;
            getSettlmets(x, y);
            break;
        case 5:
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
                std::cout << "after\n"
                          << getPlayer()->showResources();
                std::cout << (tradeWithOtherPlayers(player, give, get) ? "Trade successful" : "Trade failed") << std::endl;
                std::cout << "before:\n"
                          << getPlayer()->showResources();
            }
            break;
        case 6:
            nextTurn();
            break;
        case 7:
            printBoard();
            break;
        case 8:
            std::cout << "____________________________________________\nPlayer " << getPlayer()->getName() << "'s resources:\n";
            std::cout << getPlayer()->showResources();
            break;
        case 9:
            std::cout << "Which development card do you want to use?\n ";
            std::cout << "YearOfPlenty, Monopoly, RoadBuilding\n";
            std::cin >> input;
            std::cout << (useDevelopmentCard(getPlayer(), input) ? "Development card used successfully" : "Development card use failed") << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number from 1 to 6." << choice << std::endl;
        }

    } while (choice != 6); // I get 6 next to the next player and finish the while loop
}
void YearOfPlenty(GameManager *gameManager)
{

    std::cout << "Year of Plenty used\n";
    std::cout << "pick two resources\n";
    std::string resource1, resource2;
    std::cin >> resource1 >> resource2;
    std::map<std::string, int> resources;
    resources[resource1] = 1;
    resources[resource2] += 1;
    gameManager->getPlayer()->addResources(resources);
}
void Monopoly(GameManager *gameManager)
{
    std::string resource;
    std::cout << "Monopoly used\n";
    std::cout << "Choose a resource to take from all other players\n";
    std::cin >> resource;
    for (Player player : gameManager->players)
    {
        if (player.getName() != gameManager->getPlayer()->getName())
        {
            std::map<std::string, int> resources;
            resources[resource] = player.getResources()[resource];
            player.subtractResources(resources);
            gameManager->getPlayer()->addResources(resources);
        }
    }
}
void RoadBuilding(GameManager *gameManager)
{
    std::cout << "Road Building used\n";
    // give the player the resources to build
    std::map<std::string, int> resources;
    resources["wood"] = 1;
    resources["brick"] = 1;
    gameManager->getPlayer()->addResources(resources);
    std::cout << "Building 2 roads\n";
    int x, y, z;
    std::cout << "Building a road give me x,y for tile and the vertex z" << std::endl;
    std::cin >> x >> y >> z;
    gameManager->buildRoad(x, y, z, gameManager->getPlayer());
    std::cout << "Building a road give me x,y for tile and the vertex z" << std::endl;
    std::cin >> x >> y >> z;
    gameManager->buildRoad(x, y, z, gameManager->getPlayer());
}
void Knight(GameManager *gameManager)
{
    std::cout << "Knight used\n";
    // move the robber no need for this
    // steal a resource //and this
    // knight counter +=1
    gameManager->getPlayer()->addKnight();
    int max = 0;
    for (Player player : gameManager->players)
    {
        if (player.getKnightCount() > max)
        {
            max = player.getKnightCount();
        }
    }
    for (Player player : gameManager->players)
    {
        if (player.getKnightCount() == max) // if two players have the same it should give the first that got it but I don't need to do this
        {
            player.largestArmy();
            break;
        }
    }
}
bool GameManager::useDevelopmentCard(Player *player, std::string cardType)
{
    std::map<std::string, void (*)(GameManager *)> casemap;
    casemap["YearOfPlenty"] = &YearOfPlenty;
    casemap["Monopoly"] = &Monopoly;
    casemap["RoadBuilding"] = &RoadBuilding;
    if (player->useDevelopmentCard(cardType))
    {
        casemap[cardType](this);
        return true;
    }
    return false;
}
void GameManager::nextTurn()
{
    currentTurn = (currentTurn + 1) % players.size();
    std::cout << currentTurn << "\n";
    fflush(stdout);
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
bool GameManager::BuildSettlement(size_t row, size_t col, int z, Player *player, bool flag)
{
    return board.buildSet(row, col, z, player, flag);
}
bool GameManager::BuyDevelopmentCard(Player *player)
{
    return board.BuyDevelopmentCard(player);
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
void GameManager::giveFirstRoundResources(Player *player, int x)
{
    board.giveFirstRoundResources(player, x);
}
void GameManager::firstRound()
{
    std::cout << "\nFirst round\n";
    for (size_t i = 0; i < players.size(); i++)
    {
        std::map<std::string, int> resources = {{"wood", 4}, {"brick", 4}, {"sheep", 2}, {"wheat", 2}, {"ore", 0}};
        players[i].addResources(resources);
        bool choice = false, choice2 = false;
        while (!choice)
        {
            std::cout << "Player " << players[i].getName() << "'s turn" << std::endl;
            int x, y, z;
            std::cout << "Building a settlement give me x,y for tile and the vertex z" << std::endl;
            std::cin >> x >> y >> z;
            choice = BuildSettlement(x, y, z, &players[i], false) ? true : (std::cout << "Settlement build failed" << std::endl, false); // hope it works
            choice2 = !choice;
            while (!choice2)
            { // if it's true then I want to build a road
                std::cout << "Building a road give me x,y for tile and the vertex z" << std::endl;
                std::cin >> x >> y >> z;
                choice2 = buildRoad(x, y, z, &players[i]) ? (std::cout << "Built a road\n", true) : false; // I want it false to end the turn
            }
        }
        std::cout << players[i].showResources();
    }
    std::cout << "\nSecond round\n";
    for (size_t i = players.size() - 1; i != static_cast<size_t>(-1); --i)
    {
        // need to give resources don't forget
        bool choice = false, choice2 = false;
        while (!choice)
        {
            std::cout << "Player " << players[i].getName() << "'s turn" << std::endl;
            int x, y, z;
            std::cout << "Building a settlement give me x,y for tile and the vertex z" << std::endl;
            std::cin >> x >> y >> z;
            choice = BuildSettlement(x, y, z, &players[i], false) ? true : (std::cout << "Settlement build failed" << std::endl, false); // hope it works
            x = board.getVertex(x, y, z)->getOwnerint();
            giveFirstRoundResources(&players[i], x);
            if (choice) // need to give resources
            {
            }
            choice2 = !choice;
            while (!choice2)
            { // if it's true then I want to build a road
                std::cout << "Building a road give me x,y for tile and the vertex z" << std::endl;
                std::cin >> x >> y >> z;
                choice2 = buildRoad(x, y, z, &players[i]) ? (std::cout << "Built a road\n", true) : false; // I want it false to end the turn
            }
        }
        std::cout << players[i].showResources();
    }
}