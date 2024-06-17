#include "Player.h"

Player::Player(std::string playerName, std::string color) // didn't do decunstor;
    : color(color), name(playerName), victoryPoints(0)
{
    // Initialize resources to 0
    // resources = {{"wood", 8}, {"brick", 8}, {"sheep", 6}, {"wheat", 6}, {"ore", 1}}; // game to expreimet and show
    // resources = {{"wood", 4}, {"brick", 4}, {"sheep", 2}, {"wheat", 2}, {"ore", 0}}; // in a real game
    resources = {{"wood", 0}, {"brick", 0}, {"sheep", 0}, {"wheat", 0}, {"ore", 0}}; // in a real game
}
Player::~Player()
{
    for (size_t i = 0; i < developmentCards.size(); i++)
    {
        // delete developmentCards[i]; // if game ended and I have cards I need to delete them
    }
}
std::map<std::string, int> Player::getResources() const
{
    return resources;
}
void Player::addKnight()
{
    knightCount++;
}
int Player::getKnightCount() const
{
    return knightCount;
}
bool Player::buildSettlement()
{ // I get 3 lemurs for this
    if (!canBuildSettlement())
    {
        std::cout << "bro you broke";
        return false;
    }
    // make him pay for the settelemtn
    resources["wood"] -= 1;
    resources["brick"] -= 1;
    resources["sheep"] -= 1;
    resources["wheat"] -= 1;
    // add the victory point it gives me
    victoryPoints += 1;
    return true; // bro I have a problem of forgetting the return statement mannn
}
bool Player::upgradeToCity()
{
    if (!canUpgradeCity())
    {
        std::cout << "bro you broke";
        return false;
    }
    // make him pay for the city
    resources["ore"] -= 3;
    resources["wheat"] -= 2;
    // add the victory point it gives me
    victoryPoints += 1;
    return true;
}
bool Player::useDevelopmentCard(std::string cardType)
{
    // Logic to use a development card
    for (size_t i = 0; i < developmentCards.size(); i++)
    {
        if (developmentCards[i]->getType() == cardType)
        {
            developmentCards[i]->use();
            delete developmentCards[i];
            developmentCards.erase(developmentCards.begin() + i);
            return true;
        }
    }
    return false;
}
bool Player::buildRoad()
{

    if (canBuildRoad())
    {
        resources["wood"] -= 1;
        resources["brick"] -= 1;
        return true;
    }
    else
    {
        std::cout << "bro you broke";
        return false;
    }
}
bool Player::hasResources(const std::map<std::string, int> &required) const
{
    for (const auto &item : required)
    {
        if (resources.at(item.first) < item.second)
        {
            return false;
        }
    }
    return true;
}

void Player::addResources(const std::map<std::string, int> &additional)
{
    for (const auto &item : additional)
    {
        resources[item.first] += item.second;
    }
}

void Player::subtractResources(const std::map<std::string, int> &subtracted)
{
    for (const auto &item : subtracted)
    {
        resources[item.first] -= item.second;
    }
}

void Player::addResource(std::string resource, int amount)
{
    std::cout << "added " << amount << " " << resource << " to " << name << std::endl;
    resources[resource] += amount;
}
std::string Player::showResources()
{
    std::vector<std::string> resourceOrder = {"wood", "brick", "sheep", "wheat", "ore"};
    std::string result = "";

    for (const std::string &resource : resourceOrder)
    {
        result += resource + ": " + std::to_string(resources[resource]) + "\n";
    }
    result += "Development Cards:\n";
    for (size_t i = 0; i < developmentCards.size(); i++)
    {
        result += developmentCards[i]->getType() + "\n";
    }

    return result;
}
// could I buy this things, mmm prices of things PRIVATES
bool Player::canBuildSettlement() const
{
    // Logic to determine if the player can build a settlement
    return resources.at("wood") >= 1 && resources.at("brick") >= 1 && resources.at("sheep") >= 1 && resources.at("wheat") >= 1;
}
bool Player::buyDevCard(Card *c)
{
    if (canBuyDevCard())
    {
        resources["sheep"] -= 1;
        resources["ore"] -= 1;
        resources["wheat"] -= 1;

        if (c->getType() == "VictoryPoint")
        {
            victoryPoints++;
            std::cout << victoryPoints;
            delete c;
            return true;
        }
        else
        {
            developmentCards.push_back(c);
            return true;
        }
    }
    return false;
}
bool Player::canBuyDevCard() const
{
    return resources.at("sheep") >= 1 && resources.at("ore") >= 1 && resources.at("wheat") >= 1;
}
bool Player::canUpgradeCity() const
{
    return resources.at("ore") >= 3 && resources.at("wheat") >= 2;
}
bool Player::canBuildRoad() const
{
    return resources.at("wood") >= 1 && resources.at("brick") >= 1;
}

std::string Player::getName() const
{
    return name;
}
/**
 * @brief add victory points because there's only 3 knights than don't need to unlargest army
 */
void Player::largestArmy()
{
    victoryPoints += 2;
}

// very himportant!
std::string Player::getColor() const
{
    return color;
}

int Player::getVictoryPoints() const
{
    return victoryPoints;
}