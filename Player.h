#ifndef PLAYER_H
#define PLAYER_H

// #include <string>
#include <iostream>

#include <map>
#include <vector>
#include "Card.h"
#include <typeinfo>

// #include "Settlement.h"
// #include "City.h"
// #include "Road.h"
// #include "DevelopmentCard.h"

class Player
{
public:
    Player(std::string name, std::string color);
    ~Player();
    bool buildSettlement();
    bool upgradeToCity();
    void addResource(std::string resource, int amount);
    bool buildRoad();
    // void tradeResources(Player& otherPlayer, std::map<std::string, int> offer, std::map<std::string, int> request);
    // void useDevelopmentCard(std::string cardType);
    std::string showResources();
    // void endTurn();
    std::string getName() const;
    std::string getColor() const;
    // void setColor(std::string color);
    int getVictoryPoints() const;
    void subtractResources(const std::map<std::string, int> &subtracted);
    void addResources(const std::map<std::string, int> &additional);
    bool hasResources(const std::map<std::string, int> &required) const;
    bool buyDevCard(Card *card);
    bool useDevelopmentCard(std::string cardType);
    std::map<std::string, int> getResources() const;
    void addKnight();
    int getKnightCount() const;
    void largestArmy();
    int amountOfTotalResources() const;
    void discardHalfResources();

private:
    int knightCount = 0;

    std::vector<Card *> developmentCards;
    bool canBuildRoad() const;
    std::string color;
    bool canBuildSettlement() const;
    bool canBuyDevCard() const;
    bool canUpgradeCity() const;
    std::string name;
    std::map<std::string, int> resources; // e.g., {"wood": 3, "brick": 2}
    // std::vector<DevelopmentCard> developmentCards;
    int victoryPoints;
};

#endif // PLAYER_H
