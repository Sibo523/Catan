#include "Card.h"

void DevelopmentCard::use()
{
    std::cout << "Using a Development Card" << std::endl;
}

std::string DevelopmentCard::getType() const
{
    return "Development";
}

void MonopolyCard::use()
{
    std::cout << "Using Monopoly Card: Choose a resource and take it from all other players." << std::endl;
}

std::string MonopolyCard::getType() const
{
    return "Monopoly";
}

void RoadBuildingCard::use()
{
    std::cout << "Using Road Building Card: Build 2 roads at no cost." << std::endl;
}

std::string RoadBuildingCard::getType() const
{
    return "RoadBuilding";
}

void YearOfPlentyCard::use()
{
    std::cout << "Using Year of Plenty Card: Take 2 resources of your choice from the bank." << std::endl;
}

std::string YearOfPlentyCard::getType() const
{
    return "YearOfPlenty";
}

void KnightCard::use()
{
    std::cout << "Using a Knight Card" << std::endl;
}

std::string KnightCard::getType() const
{
    return "Knight";
}

void VictoryPointCard::use()
{
    std::cout << "Using a Victory Point Card" << std::endl;
}

std::string VictoryPointCard::getType() const
{
    return "VictoryPoint";
}
