#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Base class Card
class Card
{
public:
    virtual ~Card() = default;
    virtual void use() = 0;
};

// Derived class for Development Card
class DevelopmentCard : public Card
{
public:
    void use() override
    {
        std::cout << "Using a Development Card" << std::endl;
    }
};

// Specific Development Cards
class MonopolyCard : public DevelopmentCard
{
public:
    void use() override
    {
        std::cout << "Using Monopoly Card: Choose a resource and take it from all other players." << std::endl;
    }
};

class RoadBuildingCard : public DevelopmentCard
{
public:
    void use() override
    {
        std::cout << "Using Road Building Card: Build 2 roads at no cost." << std::endl;
    }
};

class YearOfPlentyCard : public DevelopmentCard
{
public:
    void use() override
    {
        std::cout << "Using Year of Plenty Card: Take 2 resources of your choice from the bank." << std::endl;
    }
};

// Derived class for Knight Card
class KnightCard : public Card
{
public:
    void use() override
    {
        std::cout << "Using a Knight Card" << std::endl;
    }
};

// Derived class for Victory Point Card
class VictoryPointCard : public Card
{
public:
    void use() override
    {
        std::cout << "Using a Victory Point Card" << std::endl;
    }
};
