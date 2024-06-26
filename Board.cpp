#include "Board.h"
#include <iomanip>
#include <unordered_set>
#include "Card.h"
#include <random>
Board::Board()
{
    // Initialize the board
    setupBoard();
    setupCards();
}

Board::~Board()
{
    std::unordered_set<Vertex *> deletedVertices; // to not delete the same vertex twice
    std::unordered_set<Road *> deletedRoads;      // to not delete the same road twice
    delete player;
    for (int i = 0; i < cards.size(); i++)
    {
        delete cards[i]; // if there are any cards left
    }
    for (size_t i = 0; i < (size_t)tiles.size(); i++)
    {
        for (size_t j = 0; j < (size_t)tiles[i].size(); j++)
        {
            for (size_t k = 1; k < 7; k++)
            {
                Vertex *vertex = tiles[i][j].getVertexPointer(k);
                Road *road = tiles[i][j].getRoadPtr(k);

                if (road != nullptr && deletedRoads.count(road) == 0)
                {
                    delete road;
                    deletedRoads.insert(road);
                }
                if (vertex != nullptr && deletedVertices.count(vertex) == 0)
                {
                    if (vertex->isSettled())
                    {
                        delete vertex->set;
                    }
                    delete vertex;
                    deletedVertices.insert(vertex);
                }
            }
        }
    }
}

void Board::setupCards()
{
    // Logic to setup cards
    for (int i = 0; i < 3; i++)
    {
        Card *c = new KnightCard();
        cards.push_back(c);
    }
    for (int i = 0; i < 4; i++)
    {
        Card *c = new VictoryPointCard();
        cards.push_back(c);
    }
    for (int i = 0; i < 5; i++)
    {
        Card *c1 = new MonopolyCard();
        cards.push_back(c1);

        Card *c2 = new RoadBuildingCard();
        cards.push_back(c2);

        Card *c3 = new YearOfPlentyCard();
        cards.push_back(c3);
    }
    // shuffle cards
    // std::random_device rd;
    // std::mt19937 g(rd());

    // // Shuffle the deck
    // std::shuffle(cards.begin(), cards.end(), g);
}

/*
    buy a random devolpment card from the deck, add to the player and pop from the deck, player frees the card
*/
bool Board::BuyDevelopmentCard(Player *player)
{
    player->buyDevCard(cards.back());
    cards.pop_back(); // to not double free
    return true;
}

void Board::moveRobber(int x, int y)
{
    placeRobber(x, y);
}

void Board::generateResources(int diceRoll)
{
    // Logic to generate resources based on dice roll
    for (auto &row : tiles)
    {
        for (auto &tile : row)
        {
            if (tile.getNumberToken() == diceRoll)
            {
                for (int i = 1; i < 7; i++)
                {
                    if (tile.getVertex(i).isSettled())
                    {
                        tile.getVertex(i).getOwnerPlayerPtr()->addResource(tile.getResource(), tile.getVertex(i).getSettlement().getAmount());
                    }
                }
            }
        }
    }
}

int Board::generate_number_token(std::vector<std::pair<int, int>> &numberTokens)
{
    int numberToken = rand() % numberTokens.size(); // get the number token
    while (numberTokens[numberToken].second == 0)
    {
        numberToken = rand() % numberTokens.size();
    }
    numberTokens[numberToken].second--; // decrement the number of tokens
    return numberTokens[numberToken].first;
}
std::string Board::generate_resource(std::vector<std::pair<std::string, int>> &numberTokens)
{
    int num = rand() % numberTokens.size();
    while (numberTokens[num].second == 0)
    {
        num = rand() % numberTokens.size(); // reroll till I generate the right tiles.
    }
    numberTokens[num].second--;
    return numberTokens[num].first;
}
bool Board::checkValidTile(size_t x, size_t y)
{ // row, col
    if (x < 0 || x >= tiles.size() || y < 0 || y >= tiles[x].size())
    {
        return false;
    }
    return true;
}

