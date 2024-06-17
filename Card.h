#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Base class Card
class Card
{
public:
    virtual ~Card() = default;
    virtual void use() = 0;
    virtual std::string getType() const = 0;
};

// Derived class for Development Card
class DevelopmentCard : public Card
{
public:
    ~DevelopmentCard() override = default;
    void use() override;
    std::string getType() const override; // Declaration only
};

// Specific Development Cards
class MonopolyCard : public DevelopmentCard
{
public:
    ~MonopolyCard() override = default;
    void use() override;
    std::string getType() const override; // Declaration only
};

class RoadBuildingCard : public DevelopmentCard
{
public:
    ~RoadBuildingCard() override = default;
    void use() override;
    std::string getType() const override; // Declaration only
};

class YearOfPlentyCard : public DevelopmentCard
{
public:
    ~YearOfPlentyCard() override = default;
    void use() override;
    std::string getType() const override; // Declaration only
};

// Derived class for Knight Card
class KnightCard : public Card
{
public:
    ~KnightCard() override = default;
    void use() override;
    std::string getType() const override; // Declaration only
};

// Derived class for Victory Point Card
class VictoryPointCard : public Card
{
public:
    ~VictoryPointCard() override = default;
    void use() override;
    std::string getType() const override; // Declaration only
};

#endif // CARD_H
