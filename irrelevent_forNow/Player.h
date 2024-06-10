#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include "Settlement.h"
#include "City.h"
#include "Road.h"
#include "DevelopmentCard.h"

class Player {
public:
    Player(std::string name);
    void buildSettlement(int x, int y);
    void buildCity(int x, int y);
    void buildRoad(int x1, int y1, int x2, int y2);
    void tradeResources(Player& otherPlayer, std::map<std::string, int> offer, std::map<std::string, int> request);
    void useDevelopmentCard(std::string cardType);
    void endTurn();
    std::string getName() const;
    std::string getColor() const;
    void setColor(std::string color);

private:
    std::string color;
    std::string name;
    std::map<std::string, int> resources; // e.g., {"wood": 3, "brick": 2}
    std::vector<Settlement> settlements;
    std::vector<City> cities;
    std::vector<Road> roads;
    std::vector<DevelopmentCard> developmentCards;
    int victoryPoints;
};

#endif // PLAYER_H