void Board::ReleventTiles(int ver, std::vector<std::pair<Tile, int>> &relevantTiles) // gives me all the one that contains the vertex
{
    for (size_t i = 0; i < tiles.size(); i++)
    {
        for (size_t j = 0; j < tiles[i].size(); j++)
        {
            for (size_t k = 1; k < 7; k++) // 1 to 6 technically
            {
                if (tiles[i][j].getVertex(k).getOwnerint() == ver) // almost fucked this up lol k+1 means
                {
                    relevantTiles.push_back(std::make_pair(tiles[i][j], k));
                }
            }
        }
    }
}
bool Board::switchRoadforSettlment(int x, int y, int z, Player *player)
{

    switch (z)
    {       // look at the png for clarifcation
    case 1: // I am edge 1 and I want my neighbors
        return checkforRoad(x, y, 1, player) || checkforRoad(x, y, 6, player) ||
               (x > 2 ? checkforRoad(x - 1, y, 2, player) : checkforRoad(x - 1, y, 5, player)); // good
    case 2:
        return checkforRoad(x, y, 6, player) || checkforRoad(x, y, 5, player) || // good
               (checkforRoad(x, y - 1, 1, player)) || (x >= 2 ? checkforRoad(x - 1, y, 4, player) : false);
    case 3:
        return checkforRoad(x, y, 1, player) || checkforRoad(x, y, 2, player) || // good
               (x > 2 ? (checkforRoad(x - 1, y + 1, 3, player))
                      : checkforRoad(x, y + 1, 6, player)); // look down
    case 4:
        return checkforRoad(x, y, 5, player) || checkforRoad(x, y, 4, player) || // good
               (x > 2 ? (checkforRoad(x, y - 1, 3, player)) : checkforRoad(x + 1, y, 6, player));
    case 5:
        return checkforRoad(x, y, 2, player) || checkforRoad(x, y, 3, player) ||
                       checkforRoad(x, y + 1, 4, player) ||
                       x > 2
                   ? false
                   : checkforRoad(x + 1, y + 1, 1, player); // look up
    case 6:
        return checkforRoad(x, y, 3, player) || checkforRoad(x, y, 4, player) ||
               (x > 2 ? (checkforRoad(x + 1, y - 1, 2, player) || checkforRoad(x + 1, y, 6, player)) : (checkforRoad(x + 1, y, 2, player)));
    }
    return false; // Default case if z is not 1-6
}
bool Board::buildSet(int x, int y, int z, Player *player, bool midgame)
{ // need to use name for the player thingi
    if (tiles[x][y].getVertex(z).isSettled())
    {
        return false;
    }
    if (midgame)
    {
        if (!switchRoadforSettlment(x, y, z, player))
        {
            return false; // no road close to me can't reach
        }
    }
    int ver = tiles[x][y].getVertex(z).getOwnerint(); // I know what is the name of the vertex

    std::vector<std::pair<Tile, int>> relevantTiles;
    ReleventTiles(ver, relevantTiles);
    for (size_t i = 0; i < relevantTiles.size(); i++)
    {
        if (relevantTiles[i].first.neighborSet(relevantTiles[i].second)) // I get into the tile and then find the neigbor settlment or Road
        {
            return false;
        }
    }
    if (!player->buildSettlement())
    {
        return false;
    }
    Settlement *s = new Settlement(player);
    tiles[x][y].getVertexPointer(z)->settle(s);
    return true;
}
bool manageProblems(Vertex *v, std::string name)
{
    if (v == nullptr)
    {
        std::cout << "good luck";
        return false;
    }
    if (!v->isSettled())
    {
        std::cout << "No settlment to upgrade" << std::endl;
        return false;
    }
    if (v->getOwnerPlayer().getName() != name)
    {
        std::cout << "Not your settlement" << std::endl;
        return false;
    }
    return true;
}
bool Board::upgradeToCity(int x, int y, int z, Player *player)
{

    Vertex *v = getVertex(x, y, z);

    if (!manageProblems(v, player->getName()))
    {
        return false;
    }
    if (!player->upgradeToCity())
    {
        return false;
    }

    v->getSettlementPtr()->upgradeToCity();
    return true;
}

Vertex *Board::getVertex(int x, int y, int z)
{
    if (!checkValidTile(x, y) || z < 1 || z > 6)
    {
        throw std::invalid_argument("Invalid tile");
    }
    return tiles[x][y].getVertexPointer(z);
}

// the whole setup
/**
 * @brief Initialize the vertices of the board
 *
 */
