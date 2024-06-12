#ifndef PLAYER_H
#define PLAYER_H

// #include <string>
#include <iostream>

#include <map>
#include <vector>
// #include "Settlement.h"
// #include "City.h"
// #include "Road.h"
// #include "DevelopmentCard.h"

class Player {
public:
    Player(std::string name,std::string color);
    bool buildSettlement();
    bool upgradeToCity();
    void addResource(std::string resource, int amount);
    // void tradeResources(Player& otherPlayer, std::map<std::string, int> offer, std::map<std::string, int> request);
    // void useDevelopmentCard(std::string cardType);
    std::string showResources();
    void endTurn();
    std::string getName() const;
    std::string getColor() const;
    void setColor(std::string color);
    int getVictoryPoints() const;
private:
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
