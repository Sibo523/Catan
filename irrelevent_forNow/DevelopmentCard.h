#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H

#include <string>

class DevelopmentCard {
public:
    DevelopmentCard(std::string type);
    void use();

private:
    std::string type; // e.g., "knight", "victory point", "road building", "monopoly", "year of plenty"
};

#endif // DEVELOPMENTCARD_H