void Board::initializeVertices()
{
    // Logic to initialize vertices
    int num = 0;
    for (size_t i = 0; i < tiles[0].size(); i++)
    {
        Vertex *v = new Vertex(num++, 1);
        tiles[0][i].addVertex(v, 1);
    }
    for (size_t i = 0; i < tiles.size(); i++)
    {
        Vertex *v1 = new Vertex(num++, 1);
        Vertex *v2 = new Vertex(num++, 2);
        tiles[i][0].addVertex(v1, 2);
        tiles[i][0].addVertex(v2, 4);

        for (size_t j = 0; j < tiles[i].size(); j++)
        {
            Vertex *v3 = new Vertex(num++, 1);
            Vertex *v4 = new Vertex(num++, 2);
            tiles[i][j].addVertex(v3, 3);
            tiles[i][j].addVertex(v4, 5);

            // for indexes 3,2 and 5,4
            put3254(i, j, v3, v4);
            // for indexes 1top left5 or right 4 and 6 donn left 3 or right2
            fourToOne(i, j);
        }
    }
    // for 6 and 3 2
    for (size_t i = 0; i < tiles.size(); i++)
    {
        for (size_t j = 0; j < tiles[i].size(); j++)
        {
            sixToTwo(i, j);
        }
    }
    for (size_t i = 0; i < tiles[4].size(); i++)
    {
        Vertex *v = new Vertex(num++, 1);
        tiles[4][i].addVertex(v, 6);
    }
}
void Board::put3254(int i, int j, Vertex *v1, Vertex *v2)
{
    if (checkValidTile(i, j + 1))
    { // check inbound
        tiles[i][j + 1].addVertex(v1, 2);
        tiles[i][j + 1].addVertex(v2, 4);
    }
}
void Board::fourToOne(int i, int j)
{
    if (checkValidTile(i - 1, 0))
    { // for 1,4
        // std::cout<<tiles[i-1].size()<<std::endl;
        if ((size_t)j == tiles[i - 1].size())
        {                                                                      // if I am in the end I have to go back by one
            tiles[i][j].addVertex(tiles[i - 1][j - 1].getVertexPointer(4), 1); // no way I found this bug so fast
        }
        else
        {
            tiles[i][j].addVertex(tiles[i - 1][j].getVertexPointer(5), 1);
        }
    }
}
void Board::sixToTwo(int i, int j)
{
    if (checkValidTile(i + 1, 0))
    {
        if ((size_t)j == tiles[i + 1].size())
        {
            tiles[i][j].addVertex(tiles[i + 1][j - 1].getVertexPointer(3), 6);
        }
        else
        {
            tiles[i][j].addVertex(tiles[i + 1][j].getVertexPointer(3), 6);
        }
    }
}

void Board::initializeTiles()
{
    std::vector<std::pair<std::string, int>> resourceTypes = {
        {"wood", 4}, {"brick", 3}, {"sheep", 4}, {"wheat", 4}, {"ore", 3}};
    std::vector<std::pair<int, int>> numberTokens = {
        {2, 1}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 1}};
    std::vector<size_t> cols = {3, 4, 5, 4, 3};
    for (size_t i = 0; i < 5; i++)
    {
        std::vector<Tile> row;
        for (size_t j = 0; j < cols[i]; j++)
        {
            if (i == 2 && j == 2)
            {
                row.push_back(Tile("desert", 0));
            }
            else
            {

                std::string type = generate_resource(resourceTypes); // get the resource type
                int numberToken = generate_number_token(numberTokens);
                row.push_back(Tile(type, numberToken));
            }
        }
        tiles.push_back(row);
    }
}

