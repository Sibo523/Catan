#include "Player.h"

Player::Player(std::string playerName,std::string color) //didn't do decunstor;
    : color(color),name(playerName), victoryPoints(0)
{
    // Initialize resources to 0
    resources = {{"wood", 10}, {"brick",5 }, {"sheep", 5}, {"wheat", 5}, {"ore", 5}}; // aight
}

bool Player::buildSettlement()
{                                             // I get 3 lemurs for this
   if (!canBuildSettlement())
   {
        std::cout<<"bro you broke";
        return false;
   }
   //make him pay for the settelemtn
    resources["wood"] -= 1;
    resources["brick"] -= 1;
    resources["sheep"] -= 1;
    resources["wheat"] -= 1;
    //add the victory point it gives me 
    victoryPoints += 1;
    return true; // bro I have a problem of forgetting the return statement mannn 
}
bool Player::upgradeToCity()
{
    if (!canUpgradeCity())
    {
        std::cout<<"bro you broke";
        return false;
    }
    //make him pay for the city
    resources["ore"] -= 3;
    resources["wheat"] -= 2;
    //add the victory point it gives me 
    victoryPoints += 1;
    return true;
}
void Player::addResource(std::string resource, int amount)
{
    resources[resource] += amount;
}
std::string Player::showResources()
{
    std::vector<std::string> resourceOrder = {"wood", "brick", "sheep", "wheat", "ore"};
    std::string result = "";

    for (const std::string& resource : resourceOrder)
    {
        result += resource + ": " + std::to_string(resources[resource]) + "\n";
    }

    return result;
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
// void Player::endTurn()
// {
//     // Logic to end the player's turn
// }
std::string Player::getName() const
{
    return name;
}

// very himportant!
std::string Player::getColor() const
{
    return color;
}
// void Player::setColor(std::string playerColor)
// {
//     color = playerColor;
// }
int Player::getVictoryPoints() const
{
    return victoryPoints;
}