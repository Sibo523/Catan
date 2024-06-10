#include "Player.h"

Player::Player(std::string playerName) 
    : name(playerName), victoryPoints(0) {
    // Initialize resources to 0
    resources = {{"wood", 0}, {"brick", 0}, {"sheep", 0}, {"wheat", 0}, {"ore", 0}};
}

void Player::buildSettlement(int x, int y) {
    settlements.push_back(Settlement(*this, {x, y}));
    // Additional logic to handle resources and game state
}

void Player::buildCity(int x, int y) {
    // Logic to upgrade a settlement to a city
}

void Player::buildRoad(int x1, int y1, int x2, int y2) {
    roads.push_back(Road(*this, {x1, y1}, {x2, y2}));
    // Additional logic to handle resources and game state
}

void Player::tradeResources(Player& otherPlayer, std::map<std::string, int> offer, std::map<std::string, int> request) {
    // Logic to trade resources between players
}

void Player::useDevelopmentCard(std::string cardType) {
    // Logic to use a development card
}

void Player::endTurn() {
    // Logic to end the player's turn
}
std::string Player::getName() const {
    return name;
}
std::string Player::getColor() const {
    return color;
}
void Player::setColor(std::string playerColor) {
    color = playerColor;
}