void Board::initializeRoads()
{
    // Logic to initialize roads
    for (size_t i = 0; i < tiles[0].size(); i++)
    {
        Road *v = new Road(player);
        Road *v1 = new Road(player);
        tiles[0][i].addRoad(v, 1);
        tiles[0][i].addRoad(v1, 6);
    }
    // middles
    for (size_t i = 0; i < tiles.size(); i++)
    {
        Road *v1 = new Road(player);
        tiles[i][0].addRoad(v1, 5);
        // Road *v2 = new Road(player);
        // tiles[i][0].addRoad(v2, 2);

        for (size_t j = 0; j < tiles[i].size(); j++)
        {
            Road *v3 = new Road(player);
            tiles[i][j].addRoad(v3, 2);
            if (j != 0)
            {
                Road *v4 = tiles[i][j - 1].getRoadPtr(2);
                connect5to2(i, j, v4);
            }

            // the floor
            Road *v5 = new Road(player);
            tiles[i][j].addRoad(v5, 3);
            Road *v6 = new Road(player);
            tiles[i][j].addRoad(v6, 4);
            if ((i == 1 || i == 2) && (j == 0 || j == tiles[i].size() - 1))
            {
                if (j == 0) // ceiling edge cases
                {
                    Road *v7 = new Road(player);
                    tiles[i][j].addRoad(v7, 6);
                    Road *v8 = tiles[i - 1][j].getRoadPtr(4);
                    connect1to4(i, j, v8);
                }
                else
                {
                    Road *v7 = new Road(player);
                    tiles[i][j].addRoad(v7, 1);
                    Road *v8 = tiles[i - 1][j - 1].getRoadPtr(3);
                    connect6to3(i, j, v8);
                }
            }
            else // creating floor
            {
                if (i == 0)
                    continue;
                Road *v7;
                Road *v8;
                if (tiles[i].size() > tiles[i - 1].size())
                {
                    v7 = tiles[i - 1][j].getRoadPtr(4);
                    v8 = tiles[i - 1][j - 1].getRoadPtr(3);
                }
                else
                {
                    v7 = tiles[i - 1][j + 1].getRoadPtr(4);
                    v8 = tiles[i - 1][j].getRoadPtr(3);
                }
                // connect ceiling not edge cases
                connect1to4(i, j, v7);
                connect6to3(i, j, v8);
            }
        }
    }
}

void Board::connect5to2(int x, int y, Road *r1)
{
    tiles[x][y].addRoad(r1, 5);
}
void Board::connect1to4(int x, int y, Road *r1)
{
    tiles[x][y].addRoad(r1, 1);
}
void Board::connect6to3(int x, int y, Road *r1)
{
    tiles[x][y].addRoad(r1, 6);
}

void Board::setupBoard()
{ // generate the board
    // srand(time(0)); // to make it randomized every time

    // Initialize tiles
    initializeTiles();

    // Initialize vertices
    initializeVertices();

    // Initialize roads
    initializeRoads();
}

