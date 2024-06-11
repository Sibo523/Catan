#include "GameManager.h"

// GameManager::GameManager(std::vector<Player> gamePlayers) 
//     : players(gamePlayers), currentTurn(0), gameState("not started") {}

GameManager::GameManager() :currentTurn(0), gameState("not started") {}

void GameManager::startGame() {
    gameState = "started";
    // board = Board();
    board.printBoard();
}

void GameManager::endGame() {
    gameState = "ended";
    // Additional logic to end the game
}

void GameManager::nextTurn() {
    // currentTurn = (currentTurn + 1) % players.size();
    // Additional logic to handle turn transition
}
void GameManager::get(size_t row, size_t col){
    board.getTile(row,col);
}
void GameManager::getSettlmets(int x, int y){
    board.printTileSet(x,y);
}
bool GameManager::BuildSettlement(size_t row, size_t col,int z, std::string name){
    return board.buildSet(row,col,z,name);
}
void GameManager::printBoard(){
    board.printBoard();
}
bool GameManager::checkWinCondition() {
    // Logic to check if a player has won the game
    return false;
}
