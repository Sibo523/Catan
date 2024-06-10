#include "Board.h"

Board::Board() {
    // Initialize the board
    setupBoard();
}

void Board::placeRobber(int x, int y) {
    robberPosition = {x, y};
}

void Board::moveRobber(int x, int y) {
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


int Board::generate_number_token(std::vector<std::pair<int,int>> &numberTokens){
    int numberToken = rand() % numberTokens.size(); // get the number token
    while (numberTokens[numberToken].second == 0){
        numberToken = rand() % numberTokens.size();
    } 
    numberTokens[numberToken].second--; // decrement the number of tokens
    return numberTokens[numberToken].first;
}
std::string Board::generate_resource( std::vector<std::pair<std::string,int>>& numberTokens){
    int num = rand()%numberTokens.size();
    while(numberTokens[num].second == 0){
        num = rand()%numberTokens.size(); // reroll till I generate the right tiles.
    }
    numberTokens[num].second--;
    return numberTokens[num].first;
}
bool Board::checkValidTile(int x, int y) { // row, col 
    if (x < 0 || x >= tiles.size() || y < 0 || y >= tiles[x].size()) {
        return false;
    }
    return true;
}
/**
 * @brief Initialize the vertices of the board
 * 
*/
void Board::initializeVertices() { 
    // Logic to initialize vertices
    int num =0 ;
    for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = 0; j < tiles[i].size(); j++) {
            int temp = num;
            Vertex v1 = Vertex(num++,1);
            // std::cout<<num<<"+";
            Vertex v2 = Vertex(num++,2);
            // std::cout<<num<<"+";
            tiles[i][j].addVertex(v1, 3-1);

            // tiles[i][j].print();
            tiles[i][j].addVertex(v2, 5-1);
            if (checkValidTile(i, j+1)) { // check for inbound
                // tiles[i][j].print();
                tiles[i][j+1].addVertex(v1, 2 -1);
                // tiles[i][j+1].print();

                tiles[i][j+1].addVertex(v2, 4 -1 );
            }
        }
    }
}
void Board::setupBoard() { //generate the board
    // Logic to setup the board
    // srand(time(0)); // to make it randomized every time
    // Initialize tiles
    std::vector<std::pair<std::string,int>> resourceTypes = {
        {"wood", 4}, {"brick", 3}, {"sheep", 4}, {"wheat", 4}, {"ore", 3}
    };
    std::vector<std::pair<int,int>> numberTokens = {
        {2,1}, {3,2},{4,2},{5,2},{6,2},{8,2},{9,2},{10,2},{11,2},{12,1}
    };
    std::vector<int> cols = {3,4,5,4,3};
    for (size_t i = 0; i < 5;i++){
        std::vector<Tile> row;
        for (size_t j = 0; j < cols[i]; j++){
            if (i == 2 && j == 2){
                row.push_back(Tile("desert", 0));
            } else {

                std::string type = generate_resource(resourceTypes); // get the resource type                
                int numberToken = generate_number_token(numberTokens);
                row.push_back(Tile(type, numberToken));
            }
        }
        tiles.push_back(row);
    }
    // Initialize vertices
    initializeVertices();
}

void Board::printBoard(){
    const std::vector<std::vector<Tile>>& tile = getTiles();
    std::vector<std::string> resources = { "        ", "    ", "", "    ", "        "};
    for (size_t i = 0; i < tile.size(); ++i) {
        std::cout<<resources[i];
        for (size_t j = 0; j < tile[i].size(); ++j) {
            std::cout << tile[i][j].toString() << " ";
        }
        std::cout << std::endl;
    }
}
std::vector<std::vector<Tile>> Board::getTiles() {
    return tiles;
}
void Board::getTile(const size_t x,const size_t y) {
    tiles[x][y].print();
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