void Board::printBoard()
{
    std::vector<std::string> resources = {"            ", "      ", "", "      ", "            "};

    // Print the top row of vertex owners
    std::cout << "                   ";
    for (size_t i = 0; i < tiles[0].size(); ++i)
    {
        std::cout << (tiles[0][i].getVertex(1).isSettled() ? tiles[0][i].getVertex(1).getOwnerPlayer().getColor() : RESET) << std::setw(9) << "__" + tiles[0][i].getVertex(1).getOwner() + "__ " << RESET << "  ";
    }
    std::cout << std::endl;

    // Print the rest of the board
    std::vector<std::string> offset = {"             ", "       ", " ", "       ", "             "};
    for (size_t i = 0; i < tiles.size(); i++)
    {
        // print middle part of the roads
        if (!(i == 3 || i == 4))
        {
            std::cout << offset[i] + "       ";
        }
        else if (i == 3)
        {
            std::cout << "    ";
        }
        else
        {
            std::cout << "          ";
        }

        if (i == 3 || i == 4)
        {
            std::cout << tiles[i - 1][0].getRoadPtr(4)->getOwner().getColor() << std::setw(9) << "\\" << RESET << " ";
        }
        for (size_t j = 0; j < tiles[i].size(); j++) // road
        {
            std::cout << tiles[i][j].getRoadPtr(6)->getOwner().getColor() << "/" << RESET << "";
            std::cout << tiles[i][j].getRoadPtr(1)->getOwner().getColor() << std::setw(9) << "\\" << RESET << " ";
        }
        if (i == 3 || i == 4)
        { // road
            std::cout << tiles[i - 1][tiles[i - 1].size() - 1].getRoadPtr(3)->getOwner().getColor() << "/" << RESET << "";
        }
        std::cout << std::endl;
        for (int k = 0; k < 2; ++k)
        {
            std::cout << resources[i];
            if (k == 0) // Vertex
            {
                std::cout << (tiles[i][0].getVertex(2).isSettled() ? tiles[i][0].getVertex(2).getOwnerPlayer().getColor() : RESET)
                          << std::setw(8) << tiles[i][0].getVertex(2).getOwner() << RESET << "  ";
            }
            else // vertex
            {
                std::cout << (tiles[i][0].getVertex(4).isSettled() ? tiles[i][0].getVertex(4).getOwnerPlayer().getColor() : RESET)
                          << "  " << std::setw(8) << "__" + tiles[i][0].getVertex(4).getOwner() + "__" << RESET << "  ";
            }
            // Road
            for (size_t j = 0; j < tiles[i].size(); ++j) // vertex
            {
                std::cout << (tiles[i][j].getVertex(k == 0 ? 3 : 5).isSettled() ? tiles[i][j].getVertex(k == 0 ? 3 : 5).getOwnerPlayer().getColor() : RESET)
                          << "" << std::setw(9) << (k == 0 ? "" : "__") + tiles[i][j].getVertex(k == 0 ? 3 : 5).getOwner() + (k == 0 ? "" : "__") << RESET << "  ";
            }
            std::cout << std::endl;

            if (k == 0)
            {
                std::cout << resources[i] + "       ";
                for (size_t j = 0; j < tiles[i].size(); ++j)
                {
                    // Assuming resources and number tokens are strings for simplicity
                    std::string resource = tiles[i][j].getResource();
                    std::cout << tiles[i][j].getRoadPtr(5)->getOwner().getColor() << "|" << RESET << "";

                    std::string numberToken = std::to_string(tiles[i][j].getNumberToken());

                    // Assign colors based on resource type
                    std::string color;
                    if (resource == "wheat")
                        color = YELLOW;
                    else if (resource == "sheep")
                        color = GREEN;
                    else if (resource == "brick")
                        color = RED;
                    else if (resource == "ore")
                        color = BLUE;
                    else if (resource == "wood")
                        color = MAGENTA;
                    else if (resource == "desert")
                        color = CYAN;
                    else
                        color = WHITE;

                    std::cout << color << std::setw(8) << resource + "-" + numberToken << RESET << "  ";
                }
                std::cout << tiles[i][tiles[i].size() - 1].getRoadPtr(2)->getOwner().getColor() << "|" << RESET << "";

                std::cout << std::endl;
            }
        }
    }

    std::cout << "                   ";
    for (size_t i = 0; i < tiles[4].size(); ++i)
    {
        std::cout << std::setw(2) << tiles[4][i].getRoadPtr(4)->getOwner().getColor() << "\\" << RESET << " ";
        std::cout << std::setw(2) << tiles[4][i].getRoadPtr(3)->getOwner().getColor() << "/" << RESET << "     ";
    }
    // Print the end of the board
    std::cout << std::endl
              << "                ";
    for (size_t i = 0; i < tiles[4].size(); ++i)
    {
        std::cout << (tiles[4][i].getVertex(6).isSettled() ? tiles[4][i].getVertex(6).getOwnerPlayer().getColor() : RESET)
                  << std::setw(9) << tiles[4][i].getVertex(6).getOwner() << RESET << "   ";
    }
} // enf of function
bool Board::rightSet(int x, int y, int z, Player *player) // return true if I am next to a settelment
{
    if (tiles[x][y].getVertex(z).isSettled() ? tiles[x][y].getVertex(z).getOwnerPlayer().getName() != player->getName() : false)
    {
        return false;
    }
    return tiles[x][y].getVertex(z).isSettled();
}
bool Board::switchy(int x, int y, int z, Player *player) // return true if I can build
{
    switch (z)
    {
    case 1:
        return rightSet(x, y, 1, player) || rightSet(x, y, 3, player);
        break;
    case 2:
        return rightSet(x, y, 3, player) || rightSet(x, y, 5, player);
        break;
    case 3:
        return rightSet(x, y, 5, player) || rightSet(x, y, 6, player);
        break;
    case 4:
        return rightSet(x, y, 4, player) || rightSet(x, y, 6, player);
        break;
    case 5:
        return rightSet(x, y, 2, player) || rightSet(x, y, 4, player);
        break;
    case 6:
        return rightSet(x, y, 2, player) || rightSet(x, y, 1, player);
        break;
    default:
        break;
    }
}
bool Board::checkforRoad(int x, int y, int z, Player *player)
{
    if (x < 0 || x >= tiles.size() || y < 0 || y >= tiles[x].size())
    {
        return false;
    }
    if (tiles[x][y].getRoadPtr(z)->getOwner().getName() == player->getName()) // if they are owned by the same player we good
    {
        return true;
    }
    return false;
}

