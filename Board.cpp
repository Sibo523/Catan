#include "Board.h"
#include <iomanip>
#include <unordered_set>

Board::Board()
{
    // Initialize the board
    setupBoard();
}

Board::~Board() // I wanted a simple implemantation of the destructor but I had to do this :(
{
    std::unordered_set<Vertex*> deletedVertices;

    for (size_t i = 0; i < (size_t)tiles.size(); i++)
    {
        for (size_t j = 0; j < (size_t)tiles[i].size(); j++)
        {
            for (size_t k = 1; k < 7; k++)
            {
                Vertex* vertex = tiles[i][j].getVertexPointer(k);
                if (vertex == NULL || deletedVertices.count(vertex))
                {
                    continue;
                }
                
                delete vertex;
                deletedVertices.insert(vertex);
            }
        }
    }
}
    
    


void Board::placeRobber(int x, int y)
{
    robberPosition = {x, y};
}

void Board::moveRobber(int x, int y)
{
    placeRobber(x, y);
}

// void Board::generateResources(int diceRoll) {
//     // Logic to generate resources based on dice roll
//     for (auto& row : tiles) {
//         for (auto& tile : row) {
//             if (tile.getNumberToken() == diceRoll) {
//                 // Give resources to players
//                 tile.getResource();
//             }
//         }
//     }
// }

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



void Board::ReleventTiles(int ver, std::vector<std::pair<Tile, int>> &relevantTiles)
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
bool Board::buildSet(int x, int y, int z, std::string name){ //need to use name for the player thingi
    if (tiles[x][y].getVertex(z).isSettled()){
        return false;
    }
    int ver = tiles[x][y].getVertex(z).getOwnerint(); // I know what is the name of the owner
    
    std::vector<std::pair<Tile,int>> relevantTiles; 
    ReleventTiles(ver,relevantTiles);
    for (size_t i = 0; i < relevantTiles.size(); i++)
    {
        if (relevantTiles[i].first.neighborSet(relevantTiles[i].second)) // I get into the tile and then find the neigbor set of 
        {
            return false;
        }
    }
    tiles[x][y].getVertexPointer(z)->settle();
    return true;
}



//the whole setup 
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
        Vertex* v = new Vertex(num++, 1);
        tiles[0][i].addVertex(v, 1);
    }
    for (size_t i = 0; i < tiles.size(); i++)
    {
        Vertex* v1 = new Vertex(num++, 1);
        Vertex* v2 = new Vertex(num++, 2);
        tiles[i][0].addVertex(v1, 2);
        tiles[i][0].addVertex(v2, 4);


        for (size_t j = 0; j < tiles[i].size(); j++)
        {
            Vertex* v3 = new Vertex(num++, 1);
            Vertex* v4 = new Vertex(num++, 2);
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
        Vertex* v = new Vertex(num++, 1);
        tiles[4][i].addVertex(v, 6);

    }
}
void Board::put3254(int i, int j, Vertex* v1, Vertex* v2)
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
        { // if I am in the end I have to go back by one
            tiles[i][j].addVertex(tiles[i - 1][j - 1].getVertexPointer(5), 1);
        }
        else
        {
            tiles[i][j].addVertex(tiles[i - 1][j].getVertexPointer(4), 1);
        }
    }
}
void Board::sixToTwo(int i, int j)
{
    if (checkValidTile(i + 1, 0))
    {
        if ((size_t) j == tiles[i + 1].size())
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
void Board::setupBoard()
{ // generate the board
    // Logic to setup the board
    // srand(time(0)); // to make it randomized every time
    // Initialize tiles
    initializeTiles();
    // Initialize vertices
    initializeVertices();
}

void Board::printBoard()
{
    std::vector<std::string> resources = {"           ", "     ", "", "     ", "           "};

    // Print the top row of vertex owners
    std::cout << "                ";
    for (size_t i = 0; i < tiles[0].size(); ++i)
    {
        std::cout << WHITE << std::setw(9) << tiles[0][i].getVertex(1).getOwner() << RESET << "  ";
    }
    std::cout << std::endl;

    // Print the rest of the board
    for(size_t i = 0; i < tiles.size(); ++i)
    {
        for (int k = 0; k < 2; ++k)
        {
            std::cout << resources[i];

            if (k == 0)
            {
                std::cout << WHITE << std::setw(8) << tiles[i][0].getVertex(2).getOwner() << RESET << "  ";
            }
            else
            {
                std::cout << WHITE << std::setw(8) << tiles[i][0].getVertex(4).getOwner() << RESET << "  ";
            }

            for (size_t j = 0; j < tiles[i].size(); ++j)
            {
                std::cout << WHITE << std::setw(9) << tiles[i][j].getVertex(k == 0 ? 3 : 5).getOwner() << RESET << "  ";
            }
            std::cout << std::endl;
            
            if(k == 0)
            {
                std::cout << resources[i] + "       ";
                for(size_t j = 0; j < tiles[i].size(); ++j)
                {
                    // Assuming resources and number tokens are strings for simplicity
                    std::string resource = tiles[i][j].getResource();
                    
                    std::string numberToken = std::to_string(tiles[i][j].getNumberToken());
                    
                    // Assign colors based on resource type
                    std::string color;
                    if (resource == "wheat") color = YELLOW;
                    else if (resource == "sheep") color = GREEN;
                    else if (resource == "brick") color = RED;
                    else if (resource == "ore") color = BLUE;
                    else if (resource == "wood") color = MAGENTA;
                    else if (resource == "desert") color = CYAN;
                    else color = WHITE;

                    std::cout << color << std::setw(8) << resource + "-" + numberToken << RESET << "   ";
                }
                std::cout << std::endl;
            }
        }
        
    }

    // Print the end of the board
    std::cout << "                ";
    for (size_t i = 0; i < tiles[4].size(); ++i)
    {
        std::cout << WHITE << std::setw(9) << tiles[4][i].getVertex(6).getOwner() << RESET << "  ";
    }
    // for(int i =0; i < tiles.size(); i++)
    //     {
    //         for(int j = 0; j <tiles[i].size(); j++)
    //         {
    //             for(int k = 1; k < 7; k++)
    //             {
    //                 if(tiles[i][j].getVertex(k).isSettled() )
    //                 {
    //                     //std::cout<< "I guess it works"<< k << std::endl;
    //                 }
    //             }
    //         }
    //     }
    
}

void Board::getTile(const size_t x, const size_t y)
{
    tiles[x][y].print();
    std::cout << std::endl;
}
void Board::printTileSet(int x, int y)
{   
    tiles[x][y].printSettelments();
    std::cout<<std::endl;
}

// std::ostream& operator<<(std::ostream& os, const Board& board) {
//     for (const auto& row : board.tiles) {
//         for (const auto& tile : row) {
//             os << tile.getResource() << " ";
//         }
//         os << "\n";
//     }
//     return os;
// }
