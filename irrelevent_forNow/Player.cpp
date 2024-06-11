#include "Player.h"

Player::Player(std::string playerName)
    : name(playerName), victoryPoints(0)
{
    // Initialize resources to 0
    resources = {{"wood", 0}, {"brick", 0}, {"sheep", 0}, {"wheat", 0}, {"ore", 0}}; // aight
}

void Player::buildSettlement(int x, int y,int z)
{                                             // I get 3 lemurs for this
   if (!canBuildSettlement())
   {
        std::cout<<"bro you broke";
   }
   
}


//could I buy this things, mmm prices of things PRIVATES
bool Player::canBuildSettlement() const
{
    // Logic to determine if the player can build a settlement
    return resources.at("wood") >= 1 && resources.at("brick") >= 1 && resources.at("sheep") >= 1 && resources.at("wheat") >= 1;
}
bool Player::canBuyDevCard() const
{
    return resources.at("sheep") >= 1 && resources.at("ore") >= 1 && resources.at("wheat") >= 1;
}
bool Player::canUpgradeCity() const
{
    return resources.at("ore") >= 3 && resources.at("wheat") >= 2;    
}

/*
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
*/
void Player::endTurn()
{
    // Logic to end the player's turn
}
std::string Player::getName() const
{
    return name;
}

// very himportant!
std::string Player::getColor() const
{
    return color;
}
void Player::setColor(std::string playerColor)
{
    color = playerColor;
}