bool Board::switchRoad(int x, int y, int z, Player *player)
{
    switch (z)
    {       // look at the png for clarifcation
    case 1: // I am edge 1 and I want my neighbors
        return checkforRoad(x, y, 2, player) || checkforRoad(x, y, 6, player) ||
               (x > 2 ? (checkforRoad(x - 1, y + 1, 3, player) || checkforRoad(x - 1, y + 1, 5, player)) // look up
                      : (checkforRoad(x - 1, y, 3, player) || checkforRoad(x - 1, y, 5, player)));       // need the other tile
    case 2:
        return checkforRoad(x, y, 1, player) || checkforRoad(x, y, 3, player) ||
               (checkforRoad(x, y + 1, 6, player) || checkforRoad(x, y + 1, 4, player));
    case 3:
        return checkforRoad(x, y, 2, player) || checkforRoad(x, y, 4, player) ||
               (x > 2 ? (checkforRoad(x + 1, y, 2, player) || checkforRoad(x + 1, y, 4, player)) : (checkforRoad(x + 1, y + 1, 2, player) || checkforRoad(x + 1, y + 1, 4, player))); // look down
    case 4:
        return checkforRoad(x, y, 3, player) || checkforRoad(x, y, 5, player) ||
               (x > 2 ? (checkforRoad(x + 1, y - 1, 2, player) || checkforRoad(x + 1, y - 1, 6, player)) : (checkforRoad(x + 1, y, 2, player) || checkforRoad(x + 1, y, 6, player)));
    case 5:
        return checkforRoad(x, y, 4, player) || checkforRoad(x, y, 6, player) ||
               (checkforRoad(x, y - 1, 1, player) || checkforRoad(x, y - 1, 3, player)); // look up
    case 6:
        return checkforRoad(x, y, 1, player) || checkforRoad(x, y, 5, player) ||
               (x >= 2 ? (checkforRoad(x - 1, y, 2, player) || checkforRoad(x - 1, y, 4, player)) : (checkforRoad(x - 1, y - 1, 2, player) || checkforRoad(x - 1, y - 1, 4, player)));
    }
    return false; // Default case if z is not 1-6
}
void Board::giveFirstRoundResources(Player *player, int x)
{

    std::vector<std::pair<Tile, int>> relevantTiles;
    ReleventTiles(x, relevantTiles);
    for (int i = 0; i < relevantTiles.size(); i++)
    {
        player->addResource(relevantTiles[i].first.getResource(), 1);
    }
}
bool Board::buildRoad(int x, int y, int z, Player *player)
{
    if (tiles[x][y].getRoadPtr(z)->getOwner().getName() != "")
    {
        return false;
    }
    if (!switchy(x, y, z, player) && !switchRoad(x, y, z, player)) // to check for settelments
    {
        return false;
    }

    if (!player->buildRoad())
    {
        return false;
    }
    tiles[x][y].getRoadPtr(z)->setOwner(player);
    return true;
}
void Board::getTile(const size_t x, const size_t y)
{
    tiles[x][y].print();
    std::cout << std::endl;
}
void Board::printTileSet(int x, int y)
{
    tiles[x][y].printSettelments();
    std::cout << std::endl;
}
void Board::showRoads(int x, int y)
{
    tiles[x][y].printRoads();
    std::cout << std::endl;
}
bool Board::tradeResources(Player &me, Player &other, std::map<std::string, int> offer, std::map<std::string, int> request)
{
    // Check if 'me' has enough resources to offer
    if (!me.hasResources(offer))
    {
        return false;
    }

    // Check if 'other' has enough resources to meet the request
    if (!other.hasResources(request))
    {
        return false;
    }

    // Perform the trade
    me.subtractResources(offer);
    other.addResources(offer);

    other.subtractResources(request);
    me.addResources(request);

    return true;
}
void Board::placeRobber(int x, int y) // maybe in the future
{
    robberPosition = {x, y};
}
